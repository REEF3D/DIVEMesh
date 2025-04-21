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

#include"decomp.h"

void decomp::partition_manual(lexer* p,dive* a)
{	
    a->mx=p->M30_x;
    a->my=p->M30_y;
    a->mz=p->M30_z;
    
    a->xorig[0]=p->xmin;
    a->yorig[0]=p->ymin;
    a->zorig[0]=p->zmin;
    a->xnode[0]=0;
    a->ynode[0]=0;
    a->znode[0]=0;

    a->xorig[a->mx]=p->xmax;
    a->yorig[a->my]=p->ymax;
    a->zorig[a->mz]=p->zmax;
    a->xnode[a->mx]=p->knox;
    a->ynode[a->my]=p->knoy;
    a->znode[a->mz]=p->knoz;
    
    // partition
    for(n=1;n<a->mx;n++)
    {
    a->xnode[n]=p->M31[n];
    a->xorig[n]=p->XN[a->xnode[n]+marge];
	}

    for(n=1;n<a->my;n++)
    {
    a->ynode[n]=p->M32[n];
    a->yorig[n]=p->YN[a->ynode[n]+marge];
    }
    

    for(n=1;n<a->mz;n++)
    {	
    a->znode[n]=p->M33[n];
    a->zorig[n]=p->ZN[a->znode[n]+marge];
    }
    
}