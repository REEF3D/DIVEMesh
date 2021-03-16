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

#include"surface.h"
#include"lexer.h"
#include"dive.h"

void surface::makesurfsolid(lexer* p, dive* a)
{
    int count=a->surfcount;
    for(qn=0;qn<a->surfcount_solid;++qn)
    {
        a->surf[count][0]=a->surf_solid[qn][0];
        a->surf[count][1]=a->surf_solid[qn][1];
        a->surf[count][2]=a->surf_solid[qn][2];
        a->surf[count][3]=a->surf_solid[qn][3];
        a->surf[count][4]=a->surf_solid[qn][4];
        count++;
    }

    count=a->surfcount;
    for(qn=0;qn<a->surfcount_solid;++qn)
    {
        a->gcd[count] = 0.5*p->dx;
        ++count;
    }

    a->surfcount +=a->surfcount_solid;
}
