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

void geodat::coarsen(lexer *p, dive *a)
{
    int count;
    
    // x
    count=0;
    ILOOP
    if(i%p->G30==0)
    {
    XC[count]=p->XP[IP];
    ++count;
    }
    
    kx=count;
    
    // y
    count=0;
    JLOOP
    if(j%p->G30==0)
    {
    YC[count]=p->YP[JP];
    ++count;
    }
    
    ky=count;
    
    cout<<"coarsen knox:"<<p->knox<<" kx: "<<kx<<" | knoy:"<<p->knoy<<" ky: "<<ky<<endl;
    
}

void geodat::prolong(lexer *p, dive *a)
{
    
    
    
}



double geodat::ccslipol4(lexer *p, double *f, double xp, double yp)
{
    ii=i;
    jj=j;
    
    i = p->posc_i(xp);
    j = p->posc_j(yp);
		/*
    // wa
    wa = (p->XP[IP1]-xp)/p->DXN[IP];
    
    if((p->XP[IP1]-xp)/p->DXN[IP]<0.0)
    {
    wa = (p->XP[IP2]-xp)/p->DXN[IP1];
    ++i;
    }
    
    if((p->XP[IP1]-xp)/p->DXN[IP]>1.0)
    {
    wa = (p->XP[IP]-xp)/p->DXN[IM1];
    --i;
    }
    

    // wb
    wb = (p->YP[JP1]-yp)/p->DYN[JP];
    
    if((p->YP[JP1]-yp)/p->DYN[JP]<0.0)
    {
    wb = (p->YP[JP2]-yp)/p->DYN[JP1];
    ++j;
    }
    
    if((p->YP[JP1]-yp)/p->DYN[JP]>1.0)
    {
    wb = (p->YP[JP]-yp)/p->DYN[JM1];
    --j;
    }
    
    

    value =  lintsl4(f,i,j,wa,wb);

    i=ii;
    j=jj;
    */

    return value;
}


double geodat::lintsl4(lexer *p, double *f, int& i,int& j, double wa, double wb)
{
    v1=v2=v3=v4=0.0;
    c1=c2=c3=c4=0;

/*
    if(p->flagslice4[IJ]>0)
    {
    v1=f(i,j);
    c1=1;
    }
    
    if(p->flagslice4[IJp1]>0)
    {
    v2=f(i,j+1);
    c2=1;
    }
    
    if(p->flagslice4[Ip2J]>0)
    {
    v3=f(i+1,j);
    c3=1;
    }
    
    if(p->flagslice4[Ip1Jp1]>0)
    {
    v4=f(i+1,j+1);
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
    
    if(c2==0 && c4==0 && c1==1 && c3==1)
    {
    x1=x2=0.0;
    }

    value = wb*x1 + (1.0-wb)*x2;
    */
 return value;

}



