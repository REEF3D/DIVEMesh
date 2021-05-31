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

#include"sphere_bl.h"
#include"lexer.h"
#include"dive.h"

sphere_bl::sphere_bl(lexer *pp, int rank, int side) : eps(1.0e-9), psi(1.0e-9*pp->dx)
{
    p=pp;

    sphere_bl_rank = rank;
    sphere_bl_side = side;
    sphere_bl_type = 21;

    xm=p->B22_xm[rank];
    ym=p->B22_ym[rank];
    zm=p->B22_zm[rank];
    r=p->B22_r[rank];

    xs = xm-r;
    xe = xm+r;

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

sphere_bl::~sphere_bl()
{
}

void sphere_bl::read(lexer *p, dive *a, int& rankcount)
{
}

double sphere_bl::fx(lexer *p, dive *a, int ii, int jj, int kk)
{
    xn = p->XN[II]-xm;
    yn = p->YN[JJ]-ym;
    zn = p->ZN[KK]-zm;

    if(xn>=0.0)
    signx=1.0;

    if(xn<0.0)
    signx=-1.0;

    root=r*r - yn*yn - zn*zn;
	root = root>=-psi?root:1.0e20;

	if(root>=-psi  && root<psi)
		root=0.0;


    val = signx*sqrt(root) + xm;

    return val;
}

double sphere_bl::fy(lexer *p, dive *a, int ii, int jj, int kk)
{
    xn = p->XN[II]-xm;
    yn = p->YN[JJ]-ym;
    zn = p->ZN[KK]-zm;

    if(yn>=0.0)
    signy=1.0;

    if(yn<0.0)
    signy=-1.0;

    root=r*r - xn*xn - zn*zn;
    root = root>=-psi?root:1.0e20;

	if(root>=-psi  && root<psi)
		root=0.0;

    val = signy*sqrt(root) + ym;

    return val;
}

double sphere_bl::fz(lexer *p, dive *a, int ii, int jj, int kk)
{
    xn = p->XN[II]-xm;
    yn = p->YN[JJ]-ym;
    zn = p->ZN[KK]-zm;

    if(zn>=0.0)
    signz=1.0;

    if(zn<0.0)
    signz=-1.0;

    root=r*r - xn*xn - yn*yn;
    root = root>=-psi?root:1.0e20;

	if(root>=-psi  && root<psi)
		root=0.0;


    val = signz*sqrt(root) + zm;

    return val;
}

double sphere_bl::cfx(lexer *p, dive *a, int ii, int jj, int kk)
{
    xc = p->XP[II]-xm;
    yc = p->YP[JJ]-ym;
    zc = p->ZP[KK]-zm;

    if(xc>=0.0)
    signx=1.0;

    if(xc<0.0)
    signx=-1.0;

    root=r*r - yc*yc -zc*zc;
    root = root>=-psi?root:1.0e20;

	if(root>=-psi  && root<psi)
		root=0.0;


    val = signx*sqrt(root) + xm;

    return val;
}

double sphere_bl::cfy(lexer *p, dive *a, int ii, int jj, int kk)
{
    xc = p->XP[II]-xm;
    yc = p->YP[JJ]-ym;
    zc = p->ZP[KK]-zm;

    if(yc>=0.0)
    signy=1.0;

    if(yc<0.0)
    signy=-1.0;

    root=r*r - xc*xc -zc*zc;
    root = root>=-psi?root:1.0e20;

	if(root>=-psi  && root<psi)
		root=0.0;


    val = signy*sqrt(root) + ym;

    return val;
}

double sphere_bl::cfz(lexer *p, dive *a, int ii, int jj, int kk)
{
    xc = p->XP[II]-xm;
    yc = p->YP[JJ]-ym;
    zc = p->ZP[KK]-zm;

    if(zc>=0.0)
    signy=1.0;

    if(zc<0.0)
    signy=-1.0;

    root=r*r - xc*xc -yc*yc;
    root = root>=-psi?root:1.0e20;

	if(root>=-psi  && root<psi)
		root=0.0;


    val = signy*sqrt(root) + zm;

    return val;
}

double sphere_bl::xstart()
{
    return xs;
}

double sphere_bl::xend()
{
    return xe;
}

double sphere_bl::ystart()
{
    return ys;
}

double sphere_bl::yend()
{
    return ye;
}

double sphere_bl::zstart()
{
    return zs;
}

double sphere_bl::zend()
{
    return ze;
}

int sphere_bl::type()
{
    return sphere_bl_type;
}

int sphere_bl::rank()
{
    return sphere_bl_rank;
}

int sphere_bl::side()
{
    return sphere_bl_side;
}

int sphere_bl::neighbor1()
{
    return nb1;
}

int sphere_bl::neighbor2()
{
    return nb2;
}

int sphere_bl::xdir(int ii, int jj, int kk)
{
    xn = p->XP[II];

    if(xn>=xm)
    sphere_bl_xdir=4;

    if(xn<xm)
    sphere_bl_xdir=1;

    return sphere_bl_xdir;
}

int sphere_bl::ydir(int ii, int jj, int kk)
{
    yn = p->YP[JJ];

    if(yn>=ym)
    sphere_bl_ydir=2;

    if(yn<ym)
    sphere_bl_ydir=3;

    return sphere_bl_ydir;
}

int sphere_bl::zdir(int ii, int jj, int kk)
{
    zn = p->ZP[KK];

    if(zn>=zm)
    sphere_bl_zdir=6;

    if(zn<zm)
    sphere_bl_zdir=5;

    return sphere_bl_zdir;
}

int sphere_bl::inbound(int ii,int jj, int kk)
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

int sphere_bl::inbound_onnode(int ii,int jj, int kk)
{
    double rad[8];
    double x[8];
    double y[8];
    double z[8];
    int bound=0;

    x[0] = p->XN[II]-xm;
    y[0] = p->YN[JJ]-ym;
    z[0] = p->ZN[KK]-zm;

    x[1] = p->XN[IIP1]-xm;
    y[1] = p->YN[JJ]-ym;
    z[1] = p->ZN[KK]-zm;

    x[2] = p->XN[IIP1]-xm;
    y[2] = p->YN[JJP1]-ym;
    z[2] = p->ZN[KK]-zm;

    x[3] = p->XN[II]-xm;
    y[3] = p->YN[JJP1]-ym;
    z[3] = p->ZN[KK]-zm;


    x[4] = p->XN[II]-xm;
    y[4] = p->YN[JJ]-ym;
    z[4] = p->ZN[KKP1]-zm;

    x[5] = p->XN[IIP1]-xm;
    y[5] = p->YN[JJ]-ym;
    z[5] = p->ZN[KKP1]-zm;

    x[6] = p->XN[IIP1]-xm;
    y[6] = p->YN[JJP1]-ym;
    z[6] = p->ZN[KKP1]-zm;

    x[7] = p->XN[II]-xm;
    y[7] = p->YN[JJP1]-ym;
    z[7] = p->ZN[KKP1]-zm;

    count=0;
    for(n=0;n<8;++n)
    {
    rad[n] = sqrt(x[n]*x[n] + y[n]*y[n] + z[n]*z[n]);

    if(rad[n]<=r+eps)
    ++count;
    }

 /*
    cout<<ii<<" "<<jj<<" "<<kk<<" . "<<i<<" "<<j<<"  "<<k<<"  "<<"RADIUS: "<<count<<"  "<<rad[0]<<"  "<<rad[1]<<"  "<<rad[2]<<"  "<<rad[3]<<endl;
    cout<<x[0]+xm<<" "<<y[0]+ym<<" . "<<x[1]+xm<<" "<<y[1]+ym<<" . "<<x[2]+xm<<" "<<y[2]+ym<<" . "<<x[3]+xm<<" "<<y[3]+ym<<" . "<<endl<<endl;

*/
    if(count>=2 && count<8)
    bound=1;

    return bound;
}

int sphere_bl::flag_val(int ii, int jj, int kk)
{
    int ival=1;
    double rad;

    xc = p->XP[II]-xm;
    yc = p->YP[JJ]-ym;
    zc = p->ZP[KK]-zm;

    rad = sqrt(xc*xc + yc*yc + zc*zc);

    if(rad<=r)
    ival=1;

    if(rad>r)
    ival=-21;

    return ival;
}
