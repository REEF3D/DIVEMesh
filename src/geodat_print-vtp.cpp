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

#include "geodat.h"
#include "lexer.h"
#include "dive.h"
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>

void geodat::print(lexer* p, dive* a, int Np, double *Fx, double *Fy, double *Fz, int mode)
{
    char name[100];
    int iin,offset[100];
    float ffn;
    int count;

    mkdir("./DIVEMesh_Geo",0777);

    if(mode==1)
    {
        snprintf(name,sizeof(name),"./DIVEMesh_Geo/REEF3D_geodat-%i.vtp",printcount);
        ++printcount;
    }
    else if(mode==2)
    {
        snprintf(name,sizeof(name),"./DIVEMesh_Geo/REEF3D_geodat_patch.vtp");
    }

    ofstream result;
    result.open(name, ios::binary);

    n=0;

    offset[n]=0;
    ++n;

    offset[n]=offset[n-1]+sizeof(float)*Np+sizeof(int); // radius
    ++n;
    offset[n]=offset[n-1]+sizeof(float)*Np+sizeof(int); // X_Coord
    ++n;
    offset[n]=offset[n-1]+sizeof(float)*Np+sizeof(int); // Y_Coord
    ++n;
    offset[n]=offset[n-1]+sizeof(float)*Np+sizeof(int); // Z_Coord
    ++n;

    // end scalars
    offset[n]=offset[n-1]+sizeof(float)*Np*3+sizeof(int); // points
    ++n;
    offset[n]=offset[n-1]+sizeof(int)*Np*2+sizeof(int); // connectivity
    ++n;
    offset[n]=offset[n-1]+sizeof(int)*Np+sizeof(int); // offsets
    ++n;

    //---------------------------------------------
    n=0;
    result<<"<?xml version=\"1.0\"?>\n";
    result<<"<VTKFile type=\"PolyData\" version=\"0.1\" byte_order=\"LittleEndian\">\n";
    result<<"<PolyData>\n";
    result<<"<Piece NumberOfPoints=\""<<Np<<"\" NumberOfVerts=\""<<Np<<"\">\n";

    result<<"<PointData>\n";
    result<<"<DataArray type=\"Float32\" Name=\"radius\" format=\"appended\" offset=\""<<offset[n]<<"\"/>\n";
    ++n;
    result<<"<DataArray type=\"Float32\" Name=\"X_Coord\" format=\"appended\" offset=\""<<offset[n]<<"\"/>\n";
    ++n;
    result<<"<DataArray type=\"Float32\" Name=\"Y_Coord\" format=\"appended\" offset=\""<<offset[n]<<"\"/>\n";
    ++n;
    result<<"<DataArray type=\"Float32\" Name=\"Z_Coord\" format=\"appended\" offset=\""<<offset[n]<<"\"/>\n";
    ++n;
    result<<"</PointData>\n";

    result<<"<Points>\n";
    result<<"<DataArray type=\"Float32\" NumberOfComponents=\"3\" format=\"appended\" offset=\""<<offset[n]<<"\"/>\n";
    ++n;
    result<<"</Points>\n";

    result<<"<Verts>\n";
    result<<"<DataArray type=\"Int32\" Name=\"connectivity\" format=\"appended\" offset=\""<<offset[n]<<"\"/>\n";
    ++n;
    result<<"<DataArray type=\"Int32\" Name=\"offsets\" format=\"appended\" offset=\""<<offset[n]<<"\"/>\n";
    ++n;
    result<<"</Verts>\n";

    result<<"</Piece>\n";
    result<<"</PolyData>\n";

    result<<"<AppendedData encoding=\"raw\">\n_";
    //----------------------------------------------------------------------------

    //  radius
    iin=sizeof(float)*Np;
    result.write((char*)&iin,sizeof(int));
    for(n=0;n<Np;++n)
    {
        ffn=0.1*p->DXM;
        result.write((char*)&ffn,sizeof(float));
    }

    //  X_coord
    iin=sizeof(float)*Np;
    result.write((char*)&iin,sizeof(int));
    for(n=0;n<Np;++n)
    {
        ffn=float(p->Xout(Fx[n],Fy[n]));
        result.write((char*)&ffn,sizeof(float));
    }

    //  Y_Coord
    iin=sizeof(float)*Np;
    result.write((char*)&iin,sizeof(int));
    for(n=0;n<Np;++n)
    {
        ffn=float(p->Yout(Fx[n],Fy[n]));
        result.write((char*)&ffn,sizeof(float));
    }

    //  Z_Coord
    iin=sizeof(float)*Np;
    result.write((char*)&iin,sizeof(int));
    for(n=0;n<Np;++n)
    {
        ffn=float(Fz[n]);
        result.write((char*)&ffn,sizeof(float));
    }

    //  XYZ
    iin=sizeof(float)*Np*3;
    result.write((char*)&iin,sizeof(int));
    for(n=0;n<Np;++n)
    {
        ffn=float(p->Xout(Fx[n],Fy[n]));
        result.write((char*)&ffn,sizeof(float));

        ffn=float(p->Yout(Fx[n],Fy[n]));
        result.write((char*)&ffn,sizeof(float));

        ffn=float(Fz[n]);
        result.write((char*)&ffn,sizeof(float));
    }

    //  Connectivity
    count=0;
    iin=sizeof(int)*Np*2;
    result.write((char*)&iin,sizeof(int));
    for(n=0;n<Np;++n)
    {
        iin=int(0);
        result.write((char*)&iin,sizeof(int));

        iin=int(count);
        result.write((char*)&iin,sizeof(int));
        ++count;
    }

    //  Offset of Connectivity
    count=0;
    iin=sizeof(int)*Np;
    result.write((char*)&iin,sizeof(int));
    for(n=0;n<Np;++n)
    {
        iin=(count+1)*2;
        result.write((char*)&iin,sizeof(int));
        ++count;
    }

    result<<"\n</AppendedData>\n";
    result<<"</VTKFile>"<<endl;

    result.close();
}
