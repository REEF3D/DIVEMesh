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

#include "geodat.h"
#include "dive.h"
#include "lexer.h"
#include "field2d.h"


void geodat::filter(lexer *p, dive *a, field2d &bed)
{
    int outer_iter = p->G31;
    int inner_iter = p->G32;

    field2d h(p),dh(p);

    for(int qn=0;qn<outer_iter;++qn)
    {
        XYLOOP
        h(i,j) = bed(i,j);

        k=0;
        XYLOOP
        if(a->flag(i,j,k)>0)
        {
            if(a->flag(i-1,j,k)<0)
            h(i-1,j) = bed(i,j);

            if(a->flag(i+1,j,k)<0)
            h(i+1,j) = bed(i,j);

            if(a->flag(i,j-1,k)<0)
            h(i,j-1) = bed(i,j);

            if(a->flag(i,j+1,k)<0)
            h(i,j+1) = bed(i,j);
        }

        // predictor
        XYLOOP
        bed(i,j) = 0.5*h(i,j) + 0.125*(h(i-1,j) + h(i+1,j) + h(i,j-1) + h(i,j+1));

        // corrector
        for(int qqn=0;qqn<inner_iter;++qqn)
        {
            XYLOOP
            dh(i,j) = h(i,j) - bed(i,j);

            XYLOOP
            dh(i,j) = 0.5*dh(i,j) + 0.125*(dh(i-1,j) + dh(i+1,j) + dh(i,j-1) + dh(i,j+1));

            XYLOOP
            bed(i,j) += dh(i,j);
        }
    }
}
