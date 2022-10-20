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

#include"lexer.h"

using namespace std;

lexer::lexer() 
{

    ini_default();
	
    read_control();
	read_geodat();
	read_data();
    
    if(S1==1)
	pre_read_stl();
    
    createspace();
    
    gridspacing();
    
	solid_preproc();
    topo_preproc();
    
    tri_space();
    
	
}

lexer::~lexer()
{

}










