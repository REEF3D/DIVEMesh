/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2022 Hans Bihs

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

#include"interpolation.h"
#include"increment.h"

class lexer;
class dive;

using namespace std;

#ifndef INVERSE_DIST_LOCAL_H_
#define INVERSE_DIST_LOCAL_H_

class inverse_dist_local : public interpolation, public increment
{
public:
    inverse_dist_local(lexer*,dive*);
    virtual ~inverse_dist_local();

    virtual void start(lexer*,dive*,int,double*,double*,double*,double*,double*,int,int,double**);
    virtual double gxy(lexer*,dive*,double*,double*,double*,double*,double*,int,int,double**);
    virtual void setup(lexer*,dive*,double*,double*,double*,double*,double*,int,int);

private:
    double xmin,xmax,ymin,ymax,zmin,zmax;
    
    int Nx,Ny;
    int count,cp;
    int counter;
    double Dmax,R,dij;
    double origx,origy,w;
    
    int **ptnum,***ptid;
    
    int r,s,t,ic,jc,kp,dd;
    int is,ie,js,je;
    
    

    double g,wsum,dist,weight;
    double xc,yc;

};

#endif



