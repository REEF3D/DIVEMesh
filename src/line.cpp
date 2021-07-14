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

#include"line.h"
#include"lexer.h"
#include"dive.h"

line::line(lexer *pp, int rank, int side) : eps(1.0e-9)
{
    p=pp;
    
    line_rank = rank;
    line_side = side;
    line_type = 1;

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

    if(xe>xs || xe<xs)
    xdenom=xe-xs;

    if(ye>ys ||  ye<ys)
    ydenom=ye-ys;

    if((line_side==1 && ye>=ys) || (line_side==2 && ye<ys))
    line_xdir=1;

    if((line_side==1 && ye<ys) || (line_side==2 && ye>=ys))
    line_xdir=4;

    if((line_side==1 && xe>=xs) || (line_side==2 && xe<xs))
    line_ydir=2;

    if((line_side==1 && xe<xs) || (line_side==2 && xe>=xs))
    line_ydir=3;

    line_zdir=0;
}

line::~line()
{
}

void line::read(lexer *p, dive *a, int& rankcount)
{
}

double line::fx(lexer *p, dive *a, int ii, int jj, int kk)
{
    val=((xe-xs)/ydenom)*(p->YN[JJ] - ys) + xs;

    return val;
}

double line::fy(lexer *p, dive *a, int ii, int jj, int kk)
{
    val=((ye-ys)/xdenom)*(p->XN[II] - xs) + ys;

    return val;
}

double line::fz(lexer *p, dive *a, int ii, int jj, int kk)
{
    val=p->ZN[KK];

    return val;
}

double line::cfx(lexer *p, dive *a, int ii, int jj, int kk)
{
    val=((xe-xs)/ydenom)*(p->YP[JJ] - ys) + xs;

    return val;
}

double line::cfy(lexer *p, dive *a, int ii, int jj, int kk)
{
    val=((ye-ys)/xdenom)*(p->XP[II] - xs) + ys;

    return val;
}

double line::cfz(lexer *p, dive *a, int ii, int jj, int kk)
{
    val=p->ZP[KK];

    return val;
}

