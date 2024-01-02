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

#include"geodat.h"
#include"dive.h"
#include"lexer.h"


double geodat::ccipol(lexer *p, double **f, double xp, double yp)
{
    iii=i;
    jjj=j;
    
    
    
    i = p->poscgen_i(xp,XC,kx);
    j = p->poscgen_j(yp,YC,ky);
    
    //if(i<0 || j<0)
    //cout<<"pos_ij: "<<i<<" "<<j<<" | "<<xp<<" "<<yp<<" YC[3]: "<<YC[3]<<" marge: "<<marge<<endl;
    
    /*
    i = MAX(i,0);
    i = MIN(i,kx-1);
    
    j = MAX(j,0);
    j = MIN(j,ky-1);*/
    
    
		
    // wa
    wa = (XC[IP1]-xp)/(XC[IP1]-XC[IP]);
    
    if(wa<0.0)
    {
    wa = (XC[IP2]-xp)/(XC[IP1]-XC[IP]);
    ++i;
    }
    
    if(wa>1.0)
    {
    wa = (XC[IP]-xp)/(XC[IP1]-XC[IP]);
    --i;
    }
    

    // wb
    wb = (YC[JP1]-yp)/(YC[JP1]-YC[JP]);
    
    if(wb<0.0)
    {
    wb = (YC[JP2]-yp)/(YC[JP1]-YC[JP]);
    ++j;
    }
    
    if(wb>1.0)
    {
    wb = (YC[JP]-yp)/(YC[JP1]-YC[JP]);
    --j;
    }
    
    //cout<<"pos_ij: "<<wa<<" "<<wb<<" | "<<xp<<" "<<yp<<" YC[3]: "<<YC[3]<<" marge: "<<marge<<endl;
    
    if(p->knoy==1)
    value =  lint2D(p,f,i,j,wa,wb);
    
    if(p->knoy>1)
    value =  lint(p,f,i,j,wa,wb);
    
    

    i=iii;
    j=jjj;
    
    return value;
}


double geodat::lint2D(lexer *p, double **f, int& i,int& j, double wa, double wb)
{
    v1=v2=v3=v4=0.0;
    c1=c2=c3=c4=0;
    
    /*
    i = MAX(i,0);
    i = MIN(i,kx-1);
    
    j = MAX(j,0);
    j = MIN(j,ky-1);*/


    if(i>=0 && i<kx)
    {
    v1=f[i+3][0+3];
    c1=1;
    }
    
    if(i+1>=0 && i+1<kx)
    {
    v3=f[i+1+3][0+3];
    c3=1;
    }

    //cout<<"v1: "<<v1<<" v3: "<<v3<<endl;

    
    // x1
    if(c1==1 && c3==1)
    value = wa*v1 + (1.0-wa)*v3;
    

 return value;

}

double geodat::lint(lexer *p, double **f, int& i,int& j, double wa, double wb)
{
    v1=v2=v3=v4=0.0;
    c1=c2=c3=c4=0;
    
    /*
    i = MAX(i,0);
    i = MIN(i,kx-1);
    
    j = MAX(j,0);
    j = MIN(j,ky-1);*/


    if(i>=0 && i<kx && j>=0 && j<ky)
    {
    v1=f[i+3][j+3];
    c1=1;
    }
    
    if(i>=0 && i<kx && j+1>=0 && j+1<ky)
    {
    v2=f[i+3][j+1+3];
    c2=1;
    }
    
    if(i+1>=0 && i+1<kx && j>=0 && j<ky)
    {
    v3=f[i+1+3][j+3];
    c3=1;
    }
    
    if(i+1>=0 && i+1<kx && j+1>=0 && j+1<ky)
    {
    v4=f[i+1+3][j+1+3];
    c4=1;
    }

    
    // x1
    if(c1==1 && c3==1)
    x1 = wa*v1 + (1.0-wa)*v3;
    
    if(c1==1 && c3==0)
    x1 = v1;
    
    if(c1==0 && c3==1)
    x1 = v3;
    
    
    // x2
    if(c2==1 && c4==1)
    x2 = wa*v2 + (1.0-wa)*v4;
    
    if(c2==1 && c4==0)
    x2 = v2;
    
    if(c2==0 && c4==1)
    x2 = v4;
    
    if((c1==0 && c3==0) && (c2==1 || c4==1))
    wb=0.0;
    
    if((c2==0 && c4==0) && (c1==1 || c3==1))
    wb=1.0;
    
    /*if(c2==0 && c4==0 && c1==1 && c3==1)
    {
    x1=x2=0.0;
    }*/

    value = wb*x1 + (1.0-wb)*x2;
    
 return value;

}
