/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2023 Hans Bihs

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

#include"box_bl.h"
#include"lexer.h"
#include"dive.h"

box_bl::box_bl(lexer *p, int rank, int side) : eps(1.0e-5*p->dx), psi(1.0e-9*p->dx)
{
    box_bl_rank = rank;
    box_bl_side = side;
    box_bl_type = 10;

    xs = p->B10_xs[rank];
    xe = p->B10_xe[rank];

    ys = p->B10_ys[rank];
    ye = p->B10_ye[rank];

    zs = p->B10_zs[rank];
    ze = p->B10_ze[rank];
    
    
    istart = p->posc_i(xs);
    iend   = p->posc_i(xe);
    
    jstart = p->posc_j(ys);
    jend   = p->posc_j(ye);

    kstart = p->posc_k(zs);
    kend   = p->posc_k(ze);
    

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

box_bl::~box_bl()
{
}

void box_bl::read(lexer *p, dive *a, int& rankcount)
{
}

double box_bl::fx(lexer *p, dive *a, int ii, int jj, int kk)
{
    val=-1.0e20;

    return val;
}

double box_bl::fy(lexer *p, dive *a, int ii, int jj, int kk)
{
    val=-1.0e20;

    return val;
}

double box_bl::fz(lexer *p, dive *a, int ii, int jj, int kk)
{
    val=-1.0e20;

    return val;
}

double box_bl::cfx(lexer *p, dive *a, int ii, int jj, int kk)
{
    val=-1.0e20;

    return val;
}

double box_bl::cfy(lexer *p, dive *a, int ii, int jj, int kk)
{
    val=-1.0e20;

    return val;
}

double box_bl::cfz(lexer *p, dive *a, int ii, int jj, int kk)
{
    val=-1.0e20;

    return val;
}

double box_bl::xstart()
{
    return xs;
}

double box_bl::xend()
{
    return xe;
}

double box_bl::ystart()
{
    return ys;
}

double box_bl::yend()
{
    return ye;
}

double box_bl::zstart()
{
    return zs;
}

double box_bl::zend()
{
    return ze;
}

int box_bl::type()
{
    return box_bl_type;
}

int box_bl::rank()
{
    return box_bl_rank;
}

int box_bl::side()
{
    return box_bl_side;
}

int box_bl::neighbor1()
{
    return nb1;
}

int box_bl::neighbor2()
{
    return nb2;
}

int box_bl::xdir(int ii, int jj, int kk)
{
    return 0;
}

int box_bl::ydir(int ii, int jj, int kk)
{
    return 0;
}

int box_bl::zdir(int ii, int jj, int kk)
{
    return 0;
}

int box_bl::inbound(int ii,int jj, int kk)
{
    int bound=1;

    return bound;
}

int box_bl::inbound_onnode(int ii,int jj, int kk)
{
    int bound=1;

    return bound;
}

int box_bl::flag_val(int ii, int jj, int kk)
{
    int ival=-21;

	if(ii>=istart && ii<iend && jj>=jstart && jj<jend && kk>=kstart && kk<kend)
	ival=1;
	
    return ival;
}


