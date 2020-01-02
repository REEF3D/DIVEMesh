/*--------------------------------------------------------------------
REEF3D
Copyright 2008-2020 Hans Bihs

This file is part of REEF3D.

REEF3D is free software; you can redistribute it and/or modify it
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
--------------------------------------------------------------------*/

#include"geodat.h"
#include"lexer.h"
#include"dive.h"
#include<iostream>
#include<fstream>
#include<sys/stat.h>
#include<sys/types.h>

void geodat::print(lexer* p, dive* a)
{
    char name[100];
    int iin,offset[100];
    float ffn;
    int count;
    
	
    sprintf(name,"REEF3D_geodat.vtu");



	ofstream result;
	result.open(name, ios::binary);

    n=0;

	offset[n]=0;
	++n;
	
	offset[n]=offset[n-1]+4*(p->G10)+4;
	++n;
	offset[n]=offset[n-1]+4*(p->G10)+4;
	++n;	
	offset[n]=offset[n-1]+4*(p->G10)+4;
	++n;	
    offset[n]=offset[n-1]+4*(p->G10)+4;
	++n;	
	
	// end scalars
    offset[n]=offset[n-1]+4*(p->G10)*3+4;
    ++n;
    offset[n]=offset[n-1]+4*(p->G10)*2+4;
    ++n;
	offset[n]=offset[n-1]+4*(p->G10)+4;
    ++n;
	offset[n]=offset[n-1]+4*(p->G10)+4;
    ++n;

	//---------------------------------------------
	n=0;
	result<<"<?xml version=\"1.0\"?>"<<endl;
	result<<"<VTKFile type=\"UnstructuredGrid\" version=\"0.1\" byte_order=\"LittleEndian\">"<<endl;
	result<<"<UnstructuredGrid>"<<endl;
	result<<"<Piece NumberOfPoints=\""<<p->G10<<"\" NumberOfCells=\""<<p->G10<<"\">"<<endl;
	
	
	result<<"<PointData >"<<endl;
    result<<"<DataArray type=\"Float32\" Name=\"radius\"  format=\"appended\" offset=\""<<offset[n]<<"\" />"<<endl;
    ++n;
	result<<"<DataArray type=\"Float32\" Name=\"X_Coord\"  format=\"appended\" offset=\""<<offset[n]<<"\" />"<<endl;
    ++n;
    result<<"<DataArray type=\"Float32\" Name=\"Y_Coord\"  format=\"appended\" offset=\""<<offset[n]<<"\" />"<<endl;
    ++n;
    result<<"<DataArray type=\"Float32\" Name=\"Z_Coord\"  format=\"appended\" offset=\""<<offset[n]<<"\" />"<<endl;
    ++n;
	result<<"</PointData>"<<endl;
	
	
	

    result<<"<Points>"<<endl;
    result<<"<DataArray type=\"Float32\"  NumberOfComponents=\"3\"  format=\"appended\" offset=\""<<offset[n]<<"\" />"<<endl;
    ++n;
    result<<"</Points>"<<endl;
	
	

    result<<"<Cells>"<<endl;
	result<<"<DataArray type=\"Int32\"  Name=\"connectivity\"  format=\"appended\" offset=\""<<offset[n]<<"\" />"<<endl;
    ++n;
	result<<"<DataArray type=\"Int32\"  Name=\"offsets\"  format=\"appended\" offset=\""<<offset[n]<<"\" />"<<endl;
	++n;
    result<<"<DataArray type=\"Int32\"  Name=\"types\"  format=\"appended\" offset=\""<<offset[n]<<"\" />"<<endl;
    ++n;
	result<<"</Cells>"<<endl;

    result<<"</Piece>"<<endl;
    result<<"</UnstructuredGrid>"<<endl;

//----------------------------------------------------------------------------
    result<<"<AppendedData encoding=\"raw\">"<<endl<<"_";
	

//  radius
    iin=4*(p->G10);
    result.write((char*)&iin, sizeof (int));
	for(n=0;n<p->G10;++n)
	{
	ffn=0.1*p->DXM;
	result.write((char*)&ffn, sizeof (float));
	}
	
//  X_coord
    iin=4*(p->G10);
    result.write((char*)&iin, sizeof (int));
	for(n=0;n<p->G10;++n)
	{
	ffn=float(p->G10_x[n]);
	result.write((char*)&ffn, sizeof (float));
	}
    
//  Y_Coord
    iin=4*(p->G10);
    result.write((char*)&iin, sizeof (int));
	for(n=0;n<p->G10;++n)
	{
	ffn=float(p->G10_y[n]);
	result.write((char*)&ffn, sizeof (float));
	}
    
//  Z_Coord
    iin=4*(p->G10);
    result.write((char*)&iin, sizeof (int));
	for(n=0;n<p->G10;++n)
	{
	ffn=float(p->G10_z[n]);
	result.write((char*)&ffn, sizeof (float));
	}


//  XYZ
	iin=4*(p->G10)*3;
	result.write((char*)&iin, sizeof (int));
    for(n=0;n<p->G10;++n)
	{
	ffn=float(p->G10_x[n]);
	result.write((char*)&ffn, sizeof (float));

	ffn=float(p->G10_y[n]);
	result.write((char*)&ffn, sizeof (float));

	ffn=float(p->G10_z[n]);
	result.write((char*)&ffn, sizeof (float));
	}
	
//  Connectivity
	count=0;
    iin=4*(p->G10)*2;
    result.write((char*)&iin, sizeof (int));
	for(n=0;n<p->G10;++n)
	{
	iin=int(0);
	result.write((char*)&iin, sizeof (int));

	iin=int(count);
	result.write((char*)&iin, sizeof (int));
	++count;
	}

//  Offset of Connectivity
	count=0;
    iin=4*(p->G10);
    result.write((char*)&iin, sizeof (int));
	for(n=0;n<p->G10;++n)
	{
	iin=(count+1)*2;
	result.write((char*)&iin, sizeof (int));
	++count;
	}


//  Cell types
    iin=4*(p->G10);
    result.write((char*)&iin, sizeof (int));
	for(n=0;n<p->G10;++n)
	{
	iin=1;
	result.write((char*)&iin, sizeof (int));
	}

	result<<endl<<"</AppendedData>"<<endl;
    result<<"</VTKFile>"<<endl;

	result.close();
}

