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

class lexer;
class dive;

using namespace std;

#ifndef ENTITY_H_
#define ENTITY_H_

class entity
{
public:
    virtual void read(lexer*,dive*,int&)=0;

    virtual double fx(lexer*,dive*,int,int,int)=0;
    virtual double fy(lexer*,dive*,int,int,int)=0;
    virtual double fz(lexer*,dive*,int,int,int)=0;

    virtual double cfx(lexer*,dive*,int,int,int)=0;
    virtual double cfy(lexer*,dive*,int,int,int)=0;
    virtual double cfz(lexer*,dive*,int,int,int)=0;

    virtual double xstart()=0;
    virtual double xend()=0;
    virtual double ystart()=0;
    virtual double yend()=0;
    virtual double zstart()=0;
    virtual double zend()=0;

    virtual int xdir(int,int,int)=0;
    virtual int ydir(int,int,int)=0;
    virtual int zdir(int,int,int)=0;

    virtual int inbound(int,int,int)=0;
    virtual int inbound_onnode(int,int,int)=0;

    virtual int flag_val(int,int,int)=0;

    virtual int type()=0;
    virtual int rank()=0;
    virtual int side()=0;

    virtual int neighbor1()=0;
    virtual int neighbor2()=0;

};

#endif

