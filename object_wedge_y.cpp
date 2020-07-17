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

#include"wedge_y.h"
#include"lexer.h"
#include"dive.h"

wedge_y::wedge_y(lexer *pp, int rank, int side) : eps(1.0e-5*pp->dx)
{
    p=pp;
    
    wedge_y_rank = rank;
    wedge_y_side = side;
    wedge_y_type = 62;

    xs = p->O62_xs[rank];
    xe = p->O62_xe[rank];

    ys = p->O62_ys[rank];
    ye = p->O62_ye[rank];

    zs = p->O62_zs[rank];
    ze = p->O62_ze[rank];

    slope=(ze-zs)/(ye-ys);

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
    wedge_y_ydir=2;
    wedge_y_zdir=5;
    }

    if(ze<zs)
    {
    zsmall=ze;
    zlarge=zs;
    wedge_y_ydir=3;
    wedge_y_zdir=5;
    }

    wedge_y_xdir=0;
}

wedge_y::~wedge_y()
{
}

void wedge_y::read(lexer *p, dive *a, int& rankcount)
{
}

double wedge_y::fx(lexer *p, dive *a, int ii, int jj, int kk)
{
    val=p->XN[II];

    val=-1000.0;

    return val;
}

double wedge_y::fy(lexer *p, dive *a, int ii, int jj, int kk)
{
	zn = p->ZN[KK];

    val = (1.0/slope)*(zn-zs) + ys;

    return val;
}

double wedge_y::fz(lexer *p, dive *a, int ii, int jj, int kk)
{
    yn = p->YN[JJ];

    val = slope*(yn-ys) + zs;

    return val;
}

double wedge_y::cfx(lexer *p, dive *a, int ii, int jj, int kk)
{
	val=p->XP[II];

    return val;
}

double wedge_y::cfy(lexer *p, dive *a, int ii, int jj, int kk)
{
    zc = p->ZP[KK];

    val = (1.0/slope)*(zc-zs) + ys;

    return val;
}

double wedge_y::cfz(lexer *p, dive *a, int ii, int jj, int kk)
{
    yc = p->YP[JJ];

    val = slope*(yc-ys) + zs;

    return val;
}

double wedge_y::xstart()
{
    return xs;
}

double wedge_y::xend()
{
    return xe;
}

double wedge_y::ystart()
{
    return ys;
}

double wedge_y::yend()
{
    return ye;
}

double wedge_y::zstart()
{
    return zs;
}

double wedge_y::zend()
{
    return ze;
}

int wedge_y::type()
{
    return wedge_y_type;
}

int wedge_y::rank()
{
    return wedge_y_rank;
}

int wedge_y::side()
{
    return wedge_y_side;
}

int wedge_y::neighbor1()
{
    return nb1;
}

int wedge_y::neighbor2()
{
    return nb2;
}

int wedge_y::xdir(int ii, int jj, int kk)
{

    return wedge_y_xdir;
}

int wedge_y::ydir(int ii, int jj, int kk)
{

    return wedge_y_ydir;
}

int wedge_y::zdir(int ii, int jj, int kk)
{
    return wedge_y_zdir;
}

int wedge_y::inbound(int ii,int jj, int kk)
{
    int bound=1;
    return bound;
}

int wedge_y::inbound_onnode(int ii,int jj, int kk)
{
    double yval,zval;
    int bound=0;

    yc = p->YP[JJ];
    zc = p->ZP[KK];

    yn = p->YN[JJ];
    zn = p->ZN[KK];

    zval = slope*(yc-ys) + zs;
    yval = (1.0/slope)*(zc-zs) + ys;

    if((yval>=yn && yval<yn+p->DY[jj]) || (zval>=zn && zval<zn+p->DZ[kk]))
    if(yval>=ysmall && yval<ylarge)
    if(zval>=zsmall && zval<zlarge)
    bound=1;

    return bound;
}

int wedge_y::flag_val(int ii, int jj, int kk)
{
    int ival=1;

    xc = p->XP[II];
    yc = p->YP[JJ];
    zc = p->ZP[KK];

    if( xc>=xs && xc<xe
    &&  yc>=ys && yc<ye
    &&  zc>=zsmall && zc< slope*(yc-ys) + zs)
    ival=-21;

    return ival;
}

