/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2018 Hans Bihs

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

#include"cce.h"
#include"dive.h"
#include"lexer.h"
#include"entity.h"

cce::cce(lexer *p, dive *a) : eps(1.0e-5*p->DXM)
{
	cceout.open("DIVEMesh-CCE.txt");
}

cce::~cce()
{
}

void cce::start(lexer* p, dive* a, entity *pent)
{
    count=a->facetcount;
    ptcount=a->ccpointcount;

     xstart=pent->xstart();
     xend=pent->xend();
     ystart=pent->ystart();
     yend=pent->yend();
     zstart=pent->zstart();
     zend=pent->zend();

    onnode=0;
    onnode_fill=0;

    if(xend>=xstart)
    {
    xsmall=xstart;
    xlarge=xend;
    }

    if(xend<xstart)
    {
    xsmall=xend;
    xlarge=xstart;
    }

    if(yend>=ystart)
    {
    ysmall=ystart;
    ylarge=yend;
    }

    if(yend<ystart)
    {
    ysmall=yend;
    ylarge=ystart;
    }

    if(zend>=zstart)
    {
    zsmall=zstart;
    zlarge=zend;
    }

    if(zend<zstart)
    {
    zsmall=zend;
    zlarge=zstart;
    }

     // here: grid-line check
     NODELOOP
     {
     xc = p->XN[IP];
     yc = p->YN[JP];
     zc = p->ZN[KP];

     if(xc>=xsmall-eps-p->DX[IP] && xc<=xlarge+eps+p->DX[IP])
     if(yc>=ysmall-eps-p->DY[JP] && yc<=ylarge+eps+p->DY[JP])
     if(zc>=zsmall-eps-p->DZ[KP] && zc<=zlarge+eps+p->DZ[KP])
     {
     xx0 = pent->fx(p,a,i,j,k);
     yy0 = pent->fy(p,a,i,j,k);


//xxxxxxxx
         if(xx0>=xc-eps && xx0<xc+p->DX[IP]-eps)
         {

         ptcount++;
         a->ccpoint[ptcount][0]=xx0;
         a->ccpoint[ptcount][1]=yc;
         a->ccpoint[ptcount][2]=zc;

         if(xx0>=xc+eps && xx0<xc+p->DX[IP]-eps)
         {

             // --
             if(a->flag(i,j-1,k-1)>-21 && pent->inbound(i,j-1,k-1)==1)
             {
                 if(a->confac(i,j-1,k-1)==0)
                 {
                 nn=count;
                 count++;
                 a->confac(i,j-1,k-1)=count;
                 }

                 if(a->confac(i,j-1,k-1)>0)
                 nn=a->confac(i,j-1,k-1);

             a->facet[nn][a->numfac(i,j-1,k-1)]=ptcount;
             a->numfac(i,j-1,k-1)++;
             a->xdir(i,j-1,k-1)=pent->xdir(i,j-1,k-1);
             a->ydir(i,j-1,k-1)=pent->ydir(i,j-1,k-1);
             a->zdir(i,j-1,k-1)=pent->zdir(i,j-1,k-1);
             }

             // --
             if(a->flag(i,j,k-1)>-21 && pent->inbound(i,j,k-1)==1)
             {
                 if(a->confac(i,j,k-1)==0)
                 {
                 nn=count;
                 count++;
                 a->confac(i,j,k-1)=count;
                 }

                 if(a->confac(i,j,k-1)>0)
                 nn=a->confac(i,j,k-1);

             a->facet[nn][a->numfac(i,j,k-1)]=ptcount;
             a->numfac(i,j,k-1)++;
             a->xdir(i,j,k-1)=pent->xdir(i,j,k-1);
             a->ydir(i,j,k-1)=pent->ydir(i,j,k-1);
             a->zdir(i,j,k-1)=pent->zdir(i,j,k-1);
             }

             // --
             if(a->flag(i,j-1,k)>-21 && pent->inbound(i,j-1,k)==1)
             {
                 if(a->confac(i,j-1,k)==0)
                 {
                 nn=count;
                 count++;
                 a->confac(i,j-1,k)=count;
                 }

                 if(a->confac(i,j-1,k)>0)
                 nn=a->confac(i,j-1,k);

             a->facet[nn][a->numfac(i,j-1,k)]=ptcount;
             a->numfac(i,j-1,k)++;
             a->xdir(i,j-1,k)=pent->xdir(i,j-1,k);
             a->ydir(i,j-1,k)=pent->ydir(i,j-1,k);
             a->zdir(i,j-1,k)=pent->zdir(i,j-1,k);
             }

             // --
             if(a->flag(i,j,k)>-21 && pent->inbound(i,j,k)==1)
             {
                 if(a->confac(i,j,k)==0)
                 {
                 nn=count;
                 count++;
                 a->confac(i,j,k)=count;
                 }

                 if(a->confac(i,j,k)>0)
                 nn=a->confac(i,j,k);

             a->facet[nn][a->numfac(i,j,k)]=ptcount;
             a->numfac(i,j,k)++;
             a->xdir(i,j,k)=pent->xdir(i,j,k);
             a->ydir(i,j,k)=pent->ydir(i,j,k);
             a->zdir(i,j,k)=pent->zdir(i,j,k);
             }
         }// -.-

// ----- On Node ---------------------------------------------------------------

        // --------------------------------------
        if((xx0>=xc-eps && xx0<xc+eps))
        {
            if(k==1)
            onnode++;

        // 1 : (i,j)

             if(pent->inbound_onnode(i,j,k)==1)
             {
                 // --
                 if(a->flag(i,j,k)>-21 && pent->inbound(i,j,k)==1)
                 {
                     if(a->confac(i,j,k)==0)
                     {
                     nn=count;
                     count++;
                     a->confac(i,j,k)=count;
                     }

                     if(a->confac(i,j,k)>0)
                     nn=a->confac(i,j,k);

                 a->facet[nn][a->numfac(i,j,k)]=ptcount;
                 a->numfac(i,j,k)++;
                 a->xdir(i,j,k)=pent->xdir(i,j,k);
                 a->ydir(i,j,k)=pent->ydir(i,j,k);
                 a->zdir(i,j,k)=pent->zdir(i,j,k);

                 if(k==1)
            onnode_fill++;
                 }

                 // --
                 if(a->flag(i,j,k-1)>-21 && pent->inbound(i,j,k-1)==1)
                 {
                     if(a->confac(i,j,k-1)==0)
                     {
                     nn=count;
                     count++;
                     a->confac(i,j,k-1)=count;
                     }

                     if(a->confac(i,j,k-1)>0)
                     nn=a->confac(i,j,k-1);

                 a->facet[nn][a->numfac(i,j,k-1)]=ptcount;
                 a->numfac(i,j,k-1)++;
                 a->xdir(i,j,k-1)=pent->xdir(i,j,k-1);
                 a->ydir(i,j,k-1)=pent->ydir(i,j,k-1);
                 a->zdir(i,j,k-1)=pent->zdir(i,j,k-1);
                 }
             }


        // 2  (i,j-1)

             if(pent->inbound_onnode(i,j-1,k)==1)
             {
                   // --
                 if(a->flag(i,j-1,k)>-21 && pent->inbound(i,j-1,k)==1)
                 {
                     if(a->confac(i,j-1,k)==0)
                     {
                     nn=count;
                     count++;
                     a->confac(i,j-1,k)=count;
                     }

                     if(a->confac(i,j-1,k)>0)
                     nn=a->confac(i,j-1,k);


                 a->facet[nn][a->numfac(i,j-1,k)]=ptcount;
                 a->numfac(i,j-1,k)++;
                 a->xdir(i,j-1,k)=pent->xdir(i,j-1,k);
                 a->ydir(i,j-1,k)=pent->ydir(i,j-1,k);
                 a->zdir(i,j-1,k)=pent->zdir(i,j-1,k);

                 if(k==1)
                onnode_fill++;
                 }

                  // --
                 if(a->flag(i,j-1,k-1)>-21 && pent->inbound(i,j-1,k-1)==1)
                 {
                     if(a->confac(i,j-1,k-1)==0)
                     {
                     nn=count;
                     count++;
                     a->confac(i,j-1,k-1)=count;
                     }

                     if(a->confac(i,j-1,k-1)>0)
                     nn=a->confac(i,j-1,k-1);


                 a->facet[nn][a->numfac(i,j-1,k-1)]=ptcount;
                 a->numfac(i,j-1,k-1)++;
                 a->xdir(i,j-1,k-1)=pent->xdir(i,j-1,k-1);
                 a->ydir(i,j-1,k-1)=pent->ydir(i,j-1,k-1);
                 a->zdir(i,j-1,k-1)=pent->zdir(i,j-1,k-1);
                 }
             }



        // 3  (i-1,j-1)

             if(pent->inbound_onnode(i-1,j-1,k)==1)
             {
                  // --
                 if(a->flag(i-1,j-1,k)>-21 && pent->inbound(i-1,j-1,k)==1)
                 {
                     if(a->confac(i-1,j-1,k)==0)
                     {
                     nn=count;
                     count++;
                     a->confac(i-1,j-1,k)=count;
                     }

                     if(a->confac(i-1,j-1,k)>0)
                     nn=a->confac(i-1,j-1,k);


                 a->facet[nn][a->numfac(i-1,j-1,k)]=ptcount;
                 a->numfac(i-1,j-1,k)++;
                 a->xdir(i-1,j-1,k)=pent->xdir(i-1,j-1,k);
                 a->ydir(i-1,j-1,k)=pent->ydir(i-1,j-1,k);
                 a->zdir(i-1,j-1,k)=pent->zdir(i-1,j-1,k);

                 if(k==1)
            onnode_fill++;
                 }


                // --
                 if(a->flag(i-1,j-1,k-1)>-21 && pent->inbound(i-1,j-1,k-1)==1)
                 {
                     if(a->confac(i-1,j-1,k-1)==0)
                     {
                     nn=count;
                     count++;
                     a->confac(i-1,j-1,k-1)=count;
                     }

                     if(a->confac(i-1,j-1,k-1)>0)
                     nn=a->confac(i-1,j-1,k-1);


                 a->facet[nn][a->numfac(i-1,j-1,k-1)]=ptcount;
                 a->numfac(i-1,j-1,k-1)++;
                 a->xdir(i-1,j-1,k-1)=pent->xdir(i-1,j-1,k-1);
                 a->ydir(i-1,j-1,k-1)=pent->ydir(i-1,j-1,k-1);
                 a->zdir(i-1,j-1,k-1)=pent->zdir(i-1,j-1,k-1);
                 }
             }

        // 4   (i-1,j)
             if(pent->inbound_onnode(i-1,j,k)==1)
             {
                // --
                 if(a->flag(i-1,j,k)>-21 && pent->inbound(i-1,j,k)==1)
                 {
                     if(a->confac(i-1,j,k)==0)
                     {
                     nn=count;
                     count++;
                     a->confac(i-1,j,k)=count;
                     }

                     if(a->confac(i-1,j,k)>0)
                     nn=a->confac(i-1,j,k);

                 a->facet[nn][a->numfac(i-1,j,k)]=ptcount;
                 a->numfac(i-1,j,k)++;
                 a->xdir(i-1,j,k)=pent->xdir(i-1,j,k);
                 a->ydir(i-1,j,k)=pent->ydir(i-1,j,k);
                 a->zdir(i-1,j,k)=pent->zdir(i-1,j,k);

                 if(k==1)
            onnode_fill++;
                 }


                 // --
                 if(a->flag(i-1,j,k-1)>-21 && pent->inbound(i-1,j,k-1)==1)
                 {
                     if(a->confac(i-1,j,k-1)==0)
                     {
                     nn=count;
                     count++;
                     a->confac(i-1,j,k-1)=count;
                     }

                     if(a->confac(i-1,j,k-1)>0)
                     nn=a->confac(i-1,j,k-1);

                 a->facet[nn][a->numfac(i-1,j,k-1)]=ptcount;
                 a->numfac(i-1,j,k-1)++;
                 a->xdir(i-1,j,k-1)=pent->xdir(i-1,j,k-1);
                 a->ydir(i-1,j,k-1)=pent->ydir(i-1,j,k-1);
                 a->zdir(i-1,j,k-1)=pent->zdir(i-1,j,k-1);
                 }
             }
        }
    }

// ----------------------------------------------------------------
//yyyy

         if(yy0>=yc+eps && yy0<yc+p->DY[JP]-eps)
         {
         ptcount++;
         a->ccpoint[ptcount][0]=xc;
         a->ccpoint[ptcount][1]=yy0;
         a->ccpoint[ptcount][2]=zc;

         if(yy0>=yc+eps && yy0<yc+p->DY[JP]-eps)
         {

            // --
            if(a->flag(i-1,j,k-1)>-21 && pent->inbound(i-1,j,k-1)==1)
            {
                 if(a->confac(i-1,j,k-1)==0)
                 {
                 nn=count;
                 count++;
                 a->confac(i-1,j,k-1)=count;
                 }

                 if(a->confac(i-1,j,k-1)>0)
                 nn=a->confac(i-1,j,k-1);

             a->facet[nn][a->numfac(i-1,j,k-1)]=ptcount;
             a->numfac(i-1,j,k-1)++;
             a->xdir(i-1,j,k-1)=pent->xdir(i-1,j,k-1);
             a->ydir(i-1,j,k-1)=pent->ydir(i-1,j,k-1);
             a->zdir(i-1,j,k-1)=pent->zdir(i-1,j,k-1);
             }

             // --
             if(a->flag(i,j,k-1)>-21 && pent->inbound(i,j,k-1)==1)
             {
                 if(a->confac(i,j,k-1)==0)
                 {
                 nn=count;
                 count++;
                 a->confac(i,j,k-1)=count;
                 }

                 if(a->confac(i,j,k-1)>0)
                 nn=a->confac(i,j,k-1);

             a->facet[nn][a->numfac(i,j,k-1)]=ptcount;
             a->numfac(i,j,k-1)++;
             a->xdir(i,j,k-1)=pent->xdir(i,j,k-1);
             a->ydir(i,j,k-1)=pent->ydir(i,j,k-1);
             a->zdir(i,j,k-1)=pent->zdir(i,j,k-1);
             }

             // --
             if(a->flag(i-1,j,k)>-21 && pent->inbound(i-1,j,k)==1)
             {
                 if(a->confac(i-1,j,k)==0)
                 {
                 nn=count;
                 count++;
                 a->confac(i-1,j,k)=count;
                 }

                 if(a->confac(i-1,j,k)>0)
                 nn=a->confac(i-1,j,k);

             a->facet[nn][a->numfac(i-1,j,k)]=ptcount;
             a->numfac(i-1,j,k)++;
             a->xdir(i-1,j,k)=pent->xdir(i-1,j,k);
             a->ydir(i-1,j,k)=pent->ydir(i-1,j,k);
             a->zdir(i-1,j,k)=pent->zdir(i-1,j,k);
             }

             // --
             if(a->flag(i,j,k)>-21 && pent->inbound(i,j,k)==1)
             {
                 if(a->confac(i,j,k)==0)
                 {
                 nn=count;
                 count++;
                 a->confac(i,j,k)=count;
                 }

                 if(a->confac(i,j,k)>0)
                 nn=a->confac(i,j,k);

             a->facet[nn][a->numfac(i,j,k)]=ptcount;
             a->numfac(i,j,k)++;
             a->xdir(i,j,k)=pent->xdir(i,j,k);
             a->ydir(i,j,k)=pent->ydir(i,j,k);
             a->zdir(i,j,k)=pent->zdir(i,j,k);
             }
         }

         }

     }
     }

    a->facetcount=count;
    a->ccpointcount=ptcount;

    cout<<"cceout<< "<<a->facetcount<<" ccpoint: "<<a->ccpointcount<<" onnode: "<<onnode<<" onnodefill: "<<onnode_fill<<endl;

}




