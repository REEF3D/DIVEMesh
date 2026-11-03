/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2026 Hans Bihs

This file is part of DIVEMesh.

DIVEMesh is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, see <http://www.gnu.org/licenses/>.
--------------------------------------------------------------------
Architect: Hans Bihs
--------------------------------------------------------------------*/

#include"catchment.h"
#include"lexer.h"
#include<algorithm>
#include<cctype>
#include<cmath>
#include<fstream>
#include<iomanip>
#include<iostream>
#include<sstream>
#include<sys/stat.h>

catchment::catchment(lexer *p) : nx(0), ny(0), dx(1.0), outlet(-1), ni(0), nj(0), nb(1), D(1.0)
{
}

// ESRI ASCII grid: ncols, nrows, xllcorner|xllcenter, yllcorner|yllcenter, cellsize, [NODATA_value], rows from north to south
bool catchment::read_raster(const string &file, raster &r)
{
    ifstream f(file);

    if(!f)
    return false;

    double xll=0.0, yll=0.0;
    bool xcen=false, ycen=false;
    string key;
    int got=0;

    while(got<6 && f>>key)
    {
        string k=key;
        for(char &c : k)
        c=char(tolower(c));

        if(k=="ncols")
        {f>>r.nx; ++got;}
        else if(k=="nrows")
        {f>>r.ny; ++got;}
        else if(k=="xllcorner" || k=="xllcenter")
        {f>>xll; xcen=(k=="xllcenter"); ++got;}
        else if(k=="yllcorner" || k=="yllcenter")
        {f>>yll; ycen=(k=="yllcenter"); ++got;}
        else if(k=="cellsize")
        {f>>r.dx; ++got;}
        else if(k=="nodata_value")
        {f>>r.nodata; ++got;}
        else
        {
            // first value of the data: no NODATA_value line
            r.v.push_back(stod(key));
            break;
        }
    }

    if(r.nx<=0 || r.ny<=0 || r.dx<=0.0)
    return false;

    r.x0 = xcen ? xll-0.5*r.dx : xll;
    r.y0 = ycen ? yll-0.5*r.dx : yll;

    vector<double> rows;
    rows.reserve(size_t(r.nx)*r.ny);
    rows.insert(rows.end(),r.v.begin(),r.v.end());

    double val;
    while(rows.size()<size_t(r.nx)*r.ny && f>>val)
    rows.push_back(val);

    if(rows.size()<size_t(r.nx)*r.ny)
    return false;

    r.v.assign(size_t(r.nx)*r.ny,r.nodata);
    for(int row=0; row<r.ny; ++row)
    for(int i=0; i<r.nx; ++i)
    r.v[i + size_t(r.nx)*(r.ny-1-row)] = rows[i + size_t(r.nx)*row];

    return true;
}

void catchment::start(lexer *p)
{
    cout<<endl<<"catchment preprocessing (W 10)"<<endl;

    if(!read_raster("catchment_dem.asc",dem))
    {
        cout<<"!!! W 10: could not read catchment_dem.asc !!!"<<endl;
        exit(1);
    }

    nx=dem.nx;
    ny=dem.ny;
    dx=dem.dx;

    auto aux = [&](int flag, const char *file, raster &r)
    {
        if(flag<=0)
        return;

        if(!read_raster(file,r) || r.nx!=nx || r.ny!=ny || fabs(r.x0-dem.x0)>1.0e-6*dx || fabs(r.y0-dem.y0)>1.0e-6*dx || fabs(r.dx-dx)>1.0e-9*dx)
        {
            cout<<"!!! W 10: "<<file<<" is missing or does not have the raster geometry of catchment_dem.asc !!!"<<endl;
            exit(1);
        }
    };
    aux(p->W30,"catchment_glacier.asc",glac);
    aux(p->W31,"catchment_lake.asc",lake);
    aux(p->W32,"catchment_zone.asc",zone);

    long nval=0;
    for(int q=0; q<nx*ny; ++q)
    if(dem.valid(q))
    ++nval;

    cout<<"DEM "<<nx<<" x "<<ny<<" pixels of "<<dx<<" m, "<<nval<<" with data"<<endl;

    flood();
    accumulate();
    delineate(p);
    cells(p);
    write(p);
    write_vtk(p);
}

void catchment::write(lexer *p)
{
    ofstream f("hydro_grid.dat");

    f<<setprecision(12);
    f<<"REEF3D_HYDRO_GRID 2"<<endl;
    f<<"origin "<<dem.x0<<" "<<dem.y0<<endl;
    f<<"cellsize "<<D<<endl;
    f<<"raster "<<ni<<" "<<nj<<endl;
    f<<"bands "<<nb<<endl;
    f<<"cells "<<hc.size()<<endl;
    f<<"// id I J x y area[m2] zmean[m] down length[m] slope[-] upstream_area[m2] subcatchment zone lake_fraction";
    f<<"  then per band: elevation[m] area_fraction glacier_fraction"<<endl;

    for(size_t n=0; n<hc.size(); ++n)
    {
        const hcell &c=hc[n];
        f<<n<<" "<<c.I<<" "<<c.J<<" "<<dem.x0+(c.I+0.5)*D<<" "<<dem.y0+(c.J+0.5)*D<<" "<<c.area<<" "<<c.zmean<<" "<<c.down<<" "
         <<c.len<<" "<<c.slope<<" "<<c.aup<<" "<<c.sub<<" "<<c.zone<<" "<<c.lake;
        for(int b=0; b<nb; ++b)
        f<<" "<<c.bz[b]<<" "<<c.bf[b]<<" "<<c.bg[b];
        f<<endl;
    }

    int ng=0;
    for(int c : gcell)
    if(c>=0)
    ++ng;

    f<<"gauges "<<ng<<endl;
    f<<"// id x y cell upstream_area_dem[m2] upstream_area_cells[m2]"<<endl;
    for(size_t g=0; g<gcell.size(); ++g)
    {
        if(gcell[g]<0)
        continue;

        const int q=gpix[g];
        const int gid = (g==0) ? 0 : p->W21_id[g-1];
        f<<gid<<" "<<xc(q)<<" "<<yc(q)<<" "<<gcell[g]<<" "<<acc[q]<<" "<<hc[gcell[g]].aup_cells<<endl;
    }

    // version 2: the fine flow path of every cell, pixel centres from its outlet pixel to the outlet pixel of the
    // downstream cell (or the last pixel in the catchment); REEF3D finds where it enters an SFLOW grid (R 100 2)
    f<<"paths "<<hc.size()<<endl;
    f<<"// id points x1 y1 x2 y2 ..."<<endl;
    for(size_t n=0; n<hc.size(); ++n)
    {
        vector<int> pp(1,hc[n].out);
        int q=hc[n].out;
        while(true)
        {
            const int m=dn[q];
            if(m<0 || !inside[m])
            break;
            pp.push_back(m);
            if(cellout[m]>=0)
            break;
            q=m;
        }

        f<<n<<" "<<pp.size();
        for(int r : pp)
        f<<" "<<xc(r)<<" "<<yc(r);
        f<<endl;
    }

    cout<<"hydro_grid.dat: "<<hc.size()<<" cells of "<<D<<" m, "<<nb<<" elevation bands, "<<ng<<" gauges"<<endl;
}

void catchment::write_vtk(lexer *p)
{
    mkdir("./DIVEMesh_Hydro",0777);

    // hydrology cells as a raster (cells outside the catchment: -1)
    {
        vector<int> map(size_t(ni)*nj,-1);
        for(size_t n=0; n<hc.size(); ++n)
        map[hc[n].I + size_t(ni)*hc[n].J]=int(n);

        ofstream f("./DIVEMesh_Hydro/hydro_cells.vtk");
        f<<"# vtk DataFile Version 3.0"<<endl<<"REEF3D::HYDRO cells"<<endl<<"ASCII"<<endl<<"DATASET STRUCTURED_POINTS"<<endl;
        f<<"DIMENSIONS "<<ni+1<<" "<<nj+1<<" 1"<<endl;
        f<<setprecision(12)<<"ORIGIN "<<dem.x0<<" "<<dem.y0<<" 0"<<endl<<"SPACING "<<D<<" "<<D<<" 1"<<endl;
        f<<"CELL_DATA "<<size_t(ni)*nj<<endl;

        auto field = [&](const char *name, auto get)
        {
            f<<"SCALARS "<<name<<" double 1"<<endl<<"LOOKUP_TABLE default"<<endl;
            for(size_t m=0; m<map.size(); ++m)
            f<<(map[m]<0 ? -1.0 : get(hc[map[m]],map[m]))<<"\n";
        };
        field("cell",[](const hcell &c, int n){return double(n);});
        field("subcatchment",[](const hcell &c, int n){return double(c.sub);});
        field("zone",[](const hcell &c, int n){return double(c.zone);});
        field("area_km2",[](const hcell &c, int n){return c.area*1.0e-6;});
        field("elevation",[](const hcell &c, int n){return c.zmean;});
        field("upstream_area_km2",[](const hcell &c, int n){return c.aup*1.0e-6;});
        field("channel_slope",[](const hcell &c, int n){return c.slope;});
        field("glacier_fraction",[&](const hcell &c, int n){double g=0.0; for(int b=0;b<nb;++b) g+=c.bf[b]*c.bg[b]; return g;});
        field("lake_fraction",[](const hcell &c, int n){return c.lake;});
    }

    // network: outlet pixel of every cell to the outlet pixel of its downstream cell
    {
        ofstream f("./DIVEMesh_Hydro/hydro_network.vtk");
        f<<"# vtk DataFile Version 3.0"<<endl<<"REEF3D::HYDRO network"<<endl<<"ASCII"<<endl<<"DATASET POLYDATA"<<endl;
        f<<setprecision(12)<<"POINTS "<<hc.size()<<" double"<<endl;
        for(const hcell &c : hc)
        f<<xc(c.out)<<" "<<yc(c.out)<<" "<<zf[c.out]<<endl;

        int nl=0;
        for(const hcell &c : hc)
        if(c.down>=0)
        ++nl;

        f<<"LINES "<<nl<<" "<<3*nl<<endl;
        for(size_t n=0; n<hc.size(); ++n)
        if(hc[n].down>=0)
        f<<"2 "<<n<<" "<<hc[n].down<<endl;

        f<<"POINT_DATA "<<hc.size()<<endl<<"SCALARS upstream_area_km2 double 1"<<endl<<"LOOKUP_TABLE default"<<endl;
        for(const hcell &c : hc)
        f<<c.aup*1.0e-6<<endl;
    }

    // fine raster (W 40 1)
    if(p->W40==1)
    {
        ofstream f("./DIVEMesh_Hydro/catchment_fine.vtk");
        f<<"# vtk DataFile Version 3.0"<<endl<<"REEF3D::HYDRO catchment"<<endl<<"ASCII"<<endl<<"DATASET STRUCTURED_POINTS"<<endl;
        f<<"DIMENSIONS "<<nx+1<<" "<<ny+1<<" 1"<<endl;
        f<<setprecision(12)<<"ORIGIN "<<dem.x0<<" "<<dem.y0<<" 0"<<endl<<"SPACING "<<dx<<" "<<dx<<" 1"<<endl;
        f<<"CELL_DATA "<<size_t(nx)*ny<<endl;
        f<<setprecision(8);

        f<<"SCALARS elevation double 1"<<endl<<"LOOKUP_TABLE default"<<endl;
        for(int q=0; q<nx*ny; ++q)
        f<<(dem.valid(q) ? dem.v[q] : -9999.0)<<"\n";
        f<<"SCALARS fill_depth double 1"<<endl<<"LOOKUP_TABLE default"<<endl;
        for(int q=0; q<nx*ny; ++q)
        f<<(dem.valid(q) ? zf[q]-dem.v[q] : 0.0)<<"\n";
        f<<"SCALARS log10_upstream_area double 1"<<endl<<"LOOKUP_TABLE default"<<endl;
        for(int q=0; q<nx*ny; ++q)
        f<<(dem.valid(q) ? log10(acc[q]) : 0.0)<<"\n";
        f<<"SCALARS subcatchment double 1"<<endl<<"LOOKUP_TABLE default"<<endl;
        for(int q=0; q<nx*ny; ++q)
        f<<label[q]<<"\n";
    }
}
