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

#include"decomp.h"

void decomp::partition_planes(lexer* p, dive* a)
{
    int numtri = a->mx*2 + a->my*2 + a->mz*2;
    
    p->Darray(trix,numtri,3);
    p->Darray(triy,numtri,3);
    p->Darray(triz,numtri,3);

    n=0;
    
    // partition planes
    for(qn=1;qn<a->mx;qn++)
    {
    trix[n][0] = a->xorig[qn];
    triy[n][0] = p->ymin;
    triz[n][0] = p->zmin;
    
    trix[n][1] = a->xorig[qn];
    triy[n][1] = p->ymax;
    triz[n][1] = p->zmin;
    
    trix[n][2] = a->xorig[qn];
    triy[n][2] = p->ymin;
    triz[n][2] = p->zmax;
    ++n;
    
    trix[n][0] = a->xorig[qn];
    triy[n][0] = p->ymin;
    triz[n][0] = p->zmax;
    
    trix[n][1] = a->xorig[qn];
    triy[n][1] = p->ymax;
    triz[n][1] = p->zmin;
    
    trix[n][2] = a->xorig[qn];
    triy[n][2] = p->ymax;
    triz[n][2] = p->zmax;
    ++n;
	}
    
    
    for(qn=1;qn<a->my;qn++)
    {
    trix[n][0] = p->xmin;
    triy[n][0] = a->yorig[qn];
    triz[n][0] = p->zmin;
    
    trix[n][1] = p->xmax;
    triy[n][1] = a->yorig[qn];
    triz[n][1] = p->zmin;
    
    trix[n][2] = p->xmax;
    triy[n][2] = a->yorig[qn];
    triz[n][2] = p->zmax;
    ++n;
    
    trix[n][0] = p->xmin;
    triy[n][0] = a->yorig[qn];
    triz[n][0] = p->zmin;
    
    trix[n][1] = p->xmin;
    triy[n][1] = a->yorig[qn];
    triz[n][1] = p->zmax;
    
    trix[n][2] = p->xmax;
    triy[n][2] = a->yorig[qn];
    triz[n][2] = p->zmax;
    ++n;
	}
    
    
    
    for(qn=1;qn<a->mz;qn++)
    {
    trix[n][0] = p->xmin;
    triy[n][0] = p->ymin;
    triz[n][0] = a->zorig[qn];
    
    trix[n][1] = p->xmax;
    triy[n][1] = p->ymin;
    triz[n][1] = a->zorig[qn];
    
    trix[n][2] = p->xmax;
    triy[n][2] = p->ymax;
    triz[n][2] = a->zorig[qn];
    ++n;
    
    trix[n][0] = p->xmin;
    triy[n][0] = p->ymin;
    triz[n][0] = a->zorig[qn];
    
    trix[n][1] = p->xmax;
    triy[n][1] = p->ymax;
    triz[n][1] = a->zorig[qn];
    
    trix[n][2] = p->xmin;
    triy[n][2] = p->ymax;
    triz[n][2] = a->zorig[qn];
    ++n;
	}
    
    
    tricount=n;
    
}