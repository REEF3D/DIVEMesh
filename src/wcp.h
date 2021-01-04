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

using namespace std;

#ifndef WCP_H_
#define WCP_H_

class wcp : public increment
{
public:
    wcp(lexer*,dive*);
    virtual ~wcp();

    virtual void start(lexer*,dive*);
    
    void allocate(lexer*, dive*);
    
	void read(lexer*, dive*);
    void read_mainheader(lexer*, dive*);
    void read_header(lexer*, dive*);
    void read_result(lexer*, dive*);
    
    void filename_in(lexer*, dive*,int,int);
    void filename_in_header(lexer*, dive*,int);
    
    void filename_out(lexer*, dive*,int,int);
    void filename_out_header(lexer*, dive*,int);
    
    void merge(lexer*,dive*);
    void decomp(lexer*,dive*);
	void write(lexer*,dive*);
    void write_header(lexer*,dive*);
    void filename_out(lexer*, dive*);

private:
    int iin;
    double ddn;
    float ffn;
	char name[200];
    
    int n,q,count;
    int numprocs, jdir, numiter;
    int NGx,NGy,NGz;
    
    
	double g,wsum,dist;
    double xc,yc;
    
    
    
    // arrays
    double *orig_x, *orig_y, *orig_z;
    int *orig_i, *orig_j, *orig_k;
    int *nb1,*nb2,*nb3,*nb4;
    int *NLx,*NLy,*NLz;
    
    double *simtime;
    double *X,*Y,*Z;
    double ***U,***V,***W,**eta,**bed;
    
    int *is,*ie,*js,*je;
    double *xs,*xe,*ys,*ye;
    int *Nx,*Ny,*Nz;
};

#endif


