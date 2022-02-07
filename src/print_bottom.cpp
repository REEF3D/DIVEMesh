/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2022 Hans Bihs

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

#include"print_binary.h"
#include"lexer.h"
#include"dive.h"
#include<sys/stat.h>

void print_binary::print_bottom(lexer* p,dive* a)
{
    char name[100];
    
    mkdir("./DIVEMesh_log",0777);
    
    sprintf(name,"./DIVEMesh_Log/bottom_file.dat",count);
    
    ofstream result;
	result.open(name);
    
    JLOOP
    {
        ILOOP
        result<<a->topobed(i,j)<<"\t";
        
        result<<endl;
    }
    
    result.close();
}