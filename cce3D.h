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

#include<iostream>
#include<fstream>
#include"increment.h"

class lexer;
class dive;
class entity;

using namespace std;

#ifndef CCE3D_H_
#define CCE3D_H_

class cce3D : public increment
{
public:
    cce3D(lexer*,dive*);
    virtual ~cce3D();

    virtual void start(lexer*,dive*,entity*);

private:
    void addcell(lexer*,dive*,entity*,int,int,int);
    void ini(lexer*,dive*,entity*);

    int surfl_in, surfl_out, surfl_fsf, surfl_wall, surfl_bed;
	int count,ptcount;
	int out,top,inf;
	int n,nn,q;
	int eq1,eq2;
	int ib,jb,yb;
	int onnode, onnode_fill;
	double xx0,xx1,yy0,yy1,xx2,yy2,zz0,zz1;
	double xc,yc,zc;
	const double eps,psi;
    double xstart,xend,ystart,yend,zstart,zend;
    double xsmall, xlarge, ysmall, ylarge, zsmall, zlarge;

	double signx, signy,xroot,yroot;
	
	ofstream cceout;
};

#endif



