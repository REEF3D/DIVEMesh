/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2023 Hans Bihs

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

#include"geometry.h"
#include"dive.h"
#include"lexer.h"

void geometry::wedge(lexer *p, dive *a, int rank, int &ts, int &te, double **xyz)
{

	double x1,y1,z1,x2,y2,z2,x3,y3,z3,x4,y4,z4,x5,y5,z5,x6,y6,z6;

	x1 = xyz[rank][0];
    y1 = xyz[rank][1];
    z1 = xyz[rank][2];
    
    x2 = xyz[rank][3];
    y2 = xyz[rank][4];
    z2 = xyz[rank][5];
    
    x3 = xyz[rank][6];
    y3 = xyz[rank][7];
    z3 = xyz[rank][8];
    
    x4 = xyz[rank][9];
    y4 = xyz[rank][10];
    z4 = xyz[rank][11];
	
	x5 = xyz[rank][12];
    y5 = xyz[rank][13];
    z5 = xyz[rank][14];
    
    x6 = xyz[rank][15];
    y6 = xyz[rank][16];
    z6 = xyz[rank][17];


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

	p->tri_x[p->tricount][1] = x2;
	p->tri_y[p->tricount][1] = y2;
	p->tri_z[p->tricount][1] = z2;

	p->tri_x[p->tricount][2] = x5;
	p->tri_y[p->tricount][2] = y5;
	p->tri_z[p->tricount][2] = z5;
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

	p->tri_x[p->tricount][0] = x2;
	p->tri_y[p->tricount][0] = y2;
	p->tri_z[p->tricount][0] = z2;

	p->tri_x[p->tricount][1] = x3;
	p->tri_y[p->tricount][1] = y3;
	p->tri_z[p->tricount][1] = z3;

	p->tri_x[p->tricount][2] = x5;
	p->tri_y[p->tricount][2] = y5;
	p->tri_z[p->tricount][2] = z5;
	++p->tricount;


	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = 0.0;
	p->trivec_z[p->tricount] = 0.0;

	p->tri_x[p->tricount][0] = x3;
	p->tri_y[p->tricount][0] = y3;
	p->tri_z[p->tricount][0] = z3;

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

	p->tri_x[p->tricount][0] = x1;
	p->tri_y[p->tricount][0] = y1;
	p->tri_z[p->tricount][0] = z1;

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

	p->tri_x[p->tricount][0] = x1;
	p->tri_y[p->tricount][0] = y1;
	p->tri_z[p->tricount][0] = z1;

	p->tri_x[p->tricount][1] = x6;
	p->tri_y[p->tricount][1] = y6;
	p->tri_z[p->tricount][1] = z6;

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

	p->tri_x[p->tricount][1] = x5;
	p->tri_y[p->tricount][1] = y5;
	p->tri_z[p->tricount][1] = z5;

	p->tri_x[p->tricount][2] = x6;
	p->tri_y[p->tricount][2] = y6;
	p->tri_z[p->tricount][2] = z6;
	++p->tricount;


	te=p->tricount;
}
