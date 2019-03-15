/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2019 Hans Bihs

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

#include"surface.h"
#include"dive.h"
#include"lexer.h"

void surface::normalvec(lexer* p, dive* a)
{
    double xp[6],yp[6],zp[6];
    double nx,ny,nz;
    double nl;

    LOOP
    if(a->numfac(i,j,k)>0)
    {
     q=a->confac(i,j,k);

// gcn
    xp[0]=a->ccpoint[a->facet[q][1]][0]-a->ccpoint[a->facet[q][0]][0];
    yp[0]=a->ccpoint[a->facet[q][1]][1]-a->ccpoint[a->facet[q][0]][1];
    zp[0]=a->ccpoint[a->facet[q][1]][2]-a->ccpoint[a->facet[q][0]][2];

    xp[1]=a->ccpoint[a->facet[q][2]][0]-a->ccpoint[a->facet[q][0]][0];
    yp[1]=a->ccpoint[a->facet[q][2]][1]-a->ccpoint[a->facet[q][0]][1];
    zp[1]=a->ccpoint[a->facet[q][2]][2]-a->ccpoint[a->facet[q][0]][2];

    nx=fabs(yp[0]*zp[1] - zp[0]*yp[1]);
    ny=fabs(zp[0]*xp[1] - xp[0]*zp[1]);
    nz=fabs(xp[0]*yp[1] - yp[0]*xp[1]);

    nl = sqrt(nx*nx + ny*ny + nz*nz);

    a->gcn[q][0]= nx=nx/nl;
    a->gcn[q][1]= ny=ny/nl;
    a->gcn[q][2]= nz=nz/nl;
    }
}

