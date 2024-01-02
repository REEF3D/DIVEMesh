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

#include"geometry.h"
#include"dive.h"
#include"lexer.h"


void geometry::box_array(lexer* p, dive* a,intfield &gsio,field &gs_dist,field2d &gsbed,
            int rank, int &ts, int &te, double xorig, double yorig, double zorig, double L, double G, int ni, int nj, int nk)
{	
	int aa,bb,cc;
	/*
	xorig = p->S11_xs[rank];
	yorig = p->S11_ys[rank];
	zorig = p->S11_zs[rank];
	L = p->S11_L[rank];
	G = p->S11_G[rank];
	ni = p->S11_ni[rank];
	nj = p->S11_nj[rank];
	nk = p->S11_nk[rank];*/
	
	//cout<<"BOX ARRAY: "<<ni<<" "<<nj<<" "<<nk<<endl;
	
	for(aa=0;aa<ni;++aa)
	for(bb=0;bb<nj;++bb)
	for(cc=0;cc<nk;++cc)
	{
	ts=p->tricount;
		
	xs = xorig + double(aa)*(L+G);
	ys = yorig + double(bb)*(L+G);
	zs = zorig + double(cc)*(L+G);
	xe = xs+L;
	ye = ys+L;
	ze = zs+L;
	
	
	//cout<<"XYZ: "<<xs<<" "<<ys<<" "<<zs<<" "<<xe<<" "<<xe<<" "<<xe<<" | "<<L<<" "<<G<<" "<<p->S11_L[rank]<<" "<<p->S11_G[rank]<<endl;
	
		

	// Vert

	// Face 3
		// Tri 1
		
		p->trivec_x[p->tricount] = 0.0;
		p->trivec_y[p->tricount] = -1.0;
		p->trivec_z[p->tricount] = 0.0;
		
		p->tri_x[p->tricount][0] = xe;
		p->tri_y[p->tricount][0] = ys;
		p->tri_z[p->tricount][0] = zs;
		
		p->tri_x[p->tricount][1] = xs;
		p->tri_y[p->tricount][1] = ys;
		p->tri_z[p->tricount][1] = ze;
		
		p->tri_x[p->tricount][2] = xs;
		p->tri_y[p->tricount][2] = ys;
		p->tri_z[p->tricount][2] = zs;
		++p->tricount;
		
		// Tri 2
		p->trivec_x[p->tricount] = 0.0;
		p->trivec_y[p->tricount] = -1.0;
		p->trivec_z[p->tricount] = 0.0;
		
		p->tri_x[p->tricount][0] = xe;
		p->tri_y[p->tricount][0] = ys;
		p->tri_z[p->tricount][0] = zs;
		
		p->tri_x[p->tricount][1] = xe;
		p->tri_y[p->tricount][1] = ys;
		p->tri_z[p->tricount][1] = ze;
		
		p->tri_x[p->tricount][2] = xs;
		p->tri_y[p->tricount][2] = ys;
		p->tri_z[p->tricount][2] = ze;
		++p->tricount;

	// Face 4	
		// Tri 3
		p->trivec_x[p->tricount] = 1.0;
		p->trivec_y[p->tricount] = 0.0;
		p->trivec_z[p->tricount] = 0.0;
		
		p->tri_x[p->tricount][0] = xe;
		p->tri_y[p->tricount][0] = ys;
		p->tri_z[p->tricount][0] = zs;
		
		p->tri_x[p->tricount][1] = xe;
		p->tri_y[p->tricount][1] = ys;
		p->tri_z[p->tricount][1] = ze;
		
		p->tri_x[p->tricount][2] = xe;
		p->tri_y[p->tricount][2] = ye;
		p->tri_z[p->tricount][2] = ze;
		++p->tricount;
		
		// Tri 4
		p->trivec_x[p->tricount] = 1.0;
		p->trivec_y[p->tricount] = 0.0;
		p->trivec_z[p->tricount] = 0.0;
		
		p->tri_x[p->tricount][0] = xe;
		p->tri_y[p->tricount][0] = ys;
		p->tri_z[p->tricount][0] = zs;
		
		p->tri_x[p->tricount][1] = xe;
		p->tri_y[p->tricount][1] = ye;
		p->tri_z[p->tricount][1] = zs;
		
		p->tri_x[p->tricount][2] = xe;
		p->tri_y[p->tricount][2] = ye;
		p->tri_z[p->tricount][2] = ze;
		++p->tricount;

	// Face 2	
		// Tri 5
		p->trivec_x[p->tricount] = 0.0;
		p->trivec_y[p->tricount] = 1.0;
		p->trivec_z[p->tricount] = 0.0;
		
		p->tri_x[p->tricount][0] = xe;
		p->tri_y[p->tricount][0] = ye;
		p->tri_z[p->tricount][0] = zs;
		
		p->tri_x[p->tricount][1] = xs;
		p->tri_y[p->tricount][1] = ye;
		p->tri_z[p->tricount][1] = ze;
		
		p->tri_x[p->tricount][2] = xs;
		p->tri_y[p->tricount][2] = ye;
		p->tri_z[p->tricount][2] = zs;
		++p->tricount;
		
		// Tri 6
		p->trivec_x[p->tricount] = 0.0;
		p->trivec_y[p->tricount] = 1.0;
		p->trivec_z[p->tricount] = 0.0;
		
		p->tri_x[p->tricount][0] = xe;
		p->tri_y[p->tricount][0] = ye;
		p->tri_z[p->tricount][0] = zs;
		
		p->tri_x[p->tricount][1] = xe;
		p->tri_y[p->tricount][1] = ye;
		p->tri_z[p->tricount][1] = ze;
		
		p->tri_x[p->tricount][2] = xs;
		p->tri_y[p->tricount][2] = ye;
		p->tri_z[p->tricount][2] = ze;
		++p->tricount;

	// Face 1	
		// Tri 7
		p->trivec_x[p->tricount] = -1.0;
		p->trivec_y[p->tricount] = 0.0;
		p->trivec_z[p->tricount] = 0.0;
		
		p->tri_x[p->tricount][0] = xs;
		p->tri_y[p->tricount][0] = ys;
		p->tri_z[p->tricount][0] = zs;
		
		p->tri_x[p->tricount][1] = xs;
		p->tri_y[p->tricount][1] = ys;
		p->tri_z[p->tricount][1] = ze;
		
		p->tri_x[p->tricount][2] = xs;
		p->tri_y[p->tricount][2] = ye;
		p->tri_z[p->tricount][2] = ze;
		++p->tricount;
		
		// Tri 8
		p->trivec_x[p->tricount] = -1.0;
		p->trivec_y[p->tricount] = 0.0;
		p->trivec_z[p->tricount] = 0.0;
		
		p->tri_x[p->tricount][0] = xs;
		p->tri_y[p->tricount][0] = ys;
		p->tri_z[p->tricount][0] = zs;
		
		p->tri_x[p->tricount][1] = xs;
		p->tri_y[p->tricount][1] = ye;
		p->tri_z[p->tricount][1] = zs;
		
		p->tri_x[p->tricount][2] = xs;
		p->tri_y[p->tricount][2] = ye;
		p->tri_z[p->tricount][2] = ze;
		++p->tricount;

	// Face 5	
		// Tri 9
		p->trivec_x[p->tricount] = 0.0;
		p->trivec_y[p->tricount] = 0.0;
		p->trivec_z[p->tricount] = -1.0;
		
		p->tri_x[p->tricount][0] = xe;
		p->tri_y[p->tricount][0] = ys;
		p->tri_z[p->tricount][0] = zs;
		
		p->tri_x[p->tricount][1] = xs;
		p->tri_y[p->tricount][1] = ye;
		p->tri_z[p->tricount][1] = zs;
		
		p->tri_x[p->tricount][2] = xs;
		p->tri_y[p->tricount][2] = ys;
		p->tri_z[p->tricount][2] = zs;
		++p->tricount;
		
		// Tri 10
		p->trivec_x[p->tricount] = 0.0;
		p->trivec_y[p->tricount] = 0.0;
		p->trivec_z[p->tricount] = -1.0;
		
		p->tri_x[p->tricount][0] = xe;
		p->tri_y[p->tricount][0] = ys;
		p->tri_z[p->tricount][0] = zs;
		
		p->tri_x[p->tricount][1] = xe;
		p->tri_y[p->tricount][1] = ye;
		p->tri_z[p->tricount][1] = zs;
		
		p->tri_x[p->tricount][2] = xs;
		p->tri_y[p->tricount][2] = ye;
		p->tri_z[p->tricount][2] = zs;
		++p->tricount;
		
	// Face 6
		// Tri 11
		p->trivec_x[p->tricount] = 0.0;
		p->trivec_y[p->tricount] = 0.0;
		p->trivec_z[p->tricount] = 1.0;
		
		p->tri_x[p->tricount][0] = xe;
		p->tri_y[p->tricount][0] = ys;
		p->tri_z[p->tricount][0] = ze;
		
		p->tri_x[p->tricount][1] = xs;
		p->tri_y[p->tricount][1] = ye;
		p->tri_z[p->tricount][1] = ze;
		
		p->tri_x[p->tricount][2] = xs;
		p->tri_y[p->tricount][2] = ys;
		p->tri_z[p->tricount][2] = ze;
		++p->tricount;
		
		// Tri 12
		p->trivec_x[p->tricount] = 0.0;
		p->trivec_y[p->tricount] = 0.0;
		p->trivec_z[p->tricount] = 1.0;
		
		p->tri_x[p->tricount][0] = xe;
		p->tri_y[p->tricount][0] = ys;
		p->tri_z[p->tricount][0] = ze;
		
		p->tri_x[p->tricount][1] = xe;
		p->tri_y[p->tricount][1] = ye;
		p->tri_z[p->tricount][1] = ze;
		
		p->tri_x[p->tricount][2] = xs;
		p->tri_y[p->tricount][2] = ye;
		p->tri_z[p->tricount][2] = ze;
		++p->tricount;
		
		te=p->tricount;
		
		rotate_triangle(p,a,ts,te);
		
		//ray_cast(p,a,ts,te);
        ray_cast(p,a,tri_start,tri_end,gsio,gs_dist,gsbed);
	}
	
	
}

