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

#include"wedge_x.h"
#include"lexer.h"
#include"dive.h"

wedge_x::wedge_x(lexer *pp, int rank, int side) :  eps(1.0e-5*pp->dx)
{
    p=pp;
    
    wedge_x_rank = rank;
    wedge_x_side = side;
    wedge_x_type = 61;

    xs = p->O61_xs[rank]-p->xmin;
    xe = p->O61_xe[rank]-p->xmin;

    ys = p->O61_ys[rank]-p->ymin;
    ye = p->O61_ye[rank]-p->ymin;

    zs = p->O61_zs[rank]-p->zmin;
    ze = p->O61_ze[rank]-p->zmin;

    slope=(ze-zs)/(xe-xs);

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
    wedge_x_xdir=4;
    wedge_x_zdir=5;
    }

    if(ze<zs)
    {
    zsmall=ze;
    zlarge=zs;
    wedge_x_xdir=1;
    wedge_x_zdir=5;
    }

    wedge_x_ydir=0;
}

wedge_x::~wedge_x()
{
}

void wedge_x::read(lexer *p, dive *a, int& rankcount)
{
}

double wedge_x::fx(lexer *p, dive *a, int ii, int jj, int kk)
{
    zn = p->ZN[KK];

    val = (1.0/slope)*(zn-zs) + xs;

    return val;
}

double wedge_x::fy(lexer *p, dive *a, int ii, int jj, int kk)
{
    val=p->YN[JJ];

    val=-1000.0;

    return val;
}

double wedge_x::fz(lexer *p, dive *a, int ii, int jj, int kk)
{
    xn = p->XN[II];

    val = slope*(xn-xs) + zs;

    return val;
}

double wedge_x::cfx(lexer *p, dive *a, int ii, int jj, int kk)
{
	zc = p->ZP[KK];

    val = (1.0/slope)*(zc-zs) + xs;

    return val;
}

double wedge_x::cfy(lexer *p, dive *a, int ii, int jj, int kk)
{
     val=p->YP[JJ];

    return val;
}

double wedge_x::cfz(lexer *p, dive *a, int ii, int jj, int kk)
{
    xc = p->XP[II];

    val = slope*(xc-xs) + zs;

    return val;
}

double wedge_x::xstart()
{
    return xs;
}

double wedge_x::xend()
{
    return xe;
}

double wedge_x::ystart()
{
    return ys;
}

double wedge_x::yend()
{
    return ye;
}

double wedge_x::zstart()
{
    return zs;
}

double wedge_x::zend()
{
    return ze;
}

int wedge_x::type()
{
    return wedge_x_type;
}

int wedge_x::rank()
{
    return wedge_x_rank;
}

int wedge_x::side()
{
    return wedge_x_side;
}

int wedge_x::neighbor1()
{
    return nb1;
}

int wedge_x::neighbor2()
{
    return nb2;
}

int wedge_x::xdir(int ii, int jj, int kk)
{

    return wedge_x_xdir;
}

int wedge_x::ydir(int ii, int jj, int kk)
{

    return wedge_x_ydir;
}

int wedge_x::zdir(int ii, int jj, int kk)
{
    return wedge_x_zdir;
}

int wedge_x::inbound(int ii,int jj, int kk)
{
    int bound=1;
    return bound;
}

int wedge_x::inbound_onnode(int ii,int jj, int kk)
{
    double xval,zval;
    int bound=0;

    xc = p->XP[II];
    zc = p->ZP[KK];

    xn = p->XN[II];
    zn = p->ZN[KK];

    zval = slope*(xc-xs) + zs;
    xval = (1.0/slope)*(zc-zs) + xs;

    if((xval>=xn && xval<xn+p->DX[ii]) || (zval>=zn && zval<zn+p->DZ[kk]))
    if(xval>=xsmall && xval<xlarge)
    if(zval>=zsmall && zval<zlarge)
    bound=1;

    return bound;
}

int wedge_x::flag_val(int ii, int jj, int kk)
{
    int ival=1;

    xc = p->XP[II];
    yc = p->YP[JJ];
    zc = p->ZP[KK];

    if( xc>=xs && xc<xe
    &&yc>=ys && yc<ye
    &&zc>=zsmall && zc< slope*(xc-xs) + zs)
    ival=-21;

    return ival;
}

