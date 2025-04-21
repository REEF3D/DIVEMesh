/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2025 Hans Bihs

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

void geodat::pointcheck_radius(lexer *p, dive *a, double *X, double *Y, double *F)
{
	double epsi=p->G36*p->DXYM;
	double xdiff,ydiff,zdiff;
	int count=0;
    
    //-----
    int numpt = p->Np;
    if(p->G36_select==1)
    {
    dd=3;
    Nx = p->knox; + 2*dd+1;

    int dij = int(p->G36);
    int qq;
    
    dij += 2;
    

    XYBCLOOP
    if(ptnum[i+dd][j+dd]>0)
    {
    
        qq = (rand() % ptnum[i+dd][j+dd]);
        
        n = ptid[i+dd][j+dd][qq];
        
        
        if(n==-1 && ptnum[i+dd][j+dd]>1)
        {
        qn=1;
        
            do{
            n = ptid[i+dd][j+dd][qn];
            ++qn;
            
            
            if(n>-1)
            break;

            }while(qn<ptnum[i+dd][j+dd]);
        }
        
        
        if(n>-1)
        {

        is=MAX(i-dij,-dd);
        ie=MIN(i+dij,p->knox+dd);
        
        js=MAX(j-dij,-dd);
        je=MIN(j+dij,p->knoy+dd); 

    //cout<<"PTCHK is: "<<is<<" ie: "<<ie<<" js: "<<js<<" je: "<<je<<endl;

        for(r=is;r<ie;++r)
        if(r<Nx)
        {
            for(s=js;s<je;++s)
            if(s<Ny)
            {
                for(t=0;t<ptnum[r+dd][s+dd];++t)
                {
                    
                    q = ptid[r+dd][s+dd][t];
                
                    if(n!=q && q>-1)
                    {
                    xdiff = fabs(X[n]-X[q]);
                    ydiff = fabs(Y[n]-Y[q]);
                    zdiff = fabs(F[n]-F[q]);
                    
                    
                        if(xdiff<epsi && ydiff<epsi && zdiff<epsi)
                        {
                        --numpt;
                        
                        if(numpt<=0)
                        {
                        cout<<"!!! Pointcheck gives 0 geodat points, using original Np ... numpt: "<<numpt<<endl;
                        goto part2;
                        }
                        
                        ptid[r+dd][s+dd][t]=-1;
                        }
                    }
                }
            }
        }  
        }      
    }
    
    p->Darray(Xtemp,numpt);
    p->Darray(Ytemp,numpt);
    p->Darray(Ftemp,numpt);
    

    qn=0;
        // put back
        XYBCLOOP
        for(q=0;q<ptnum[i+dd][j+dd];++q)
        {
        n = ptid[i+dd][j+dd][q];

            if(n>-1)
            {
            Xtemp[qn] = X[n];
            Ytemp[qn] = Y[n];
            Ftemp[qn] = F[n];
            ++qn;
            }
        }
        
        //cout<<"numpt: "<<numpt<<" qn: "<<qn<<endl;
        
        p->Np=qn;
        
        for(n=0;n<p->Np;++n)
        {
         
        X[n] = Xtemp[n];
        Y[n] = Ytemp[n];
        F[n] = Ftemp[n];
        //cout<<n<<" X[n]: "<<X[n]<<" Y[n]: "<<Y[n]<<" F[n]: "<<F[n]<<endl;
        }

    p->del_Darray(Xtemp,numpt);
    p->del_Darray(Ytemp,numpt);
    p->del_Darray(Ftemp,numpt);
    }
    
    
    print_sampled(p,a);
    
    part2:
    cout<<"p->Np after pointcheck: "<<p->Np<<endl;
}
    
void geodat::pointcheck_random(lexer *p, dive *a, double *X, double *Y, double *F)
{
    srand((unsigned)time(0));
    
    if(p->G37_select==1)
    do{


    q  = (rand() % p->Np);
    
                X[q] = X[p->Np-1];
                Y[q] = Y[p->Np-1];
                F[q] = F[p->Np-1];
                -- p->Np;
                --q;


    }while(p->Np>p->G37);
    
    print_sampled(p,a);
    
    cout<<"p->Np after pointcheck: "<<p->Np<<endl;
}
