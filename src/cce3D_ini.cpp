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

#include"cce3D.h"
#include"dive.h"
#include"lexer.h"
#include"entity.h"

void cce3D::ini(lexer *p, dive *a, entity *pent)
{
    count=a->facetcount;
    ptcount=a->ccpointcount;

     xstart=pent->xstart();
     xend=pent->xend();
     ystart=pent->ystart();
     yend=pent->yend();
     zstart=pent->zstart();
     zend=pent->zend();

    onnode=0;
    onnode_fill=0;

    if(xend>=xstart)
    {
    xsmall=xstart;
    xlarge=xend;
    }

    if(xend<xstart)
    {
    xsmall=xend;
    xlarge=xstart;
    }

    if(yend>=ystart)
    {
    ysmall=ystart;
    ylarge=yend;
    }

    if(yend<ystart)
    {
    ysmall=yend;
    ylarge=ystart;
    }

    if(zend>=zstart)
    {
    zsmall=zstart;
    zlarge=zend;
    }

    if(zend<zstart)
    {
    zsmall=zend;
    zlarge=zstart;
    }
}

