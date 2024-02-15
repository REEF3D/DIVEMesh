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
#include"decomp.h"

void decomp::partition_correction(lexer* p, dive* a)
{
    cout<<" maindir: "<<maindir<<endl;
    
	if(maindir==1)
	partition_correct_x(p,a);
	
	if(maindir==2)
	partition_correct_y(p,a);
	
	if(maindir==3)
	partition_correct_z(p,a);
}
	