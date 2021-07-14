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
Author: Hans Bihs
--------------------------------------------------------------------*/

#include"hdc.h"
#include"lexer.h"
#include"dive.h"
#include<iostream>
#include<fstream>
#include<sys/stat.h>
#include<sys/types.h>

void hdc::decomp(lexer *p, dive *a)
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
    
    ie[a->mx-1]=0;
    je[a->my-1]=0;
    
    // find ijnode 
    for(aa=0;aa<a->mx;++aa)
    {
        xstart = a->xorig[aa];
        xend  = a->xorig[aa+1];
        
        //cout<<" HDC decomp x_se: "<<xstart<<" "<<xend<<endl;
        
        for(i=0;i<NGx;++i)
        {
            if(i<NGx-1)
            if(X[i+1]>=xstart && X[i]<xstart)
            {
            is[aa] = i;
            xs[aa] = X[i];
            }
            
            if(i>1)
            if((X[i]>=xend && X[i-1]<xend))
            {
            ie[aa] = i+1;
            xe[aa] = X[i];
            }
            
            if((i==NGx-1 && X[i]<xend && X[i]>xstart))
            {
            ie[aa] = i+1;
            xe[aa] = X[i];
            }
        }
    }
    if(jdir==1)
    for(bb=0;bb<a->my;++bb)
    {
        ystart = a->yorig[bb];
        yend = a->yorig[bb+1];
        
        for(j=0;j<NGy;++j)
        {
            if(j<NGy-1)
            if(Y[j+1]>=ystart && Y[j]<ystart)
            {
            js[bb] = j;
            ys[bb] = Y[j];
            }
            
            if(j>1)
            if(Y[j]>=yend && Y[j-1]<yend)
            {
            je[bb] = j+1;
            ye[bb] = Y[j];
            }
            
            if((j==NGy-1 && Y[j]<yend && Y[j]>ystart))
            {
            je[bb] = j+1;
            ye[bb] = Y[j];
            }
        }
    }
    
    if(jdir==0)
    for(bb=0;bb<a->my;++bb)
    {
    js[bb] = 0;
    ys[bb] = Y[0];
    
    je[bb] = 1;
    ye[bb] = Y[0];
    }
            
    
    /*
    for(aa=0;aa<a->mx;++aa)
    for(bb=0;bb<a->my;++bb)
    {
    cout<<"jdir: "<<jdir<<endl;
    cout<<"HDC xorig["<<aa<<"]: "<<a->xorig[aa]<<" yorig["<<bb<<"]: "<<a->yorig[bb]<<endl;
    cout<<"HDC is: "<<is[aa]<<" ie: "<<ie[aa]<<" js: "<<js[bb]<<" je: "<<je[bb]<<endl;
    cout<<"HDC xs: "<<xs[aa]<<" xe: "<<xe[aa]<<" ys: "<<ys[bb]<<" ye: "<<ye[bb]<<endl<<endl;
    }
    */
    
}