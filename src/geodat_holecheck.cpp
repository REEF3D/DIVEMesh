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

#include"geodat.h"
#include"dive.h"
#include"lexer.h"

void geodat::holecheck(lexer *p, dive *a, double *X, double *Y, double *F)
{
    double dist, maxdist,meandist,zmean;
    double Dmax,R,dij;
    int pcount=0;
    int cp=0;
    int count=0;
    
    maxdist=0.0;
    meandist=0.0;
    
    // Radius
    Dmax=sqrt(pow(p->xmax-p->xmin,2.0)+pow(p->ymax-p->ymin,2.0));
    R = 0.25*Dmax*sqrt(19.0/p->Np);
    dij = MAX(int(R/(p->DXM)),p->G17);
    
    kx = p->knox;
    ky = p->knoy;
    
    for(n=0;n<p->Np;++n)
    {
        do{

        i = p->poscgen_i(X[n],XC,kx);
        j = p->poscgen_j(Y[n],YC,ky);
        
        
        is=MAX(i-dij-cp,-3);
        ie=MIN(i+dij+cp,Nx-3);
        
        js=MAX(j-dij-cp,-3);
        je=MIN(j+dij+cp,Ny-3);
        
        cout<<count<<"  IDW local "<<" i: "<<i<<" j: "<<j <<" is: "<<is<<" ie: "<<ie<<" js: "<<js<<" je: "<<je<<" dd: "<<dd<<" cp: "<<cp<<" count: "<<count<<endl;
        

            count=0;
            for(r=is;r<ie;++r)
            {
                for(s=js;s<je;++s)
                {
                    for(t=0;t<ptnum[r+dd][s+dd];++t)
                    {
                        q = ptid[r+dd][s+dd][t];
                        
                        dist = sqrt(pow(X[n]-X[q],2.0) + pow(Y[n]-Y[q],2.0));
                        
                        maxdist = MAX(maxdist,dist);
        
                        meandist += dist;
                        ++pcount;
                        ++count;
                        
                        //cout<<"MAX pointdist: "<<maxdist<<" MEAN pointdist: "<<meandist/double(pcount)<<endl;
                    }
                    
                }

            }
            if(count>0)
            zmean=zmean/double(count);
      
        cp+=2;
        }while(count<MIN(19,p->Np));
    }
    
    cout<<"MAX pointdist: "<<maxdist<<" MEAN pointdist: "<<meandist<<endl;
    
    
    
    // radius either G18 or max radius of nearest nb
    // go to very cell, is there a geodat point within the radius?
    // if not at geodat point in cell center with given height G16
        // count entries
        // resize ptid
        // fill ptid
    
}