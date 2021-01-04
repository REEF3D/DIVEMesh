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
--------------------------------------------------------------------*/

#include"solid.h"
#include"dive.h"
#include"lexer.h"

void solid::hexahedron(lexer *p, dive *a, int rank, int &ts, int &te)
{

	double x1,y1,z1,x2,y2,z2,x3,y3,z3,x4,y4,z4,x5,y5,z5,x6,y6,z6,x7,y7,z7,x8,y8,z8;

	x1 = p->S84_x1[rank];
    y1 = p->S84_y1[rank];
    z1 = p->S84_z1[rank];
    
    x2 = p->S84_x2[rank];
    y2 = p->S84_y2[rank];
    z2 = p->S84_z2[rank];
    
    x3 = p->S84_x3[rank];
    y3 = p->S84_y3[rank];
    z3 = p->S84_z3[rank];
    
    x4 = p->S84_x4[rank];
    y4 = p->S84_y4[rank];
    z4 = p->S84_z4[rank];
	
	x5 = p->S84_x5[rank];
    y5 = p->S84_y5[rank];
    z5 = p->S84_z5[rank];
	
	x6 = p->S84_x6[rank];
    y6 = p->S84_y6[rank];
    z6 = p->S84_z6[rank];
  
	x7 = p->S84_x7[rank];
    y7 = p->S84_y7[rank];
    z7 = p->S84_z7[rank];
	
	x8 = p->S84_x8[rank];
    y8 = p->S84_y8[rank];
    z8 = p->S84_z8[rank];
	
	ts=p->tricount;
	
	
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = 0.0;
	p->trivec_z[p->tricount] = 0.0;
	
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
    
    
    p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = 0.0;
	p->trivec_z[p->tricount] = 0.0;
	
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
    
    
    
    p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = 0.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = x1;
	p->tri_y[p->tricount][0] = y1;
	p->tri_z[p->tricount][0] = z1;
	
	p->tri_x[p->tricount][1] = x2;
	p->tri_y[p->tricount][1] = y2;
	p->tri_z[p->tricount][1] = z2;
	
	p->tri_x[p->tricount][2] = x6;
	p->tri_y[p->tricount][2] = y6;
	p->tri_z[p->tricount][2] = z6;
	++p->tricount;
	
	
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = 0.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = x1;
	p->tri_y[p->tricount][0] = y1;
	p->tri_z[p->tricount][0] = z1;
	
	p->tri_x[p->tricount][1] = x5;
	p->tri_y[p->tricount][1] = y5;
	p->tri_z[p->tricount][1] = z5;
	
	p->tri_x[p->tricount][2] = x6;
	p->tri_y[p->tricount][2] = y6;
	p->tri_z[p->tricount][2] = z6;
	++p->tricount;
	
	
	
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = 0.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = x2;
	p->tri_y[p->tricount][0] = y2;
	p->tri_z[p->tricount][0] = z2;
	
	p->tri_x[p->tricount][1] = x3;
	p->tri_y[p->tricount][1] = y3;
	p->tri_z[p->tricount][1] = z3;
	
	p->tri_x[p->tricount][2] = x6;
	p->tri_y[p->tricount][2] = y6;
	p->tri_z[p->tricount][2] = z6;
	++p->tricount;
	
	
	
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = 0.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = x3;
	p->tri_y[p->tricount][0] = y3;
	p->tri_z[p->tricount][0] = z3;
	
	p->tri_x[p->tricount][1] = x7;
	p->tri_y[p->tricount][1] = y7;
	p->tri_z[p->tricount][1] = z7;
	
	p->tri_x[p->tricount][2] = x6;
	p->tri_y[p->tricount][2] = y6;
	p->tri_z[p->tricount][2] = z6;
	++p->tricount;
	
	
	
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = 0.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = x3;
	p->tri_y[p->tricount][0] = y3;
	p->tri_z[p->tricount][0] = z3;
	
	p->tri_x[p->tricount][1] = x7;
	p->tri_y[p->tricount][1] = y7;
	p->tri_z[p->tricount][1] = z7;
	
	p->tri_x[p->tricount][2] = x4;
	p->tri_y[p->tricount][2] = y4;
	p->tri_z[p->tricount][2] = z4;
	++p->tricount;
	
	
	
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = 0.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = x4;
	p->tri_y[p->tricount][0] = y4;
	p->tri_z[p->tricount][0] = z4;
	
	p->tri_x[p->tricount][1] = x7;
	p->tri_y[p->tricount][1] = y7;
	p->tri_z[p->tricount][1] = z7;
	
	p->tri_x[p->tricount][2] = x8;
	p->tri_y[p->tricount][2] = y8;
	p->tri_z[p->tricount][2] = z8;
	++p->tricount;
	
	
	
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = 0.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = x1;
	p->tri_y[p->tricount][0] = y1;
	p->tri_z[p->tricount][0] = z1;
	
	p->tri_x[p->tricount][1] = x4;
	p->tri_y[p->tricount][1] = y4;
	p->tri_z[p->tricount][1] = z4;
	
	p->tri_x[p->tricount][2] = x5;
	p->tri_y[p->tricount][2] = y5;
	p->tri_z[p->tricount][2] = z5;
	++p->tricount;
	
	
	
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = 0.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = x4;
	p->tri_y[p->tricount][0] = y4;
	p->tri_z[p->tricount][0] = z4;
	
	p->tri_x[p->tricount][1] = x5;
	p->tri_y[p->tricount][1] = y5;
	p->tri_z[p->tricount][1] = z5;
	
	p->tri_x[p->tricount][2] = x8;
	p->tri_y[p->tricount][2] = y8;
	p->tri_z[p->tricount][2] = z8;
	++p->tricount;
	
	
	
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = 0.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = x5;
	p->tri_y[p->tricount][0] = y5;
	p->tri_z[p->tricount][0] = z5;
	
	p->tri_x[p->tricount][1] = x6;
	p->tri_y[p->tricount][1] = y6;
	p->tri_z[p->tricount][1] = z6;
	
	p->tri_x[p->tricount][2] = x7;
	p->tri_y[p->tricount][2] = y7;
	p->tri_z[p->tricount][2] = z7;
	++p->tricount;
	
	
	
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = 0.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = x5;
	p->tri_y[p->tricount][0] = y5;
	p->tri_z[p->tricount][0] = z5;
	
	p->tri_x[p->tricount][1] = x7;
	p->tri_y[p->tricount][1] = y7;
	p->tri_z[p->tricount][1] = z7;
	
	p->tri_x[p->tricount][2] = x8;
	p->tri_y[p->tricount][2] = y8;
	p->tri_z[p->tricount][2] = z8;
	++p->tricount;
	
	cout<<"HEXA: "<<p->tricount<<endl;
	te=p->tricount;
}