/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2018 Hans Bihs

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

#include"pipe_y_bl.h"
#include"lexer.h"
#include"dive.h"

pipe_y_bl::pipe_y_bl(lexer *pp, int rank, int side) : eps(1.0e-5*pp->dx), psi(1.0e-9*pp->dx)
{
    p = pp;
    
    pipe_y_bl_rank = rank;
    pipe_y_bl_side = side;
    pipe_y_bl_type = 32;

    xm=p->B32_xm[rank]-p->xmin;
    zm=p->B32_zm[rank]-p->zmin;
    r=p->B32_r[rank];

    ys = p->B32_ys[rank];
    ye = p->B32_ye[rank];

    xs = xm-r;
    xe = xm+r;

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

pipe_y_bl::~pipe_y_bl()
{
}

void pipe_y_bl::read(lexer *p, dive *a, int& rankcount)
{
}

double pipe_y_bl::fx(lexer *p, dive *a, int ii, int jj, int kk)
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

double pipe_y_bl::fy(lexer *p, dive *a, int ii, int jj, int kk)
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

double pipe_y_bl::fz(lexer *p, dive *a, int ii, int jj, int kk)
{
    xn = p->XN[II]-xm;
    zn = p->ZN[KK]-zm;

    if(zn>=0.0)
    signz=1.0;

    if(zn<0.0)
    signz=-1.0;

    root=r*r  - xn*xn;
    root = root>=-psi?root:1.0e20;
	
	if(root>=-psi  && root<psi)
		root=0.0;

    val = signz*sqrt(root) + zm;

    return val;
}

double pipe_y_bl::cfx(lexer *p, dive *a, int ii, int jj, int kk)
{
    xn = p->XP[II]-xm;
    zn = p->ZP[KK]-zm;

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

double pipe_y_bl::cfy(lexer *p, dive *a, int ii, int jj, int kk)
{
    double rad;

    xn = p->XP[II]-xm;
    zn = p->ZP[KK]-zm;

    rad = sqrt(xc*xc + zc*zc);

    if(rad>=r-eps && rad<r+eps)
    val=p->YP[JJ];

    if(rad<r-eps || rad>=r+eps)
    val=ysmall-10.0;

    return val;
}

double pipe_y_bl::cfz(lexer *p, dive *a, int ii, int jj, int kk)
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

double pipe_y_bl::xstart()
{
    return xs;
}

double pipe_y_bl::xend()
{
    return xe;
}

double pipe_y_bl::ystart()
{
    return ys;
}

double pipe_y_bl::yend()
{
    return ye;
}

double pipe_y_bl::zstart()
{
    return zs;
}

double pipe_y_bl::zend()
{
    return ze;
}

int pipe_y_bl::type()
{
    return pipe_y_bl_type;
}

int pipe_y_bl::rank()
{
    return pipe_y_bl_rank;
}

int pipe_y_bl::side()
{
    return pipe_y_bl_side;
}

int pipe_y_bl::neighbor1()
{
    return nb1;
}

int pipe_y_bl::neighbor2()
{
    return nb2;
}

int pipe_y_bl::xdir(int ii, int jj, int kk)
{
    xn = p->XP[II];

    if(xn>=xm)
    pipe_y_bl_xdir=4;

    if(xn<xm)
    pipe_y_bl_xdir=1;

    return pipe_y_bl_xdir;
}

int pipe_y_bl::ydir(int ii, int jj, int kk)
{
    pipe_y_bl_ydir=0;
    return pipe_y_bl_ydir;
}

int pipe_y_bl::zdir(int ii, int jj, int kk)
{
    zn = p->ZP[KK];

    if(zn>=zm)
    pipe_y_bl_zdir=6;

    if(zn<zm)
    pipe_y_bl_zdir=5;

    return pipe_y_bl_zdir;
}

int pipe_y_bl::inbound(int ii,int jj, int kk)
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

int pipe_y_bl::inbound_onnode(int ii,int jj, int kk)
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

int pipe_y_bl::flag_val(int ii, int jj, int kk)
{
    int ival=1;
    double rad;

    xc = p->XP[II]-xm;
    yc = p->YP[JJ];
    zc = p->ZP[KK]-zm;

    rad = sqrt(xc*xc + zc*zc);

    if(rad>=r)
    ival=-21;

    if(rad<r)
    ival=1;

    if(yc<=ysmall-p->DY[jj]-eps && yc>=ylarge+p->DY[jj]+eps)
    ival=-21;

    return ival;
}


