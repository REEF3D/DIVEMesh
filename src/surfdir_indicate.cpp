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

#include"surfdir_indicate.h"
#include"dive.h"
#include"lexer.h"
#include"entity.h"

surfdir_indicate::surfdir_indicate() : eps(1.0e-15)
{
}

surfdir_indicate::~surfdir_indicate()
{
}

void surfdir_indicate::indicate(lexer* p, dive* a, entity *pent)
{
     xstart=pent->xstart();
     xend=pent->xend();

     ystart=pent->ystart();
     yend=pent->yend();

     zstart=pent->zstart();
     zend=pent->zend();

     //cout<<pent->side()<<" xs: "<<xstart<<" xe: "<<xend<<" ys: "<<ystart<<" ye: "<<yend<<" zs: "<<zstart<<" ze: "<<zend<<endl;

    if(xend>=xstart)
    {
    xdir=1;
    xsmall=xstart;
    xlarge=xend;
    }

    if(xend<xstart)
    {
    xdir=-1;
    xsmall=xend;
    xlarge=xstart;
    }

    if(yend>=ystart)
    {
    ydir=1;
    ysmall=ystart;
    ylarge=yend;
    }

    if(yend<ystart)
    {
    ydir=-1;
    ysmall=yend;
    ylarge=ystart;
    }

    side=pent->side();

    LOOP
     {
     xc0 = p->XP[IP];
     yc0 = p->YP[JP];
     zc0 = p->ZP[KP];

     xc1 = p->XP[IP1];
     yc1 = p->YP[JP1];
     zc1 = p->ZP[KP1];

         if(xc0>=xsmall-eps && xc0<=xlarge+eps)
         if(yc0>=ysmall-eps && yc0<=ylarge+eps)
         if(zc0>=zstart-eps && zc0<=zend+eps)
         {

             xx = pent->cfx(p,a,i,j,k);
             yy = pent->cfy(p,a,i,j,k);

             // x-dir
             if(xx>=xc0-eps && xx<=xc1+eps)
             {
                if((ydir==1 && side==1) || (ydir==-1 && side==2))
                {
                a->flag(i,j,k)     = -21;
                a->flag(i+1,j,k) =   1;
                }

                if((ydir==-1 && side==1) || (ydir==1 && side==2))
                {
                a->flag(i,j,k)     =      1;
                a->flag(i+1,j,k) =  -21;
                }
             }

             // y-dir
             if(yy>=yc0-eps && yy<=yc1+eps)
             {
                if((xdir==1 && side==1) || (xdir==-1 && side==2))
                {
                a->flag(i,j,k)     =     1;
                a->flag(i,j+1,k) = -21;
                }

                if((xdir==-1 && side==1) || (xdir==1 && side==2))
                {
                a->flag(i,j,k)     =  -21;
                a->flag(i,j+1,k) =     1;
                }
             }
        }
     }
}

void surfdir_indicate::finalize(lexer* p, dive* a)
{

    MALOOP
    OUTCHECK
    a->flag(i,j,k)=0;

    for(n=0;n<100;++n)
    LOOP
    if(a->flag(i,j,k)==0)
    if(a->flag(i-1,j,k)>=0 && a->flag(i+1,j,k)>=0 && a->flag(i,j-1,k)>=0 && a->flag(i,j+1,k)>=0)
    if(a->flag(i-1,j,k)>0 || a->flag(i+1,j,k)>0 || a->flag(i,j-1,k)>0 || a->flag(i,j+1,k)>0)
    a->flag(i,j,k)=1;

    MALOOP
    OUTCHECK
    a->flag(i,j,k)=-21;

    MALOOP
    if(a->flag(i,j,k)==0)
    a->flag(i,j,k)=-21;

    ofstream result;
	result.open("surfdir_indicate.txt");

	k=0;
	ILOOP
	{
	    JLOOP
	    {
        if(a->flag(i,j,k)<0)
        result<<-1<<" ";

        if(a->flag(i,j,k)>0)
        result<<1<<" ";

        if(a->flag(i,j,k)==0)
        result<<0<<" ";

	    }
	    result<<" $ "<<endl;

	}
}
