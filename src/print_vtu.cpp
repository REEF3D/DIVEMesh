/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2025 Hans Bihs

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

#include"print_vtu.h"
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

print_vtu::print_vtu(lexer* p)
{
}

void print_vtu::start(lexer* p, dive* a)
{
    field nodeval(p);

    // NODELOOP
    int count=0;
    int pointnum=0;
    int tpcellnum=0;

    TPLOOP
    {
        ++count;
        ++pointnum;
        nodeval(i,j,k)=count;
    }

    LOOP
    {
        ++tpcellnum;
    }

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

    // Cells
    offset[n]=offset[n-1] + sizeof(int)*tpcellnum*8+sizeof(int);
    ++n;
    offset[n]=offset[n-1] + sizeof(int)*tpcellnum+sizeof(int);
    ++n;
    offset[n]=offset[n-1] + sizeof(int)*tpcellnum+sizeof(int);
    ++n;
    //---------------------------------------------

    std::stringstream header;

    header<<"<?xml version=\"1.0\"?>\n";
    header<<"<VTKFile type=\"UnstructuredGrid\" version=\"0.1\" byte_order=\"LittleEndian\">\n";
    header<<"<UnstructuredGrid>\n";
    header<<"<Piece NumberOfPoints=\""<<pointnum<<"\" NumberOfCells=\""<<tpcellnum<<"\">\n";

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

    header<<"<Cells>\n";
    header<<"<DataArray type=\"Int32\" Name=\"connectivity\" format=\"appended\" offset=\""<<offset[n]<<"\"/>\n";
    ++n;
    header<<"<DataArray type=\"Int32\" Name=\"offsets\" format=\"appended\" offset=\""<<offset[n]<<"\"/>\n";
    ++n;
    header<<"<DataArray type=\"Int32\" Name=\"types\" format=\"appended\" offset=\""<<offset[n]<<"\"/>\n";
    ++n;
    header<<"</Cells>\n";

    header<<"</Piece>\n";
    header<<"</UnstructuredGrid>\n";
    header<<"<AppendedData encoding=\"raw\">\n_";

    //----------------------------------------------------------------------------
    std::vector<char> buffer;
    size_t file_offset = header.str().length();
    const size_t total_size = file_offset + offset[n] + 28;
    buffer.resize(total_size);
    std::memcpy(&buffer[0], header.str().data(), file_offset);

    int iin;
    float ffn;

    //  topo
    iin=sizeof(float)*pointnum;
    std::memcpy(&buffer[file_offset],&iin,sizeof(int));
    file_offset+=sizeof(int);
    TPLOOP
    {
        ffn=float(ipol(a,a->topo_dist));
        std::memcpy(&buffer[file_offset],&ffn,sizeof(float));
        file_offset+=sizeof(float);
    }

    //  solid
    iin=sizeof(float)*pointnum;
    std::memcpy(&buffer[file_offset],&iin,sizeof(int));
    file_offset+=sizeof(int);
    TPLOOP
    {
        ffn=float(ipol(a,a->solid_dist));
        std::memcpy(&buffer[file_offset],&ffn,sizeof(float));
        file_offset+=sizeof(float);
    }

    //  XYZ
    iin=sizeof(float)*pointnum*3;
    std::memcpy(&buffer[file_offset],&iin,sizeof(int));
    file_offset+=sizeof(int);
    TPLOOP
    {
        ffn=float(p->XN[IP1]);
        std::memcpy(&buffer[file_offset],&ffn,sizeof(float));
        file_offset+=sizeof(float);

        ffn=float(p->YN[JP1]);
        std::memcpy(&buffer[file_offset],&ffn,sizeof(float));
        file_offset+=sizeof(float);

        ffn=float(p->ZN[KP1]);
        std::memcpy(&buffer[file_offset],&ffn,sizeof(float));
        file_offset+=sizeof(float);
    }

    //  Connectivity
    iin=sizeof(int)*tpcellnum*8;
    std::memcpy(&buffer[file_offset],&iin,sizeof(int));
    file_offset+=sizeof(int);
    LOOP
    {
        iin=int(nodeval(i-1,j-1,k-1)-1);
        std::memcpy(&buffer[file_offset],&iin,sizeof(int));
        file_offset+=sizeof(int);

        iin=int(nodeval(i,j-1,k-1))-1;
        std::memcpy(&buffer[file_offset],&iin,sizeof(int));
        file_offset+=sizeof(int);

        iin= int(nodeval(i,j,k-1))-1;
        std::memcpy(&buffer[file_offset],&iin,sizeof(int));
        file_offset+=sizeof(int);

        iin=int(nodeval(i-1,j,k-1))-1;
        std::memcpy(&buffer[file_offset],&iin,sizeof(int));
        file_offset+=sizeof(int);

        iin=int(nodeval(i-1,j-1,k))-1;
        std::memcpy(&buffer[file_offset],&iin,sizeof(int));
        file_offset+=sizeof(int);

        iin=int(nodeval(i,j-1,k))-1;
        std::memcpy(&buffer[file_offset],&iin,sizeof(int));
        file_offset+=sizeof(int);

        iin=int(nodeval(i,j,k))-1;
        std::memcpy(&buffer[file_offset],&iin,sizeof(int));
        file_offset+=sizeof(int);

        iin=int(nodeval(i-1,j,k))-1;
        std::memcpy(&buffer[file_offset],&iin,sizeof(int));
        file_offset+=sizeof(int);
    }

    //  Offset of Connectivity
    iin=sizeof(int)*tpcellnum;
    std::memcpy(&buffer[file_offset],&iin,sizeof(int));
    file_offset+=sizeof(int);
    for(n=0;n<tpcellnum;++n)
    {
        iin=(n+1)*8;
        std::memcpy(&buffer[file_offset],&iin,sizeof(int));
        file_offset+=sizeof(int);
    }

    //  Cell types
    iin=sizeof(int)*tpcellnum;
    std::memcpy(&buffer[file_offset],&iin,sizeof(int));
    file_offset+=sizeof(int);
    for(n=0;n<tpcellnum;++n)
    {
        iin=12;
        std::memcpy(&buffer[file_offset],&iin,sizeof(int));
        file_offset+=sizeof(int);
    }

    std::string footer = "\n</AppendedData>\n</VTKFile>\n";
    std::memcpy(&buffer[file_offset],footer.data(),footer.size());

    mkdir("./DIVEMesh_Paraview",0777);
    char filename[100];
    snprintf(filename,sizeof(filename),"./DIVEMesh_Paraview/DIVEMesh_grid-preview.vtu");
    FILE* file = fopen(filename, "wb");
    if(file)
    {
        fwrite(buffer.data(), buffer.size(), 1, file);
        fclose(file);
    }
}

double print_vtu::ipol(dive *a, field &b)
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