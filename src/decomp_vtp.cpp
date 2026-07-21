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

#include "decomp.h"
#include <sys/stat.h>

void decomp::decomp_vtp(lexer* p, dive* a)
{
    double ddn;
    char name[100];
    int n,iin,offset[5];

    mkdir("./DIVEMesh_Paraview",0777);
    snprintf(name,sizeof(name),"./DIVEMesh_Paraview/DIVEMesh_Partition.vtp");

    ofstream result;
    result.open(name, ios::binary);

    cout<<"print_partition_vtp\n";

    n=0;

    offset[n]=0;
    ++n;

    offset[n]=offset[n-1]+8*tricount*3*3 + 4;
    ++n;
    offset[n]=offset[n-1]+4*tricount*3 + 4;
    ++n;
    offset[n]=offset[n-1]+4*tricount*3 + 4;
    ++n;
    //---------------------------------------------

    result<<"<?xml version=\"1.0\"?>\n";
    result<<"<VTKFile type=\"PolyData\" version=\"0.1\" byte_order=\"LittleEndian\">\n";
    result<<"<PolyData>\n";
    result<<"<Piece NumberOfPoints=\""<<tricount*3<<"\" NumberOfPolys=\""<<tricount<<"\">\n";

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
    result<<"<DataArray type=\"Int32\" Name=\"types\" format=\"appended\" offset=\""<<offset[n]<<"\"/>\n";

    result<<"</Polys>\n";

    result<<"</Piece>\n";
    result<<"</PolyData>\n";

    result<<"<AppendedData encoding=\"raw\">\n_";

    //----------------------------------------------------------------------------


    //  XYZ
    iin=8*tricount*3*3;
    result.write((char*)&iin, sizeof(int));
    for(n=0;n<tricount;++n)
    for(q=0;q<3;++q)
    {
        ddn=trix[n][q];
        result.write((char*)&ddn, sizeof(double));

        ddn=triy[n][q];
        result.write((char*)&ddn, sizeof(double));

        ddn=triz[n][q];
        result.write((char*)&ddn, sizeof(double));
    }

    //  Connectivity POLYGON
    int count=0;
    iin=4*tricount*3;
    result.write((char*)&iin, sizeof(int));
    for(n=0;n<tricount;++n)
    for(q=0;q<3;++q)
    {
        iin=count;
        result.write((char*)&iin, sizeof(int));
        ++count;
    }

    //  Offset of Connectivity
    iin=4*tricount;
    result.write((char*)&iin, sizeof(int));
    iin=0;
    for(n=0;n<tricount;++n)
    {
        iin+=3;
        result.write((char*)&iin, sizeof(int));
    }

    //  Cell types
    iin=4*tricount;
    result.write((char*)&iin, sizeof(int));
    for(n=0;n<tricount;++n)
    {
        iin=7;
        result.write((char*)&iin, sizeof(int));
    }

    result<<"\n</AppendedData>\n";
    result<<"</VTKFile>"<<endl;

    result.close();
}
