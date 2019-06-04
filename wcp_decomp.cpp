/*--------------------------------------------------------------------
REEF3D
Copyright 2008-2019 Hans Bihs

This file is part of REEF3D.

REEF3D is free software; you can redistribute it and/or modify it
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

#include"wcp.h"
#include"lexer.h"
#include"dive.h"
#include<iostream>
#include<fstream>
#include<sys/stat.h>
#include<sys/types.h>

void wcp::decomp(lexer *p, dive *a)
{
    int istart,iend,jstart,jend;
    double xstart,xend,ystart,yend;
    
    p->Iarray(is,a->mx+2);
    p->Iarray(ie,a->mx+2);
    p->Iarray(js,a->my+2);
    p->Iarray(je,a->my+2);
    
    p->Darray(xs,a->mx+2);
    p->Darray(xe,a->mx+2);
    p->Darray(ys,a->my+2);
    p->Darray(ye,a->my+2);
    
    p->Iarray(Nx,a->mx+2);
    p->Iarray(Ny,a->mx+2);
    p->Iarray(Nz,a->my+2);
    
    // ini ijnode start and end
    is[0]=0;
    js[0]=0;
    
    ie[a->mx-1]=NGx;
    je[a->mx-1]=NGy;
    
    // find ijnode 
    for(aa=1;aa<a->mx-1;++aa)
    {
        xstart = a->xorig[aa];
        xend = a->xorig[aa+1];
        
        for(i=0;i<NGx;++i)
        {
            if(X[i+1]>=xstart && X[i]<xstart)
            {
            is[aa] = i;
            xs[aa] = X[i];
            }
            
            if(X[i]>=xend && X[i-1]<xend)
            {
            ie[aa] = i;
            xe[aa] = X[i];
            }
        }
    }
    
    for(bb=1;bb<a->my-1;++bb)
    {
        ystart = a->yorig[bb];
        yend = a->yorig[bb+1];
        
        for(j=0;j<NGy;++j)
        {
            if(Y[j+1]>=ystart && Y[j]<ystart)
            {
            js[bb] = j;
            ys[bb] = Y[j];
            }
            
            if(Y[j]>=yend && Y[j-1]<yend)
            {
            je[bb] = j;
            ye[bb] = Y[j];
            }
        }
    }

    
}