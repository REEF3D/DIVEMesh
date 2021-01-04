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

#include"interpolation.h"
#include"increment.h"
class lexer;
class dive;

using namespace std;

#ifndef INVERSE_DIST_H_
#define INVERSE_DIST_H_

class inverse_dist : public interpolation, public increment
{
public:
    inverse_dist(lexer*,dive*);
    virtual ~inverse_dist();

    virtual void start(lexer*,dive*,int,double*,double*,double*,double*,double*,int,int,double**);
    virtual double gxy(lexer*,dive*,double*,double*,double*,double*,double*,int,int,double**);

private:

    double w(lexer*,int,double*,double*,double*);

    double g,wsum,dist;
    double xc,yc;
    

};

#endif



