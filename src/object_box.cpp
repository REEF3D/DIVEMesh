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

#include"box.h"
#include"lexer.h"
#include"dive.h"

box::box(lexer *p, int rank, int side) : eps(1.0e-5*p->dx)
{
    box_rank = rank;
    box_side = side;
    box_type = 10;

    xs = p->O10_xs[rank];
    xe = p->O10_xe[rank];

    ys = p->O10_ys[rank];
    ye = p->O10_ye[rank];

    zs = p->O10_zs[rank];
    ze = p->O10_ze[rank];	
    

    istart = p->posc_i(xs);
    iend = p->posc_i(xe);
    
    jstart = p->posc_j(ys);
    jend = p->posc_j(ye);
    
    kstart = p->posc_k(zs);
    kend = p->posc_k(ze);


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

box::~box()
{
}

void box::read(lexer *p, dive *a, int& rankcount)
{

}

double box::fx(lexer *p, dive *a, int ii, int jj, int kk)
{
    val=-1.0e20;

    return val;
}

double box::fy(lexer *p, dive *a, int ii, int jj, int kk)
{
    val=-1.0e20;

    return val;
}

double box::fz(lexer *p, dive *a, int ii, int jj, int kk)
{
    val=-1.0e20;

    return val;
}

double box::cfx(lexer *p, dive *a, int ii, int jj, int kk)
{
    val=-1.0e20;

    return val;
}

double box::cfy(lexer *p, dive *a, int ii, int jj, int kk)
{
    val=-1.0e20;

    return val;
}

double box::cfz(lexer *p, dive *a, int ii, int jj, int kk)
{
    val=-1.0e20;

    return val;
}

double box::xstart()
{
    return xs;
}

double box::xend()
{
    return xe;
}

double box::ystart()
{
    return ys;
}

double box::yend()
{
    return ye;
}

double box::zstart()
{
    return zs;
}

double box::zend()
{
    return ze;
}

int box::type()
{
    return box_type;
}

int box::rank()
{
    return box_rank;
}

int box::side()
{
    return box_side;
}

int box::neighbor1()
{
    return nb1;
}

int box::neighbor2()
{
    return nb2;
}

int box::xdir(int ii, int jj, int kk)
{
    return 0;
}

int box::ydir(int ii, int jj, int kk)
{
    return 0;
}

int box::zdir(int ii, int jj, int kk)
{
    return 0;
}

int box::inbound(int ii,int jj, int kk)
{
    int bound=1;

    return bound;
}

int box::inbound_onnode(int ii,int jj, int kk)
{
  
    int bound=1;

    return bound;
}

int box::flag_val(int ii, int jj, int kk)
{
    int ival=1;

	if(ii>=istart && ii<iend && jj>=jstart && jj<jend && kk>=kstart && kk<kend)
	ival=-21;
	
    return ival;
}
