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

#include"print_stl.h"
#include"lexer.h"
#include"dive.h"
#include<sys/stat.h>

print_stl::print_stl(lexer* p, dive *a)
{
}

print_stl::~print_stl()
{
}

void print_stl::solid_stl(lexer* p, dive* a)
{
    mkdir("./DIVEMesh_Paraview",0777);
	sprintf(name,"./DIVEMesh_Paraview/REEF3D_Solid.stl");

	ofstream result;
	result.open(name, ios::binary);
    
	
	result<<"solid"<<" "<<"ascii"<<endl;
	
	
	for(n=0; n<p->tricount; ++n)
	{
	result<<" facet normal "<<p->trivec_x[n]<<" "<<p->trivec_y[n]<<" "<<p->trivec_z[n]<<endl;
	result<<"  outer loop"<<endl;
	result<<"   vertex "<<p->tri_x[n][0]<<" "<<p->tri_y[n][0]<<" "<<p->tri_z[n][0]<<endl;
	result<<"   vertex "<<p->tri_x[n][1]<<" "<<p->tri_y[n][1]<<" "<<p->tri_z[n][1]<<endl;
	result<<"   vertex "<<p->tri_x[n][2]<<" "<<p->tri_y[n][2]<<" "<<p->tri_z[n][2]<<endl;
	result<<"  endloop"<<endl;
	result<<" endfacet"<<endl;
	}
	
	result<<"endsolid"<<endl;
	

	result.close();	
}

void print_stl::topo_stl(lexer* p, dive* a)
{
    mkdir("./DIVEMesh_Paraview",0777);
	sprintf(name,"./DIVEMesh_Paraview/REEF3D_Topo.stl");

	ofstream result;
	result.open(name, ios::binary);
    
	
	result<<"topo"<<" "<<"ascii"<<endl;
	
	
	for(n=0; n<p->tricount; ++n)
	{
	result<<" facet normal "<<p->trivec_x[n]<<" "<<p->trivec_y[n]<<" "<<p->trivec_z[n]<<endl;
	result<<"  outer loop"<<endl;
	result<<"   vertex "<<p->tri_x[n][0]<<" "<<p->tri_y[n][0]<<" "<<p->tri_z[n][0]<<endl;
	result<<"   vertex "<<p->tri_x[n][1]<<" "<<p->tri_y[n][1]<<" "<<p->tri_z[n][1]<<endl;
	result<<"   vertex "<<p->tri_x[n][2]<<" "<<p->tri_y[n][2]<<" "<<p->tri_z[n][2]<<endl;
	result<<"  endloop"<<endl;
	result<<" endfacet"<<endl;
	}
	
	result<<"endsolid"<<endl;
	

	result.close();	
}


void print_stl::solid_vtp(lexer* p, dive* a)
{
    mkdir("./DIVEMesh_Paraview",0777);
	sprintf(name,"./DIVEMesh_Paraview/REEF3D_Solid.vtp");

	ofstream result;
	result.open(name, ios::binary);
	
	cout<<"print_solid"<<endl;

    n=0;

	offset[n]=0;
	++n;

    offset[n]=offset[n-1]+8*p->tricount*3*3 + 4;
    ++n;
    offset[n]=offset[n-1]+4*p->tricount*3 + 4;
    ++n;
    offset[n]=offset[n-1]+4*p->tricount*3 + 4;
    ++n;
	//---------------------------------------------

	result<<"<?xml version=\"1.0\"?>"<<endl;
	result<<"<VTKFile type=\"PolyData\" version=\"0.1\" byte_order=\"LittleEndian\">"<<endl;
	result<<"<PolyData>"<<endl;
	result<<"<Piece NumberOfPoints=\""<<p->tricount*3<<"\" NumberOfPolys=\""<<p->tricount<<"\">"<<endl;

    n=0;
    result<<"<Points>"<<endl;
    result<<"<DataArray type=\"Float64\"  NumberOfComponents=\"3\"  format=\"appended\" offset=\""<<offset[n]<<"\" />"<<endl;
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
	iin=8*p->tricount*3*3;
	result.write((char*)&iin, sizeof (int));
    for(n=0;n<p->tricount;++n)
	for(q=0;q<3;++q)
	{
	ddn=p->tri_x[n][q];
	result.write((char*)&ddn, sizeof (double));

	ddn=p->tri_y[n][q];
	result.write((char*)&ddn, sizeof (double));

	ddn=p->tri_z[n][q];
	result.write((char*)&ddn, sizeof (double));
	}

//  Connectivity POLYGON
	int count=0;
    iin=4*p->tricount*3;
    result.write((char*)&iin, sizeof (int));
    for(n=0;n<p->tricount;++n)
	for(q=0;q<3;++q)
	{
	iin=count;
	result.write((char*)&iin, sizeof (int));
	++count;
	}

//  Offset of Connectivity
    iin=4*p->tricount;
    result.write((char*)&iin, sizeof (int));
	iin=0;
	for(n=0;n<p->tricount;++n)
	{
	iin+= 3;//a->polygon_offset[n];
	result.write((char*)&iin, sizeof (int));
	}

//  Cell types
    iin=4*p->tricount;
    result.write((char*)&iin, sizeof (int));
	for(n=0;n<p->tricount;++n)
	{
	iin=7;
	result.write((char*)&iin, sizeof (int));
	}

	result<<endl<<"</AppendedData>"<<endl;
    result<<"</VTKFile>"<<endl;

	result.close();	
}

void print_stl::topo_vtp(lexer* p, dive* a)
{
    mkdir("./DIVEMesh_Paraview",0777);
	sprintf(name,"./DIVEMesh_Paraview/REEF3D_Topo.vtp");

	ofstream result;
	result.open(name, ios::binary);
	
	cout<<"print_topo"<<endl;

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

	result<<"<?xml version=\"1.0\"?>"<<endl;
	result<<"<VTKFile type=\"PolyData\" version=\"0.1\" byte_order=\"LittleEndian\">"<<endl;
	result<<"<PolyData>"<<endl;
	result<<"<Piece NumberOfPoints=\""<<p->tricount*3<<"\" NumberOfPolys=\""<<p->tricount<<"\">"<<endl;

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
	iin=4*p->tricount*3*3;
	result.write((char*)&iin, sizeof (int));
    for(n=0;n<p->tricount;++n)
	for(q=0;q<3;++q)
	{
	ffn=p->tri_x[n][q];
	result.write((char*)&ffn, sizeof (float));

	ffn=p->tri_y[n][q];
	result.write((char*)&ffn, sizeof (float));

	ffn=p->tri_z[n][q];
	result.write((char*)&ffn, sizeof (float));
	}

//  Connectivity POLYGON
	int count=0;
    iin=4*p->tricount*3;
    result.write((char*)&iin, sizeof (int));
    for(n=0;n<p->tricount;++n)
	for(q=0;q<3;++q)
	{
	iin=count;
	result.write((char*)&iin, sizeof (int));
	++count;
	}

//  Offset of Connectivity
    iin=4*p->tricount;
    result.write((char*)&iin, sizeof (int));
	iin=0;
	for(n=0;n<p->tricount;++n)
	{
	iin+= 3;//a->polygon_offset[n];
	result.write((char*)&iin, sizeof (int));
	}

//  Cell types
    iin=4*p->tricount;
    result.write((char*)&iin, sizeof (int));
	for(n=0;n<p->tricount;++n)
	{
	iin=7;
	result.write((char*)&iin, sizeof (int));
	}

	result<<endl<<"</AppendedData>"<<endl;
    result<<"</VTKFile>"<<endl;

	result.close();	
}







