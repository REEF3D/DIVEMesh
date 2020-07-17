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

#include"pipe_z_bl.h"
#include"lexer.h"
#include"dive.h"

pipe_z_bl::pipe_z_bl(lexer *pp, int rank, int side) : eps(1.0e-5*pp->dx), psi(1.0e-9*pp->dx)
{
    p=pp;
    
    pipe_z_bl_rank = rank;
    pipe_z_bl_side = side;
    pipe_z_bl_type = 31;

    ym=p->B33_ym[rank];
    xm=p->B33_xm[rank];
    r=p->B33_r[rank];

    xs = xm-r;
    xe = xm+r;

    ys = ym-r;
    ye = ym+r;

    zs = p->B33_zs[rank];
    ze = p->B33_ze[rank];

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

pipe_z_bl::~pipe_z_bl()
{
}

void pipe_z_bl::read(lexer *p, dive *a, int& rankcount)
{

}

double pipe_z_bl::fx(lexer *p, dive *a, int ii, int jj, int kk)
{

    xn = p->XN[II]-xm;
    yn = p->YN[JJ]-ym;

    if(xn>=0.0)
    signx=1.0;

    if(xn<0.0)
    signx=-1.0;

    root=r*r - yn*yn;
    root = root>=-psi?root:1.0e20;
	
	if(root>=-psi  && root<psi)
		root=0.0;

    val = signx*sqrt(root) + xm;

    return val;
}

double pipe_z_bl::fy(lexer *p, dive *a, int ii, int jj, int kk)
{
    xn = p->XN[II]-xm;
    yn = p->YN[JJ]-ym;

    if(yn>=0.0)
    signy=1.0;

    if(yn<0.0)
    signy=-1.0;

    root=r*r - xn*xn;
    root = root>=-psi?root:1.0e20;
	
	if(root>=-psi  && root<psi)
		root=0.0;

    val = signy*sqrt(root) + ym;

    return val;
}

double pipe_z_bl::fz(lexer *p, dive *a, int ii, int jj, int kk)
{
    val=p->ZN[KK];

    return val;
}

double pipe_z_bl::cfx(lexer *p, dive *a, int ii, int jj, int kk)
{
    xc = p->XP[II]-xm;
    yc = p->YP[JJ]-ym;

    if(xc>=0.0)
    signx=1.0;

    if(xc<0.0)
    signx=-1.0;

    root=r*r - yc*yc;
    root = root>=-psi?root:1.0e20;
	
	if(root>=-psi  && root<psi)
		root=0.0;

    val = signx*sqrt(root) + xm;

    return val;
}

double pipe_z_bl::cfy(lexer *p, dive *a, int ii, int jj, int kk)
{
    xc = p->XP[II]-xm;
    yc = p->YP[JJ]-ym;

    if(yc>=0.0)
    signy=1.0;

    if(yc<0.0)
    signy=-1.0;

    root=r*r - xc*xc;
    root = root>=-psi?root:1.0e20;
	
	if(root>=-psi  && root<psi)
		root=0.0;

    val = signy*sqrt(root) + ym;

    return val;
}

double pipe_z_bl::cfz(lexer *p, dive *a, int ii, int jj, int kk)
{
    val=p->ZP[KK];

    return val;
}

double pipe_z_bl::xstart()
{
    return xs;
}

double pipe_z_bl::xend()
{
    return xe;
}

double pipe_z_bl::ystart()
{
    return ys;
}

double pipe_z_bl::yend()
{
    return ye;
}

double pipe_z_bl::zstart()
{
    return zs;
}

double pipe_z_bl::zend()
{
    return ze;
}

int pipe_z_bl::type()
{
    return pipe_z_bl_type;
}

int pipe_z_bl::rank()
{
    return pipe_z_bl_rank;
}

int pipe_z_bl::side()
{
    return pipe_z_bl_side;
}

int pipe_z_bl::neighbor1()
{
    return nb1;
}

int pipe_z_bl::neighbor2()
{
    return nb2;
}

int pipe_z_bl::xdir(int ii, int jj, int kk)
{
    xn = p->XP[II];

    if(xn>=xm)
    pipe_z_bl_xdir=4;

    if(xn<xm)
    pipe_z_bl_xdir=1;

    return pipe_z_bl_xdir;
}

int pipe_z_bl::ydir(int ii, int jj, int kk)
{
    yn = p->YP[JJ];

    if(yn>=ym)
    pipe_z_bl_ydir=2;

    if(yn<ym)
    pipe_z_bl_ydir=3;

    return pipe_z_bl_ydir;
}

int pipe_z_bl::zdir(int ii, int jj, int kk)
{
    pipe_z_bl_ydir=0;

    return pipe_z_bl_zdir;
}

int pipe_z_bl::inbound(int ii,int jj, int kk)
{
    int bound=1;

    return bound;
}

int pipe_z_bl::inbound_onnode(int ii,int jj, int kk)
{
    double rad[4];
    double x[4];
    double y[4];
    int bound=0;

    x[0] = p->XN[II]-xm;
    y[0] = p->YN[JJ]-ym;

    x[1] = p->XN[IIP1]-xm;
    y[1] = p->YN[JJ]-ym;

    x[2] = p->XN[IIP1]-xm;
    y[2] = p->YN[JJP1]-ym;

    x[3] = p->XN[II]-xm;
    y[3] = p->YN[JJP1]-ym;

    count=0;
    for(n=0;n<4;++n)
    {
    rad[n] = sqrt(x[n]*x[n] + y[n]*y[n]);

    if(rad[n]<=r+eps)
    ++count;
    }

    // cout<<ii<<" "<<jj<<"  "<<"RADIUS: "<<count<<"  "<<rad[0]<<"  "<<rad[1]<<"  "<<rad[2]<<"  "<<rad[3]<<endl;
    // cout<<y[0]+xm<<" "<<z[0]+ym<<" . "<<y[1]+xm<<" "<<z[1]+ym<<" . "<<y[2]+xm<<" "<<z[2]+ym<<" . "<<y[3]+xm<<" "<<z[3]+ym<<" . "<<endl<<endl;

    if(count==2 || count==3)
    bound=1;

    return bound;
}

int pipe_z_bl::flag_val(int ii, int jj, int kk)
{
    int ival=1;
    double rad;

    xc = p->XP[II]-xm;
    yc = p->YP[JJ]-ym;

    rad = sqrt(xc*xc + yc*yc);

    if(rad>=r)
    ival=-21;

    if(rad<r)
    ival=1;

    return ival;
}

