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

#include"inverse_dist_local.h"
#include"dive.h"
#include"lexer.h"

inverse_dist_local::inverse_dist_local(lexer *p, dive *a) 
{
}

inverse_dist_local::~inverse_dist_local()
{
}

void inverse_dist_local::start(lexer *p, dive *a, int numpt, double *Fx, double *Fy, double *Fz, double *XC, double *YC, int kx, int ky, double **f)
{
    setup(p,a,Fx,Fy,Fz,XC,YC,kx,ky);
    
    counter=0;
    for(i=0;i<kx;++i)
    for(j=0;j<ky;++j)
    {
    f[i][j] = gxy(p,a,Fx,Fy,Fz,XC,YC,kx,ky,f);
    ++counter;
    
    if(counter%1000==0)
    cout<<counter<<endl;
    }
}

double inverse_dist_local::gxy(lexer *p, dive *a, double *Fx, double *Fy, double *Fz, double *XC, double *YC, int kx, int ky, double **f)
{    
    xc = XC[IP];
    yc = YC[JP];

    g=p->G16;
    wsum=0.0;

    double zmean=0.0;
    cp=0;
    do{
        is=MAX(i-dij-cp,-3);
        ie=MIN(i+dij+cp,Nx-3);
        
        js=MAX(j-dij-cp,-3);
        je=MIN(j+dij+cp,Ny-3);
        
        //cout<<counter<<"  IDW local "<<" i: "<<i<<" j: "<<j <<" is: "<<is<<" ie: "<<ie<<" js: "<<js<<" je: "<<je<<" dd: "<<dd<<" cp: "<<cp<<" count: "<<count<<endl;
        
        zmean=0.0;
        count=0;
        for(r=is;r<ie;++r)
        {
            for(s=js;s<je;++s)
            {
                for(t=0;t<ptnum[r+dd][s+dd];++t)
                {
                    q = ptid[r+dd][s+dd][t];
                
                    w = sqrt(pow(xc-Fx[q],2.0) + pow(yc-Fy[q],2.0));
                    w = pow(1.0/(w>1.0e-15?w:1.0e15),p->G35);
                    
                    wsum+=w;
                    
                    g += w*Fz[q];
                    
                    ++count;
                    zmean+=Fz[q];
                    
                }
                
            }

        }
        if(count>0)
        zmean=zmean/double(count);
  
    cp+=2;
    }while(count<MIN(19,p->Np));
    
    if(wsum>0.0)
    g/=wsum;
    
    if(wsum==0.0)
    g/=1.0e20;
    
    return g;
}








