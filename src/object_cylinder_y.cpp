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

#include"cylinder_y.h"
#include"lexer.h"
#include"dive.h"

cylinder_y::cylinder_y(lexer *pp, int rank, int side) : eps(1.0e-5*pp->dx), psi(1.0e-9*pp->dx)
{
    p=pp;
    
    cylinder_y_rank = rank;
    cylinder_y_side = side;
    cylinder_y_type = 32;

    xm=p->O32_xm[rank];
    zm=p->O32_zm[rank];
    r=p->O32_r[rank];

    xs = xm-r;
    xe = xm+r;

    ys = -1.0e12;
    ye = 1.0e12;

    zs = zm-r;
    ze = zm+r;

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
}

cylinder_y::~cylinder_y()
{
}

void cylinder_y::read(lexer *p, dive *a, int& rankcount)
{

}

double cylinder_y::fx(lexer *p, dive *a, int ii, int jj, int kk)
{
    xn = p->XN[II]-xm;
    zn = p->ZN[KK]-zm;

    if(xn>=0.0)
    signx=1.0;

    if(xn<0.0)
    signx=-1.0;

    root=r*r - zn*zn;
    root = root>=-psi?root:1.0e20;
	
	if(root>=-psi  && root<psi)
		root=0.0;

    val = signx*sqrt(root) + xm;

    return val;
}

double cylinder_y::fy(lexer *p, dive *a, int ii, int jj, int kk)
{
    double rad;

    xc = p->XN[II]-xm;
    zc = p->ZN[KK]-zm;

    rad = sqrt(xc*xc + zc*zc);

    if(rad>=r-eps && rad<r+eps)
    val=p->YN[JJ];

    if(rad<r-eps || rad>=r+eps)
    val=ysmall-10.0;

    return val;
}

double cylinder_y::fz(lexer *p, dive *a, int ii, int jj, int kk)
{
    xn = p->XN[II]-xm;
    zn = p->ZN[KK]-zm;

    if(zn>=0.0)
    signz=1.0;

    if(zn<0.0)
    signz=-1.0;

    root=r*r - xn*xn;
    root = root>=-psi?root:1.0e20;
	
	if(root>=-psi  && root<psi)
		root=0.0;

    val = signz*sqrt(root) + zm;

    return val;
}

double cylinder_y::cfx(lexer *p, dive *a, int ii, int jj, int kk)
{
    xc = p->XP[II]-xm;
    zc = p->ZP[KK]-zm;

    if(xc>=0.0)
    signx=1.0;

    if(xc<0.0)
    signx=-1.0;

    root=r*r - zc*zc;
    root = root>=-psi?root:1.0e20;
	
	if(root>=-psi  && root<psi)
		root=0.0;

    val = signx*sqrt(root) + xm;

    return val;
}

double cylinder_y::cfy(lexer *p, dive *a, int ii, int jj, int kk)
{
    double rad;

    xc = p->XP[II]-xm;
    zc = p->ZP[KK]-zm;

    rad = sqrt(xc*xc + zc*zc);

    if(rad>=r-eps && rad<r+eps)
    val=p->YP[JJ];

    if(rad<r-eps || rad>=r+eps)
    val=ysmall-10.0;

    return val;
}

double cylinder_y::cfz(lexer *p, dive *a, int ii, int jj, int kk)
{
    xc = p->XP[II]-xm;
    zc = p->ZP[KK]-zm;

    if(zc>=0.0)
    signz=1.0;

    if(zc<0.0)
    signz=-1.0;

    root=r*r - xc*xc;
    root = root>=-psi?root:1.0e20;
	
	if(root>=-psi  && root<psi)
		root=0.0;

    val = signz*sqrt(root) + zm;

    return val;
}

double cylinder_y::xstart()
{
    return xs;
}

double cylinder_y::xend()
{
    return xe;
}

double cylinder_y::ystart()
{
    return ys;
}

double cylinder_y::yend()
{
    return ye;
}

double cylinder_y::zstart()
{
    return zs;
}

double cylinder_y::zend()
{
    return ze;
}

int cylinder_y::type()
{
    return cylinder_y_type;
}

int cylinder_y::rank()
{
    return cylinder_y_rank;
}

int cylinder_y::side()
{
    return cylinder_y_side;
}

int cylinder_y::neighbor1()
{
    return nb1;
}

int cylinder_y::neighbor2()
{
    return nb2;
}

int cylinder_y::xdir(int ii, int jj, int kk)
{
    xn = p->XP[II];

    if(xn>=xm)
    cylinder_y_xdir=1;

    if(xn<xm)
    cylinder_y_xdir=4;

    return cylinder_y_xdir;
}

int cylinder_y::ydir(int ii, int jj, int kk)
{
    cylinder_y_ydir=0;
    return cylinder_y_ydir;
}

int cylinder_y::zdir(int ii, int jj, int kk)
{
    zn = p->ZP[KK];

    if(zn>=zm)
    cylinder_y_zdir=5;

    if(zn<zm)
    cylinder_y_zdir=6;

    return cylinder_y_zdir;
}

int cylinder_y::inbound(int ii,int jj, int kk)
{
    //double posx,posy,posz;
    int bound=1;
/*
    posx = p->XP[II];
    posy = p->YP[JJ];
    posz = p->ZP[KK];

    if(posx<xsmall || posx>xlarge || posy<ysmall || posy>ylarge || posz<zsmall || posz>zlarge)
    bound=0;
*/
    return bound;
}

int cylinder_y::inbound_onnode(int ii,int jj, int kk)
{
    double rad[4];
    double x[4];
    double z[4];
    int bound=0;

    x[0] = p->XN[II]-xm;
    z[0] = p->ZN[KK]-zm;

    x[1] = p->XN[IIP1]-xm;
    z[1] = p->ZN[KK]-zm;

    x[2] = p->XN[IIP1]-xm;
    z[2] = p->ZN[KKP1]-zm;

    x[3] = p->XN[II]-xm;
    z[3] = p->ZN[KKP1]-zm;

    count=0;
    for(n=0;n<4;++n)
    {
    rad[n] = sqrt(x[n]*x[n] + z[n]*z[n]);

    if(rad[n]<=r+eps)
    ++count;
    }

    if(count==2 || count==3)
    bound=1;
	

    return bound;
}

int cylinder_y::flag_val(int ii, int jj, int kk)
{
    int ival=1;
    double rad;

    xc = p->XP[II]-xm;
    zc = p->ZP[KK]-zm;

    rad = sqrt(xc*xc + zc*zc);

    if(rad<r)
    ival=-21;

    return ival;
}
