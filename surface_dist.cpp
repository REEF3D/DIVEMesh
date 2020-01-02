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

#include"surface.h"
#include"lexer.h"
#include"dive.h"

void surface::makedist(lexer* p, dive* a)
{
    cout<<"\t makedist"<<endl;

    for(n=0;n<a->surfcount;n++)
    a->gcd[n]=0.5*p->dx;

    for(n=0;n<a->surfcount;++n)
    {
        i=a->surf[n][0];
        j=a->surf[n][1];
        k=a->surf[n][2];

        if(a->confac(i,j,k)>0)
        a->gcd[n]=distcalc(p,a,a->surf[n][3],i,j,k,0,0,0);

        if(a->confac(i,j,k)==0)
        {
            if(a->confac(i-1,j,k)>0 && a->flag(i-1,j,k)<0 && a->surf[n][3]==1)
            a->gcd[n]=distcalc(p,a,1,i,j,k,-1,0,0);

            if(a->confac(i+1,j,k)>0 && a->flag(i+1,j,k)<0 && a->surf[n][3]==4)
            a->gcd[n]=distcalc(p,a,4,i,j,k,1,0,0);

            if(a->confac(i,j-1,k)>0 && a->flag(i,j-1,k)<0 && a->surf[n][3]==3)
            a->gcd[n]=distcalc(p,a,3,i,j,k,0,-1,0);

            if(a->confac(i,j+1,k)>0 && a->flag(i,j+1,k)<0 && a->surf[n][3]==2)
            a->gcd[n]=distcalc(p,a,2,i,j,k,0,1,0);

            if(a->confac(i,j,k-1)>0 && a->flag(i,j,k-1)<0 && a->surf[n][3]==5)
            a->gcd[n]=distcalc(p,a,5,i,j,k,0,0,-1);

            if(a->confac(i,j,k+1)>0 && a->flag(i,j,k+1)<0 && a->surf[n][3]==6)
            a->gcd[n]=distcalc(p,a,6,i,j,k,0,0,1);
        }
    }
}

double surface::distcalc(lexer* p, dive* a, int cs, int ii,int jj,int kk,int aa, int bb, int cc)
{
    double dist;
    double xc,yc,zc;
    double denom=0.0;
    double sumx,sumy,sumz;
    int nn;

    sumx=sumy=sumz=0.0;

     i=ii+aa;
     j=jj+bb;
     k=kk+cc;

     xc = p->XP[II];
     yc = p->YP[JJ];
     zc = p->ZP[KK];

    q=a->confac(i,j,k);

    for(nn=0;nn<a->numfac(i,j,k);++nn)
    {
    sumx+=fabs(xc-a->ccpoint[a->facet[q][nn]][0]);
    sumy+=fabs(yc-a->ccpoint[a->facet[q][nn]][1]);
    sumz+=fabs(zc-a->ccpoint[a->facet[q][nn]][2]);

    denom+=1.0;
    }


    if(cs==1 || cs==4)
    dist=fabs(sumx/denom);

    if(cs==2 || cs==3)
    dist=fabs(sumy/denom);

    if(cs==5 || cs==6)
    dist=fabs(sumz/denom);
	
    return dist;
}
