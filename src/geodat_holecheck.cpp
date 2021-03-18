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
    int check;
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
    cout<<"PCOUNT: "<<pcount<<endl;
    
    for(n=0;n<p->Np;++n)
    {
        i = p->poscgen_i(X[n],XC,kx);
        j = p->poscgen_j(Y[n],YC,ky);
        
        //cp=0;
        //do{

        is=MAX(i-dij-cp,-3);
        ie=MIN(i+dij+cp,Nx-3);
        
        js=MAX(j-dij-cp,-3);
        je=MIN(j+dij+cp,Ny-3);
        
        //cout<<n<<"  IDW local "<<" i: "<<i<<" j: "<<j <<" is: "<<is<<" ie: "<<ie<<" js: "<<js<<" je: "<<je<<" dd: "<<dd<<" cp: "<<cp<<" count: "<<count<<endl;
        

            count=0;
            for(r=is;r<ie;++r)
            {
                for(s=js;s<je;++s)
                {
                    for(t=0;t<ptnum[r+dd][s+dd];++t)
                    {
                        q = ptid[r+dd][s+dd][t];
                        
                        if(q!=n)
                        {
                        dist = sqrt(pow(X[n]-X[q],2.0) + pow(Y[n]-Y[q],2.0));
                        
                        maxdist = MAX(maxdist,dist);
        
                        meandist += dist;
                        ++pcount;
                        ++count;
                        
                        cout<<"DIST: "<<dist<<" X[n]: "<<X[n]<<" X[q]: "<<X[q]<<" Y[n]: "<<Y[n]<<" Y[q]: "<<Y[q]<<"  ptnum[r+dd][s+dd]: "<<ptnum[r+dd][s+dd]<<" t: "<<t<<endl;
                        }
                        
                        
                    }
                    
                }

            }
      
        //cp+=2;
        //}while(count<MIN(9,p->Np) && cp<10);
        
        //cout<<"PCOUNT: "<<pcount<<endl;
    }
    
    cout<<"MAX pointdist: "<<maxdist<<" MEAN pointdist: "<<meandist/double(pcount)<<" MEAN pointdist: "<<meandist<<" pcount: "<<pcount<<endl;
    
    
    meandist = meandist/double(pcount);
    
    
    
    ///- ---- -- -- - - -
    
    int **ptnum_old;
    p->Iarray(ptnum_old,Nx,Ny);
    
    for(r=0;r<Nx;++r)
    for(s=0;s<Ny;++s)
    ptnum_old[r][s]=ptnum[r][s];
    
    // radius either G18 or max radius of nearest nb
    // go to very cell, is there a geodat point within the radius?
    // if not at geodat point in cell center with given height G16
        // count entries
        // resize ptid
        // fill ptid
        
    dij =int(meandist/(p->DXM));
    
    cout<<"DIJ: "<<dij<<endl;
    
    // count entries
    for(i=0;i<kx;++i)
    for(j=0;j<ky;++j)
    {
      

        is=MAX(i-dij,-3);
        ie=MIN(i+dij,Nx-3);
        
        js=MAX(j-dij,-3);
        je=MIN(j+dij,Ny-3);
        
        //cout<<n<<"  IDW local "<<" i: "<<i<<" j: "<<j <<" | is: "<<is<<" ie: "<<ie<<" js: "<<js<<" je: "<<je<<" dd: "<<dd<<" cp: "<<cp<<" count: "<<count<<endl;
        

        check=0;
        for(r=is;r<ie;++r)
        for(s=js;s<je;++s)
        for(t=0;t<ptnum[r+dd][s+dd];++t)
        check=1;
            
        if(check==0)
        {
        ++ptnum[i+dd][j+dd];
        ++count;
        }

    //cout<<"check: "<<check<<" "<<" i: "<<i<<" j: "<<j<<endl;
    }
    cout<<"COUNT: "<<count<<endl;
    // p->Iresize(ptid,Nx,Ny,ptnum_old,ptnum);
    
    
    p->Dresize(X,p->Np,p->Np+count);
    p->Dresize(Y,p->Np,p->Np+count);
    p->Dresize(F,p->Np,p->Np+count);
    
    
    // FILL
    for(i=0;i<kx;++i)
    for(j=0;j<ky;++j)
    {
      

        is=MAX(i-dij,-3);
        ie=MIN(i+dij,Nx-3);
        
        js=MAX(j-dij,-3);
        je=MIN(j+dij,Ny-3);
        
        //cout<<n<<"  IDW local "<<" i: "<<i<<" j: "<<j <<" | is: "<<is<<" ie: "<<ie<<" js: "<<js<<" je: "<<je<<" dd: "<<dd<<" cp: "<<cp<<" count: "<<count<<endl;
        

        check=0;
        for(r=is;r<ie;++r)
        for(s=js;s<je;++s)
        for(t=0;t<ptnum[r+dd][s+dd];++t)
        check=1;
            
        if(check==0)
        {
        X[p->Np] = p->XP[IP];
        Y[p->Np] = p->YP[JP];
        F[p->Np] = p->G16;
        ptid[ic+dd][jc+dd][ptnum[ic+dd][jc+dd]]=p->Np;
        ++p->Np;
        }

    //cout<<"check: "<<check<<" "<<" i: "<<i<<" j: "<<j<<endl;
    }
    
    
}