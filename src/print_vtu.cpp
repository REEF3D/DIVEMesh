/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2023 Hans Bihs

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
#include <iomanip>

print_vtu::print_vtu(lexer* p) 
{

}

print_vtu::~print_vtu()
{
}

void print_vtu::start(lexer* p,dive* a)
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

    mkdir("./DIVEMesh_Paraview",0777);
    sprintf(name,"./DIVEMesh_Paraview/DIVEMesh_grid-preview.vtu");
    
	// Open File
	ofstream result;
	result.open(name, ios::binary);

    n=0;

	offset[n]=0;
	++n;
    
    // topo
	offset[n]=offset[n-1]+4*(pointnum)+4;
	++n;
    
    // solid
	offset[n]=offset[n-1]+4*(pointnum)+4;
	++n;

	// Points
    offset[n]=offset[n-1]+4*(pointnum)*3+4;
    ++n;
	
	// Cells
    offset[n]=offset[n-1] + 4*tpcellnum*8 + 4;
    ++n;
    offset[n]=offset[n-1] + 4*(tpcellnum)+4;
    ++n;
	offset[n]=offset[n-1] + 4*(tpcellnum)+4;
    ++n;
	//---------------------------------------------

	result<<"<?xml version=\"1.0\"?>"<<endl;
	result<<"<VTKFile type=\"UnstructuredGrid\" version=\"0.1\" byte_order=\"LittleEndian\">"<<endl;
	result<<"<UnstructuredGrid>"<<endl;
	result<<"<Piece NumberOfPoints=\""<<pointnum<<"\" NumberOfCells=\""<<tpcellnum<<"\">"<<endl;

    n=0;
    result<<"<PointData >"<<endl;

    result<<"<DataArray type=\"Float32\" Name=\"topo\"  format=\"appended\" offset=\""<<offset[n]<<"\" />"<<endl;
    ++n;

	result<<"<DataArray type=\"Float32\" Name=\"solid\"  format=\"appended\" offset=\""<<offset[n]<<"\" />"<<endl;
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
	
//  topo
    iin=4*(pointnum);
    result.write((char*)&iin, sizeof (int));
	TPLOOP
	{
	ffn=float(ipol(a,a->topo_dist));
	result.write((char*)&ffn, sizeof (float));
	}
	
//  solid
    iin=4*(pointnum);
    result.write((char*)&iin, sizeof (int));
	TPLOOP
	{
	ffn=float(ipol(a,a->solid_dist));
	result.write((char*)&ffn, sizeof (float));
	}
	
//  XYZ
	iin=4*(pointnum)*3;
	result.write((char*)&iin, sizeof (int));
    TPLOOP
	{
    ffn=float(p->XN[IP1]);
	result.write((char*)&ffn, sizeof (float));

	ffn=float(p->YN[JP1]);
	result.write((char*)&ffn, sizeof (float));

	ffn=float(p->ZN[KP1]);
	result.write((char*)&ffn, sizeof (float));
	}


//  Connectivity
    iin=4*(tpcellnum)*8;
    result.write((char*)&iin, sizeof (int));
    LOOP
	{
	iin=int(nodeval(i-1,j-1,k-1)-1);
	result.write((char*)&iin, sizeof (int));

	iin=int(nodeval(i,j-1,k-1))-1;
	result.write((char*)&iin, sizeof (int));

    iin= int(nodeval(i,j,k-1))-1;
	result.write((char*)&iin, sizeof (int));

	iin=int(nodeval(i-1,j,k-1))-1;
	result.write((char*)&iin, sizeof (int));

	iin=int(nodeval(i-1,j-1,k))-1;
	result.write((char*)&iin, sizeof (int));

	iin=int(nodeval(i,j-1,k))-1;
	result.write((char*)&iin, sizeof (int));

	iin=int(nodeval(i,j,k))-1;
	result.write((char*)&iin, sizeof (int));

	iin=int(nodeval(i-1,j,k))-1;
	result.write((char*)&iin, sizeof (int));
	}


//  Offset of Connectivity
    iin=4*(tpcellnum);
    result.write((char*)&iin, sizeof (int));
	for(n=0;n<tpcellnum;++n)
	{
	iin=(n+1)*8;
	result.write((char*)&iin, sizeof (int));
	}


//  Cell types
    iin=4*(tpcellnum);
    result.write((char*)&iin, sizeof (int));
	for(n=0;n<tpcellnum;++n)
	{
	iin=12;
	result.write((char*)&iin, sizeof (int));
	}

	result<<endl<<"</AppendedData>"<<endl;
    result<<"</VTKFile>"<<endl;

	result.close();
	
}

double print_vtu::ipol(dive *a, field &b)
{
    int q=0;
    
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
    
    double denom = 1.0/double(q);
    
    if(q==0)
    denom=1.0;

    value=denom*(v1+v2+v3+v4+v5+v6+v7+v8);

    return value;
}