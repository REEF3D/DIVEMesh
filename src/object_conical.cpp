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

#include"conical.h"
#include"lexer.h"
#include"dive.h"

conical::conical(lexer *pp, int rank, int side) : eps(1.0e-3*pp->dx), psi(1.0e-9*pp->dx)
{
    p=pp;
    
	cout<<"conical"<<endl;
    conical_rank = rank;
    conical_side = side;
    conical_type = 43;
	

    xm=p->O43_xm[rank];
    ym=p->O43_ym[rank];
	
	z1=p->O43_z1[rank];
	z2=p->O43_z2[rank];
	
    r1=p->O43_r1[rank];
	r2=p->O43_r2[rank];
	
	rmin = MIN(r1,r2);
	rmax = MAX(r1,r2);

    xs = xm-rmax;
    xe = xm+rmax;

    ys = ym-rmax;
    ye = ym+rmax;

    zs = z1;
    ze = z2;

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

    conical_zdir=0;
}

conical::~conical()
{
}

void conical::read(lexer *p, dive *a, int& rankcount)
{

}

double conical::fx(lexer *p, dive *a, int ii, int jj, int kk)
{

    xn = p->XN[II]-xm;
    yn = p->YN[JJ]-ym;
	zn = p->ZN[KK];
	
	r = ((r2-r1)/(z2-z1))*zn + r1; 

    if(xn>=0.0)
    signx=1.0;

    if(xn<0.0)
    signx=-1.0;

    root=r*r - yn*yn;
    root = root>=0.0?root:1.0e20;
	

    val = signx*sqrt(root) + xm;
	

    return val;
}

double conical::fy(lexer *p, dive *a, int ii, int jj, int kk)
{
    xn = p->XN[II]-xm;
    yn = p->YN[JJ]-ym;
	zn = p->ZN[KK];
	
	r = ((r2-r1)/(z2-z1))*zn + r1; 

    if(yn>=0.0)
    signy=1.0;

    if(yn<0.0)
    signy=-1.0;

    root=r*r - xn*xn;
    root = root>=0.0?root:1.0e20;
	

    val = signy*sqrt(root) + ym;
	

    return val;
}

double conical::fz(lexer *p, dive *a, int ii, int jj, int kk)
{
	xc = p->XN[II]-xm;
    yc = p->YN[JJ]-ym;

	d =  sqrt(xc*xc + yc*yc) -r2;
	
	val = z2 - d*(fabs(z2-z1)/fabs(r2-r1));
	
	if(val<zsmall-p->DZ[KM1] || val>zlarge+p->DZ[KP1])
	val=1.0e20;

    return val;
}

double conical::cfx(lexer *p, dive *a, int ii, int jj, int kk)
{
    xc = p->XP[II]-xm;
    yc = p->YP[JJ]-ym;
	zc = p->ZP[KK];
	
	r = ((r2-r1)/(z2-z1))*zn + r1; 

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

double conical::cfy(lexer *p, dive *a, int ii, int jj, int kk)
{
    xc = p->XP[II]-xm;
    yc = p->YP[JJ]-ym;
	zc = p->ZP[KK];
	
	r = ((r2-r1)/(z2-z1))*zn + r1; 

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

double conical::cfz(lexer *p, dive *a, int ii, int jj, int kk)
{
    xc = p->XP[II]-xm;
    yc = p->YP[JJ]-ym;

	d =  sqrt(xc*xc + yc*yc) - r2;
	
	val = z2 - d*(fabs(z2-z1)/fabs(r2-r1));

    return val;
}

double conical::xstart()
{
    return xs;
}

double conical::xend()
{
    return xe;
}

double conical::ystart()
{
    return ys;
}

double conical::yend()
{
    return ye;
}

double conical::zstart()
{
    return zs;
}

double conical::zend()
{
	double ze_val = ze;
	
    return ze_val;
}

int conical::type()
{
    return conical_type;
}

int conical::rank()
{
    return conical_rank;
}

int conical::side()
{
    return conical_side;
}

int conical::neighbor1()
{
    return nb1;
}

int conical::neighbor2()
{
    return nb2;
}

int conical::xdir(int ii, int jj, int kk)
{
    xn = p->XP[II];

    if(xn>=xm)
    conical_xdir=1;

    if(xn<xm)
    conical_xdir=4;

    return conical_xdir;
}

int conical::ydir(int ii, int jj, int kk)
{
    yn = p->YP[JJ];

    if(yn>=ym)
    conical_ydir=3;

    if(yn<ym)
    conical_ydir=2;

    return conical_ydir;
}

int conical::zdir(int ii, int jj, int kk)
{
	
	if(r1==r2)
    conical_zdir=0;
	
    if(r1>r2)
    conical_zdir=5;

    if(r1<r2)
    conical_zdir=6;

    return conical_zdir;
}

int conical::inbound(int ii,int jj, int kk)
{
	int bound=1;
	
    xc = p->XP[II];
    yc = p->YP[JJ];
	zc = p->ZP[KK];
	
	if(zc>ze || zc<zs)
	bound=0;
	
    return bound;
}

int conical::inbound_onnode(int ii,int jj, int kk)
{
    double rad[8];
    double x[8];
    double y[8];
	double z[8];
    int bound=0;

    x[0] = p->XN[II]-xm;
    y[0] = p->YN[JJ]-ym;
    z[0] = p->ZN[KK];

    x[1] = p->XN[IIP1]-xm;
    y[1] = p->YN[JJ]-ym;
    z[1] = p->ZN[KK];

    x[2] = p->XN[IIP1]-xm;
    y[2] = p->YN[JJ]-ym;
    z[2] = p->ZN[KK];

    x[3] = p->XN[II]-xm;
    y[3] = p->YN[JJP1]-ym;
    z[3] = p->ZN[KK];


    x[4] = p->XN[II]-xm;
    y[4] = p->YN[JJ]-ym;
    z[4] = p->ZN[KKP1];

    x[5] = p->XN[IIP1]-xm;
    y[5] = p->YN[JJ]-ym;
    z[5] = p->ZN[KKP1];

    x[6] = p->XN[IIP1]-xm;
    y[6] = p->YN[JJP1]-ym;
    z[6] = p->ZN[KKP1];

    x[7] = p->XN[II]-xm;
    y[7] = p->YN[JJP1]-ym;
    z[7] = p->ZN[KKP1];


    count=0;
    for(n=0;n<8;++n)
    {
	r = ((r2-r1)/(z2-z1))*z[n] + r1; 
	
    rad[n] = sqrt(x[n]*x[n] + y[n]*y[n]);

    if(rad[n]<=r+eps && z[n]<=ze+eps && z[n]>=zs-eps)
    ++count;
    }

    if(count>=2 && count<8)
    bound=1;
	
	if(kk>4)
	bound=0;

    return bound;
}

int conical::flag_val(int ii, int jj, int kk)
{
    int ival=1;
    double rad;

    xc = p->XP[II]-xm;
    yc = p->YP[JJ]-ym;
	zc = p->ZP[KK];
	
	r = ((r2-r1)/(z2-z1))*zc + r1; 
	
    rad = sqrt(xc*xc + yc*yc);

    if(rad<r && zc>=z1 && zc<z2)
    ival=-21;

    return ival;
}
