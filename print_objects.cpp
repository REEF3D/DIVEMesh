/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2020 Hans Bihs

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
--------------------------------------------------------------------*/

#include"print_objects.h"
#include"lexer.h"
#include"dive.h"


print_objects::print_objects(lexer* p, dive *a)
{
}

print_objects::~print_objects()
{
}

void print_objects::start(lexer* p, dive* a)
{
	sprintf(name,"REEF3D_Geometry-Object.vtp");

	ofstream result;
	result.open(name, ios::binary);

    n=0;

	offset[n]=0;
	++n;

    offset[n]=offset[n-1]+4*(a->vertice_num)*3 + 4;
    ++n;
    offset[n]=offset[n-1]+4*a->polygon_sum + 4;
    ++n;
    offset[n]=offset[n-1]+4*a->polygon_num + 4;
    ++n;
	//---------------------------------------------

	result<<"<?xml version=\"1.0\"?>"<<endl;
	result<<"<VTKFile type=\"PolyData\" version=\"0.1\" byte_order=\"LittleEndian\">"<<endl;
	result<<"<PolyData>"<<endl;
	result<<"<Piece NumberOfPoints=\""<<a->vertice_num<<"\" NumberOfPolys=\""<<a->polygon_num<<"\">"<<endl;

    n=0;
    result<<"<Points>"<<endl;
    result<<"<DataArray type=\"Float32\"  NumberOfComponents=\"3\"  format=\"appended\" offset=\""<<offset[n]<<"\" />"<<endl;
    ++n;
    result<<"</Points>"<<endl;

    result<<"<Polys>"<<endl;
    result<<"<DataArray type=\"Int32\"  Name=\"connectivity\"  format=\"appended\" offset=\""<<offset[n]<<"\" />"<<endl;
    ++n;
	result<<"<DataArray type=\"Int32\"  Name=\"offsets\"  format=\"appended\" offset=\""<<offset[n]<<"\" />"<<endl;
	++n;
    result<<"<DataArray type=\"Int32\"  Name=\"types\"  format=\"appended\" offset=\""<<offset[n]<<"\" />"<<endl;

	result<<"</Polys>"<<endl;

    result<<"</Piece>"<<endl;
    result<<"</PolyData>"<<endl;

//----------------------------------------------------------------------------
    result<<"<AppendedData encoding=\"raw\">"<<endl<<"_";


//  XYZ
	iin=4*a->vertice_num*3;
	result.write((char*)&iin, sizeof (int));
    for(n=0;n<a->vertice_num;++n)
	{
	ffn=a->vertice[n][0];
	result.write((char*)&ffn, sizeof (float));

	ffn=a->vertice[n][1];
	result.write((char*)&ffn, sizeof (float));

	ffn=a->vertice[n][2];
	result.write((char*)&ffn, sizeof (float));
	}

//  Connectivity POLYGON
    iin=4*a->polygon_sum;
    result.write((char*)&iin, sizeof (int));
    for(n=0;n<a->polygon_num;++n)
	for(q=0;q<a->numvert[n];++q)
	{
	iin=a->polygon[n][q];
	result.write((char*)&iin, sizeof (int));
	}

//  Offset of Connectivity
    iin=4*a->polygon_num;
    result.write((char*)&iin, sizeof (int));
	iin=0;
	for(n=0;n<a->polygon_num;++n)
	{
	iin+=+ a->numvert[n];//a->polygon_offset[n];
	result.write((char*)&iin, sizeof (int));
	}

//  Cell types
    iin=4*a->polygon_num;
    result.write((char*)&iin, sizeof (int));
	for(n=0;n<a->polygon_num;++n)
	{
	iin=7;
	result.write((char*)&iin, sizeof (int));
	}

	result<<endl<<"</AppendedData>"<<endl;
    result<<"</VTKFile>"<<endl;

	result.close();	
}







