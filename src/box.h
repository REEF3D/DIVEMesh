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
--------------------------------------------------------------------*/


#include"entity.h"
#include"increment.h"

class lexer;
class dive;

using namespace std;

#ifndef BOX_H_
#define BOX_H_

class box : public entity, public increment
{
public:
    box(lexer*,int,int);
    virtual ~box();

    virtual void read(lexer*,dive*,int&);

    virtual double fx(lexer*,dive*,int,int,int);
    virtual double fy(lexer*,dive*,int,int,int);
    virtual double fz(lexer*,dive*,int,int,int);

    virtual double cfx(lexer*,dive*,int,int,int);
    virtual double cfy(lexer*,dive*,int,int,int);
    virtual double cfz(lexer*,dive*,int,int,int);

    virtual double xstart();
    virtual double xend();
    virtual double ystart();
    virtual double yend();
    virtual double zstart();
    virtual double zend();

    virtual int xdir(int,int,int);
    virtual int ydir(int,int,int);
    virtual int zdir(int,int,int);

    virtual int inbound(int,int,int);
    virtual int inbound_onnode(int,int,int);

    virtual int flag_val(int,int,int);

    virtual int type();
    virtual int rank();
    virtual int side();

    virtual int neighbor1();
    virtual int neighbor2();

private:
    double xs,xe,ys,ye,zs,ze;
    double xsmall,xlarge,ysmall,ylarge,zsmall,zlarge;
    double xn,yn,zn,xc,yc,zc;
	int iend,istart,jend,jstart,kstart,kend;
    double signx, signy;
    double slope;
    int nb1,nb2;
    int box_type,box_side,box_rank;
    int box_xdir, box_ydir, box_zdir;

    double val, xdenom, ydenom;
    const double eps;
    int count;
};

#endif





/*
#include<iostream>
#include"field.h"
#include"lexer.h"
#include"resize.h"

class lexer;
class dive;

using namespace std;

#ifndef BOX_H_
#define BOX_H_

class box : public increment
{
public:
    box();
    virtual ~box();

    virtual void preproc(lexer*,dive*);
	virtual void flag(lexer*,dive*);
	virtual void ibm(lexer*,dive*);

private:
	int iend,istart,jend,jstart,kstart,kend;

};


#endif
*/
