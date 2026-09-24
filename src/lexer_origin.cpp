/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2026 Hans Bihs

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
#include<algorithm>

void lexer::origin_calc()
{
    // xmin,xmax
    xmin=+1.0e19;
    ymin=+1.0e19;
    zmin=+1.0e19;

    xmax=-1.0e19;
    ymax=-1.0e19;
    zmax=-1.0e19;

    for(qn=0;qn<B10;++qn)
    {
        xmin=std::min(xmin,B10_xs[qn]);
        ymin=std::min(ymin,B10_ys[qn]);
        zmin=std::min(zmin,B10_zs[qn]);
        xmin=std::min(xmin,B10_xe[qn]);
        ymin=std::min(ymin,B10_ye[qn]);
        zmin=std::min(zmin,B10_ze[qn]);

        xmax=std::max(xmax,B10_xs[qn]);
        ymax=std::max(ymax,B10_ys[qn]);
        zmax=std::max(zmax,B10_zs[qn]);
        xmax=std::max(xmax,B10_xe[qn]);
        ymax=std::max(ymax,B10_ye[qn]);
        zmax=std::max(zmax,B10_ze[qn]);
    }

    if(S1==1 && S2==1)
    {
        xmin=xs_stl;
        ymin=ys_stl;
        zmin=zs_stl;
        xmax=xe_stl;
        ymax=ye_stl;
        zmax=ze_stl;
    }

    // origin
    global_orig_x = xmin + B3_dx;
    global_orig_y = ymin + B3_dy;
}


void lexer::origin_apply()
{
    /*if(B6==1)
    for(qn=0;qn<B10;++qn)
    {
        B10_xs[qn] -= global_orig_x;
        B10_xe[qn] -= global_orig_x;

        B10_ys[qn] -= global_orig_y;
        B10_ye[qn] -= global_orig_y;
    }*/
}