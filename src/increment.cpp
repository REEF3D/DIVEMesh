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

#include "increment.h"

increment::increment()
{
    xma=1;
    yma=1;
    zma=1;
    
    marge=5;
    margin=3;
}

increment::~increment()
{
}

int increment::i,increment::j,increment::k,increment::aa,increment::bb,increment::cc,increment::n,increment::q,increment::qn;
int increment::xma,increment::yma,increment::zma;
int increment::marge;
int increment::margin;

int increment::conv(double a)
{

    int b,c;
    double d,diff;

    c= int( a);
    d=double(c);
    diff=a-d;

    b=c;

    if(diff>0.5)
    b=c+1;

    if(diff<=-0.5)
    b=c-1;


    return b;

}

int increment::equals(double a, double b)
{
    int e=0;

    double c = a/b;

    double d = double(conv(c));

    c-=d;

    if(fabs(c)<1.0e-10)
    e=1;


    return e;
}
