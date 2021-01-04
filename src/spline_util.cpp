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

#include"spline.h"
#include"lexer.h"
#include"dive.h"

double spline::xstart()
{
    return xs;
}

double spline::xend()
{
    return xe;
}

double spline::ystart()
{
    return ys;
}

double spline::yend()
{
    return ye;
}

double spline::zstart()
{
    return zs;
}

double spline::zend()
{
    return ze;
}

int spline::type()
{
    return spline_type;
}

int spline::rank()
{
    return spline_rank;
}

int spline::side()
{
    return spline_side;
}

int spline::neighbor1()
{
    return nb1;
}

int spline::neighbor2()
{
    return nb2;
}

int spline::xdir(int ii, int jj, int kk)
{
    return spline_xdir;
}

int spline::ydir(int ii, int jj, int kk)
{
    return spline_ydir;
}

int spline::zdir(int ii, int jj, int kk)
{
    return spline_zdir;
}

int spline::inbound(int ii,int jj, int kk)
{
    double posx,posy,posz;
    int bound=1;

     posx = p->XP[II];
     posy = p->YP[JJ];
     posz = p->ZP[KK];

    if(posx<xsmall || posx>xlarge || posy<ysmall || posy>ylarge || posz<zsmall || posz>zlarge)
    bound=0;

    return bound;
}

int spline::inbound_onnode(int ii,int jj, int kk)
{
    int bound=0;
    double xx,yy;
    double x1,x2,y1,y2;

    x1 = p->XN[II];
    x2 = p->XN[IIP1];

    y1 = p->YN[JJ];
    y2 = p->YN[JJP1];
    
    xx = ((xe-xs)/ydenom)*(p->XP[II] - ys) + xs;
    yy = ((ye-ys)/xdenom)*(p->XP[jj] - xs) + ys;

    if((xx>x1-eps && xx<x2+eps) || (yy>y1-eps && yy<y2+eps))
    bound=1;

    return bound;
}

int spline::flag_val(int ii, int jj, int kk)
{
    int ival=0;

    return ival;
}
