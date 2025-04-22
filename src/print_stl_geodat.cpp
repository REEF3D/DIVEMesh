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

#include"print_stl_geodat.h"
#include"lexer.h"
#include"dive.h"
#include<sys/stat.h>

print_stl_geodat::print_stl_geodat(lexer* p, dive *a)
{
}

print_stl_geodat::~print_stl_geodat()
{
}

void print_stl_geodat::print_geo(lexer* p, dive* a)
{
    mkdir("./DIVEMesh_Geo",0777);
	sprintf(name,"./DIVEMesh_Geo/REEF3D_stl_geo.dat");

	ofstream result;
	result.open(name, ios::binary);
    
    if(p->S91==1)
	XYLOOP
	result<<p->XP[IP]<<" "<<p->YP[JP]<<" "<<a->zstl_min(i,j)<<endl;
    
    if(p->S91==2)
	XYLOOP
	result<<p->XP[IP]<<" "<<p->YP[JP]<<" "<<a->zstl_max(i,j)<<endl;
	


	result.close();	
}




