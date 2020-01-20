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

#include"increment.h"

class lexer;
class dive;
class interpolation;

using namespace std;

#ifndef GEODAT_H_
#define GEODAT_H_

class geodat : public increment
{
public:
    geodat(lexer*,dive*);
    virtual ~geodat();

    virtual void start(lexer*,dive*);
    virtual void gcb_estimate(lexer*,dive*);
    virtual void print(lexer*,dive*);

private:
    void dryside(lexer*,dive*);
    void coarsen(lexer*,dive*);
    void prolong(lexer*,dive*);
    
    double ccipol(lexer*, double**, double, double);
    double lint(lexer*, double**, int&,int&, double, double);
    
    int posc_i(double);
    int posc_j(double);
    int ihalf(int,int);
    
    interpolation *pipol;
    
    double *XC,*YC;
    double **topof;
    
    int kx,ky;
    int ii,jj,iii,jjj;
    
    double wa,wb,value;
    double v1,v2,v3,v4,c1,c2,c3,c4;
    double x1,x2;
    

};

#endif


