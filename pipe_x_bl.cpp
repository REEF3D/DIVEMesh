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

#include"pipe_x_bl.h"
#include"lexer.h"
#include"dive.h"

pipe_x_bl::pipe_x_bl(lexer *pp, int rank, int side) : eps(1.0e-5*pp->dx), psi(1.0e-9*pp->dx)
{
    p=pp;
    
    pipe_x_bl_rank = rank;
    pipe_x_bl_side = side;
    pipe_x_bl_type = 31;

    ym=p->B31_ym[rank]-p->ymin;
    zm=p->B31_zm[rank]-p->zmin;
    r=p->B31_r[rank];

    xs = p->B31_xs[rank];
    xe = p->B31_xe[rank];

    ys = ym-r;
    ye = ym+r;

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

pipe_x_bl::~pipe_x_bl()
{
}

void pipe_x_bl::read(lexer *p, dive *a, int& rankcount)
{
}

double pipe_x_bl::fx(lexer *p, dive *a, int ii, int jj, int kk)
{
    double rad;

    yc = p->YN[JJ]-ym;
    zc = p->ZN[KK]-zm;

    rad = sqrt(yc*yc + zc*zc);

    if(rad>=r-eps && rad<r+eps)
    val=p->XN[II];

    if(rad<r-eps || rad>=r+eps)
    val=xsmall-10.0;

    return val;
}

double pipe_x_bl::fy(lexer *p, dive *a, int ii, int jj, int kk)
{
    yn = p->YN[JJ]-ym;
    zn = p->ZN[KK]-zm;

    if(yn>=0.0)
    signy=1.0;

    if(yn<0.0)
    signy=-1.0;

    root = root>=-psi?root:1.0e20;
	
	if(root>=-psi  && root<psi)
		root=0.0;
		
    root = root>0.0?root:0.0;

    val = signy*sqrt(root) + ym;

    return val;
}

double pipe_x_bl::fz(lexer *p, dive *a, int ii, int jj, int kk)
{
    yn = p->YN[JJ]-ym;
    zn = p->ZN[KK]-zm;

    if(zn>=0.0)
    signz=1.0;

    if(zn<0.0)
    signz=-1.0;

    root = root>=-psi?root:1.0e20;
	
	if(root>=-psi  && root<psi)
		root=0.0;
		
    root = root>0.0?root:0.0;

    val = signz*sqrt(root) + zm;

    return val;
}

double pipe_x_bl::cfx(lexer *p, dive *a, int ii, int jj, int kk)
{
    double rad;

    yc = p->YP[JJ]-ym;
    zc = p->ZP[KK]-zm;

    rad = sqrt(yc*yc + zc*zc);

    if(rad>=r-eps && rad<r+eps)
    val=p->XP[II];

    if(rad<r-eps || rad>=r+eps)
    val=xsmall-10.0;

    return val;
}

double pipe_x_bl::cfy(lexer *p, dive *a, int ii, int jj, int kk)
{
    yc = p->YP[JJ]-ym;
    zc = p->ZP[KK]-zm;

    if(yc>=0.0)
    signy=1.0;

    if(yc<0.0)
    signy=-1.0;

    root=r*r - zc*zc;
    root = root>=-psi?root:1.0e20;
	
	if(root>=-psi  && root<psi)
		root=0.0;

    val = signy*sqrt(root) + ym;

    return val;
}

double pipe_x_bl::cfz(lexer *p, dive *a, int ii, int jj, int kk)
{
    yc = p->YP[JJ]-ym;
    zc = p->ZP[KK]-zm;

    if(zc>=0.0)
    signz=1.0;

    if(zc<0.0)
    signz=-1.0;

    root=r*r - yc*yc;
    root = root>=-psi?root:1.0e20;
	
	if(root>=-psi  && root<psi)
		root=0.0;

    val = signz*sqrt(root) + zm;

    return val;
}

double pipe_x_bl::xstart()
{
    return xs;
}

double pipe_x_bl::xend()
{
    return xe;
}

double pipe_x_bl::ystart()
{
    return ys;
}

double pipe_x_bl::yend()
{
    return ye;
}

double pipe_x_bl::zstart()
{
    return zs;
}

double pipe_x_bl::zend()
{
    return ze;
}

int pipe_x_bl::type()
{
    return pipe_x_bl_type;
}

int pipe_x_bl::rank()
{
    return pipe_x_bl_rank;
}

int pipe_x_bl::side()
{
    return pipe_x_bl_side;
}

int pipe_x_bl::neighbor1()
{
    return nb1;
}

int pipe_x_bl::neighbor2()
{
    return nb2;
}

int pipe_x_bl::xdir(int ii, int jj, int kk)
{
    pipe_x_bl_xdir=0;
    return pipe_x_bl_xdir;
}

int pipe_x_bl::ydir(int ii, int jj, int kk)
{
    yn = p->YP[JJ];

    if(yn>=ym)
    pipe_x_bl_ydir=2;

    if(yn<ym)
    pipe_x_bl_ydir=3;

    return pipe_x_bl_ydir;
}

int pipe_x_bl::zdir(int ii, int jj, int kk)
{
    zn = p->ZP[KK];

    if(zn>=zm)
    pipe_x_bl_zdir=6;

    if(zn<zm)
    pipe_x_bl_zdir=5;

    return pipe_x_bl_zdir;
}

int pipe_x_bl::inbound(int ii,int jj, int kk)
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

int pipe_x_bl::inbound_onnode(int ii,int jj, int kk)
{
    double rad[4];
    double y[4];
    double z[4];
    int bound=0;

    y[0] = p->YN[JJ]-ym;
    z[0] = p->ZN[KK]-zm;

    y[1] = p->YN[JJP1]-ym;
    z[1] = p->ZN[KK]-zm;

    y[2] = p->YN[JJP1]-ym;
    z[2] = p->ZN[KKP1]-zm;

    y[3] = p->YN[JJ]-ym;
    z[3] = p->ZN[KKP1]-zm;

    count=0;
    for(n=0;n<4;++n)
    {
    rad[n] = sqrt(y[n]*y[n] + z[n]*z[n]);

    if(rad[n]<=r+eps)
    ++count;
    }

    if(count==2 || count==3)
    bound=1;

    return bound;
}

int pipe_x_bl::flag_val(int ii, int jj, int kk)
{
    int ival=1;
    double rad;

    xc = p->XP[II];
    yc = p->YP[JJ]-ym;
    zc = p->ZP[KK]-zm;

    rad = sqrt(yc*yc + zc*zc);

    if(rad>=r)
    ival=-21;

    if(rad<r)
    ival=1;

    if(xc<=xsmall-p->DX[ii]-eps && xc>=xlarge+p->DX[ii]+eps)
    ival=-21;

    return ival;
}

