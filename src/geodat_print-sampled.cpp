/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2024 Hans Bihs

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

#include"geodat.h"
#include"lexer.h"
#include"dive.h"
#include<iostream>
#include<fstream>
#include<sys/stat.h>
#include<sys/types.h>

void geodat::print_sampled(lexer* p, dive* a)
{
    char name[100];
    int iin,offset[100];
    float ffn;
    int count;
    
	mkdir("./DIVEMesh_Geo",0777);
    
    sprintf(name,"./DIVEMesh_Geo/geo_sampled.dat");
    
    ofstream result;
	result.open(name);
    
    for(n=0;n<p->Np;++n)
    {
    result<<p->G10_x[n]<<" "<<p->G10_y[n]<<" "<<p->G10_z[n]<<endl;
    }
    
    
    
}