/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2024 Hans Bihs

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
class field2d;

using namespace std;

#ifndef KRIGING_H_
#define KRIGING_H_

class kriging : public interpolation, public increment
{
public:
    kriging(lexer*,dive*,int,double*,double*,double*);
    virtual ~kriging();

    virtual void start(lexer*,dive*,int,double*,double*,double*,double*,double*,int,int,double**);
    
	virtual double semivariogram(double);
	virtual void rearrange(lexer*);
	virtual void rearrange_b(lexer*);
	
	virtual void invert(lexer*,double**, double**, double*, double*);
	virtual void decomp(lexer*,double**, double**);
	virtual void backsubstitution(lexer*,double**, double*);
	virtual void matvec(lexer*,double**, double*, double*);
	virtual void solve(lexer*,double**, double*, double*);


private:
    
    void ini(lexer*,dive*,int,double*,double*,double*);
	
	double **A,**B;
	double*x,*b,*s,*row;

	int Np,n,m,q,r,count;
	double dist,xc,yc;
	double xmin,xmax,ymin,ymax;
	double mean, variance, range;
	double gamma,aii;
	
	double vmax,sum,val;
	int imax,np,nn;
};

#endif


