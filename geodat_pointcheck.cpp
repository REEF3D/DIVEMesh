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

#include"geodat.h"
#include"dive.h"
#include"lexer.h"

void geodat::pointcheck(lexer *p, dive *a, double *X, double *Y, double *F)
{
	double epsi=p->G36*p->DXYM;
	double xdiff,ydiff,zdiff;
	int count=0;

    //-----
    int numpt = p->Np;
    if(p->G37_select==0)
    {
    dd=3;
    Nx = p->knox; + 2*dd+1;

    int dij = int(p->G36);
    
    dij += 1;
    

    XYBCLOOP
    if(ptnum[i+dd][j+dd]>0)
    {

        n = ptid[i+dd][j+dd][0];
        
        
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

//cout<<"is: "<<is<<" ie: "<<ie<<" js: "<<js<<" je: "<<je<<endl; 

        for(r=is;r<ie;++r)
        {
            for(s=js;s<je;++s)
            {
                for(t=0;t<ptnum[r+dd][s+dd];++t)
                {
                    q = ptid[r+dd][s+dd][t];
                
                    if(n!=q && q>-1)
                    {
                    xdiff = fabs(X[n]-X[q]);
                    ydiff = fabs(Y[n]-Y[q]);
                    zdiff = fabs(F[n]-F[q]);
                    
                        if(xdiff<epsi && ydiff<epsi)
                        {
                        --numpt;
                        
                        ptid[r+dd][s+dd][t]=-1;
                        }
                    }
                    
                }
                
            }

        }  
        }      
    
    }
    
    int *Xtemp,*Ytemp,*Ftemp;
    
    p->Iarray(Xtemp,numpt);
    p->Iarray(Ytemp,numpt);
    p->Iarray(Ftemp,numpt);
       
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
        
        p->Np=numpt;
        
        for(n=0;n<p->Np;++n)
        {
        X[n] = Xtemp[n];
        Y[n] = Ytemp[n];
        F[n] = Ftemp[n];
        }

    p->del_Iarray(Xtemp,numpt);
    p->del_Iarray(Ytemp,numpt);
    p->del_Iarray(Ftemp,numpt);
    
    

        
    }
    
    
    //---- 
    if(p->G37_select==1)
    do{


    q  = (rand() % p->Np);
    
                X[q] = X[p->Np-1];
                Y[q] = Y[p->Np-1];
                F[q] = F[p->Np-1];
                -- p->Np;
                --q;



    }while(p->Np>p->G37);
    
    
    // remove out of bounds points
    int xs,xe,ys,ye;
    
        i=-3;
        xs=p->XN[IP];
        
        i=p->knox+3;
        xe=p->XN[IP];
        
        
        j=-3;
        ys=p->YN[JP];
        
        j=p->knoy+3;
        ye=p->YN[JP];
        
    for(n=0;n<p->Np;++n)
    {   
        
        
        if(X[n]<xs || X[n]>xe || Y[n]<ys || Y[n]>ye)
        {
        X[n] = X[p->Np-1];
        Y[n] = Y[p->Np-1];
        F[n] = F[p->Np-1];
        -- p->Np;
        --n;
        }       

    }
    
    cout<<"p->Np after pointcheck: "<<p->Np<<endl;
}
