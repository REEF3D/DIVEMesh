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

#include"print_vts.h"
#include"lexer.h"
#include"dive.h"
#include"field.h"
#include<iostream>
#include<fstream>
#include<sys/stat.h>
#include<sys/types.h>
#include<iomanip>
#include<cstddef>
#include<vector>
#include<cstring>
#include<sstream>

print_vts::print_vts(lexer* p)
{
}

void print_vts::start(lexer* p, dive* a)
{
    // number of grid points written by TPLOOP
    const size_t pointnum = size_t(p->knox+1)*size_t(p->knoy+1)*size_t(p->knoz+1);

    size_t offset[10];
    size_t n = 0;
    offset[n] = 0;
    ++n;

    // topo
    offset[n]=offset[n-1]+sizeof(float)*pointnum+sizeof(int);
    ++n;

    // solid
    offset[n]=offset[n-1]+sizeof(float)*pointnum+sizeof(int);
    ++n;

    // Points
    offset[n]=offset[n-1]+sizeof(float)*pointnum*3+sizeof(int);
    ++n;
    //---------------------------------------------

    std::stringstream header;

    header<<"<?xml version=\"1.0\"?>\n";
    header<<"<VTKFile type=\"StructuredGrid\" version=\"0.1\" byte_order=\"LittleEndian\">\n";
    header<<"<StructuredGrid WholeExtent=\"0 "<<p->knox<<" 0 "<<p->knoy<<" 0 "<<p->knoz<<"\">\n";
    header<<"<Piece Extent=\"0 "<<p->knox<<" 0 "<<p->knoy<<" 0 "<<p->knoz<<"\">\n";

    n=0;
    header<<"<PointData>\n";
    header<<"<DataArray type=\"Float32\" Name=\"topo\" format=\"appended\" offset=\""<<offset[n]<<"\"/>\n";
    ++n;
    header<<"<DataArray type=\"Float32\" Name=\"solid\" format=\"appended\" offset=\""<<offset[n]<<"\"/>\n";
    ++n;
    header<<"</PointData>\n";

    header<<"<Points>\n";
    header<<"<DataArray type=\"Float32\" NumberOfComponents=\"3\" format=\"appended\" offset=\""<<offset[n]<<"\"/>\n";
    ++n;
    header<<"</Points>\n";
    header<<"</Piece>\n";
    header<<"</StructuredGrid>\n";
    header<<"<AppendedData encoding=\"raw\">\n_";

    //----------------------------------------------------------------------------
    // stream to file through a small buffer instead of assembling the whole file in memory

    mkdir("./DIVEMesh_Paraview",0777);
    char filename[100];
    snprintf(filename,sizeof(filename),"./DIVEMesh_Paraview/DIVEMesh_grid-preview.vts");
    FILE* file = fopen(filename, "wb");
    bool ok = (file!=nullptr);

    std::vector<char> buffer(1<<20);
    size_t m=0;

    auto flush = [&]()
    {
        if(ok && m>0)
        ok = (fwrite(buffer.data(), m, 1, file)==1);
        m=0;
    };
    auto put = [&](const void *val, size_t bytes)
    {
        if(m+bytes>buffer.size())
        flush();

        if(bytes>buffer.size())
        {
            if(ok)
            ok = (fwrite(val, bytes, 1, file)==1);
            return;
        }

        std::memcpy(&buffer[m],val,bytes);
        m+=bytes;
    };
    auto put_int = [&](int val) { put(&val,sizeof(int)); };
    auto put_float = [&](float val) { put(&val,sizeof(float)); };

    const std::string head = header.str();
    put(head.data(),head.size());

    //  topo
    put_int(int(sizeof(float)*pointnum));
    TPLOOP
    put_float(float(ipol(a,a->topo_dist)));

    //  solid
    put_int(int(sizeof(float)*pointnum));
    TPLOOP
    put_float(float(ipol(a,a->solid_dist)));

    //  XYZ
    put_int(int(sizeof(float)*pointnum*3));
    TPLOOP
    {
        put_float(float(p->XN[IP1]));
        put_float(float(p->YN[JP1]));
        put_float(float(p->ZN[KP1]));
    }

    const std::string footer = "\n</AppendedData>\n</VTKFile>\n";
    put(footer.data(),footer.size());
    flush();

    if(file!=nullptr)
    ok = (fclose(file)==0) && ok;

    if(!ok)
    cout<<"!!! could not write "<<filename<<" !!!"<<endl;
}

double print_vts::ipol(dive *a, field &b)
{
    int q=0;

    double v1,v2,v3,v4,v5,v6,v7,v8;
    v1=v2=v3=v4=v5=v6=v7=v8=0.0;

    if(a->flag(i,j,k)>0)
    {
        v1=b(i,j,k);
        ++q;
    }

    if(a->flag(i,j+1,k)>0)
    {
        v2=b(i,j+1,k);
        ++q;
    }

    if(a->flag(i+1,j,k)>0)
    {
        v3=b(i+1,j,k);
        ++q;
    }

    if(a->flag(i+1,j+1,k)>0)
    {
        v4=b(i+1,j+1,k);
        ++q;
    }

    if(a->flag(i,j,k+1)>0)
    {
        v5=b(i,j,k+1);
        ++q;
    }

    if(a->flag(i,j+1,k+1)>0)
    {
        v6=b(i,j+1,k+1);
        ++q;
    }

    if(a->flag(i+1,j,k+1)>0)
    {
        v7=b(i+1,j,k+1);
        ++q;
    }

    if(a->flag(i+1,j+1,k+1)>0)
    {
        v8=b(i+1,j+1,k+1);
        ++q;
    }

    double denom = q==0 ? 1.0 : 1.0/double(q);

    return denom*(v1+v2+v3+v4+v5+v6+v7+v8);
}