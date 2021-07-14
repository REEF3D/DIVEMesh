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

#include"geometry.h"
#include"dive.h"
#include"lexer.h"

void geometry::wedge_y(lexer *p, dive *a, int rank, int &ts, int &te,
                double xs,double xe,double ys,double ye,double zs,double ze)
{

/*
	xs = p->S62_xs[rank];
    xe = p->S62_xe[rank];

    ys = p->S62_ys[rank];
    ye = p->S62_ye[rank];

    zs = p->S62_zs[rank];
    ze = p->S62_ze[rank];*/

	ts=p->tricount;

	if(zs<ze)
	{
	// sides
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

	// bottom
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = 0.0;
	p->trivec_z[p->tricount] = -1.0;

	p->tri_x[p->tricount][0] = xs;
	p->tri_y[p->tricount][0] = ys;
	p->tri_z[p->tricount][0] = zs;

	p->tri_x[p->tricount][1] = xs;
	p->tri_y[p->tricount][1] = ye;
	p->tri_z[p->tricount][1] = zs;

	p->tri_x[p->tricount][2] = xe;
	p->tri_y[p->tricount][2] = ye;
	p->tri_z[p->tricount][2] = zs;
	++p->tricount;

	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = 0.0;
	p->trivec_z[p->tricount] = -1.0;

	p->tri_x[p->tricount][0] = xs;
	p->tri_y[p->tricount][0] = ys;
	p->tri_z[p->tricount][0] = zs;

	p->tri_x[p->tricount][1] = xe;
	p->tri_y[p->tricount][1] = ys;
	p->tri_z[p->tricount][1] = zs;

	p->tri_x[p->tricount][2] = xe;
	p->tri_y[p->tricount][2] = ye;
	p->tri_z[p->tricount][2] = zs;
	++p->tricount;

	// front
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = 1.0;
	p->trivec_z[p->tricount] = 0.0;

	p->tri_x[p->tricount][0] = xs;
	p->tri_y[p->tricount][0] = ye;
	p->tri_z[p->tricount][0] = zs;

	p->tri_x[p->tricount][1] = xe;
	p->tri_y[p->tricount][1] = ye;
	p->tri_z[p->tricount][1] = zs;

	p->tri_x[p->tricount][2] = xe;
	p->tri_y[p->tricount][2] = ye;
	p->tri_z[p->tricount][2] = ze;
	++p->tricount;

	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = 1.0;
	p->trivec_z[p->tricount] = 0.0;

	p->tri_x[p->tricount][0] = xs;
	p->tri_y[p->tricount][0] = ye;
	p->tri_z[p->tricount][0] = zs;

	p->tri_x[p->tricount][1] = xs;
	p->tri_y[p->tricount][1] = ye;
	p->tri_z[p->tricount][1] = ze;

	p->tri_x[p->tricount][2] = xe;
	p->tri_y[p->tricount][2] = ye;
	p->tri_z[p->tricount][2] = ze;
	++p->tricount;

	// top
	p->trivec_x[p->tricount] = 1.0;
	p->trivec_y[p->tricount] = 0.0;
	p->trivec_z[p->tricount] = 0.0;

	p->tri_x[p->tricount][0] = xs;
	p->tri_y[p->tricount][0] = ys;
	p->tri_z[p->tricount][0] = zs;

	p->tri_x[p->tricount][1] = xe;
	p->tri_y[p->tricount][1] = ye;
	p->tri_z[p->tricount][1] = ze;

	p->tri_x[p->tricount][2] = xs;
	p->tri_y[p->tricount][2] = ye;
	p->tri_z[p->tricount][2] = ze;
	++p->tricount;

	p->trivec_x[p->tricount] = 1.0;
	p->trivec_y[p->tricount] = 0.0;
	p->trivec_z[p->tricount] = 0.0;

	p->tri_x[p->tricount][0] = xs;
	p->tri_y[p->tricount][0] = ys;
	p->tri_z[p->tricount][0] = zs;

	p->tri_x[p->tricount][1] = xe;
	p->tri_y[p->tricount][1] = ys;
	p->tri_z[p->tricount][1] = zs;

	p->tri_x[p->tricount][2] = xe;
	p->tri_y[p->tricount][2] = ye;
	p->tri_z[p->tricount][2] = ze;
	++p->tricount;
	}

	if(zs>=ze)
	{
	// sides
	p->trivec_x[p->tricount] = -1.0;
	p->trivec_y[p->tricount] = 0.0;
	p->trivec_z[p->tricount] = 0.0;

	p->tri_x[p->tricount][0] = xs;
	p->tri_y[p->tricount][0] = ys;
	p->tri_z[p->tricount][0] = ze;

	p->tri_x[p->tricount][1] = xs;
	p->tri_y[p->tricount][1] = ye;
	p->tri_z[p->tricount][1] = ze;

	p->tri_x[p->tricount][2] = xs;
	p->tri_y[p->tricount][2] = ys;
	p->tri_z[p->tricount][2] = zs;
	++p->tricount;

	p->trivec_x[p->tricount] = 1.0;
	p->trivec_y[p->tricount] = 0.0;
	p->trivec_z[p->tricount] = 0.0;

	p->tri_x[p->tricount][0] = xe;
	p->tri_y[p->tricount][0] = ys;
	p->tri_z[p->tricount][0] = ze;

	p->tri_x[p->tricount][1] = xe;
	p->tri_y[p->tricount][1] = ye;
	p->tri_z[p->tricount][1] = ze;

	p->tri_x[p->tricount][2] = xe;
	p->tri_y[p->tricount][2] = ys;
	p->tri_z[p->tricount][2] = zs;
	++p->tricount;

	// bottom
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = 0.0;
	p->trivec_z[p->tricount] = -1.0;

	p->tri_x[p->tricount][0] = xs;
	p->tri_y[p->tricount][0] = ys;
	p->tri_z[p->tricount][0] = ze;

	p->tri_x[p->tricount][1] = xs;
	p->tri_y[p->tricount][1] = ye;
	p->tri_z[p->tricount][1] = ze;

	p->tri_x[p->tricount][2] = xe;
	p->tri_y[p->tricount][2] = ye;
	p->tri_z[p->tricount][2] = ze;
	++p->tricount;

	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = 0.0;
	p->trivec_z[p->tricount] = -1.0;

	p->tri_x[p->tricount][0] = xs;
	p->tri_y[p->tricount][0] = ys;
	p->tri_z[p->tricount][0] = ze;

	p->tri_x[p->tricount][1] = xe;
	p->tri_y[p->tricount][1] = ys;
	p->tri_z[p->tricount][1] = ze;

	p->tri_x[p->tricount][2] = xe;
	p->tri_y[p->tricount][2] = ye;
	p->tri_z[p->tricount][2] = ze;
	++p->tricount;

	// front
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;

	p->tri_x[p->tricount][0] = xs;
	p->tri_y[p->tricount][0] = ys;
	p->tri_z[p->tricount][0] = zs;

	p->tri_x[p->tricount][1] = xe;
	p->tri_y[p->tricount][1] = ys;
	p->tri_z[p->tricount][1] = zs;

	p->tri_x[p->tricount][2] = xe;
	p->tri_y[p->tricount][2] = ys;
	p->tri_z[p->tricount][2] = ze;
	++p->tricount;

	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;

	p->tri_x[p->tricount][0] = xs;
	p->tri_y[p->tricount][0] = ys;
	p->tri_z[p->tricount][0] = zs;

	p->tri_x[p->tricount][1] = xs;
	p->tri_y[p->tricount][1] = ys;
	p->tri_z[p->tricount][1] = ze;

	p->tri_x[p->tricount][2] = xe;
	p->tri_y[p->tricount][2] = ys;
	p->tri_z[p->tricount][2] = ze;
	++p->tricount;

	// top
	p->trivec_x[p->tricount] = 1.0;
	p->trivec_y[p->tricount] = 0.0;
	p->trivec_z[p->tricount] = 0.0;

	p->tri_x[p->tricount][0] = xs;
	p->tri_y[p->tricount][0] = ys;
	p->tri_z[p->tricount][0] = zs;

	p->tri_x[p->tricount][1] = xe;
	p->tri_y[p->tricount][1] = ye;
	p->tri_z[p->tricount][1] = ze;

	p->tri_x[p->tricount][2] = xs;
	p->tri_y[p->tricount][2] = ye;
	p->tri_z[p->tricount][2] = ze;
	++p->tricount;

	p->trivec_x[p->tricount] = 1.0;
	p->trivec_y[p->tricount] = 0.0;
	p->trivec_z[p->tricount] = 0.0;

	p->tri_x[p->tricount][0] = xs;
	p->tri_y[p->tricount][0] = ys;
	p->tri_z[p->tricount][0] = zs;

	p->tri_x[p->tricount][1] = xe;
	p->tri_y[p->tricount][1] = ys;
	p->tri_z[p->tricount][1] = zs;

	p->tri_x[p->tricount][2] = xe;
	p->tri_y[p->tricount][2] = ye;
	p->tri_z[p->tricount][2] = ze;
	++p->tricount;
	}

	te=p->tricount;
}
