/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2021 Hans Bihs

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

void decomp::print_partition(lexer* p, dive* a)
{
    q=0;
	NLOOP
	{
    SUBLOOP
	if(a->flag(i,j,k)>0 && a->solid(i,j,k)>0)
	++subcell[q];
	
	++q;
	}

	for(q=0;q<p->M10;++q)
	ddout<<q<<" new subcell_count: "<<subcell[q]<<endl;
    
}