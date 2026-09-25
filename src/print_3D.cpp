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
Author: Hans Bihs
--------------------------------------------------------------------*/

#include"print_3D.h"
#include"lexer.h"
#include"dive.h"
#include<sys/stat.h>

print_3D::print_3D(lexer *p, dive *a)
{
}

void print_3D::solid_stl(lexer *p, dive *a)
{
    mkdir("./DIVEMesh_Paraview",0777);
    snprintf(name,sizeof(name),"./DIVEMesh_Paraview/REEF3D_Solid.stl");

    write_stl(p,a);
}

void print_3D::topo_stl(lexer *p, dive *a)
{
    mkdir("./DIVEMesh_Paraview",0777);
    snprintf(name,sizeof(name),"./DIVEMesh_Paraview/REEF3D_Topo.stl");

    write_stl(p,a);
}

void print_3D::write_stl(lexer *p, dive *a)
{
    ofstream result;
    result.open(name, ios::binary);

    result<<"topo ascii\n";

    for(n=0; n<p->tricount; ++n)
    {
        result<<" facet normal "<<p->trivec_x[n]<<" "<<p->trivec_y[n]<<" "<<p->trivec_z[n]<<"\n";
        result<<" outer loop\n";
        result<<"  vertex "<<p->tri_x[n][0]<<" "<<p->tri_y[n][0]<<" "<<p->tri_z[n][0]<<"\n";
        result<<"  vertex "<<p->tri_x[n][1]<<" "<<p->tri_y[n][1]<<" "<<p->tri_z[n][1]<<"\n";
        result<<"  vertex "<<p->tri_x[n][2]<<" "<<p->tri_y[n][2]<<" "<<p->tri_z[n][2]<<"\n";
        result<<" endloop\n";
        result<<" endfacet\n";
    }

    result<<"endsolid\n";

    result.close();
}

void print_3D::solid_vtp(lexer *p, dive *a)
{
    mkdir("./DIVEMesh_Paraview",0777);
    snprintf(name,sizeof(name),"./DIVEMesh_Paraview/REEF3D_Solid.vtp");

    cout<<"print_solid\n";

    write_vtp(p,a);
}

void print_3D::topo_vtp(lexer *p, dive *a)
{
    mkdir("./DIVEMesh_Paraview",0777);
    snprintf(name,sizeof(name),"./DIVEMesh_Paraview/REEF3D_Topo.vtp");

    cout<<"print_topo\n";

    ofstream result;
    result.open(name, ios::binary);

    n=0;

    offset[n]=0;
    ++n;

    offset[n]=offset[n-1]+4*p->tricount*3*3 + 4;
    ++n;
    offset[n]=offset[n-1]+4*p->tricount*3 + 4;
    ++n;
    offset[n]=offset[n-1]+4*p->tricount*3 + 4;
    ++n;
    //---------------------------------------------

    result<<"<?xml version=\"1.0\"?>\n";
    result<<"<VTKFile type=\"PolyData\" version=\"0.1\" byte_order=\"LittleEndian\">\n";
    result<<"<PolyData>\n";
    result<<"<Piece NumberOfPoints=\""<<p->tricount*3<<"\" NumberOfPolys=\""<<p->tricount<<"\">\n";

    n=0;
    result<<"<Points>\n";
    result<<"<DataArray type=\"Float32\" NumberOfComponents=\"3\" format=\"appended\" offset=\""<<offset[n]<<"\"/>\n";
    ++n;
    result<<"</Points>\n";

    result<<"<Polys>\n";
    result<<"<DataArray type=\"Int32\" Name=\"connectivity\" format=\"appended\" offset=\""<<offset[n]<<"\"/>\n";
    ++n;
    result<<"<DataArray type=\"Int32\" Name=\"offsets\" format=\"appended\" offset=\""<<offset[n]<<"\"/>\n";
    ++n;

    result<<"</Polys>\n";

    result<<"</Piece>\n";
    result<<"</PolyData>\n";
    result<<"<AppendedData encoding=\"raw\">\n"<<"_";

    //----------------------------------------------------------------------------

    //  XYZ
    iin=4*p->tricount*3*3;
    result.write((char*)&iin, sizeof(int));
    for(n=0;n<p->tricount;++n)
    for(q=0;q<3;++q)
    {
        ffn=p->tri_x[n][q];
        result.write((char*)&ffn, sizeof(float));

        ffn=p->tri_y[n][q];
        result.write((char*)&ffn, sizeof(float));

        ffn=p->tri_z[n][q];
        result.write((char*)&ffn, sizeof(float));
    }

    //  Connectivity POLYGON
    int count=0;
    iin=4*p->tricount*3;
    result.write((char*)&iin, sizeof(int));
    for(n=0;n<p->tricount;++n)
    for(q=0;q<3;++q)
    {
        iin=count;
        result.write((char*)&iin, sizeof(int));
        ++count;
    }

    //  Offset of Connectivity
    iin=4*p->tricount;
    result.write((char*)&iin, sizeof(int));
    iin=0;
    for(n=0;n<p->tricount;++n)
    {
        iin+= 3;
        result.write((char*)&iin, sizeof(int));
    }

    result<<endl<<"</AppendedData>\n";
    result<<"</VTKFile>\n";

    result.close();
}

void print_3D::write_vtp(lexer *p, dive *a)
{
    ofstream result;
    result.open(name, ios::binary);

    n=0;

    offset[n] = 0;
    ++n;

    offset[n] = offset[n-1] + sizeof(double)*p->tricount*3*3 + sizeof(int);
    ++n;
    offset[n] = offset[n-1] + sizeof(int)*p->tricount*3 + sizeof(int);
    ++n;
    offset[n] = offset[n-1] + sizeof(int)*p->tricount + sizeof(int);
    ++n;
    //---------------------------------------------

    result<<"<?xml version=\"1.0\"?>\n";
    result<<"<VTKFile type=\"PolyData\" version=\"0.1\" byte_order=\"LittleEndian\">\n";
    result<<"<PolyData>\n";
    result<<"<Piece NumberOfPoints=\""<<p->tricount*3<<"\" NumberOfPolys=\""<<p->tricount<<"\">\n";

    n=0;
    result<<"<Points>\n";
    result<<"<DataArray type=\"Float64\" NumberOfComponents=\"3\" format=\"appended\" offset=\""<<offset[n]<<"\"/>\n";
    ++n;
    result<<"</Points>\n";

    result<<"<Polys>\n";
    result<<"<DataArray type=\"Int32\" Name=\"connectivity\" format=\"appended\" offset=\""<<offset[n]<<"\"/>\n";
    ++n;
    result<<"<DataArray type=\"Int32\" Name=\"offsets\" format=\"appended\" offset=\""<<offset[n]<<"\"/>\n";
    ++n;
    result<<"</Polys>\n";

    result<<"</Piece>\n";
    result<<"</PolyData>\n";
    result<<"<AppendedData encoding=\"raw\">\n_";

    //----------------------------------------------------------------------------

    //  XYZ
    iin = sizeof(double)*p->tricount*3*3;
    result.write((char*)&iin, sizeof(int));
    for(n=0;n<p->tricount;++n)
    for(q=0;q<3;++q)
    {
        ddn = p->Xout(p->tri_x[n][q],p->tri_y[n][q]);
        result.write((char*)&ddn, sizeof(double));

        ddn = p->Yout(p->tri_x[n][q],p->tri_y[n][q]);
        result.write((char*)&ddn, sizeof(double));

        ddn = p->tri_z[n][q];
        result.write((char*)&ddn, sizeof(double));
    }

    //  Connectivity POLYGON
    int count = 0;
    iin = sizeof(int)*p->tricount*3;
    result.write((char*)&iin, sizeof(int));
    for(n=0; n<p->tricount; ++n)
    for(q=0; q<3; ++q)
    {
        iin = count;
        result.write((char*)&iin, sizeof(int));
        ++count;
    }

    //  Offset of Connectivity
    iin = sizeof(int)*p->tricount;
    result.write((char*)&iin, sizeof(int));
    iin = 0;
    for(n=0; n<p->tricount; ++n)
    {
        iin += 3;
        result.write((char*)&iin, sizeof(int));
    }

    result<<endl<<"</AppendedData>\n";
    result<<"</VTKFile>\n";

    result.close();
}
