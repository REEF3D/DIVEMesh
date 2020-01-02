/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2020 Hans Bihs

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

spline::spline(lexer *pp, int rank, int side) : eps(1.0e-9)
{
    p = pp;
    
    spline_rank = rank;
    spline_side = side;
    spline_type = 1;

    if(side==1)
    {
    xs = p->F11_xs[rank];
    xe = p->F11_xe[rank];

    ys = p->F11_ys[rank];
    ye = p->F11_ye[rank];

    zs = p->F3_zs;
    ze = p->F3_ze;
    }

    if(side==2)
    {
    xs = p->F21_xs[rank];
    xe = p->F21_xe[rank];

    ys = p->F21_ys[rank];
    ye = p->F21_ye[rank];

    zs = p->F3_zs;
    ze = p->F3_ze;
    }

    if(xe>=xs)
    {
    xsmall=xs;
    xlarge=xe;
    }

    if(xe<xs)
    {
    xsmall=xe;
    xlarge=xs;
    }

    if(ye>=ys)
    {
    ysmall=ys;
    ylarge=ye;
    }

    if(ye<ys)
    {
    ysmall=ye;
    ylarge=ys;
    }

    if(ze>=zs)
    {
    zsmall=zs;
    zlarge=ze;
    }

    if(ze<zs)
    {
    zsmall=ze;
    zlarge=zs;
    }

    xdenom=1.0e19;
    ydenom=1.0e19;

    if(xe>xs+1.0e-12 || xe<xs-1.0e-12)
    xdenom=xe-xs;

    if(ye>ys+1.0e-12 ||  ye<ys+1.0e-12)
    ydenom=ye-ys;

    if((spline_side==1 && ye>=ys) || (spline_side==2 && ye<ys))
    spline_xdir=1;

    if((spline_side==1 && ye<ys) || (spline_side==2 && ye>=ys))
    spline_xdir=4;

    if((spline_side==1 && xe>=xs) || (spline_side==2 && xe<xs))
    spline_ydir=2;

    if((spline_side==1 && xe<xs) || (spline_side==2 && xe>=xs))
    spline_ydir=3;

    spline_zdir=0;
}

spline::~spline()
{
}

void spline::read(lexer *p, dive *a, int& rankcount)
{

}

double spline::fx(lexer *p, dive *a, int ii, int jj, int kk)
{
    val=((xe-xs)/ydenom)*(p->YN[JJ] - ys) + xs;

    return val;
}

double spline::fy(lexer *p, dive *a, int ii, int jj, int kk)
{
    val=((ye-ys)/xdenom)*(p->XN[II] - xs) + ys;

    return val;
}

double spline::fz(lexer *p, dive *a, int ii, int jj, int kk)
{
    val=p->ZN[KK];

    return val;
}

double spline::cfx(lexer *p, dive *a, int ii, int jj, int kk)
{
    val=((xe-xs)/ydenom)*(p->YP[JJ] - ys) + xs;

    return val;
}

double spline::cfy(lexer *p, dive *a, int ii, int jj, int kk)
{
    val=((ye-ys)/xdenom)*(p->XP[II] - xs) + ys;

    return val;
}

double spline::cfz(lexer *p, dive *a, int ii, int jj, int kk)
{
    val=p->ZP[KK];

    return val;
}

