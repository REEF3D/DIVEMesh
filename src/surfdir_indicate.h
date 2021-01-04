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

#include"increment.h"

class lexer;
class dive;
class entity;

using namespace std;

#ifndef SURFDIR_INDICATE_H_
#define SURFDIR_INDICATE_H_

class surfdir_indicate : public increment
{
public:
    surfdir_indicate();
    virtual ~surfdir_indicate();

    virtual void indicate(lexer*,dive*,entity*);
    virtual void finalize(lexer*,dive*);


private:
    double xc0,yc0,zc0,xc1,yc1,zc1,xc2,yc2,zc2;
    double xx,yy;
    double xstart,xend,ystart,yend,zstart,zend;
    double xsmall, xlarge, ysmall, ylarge;
    const double eps;

    int xdir,ydir,side;


};

#endif



