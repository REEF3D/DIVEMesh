/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2020 Hans Bihs

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
--------------------------------------------------------------------*/

#include"solid.h"
#include"dive.h"
#include"lexer.h"

void solid::tetrahedon(lexer *p, dive *a, int rank, int &ts, int &te)
{

	double x1,y1,z1,x2,y2,z2,x3,y3,z3,x4,y4,z4;

	x1 = p->S81_x1[rank];
    y1 = p->S81_y1[rank];
    z1 = p->S81_z1[rank];
    
    x2 = p->S81_x2[rank];
    y2 = p->S81_y2[rank];
    z2 = p->S81_z2[rank];
    
    x3 = p->S81_x3[rank];
    y3 = p->S81_y3[rank];
    z3 = p->S81_z3[rank];
    
    x4 = p->S81_x4[rank];
    y4 = p->S81_y4[rank];
    z4 = p->S81_z4[rank];
	
	
	ts=p->tricount;
	
	
	p->trivec_x[p->tricount] = (y2-y1)*(z3-z1) - (z2-z1)*(y3-y1);
	p->trivec_y[p->tricount] = (z2-z1)*(x3-x1) - (x2-x1)*(z3-z1);
	p->trivec_z[p->tricount] = (x2-x1)*(y3-y1) - (y2-y1)*(x3-x1);
	
	p->tri_x[p->tricount][0] = x1;
	p->tri_y[p->tricount][0] = y1;
	p->tri_z[p->tricount][0] = z1;
	
	p->tri_x[p->tricount][1] = x2;
	p->tri_y[p->tricount][1] = y2;
	p->tri_z[p->tricount][1] = z2;
	
	p->tri_x[p->tricount][2] = x3;
	p->tri_y[p->tricount][2] = y3;
	p->tri_z[p->tricount][2] = z3;
	++p->tricount;
    
    
    p->trivec_x[p->tricount] = (y2-y1)*(z4-z1) - (z2-z1)*(y4-y1);
	p->trivec_y[p->tricount] = (z2-z1)*(x4-x1) - (x2-x1)*(z4-z1);
	p->trivec_z[p->tricount] = (x2-x1)*(y4-y1) - (y2-y1)*(x4-x1);
	
	p->tri_x[p->tricount][0] = x1;
	p->tri_y[p->tricount][0] = y1;
	p->tri_z[p->tricount][0] = z1;
	
	p->tri_x[p->tricount][1] = x2;
	p->tri_y[p->tricount][1] = y2;
	p->tri_z[p->tricount][1] = z2;
	
	p->tri_x[p->tricount][2] = x4;
	p->tri_y[p->tricount][2] = y4;
	p->tri_z[p->tricount][2] = z4;
	++p->tricount;
    
    
    p->trivec_x[p->tricount] = (y4-y1)*(z3-z1) - (z4-z1)*(y3-y1);
	p->trivec_y[p->tricount] = (z4-z1)*(x3-x1) - (x4-x1)*(z3-z1);
	p->trivec_z[p->tricount] = (x4-x1)*(y3-y1) - (y4-y1)*(x3-x1);
	
	p->tri_x[p->tricount][0] = x1;
	p->tri_y[p->tricount][0] = y1;
	p->tri_z[p->tricount][0] = z1;
	
	p->tri_x[p->tricount][1] = x3;
	p->tri_y[p->tricount][1] = y3;
	p->tri_z[p->tricount][1] = z3;
	
	p->tri_x[p->tricount][2] = x4;
	p->tri_y[p->tricount][2] = y4;
	p->tri_z[p->tricount][2] = z4;
	++p->tricount;
    
    
    
    p->trivec_x[p->tricount] = (y2-y4)*(z3-z4) - (z2-z4)*(y3-y4);
	p->trivec_y[p->tricount] = (z2-z4)*(x3-x4) - (x2-x4)*(z3-z4);
	p->trivec_z[p->tricount] = (x2-x4)*(y3-y4) - (y2-y4)*(x3-x4);
	
	p->tri_x[p->tricount][0] = x2;
	p->tri_y[p->tricount][0] = y2;
	p->tri_z[p->tricount][0] = z2;
	
	p->tri_x[p->tricount][1] = x3;
	p->tri_y[p->tricount][1] = y3;
	p->tri_z[p->tricount][1] = z3;
	
	p->tri_x[p->tricount][2] = x4;
	p->tri_y[p->tricount][2] = y4;
	p->tri_z[p->tricount][2] = z4;
	++p->tricount;
	
	
	te=p->tricount;
}