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

#include"cce3D.h"
#include"dive.h"
#include"lexer.h"
#include"entity.h"

cce3D::cce3D(lexer *p, dive *a) : eps(1.0e-5*p->dx),psi(1.2*p->dx)
{
	cceout.open("DIVEMesh-CCE3D.txt");
}

cce3D::~cce3D()
{
}

void cce3D::start(lexer* p, dive* a, entity *pent)
{
     ini(p,a,pent);
	 int vertice=0;
	 
     /*
    NODELOOP
    {
    if(p->DX[IP]<p->dx-eps || p->DX[IP]>p->dx+eps)
    cout<<"DX: "<<p->DX[IP]<<" i: "<<i<<" j: "<<j<<" k: "<<k<<endl;
    
    if(p->DY[JP]<p->dx-eps || p->DY[JP]>p->dx+eps)
    cout<<"DY: "<<p->DY[JP]<<" i: "<<i<<" j: "<<j<<" k: "<<k<<endl;
    
    if(p->DZ[KP]<p->dx-eps || p->DZ[KP]>p->dx+eps)
    cout<<"DZ: "<<p->DZ[KP]<<" i: "<<i<<" j: "<<j<<" k: "<<k<<endl;
    }*/
    

// 1st round: check onnode
	 MALOOP
	 a->onnode(i,j,k)=0;  
	 	 
	 NODELOOP
     {
     xc = p->XN[IP];
     yc = p->YN[JP];
     zc = p->ZN[KP];
	

     if(xc>=xsmall-p->DX[IM1] && xc<=xlarge+p->DX[IP1])
     if(yc>=ysmall-p->DY[JM1] && yc<=ylarge+p->DY[JP1])
     if(zc>=zsmall-p->DZ[KM1] && zc<=zlarge+p->DZ[KP1])
     {
		 xx0 = pent->fx(p,a,i,j,k);
		 yy0 = pent->fy(p,a,i,j,k);
		 zz0 = pent->fz(p,a,i,j,k);
		
		 //1
		 if(xx0>=xc-eps && xx0<xc+p->DX[IP]-eps)
		 if(xx0>=xsmall-p->DX[IM1] && xx0<=xlarge+p->DX[IP1])
		 {
			 // 1.1 xx0
			 if(xx0>=xc+eps && xx0<xc+p->DX[IP]-eps)
			 {
				 a->onnode(i,j,k)+=1;
				 a->onnode(i,j-1,k)+=1;
				 a->onnode(i,j,k-1)+=1;
				 a->onnode(i,j-1,k-1)+=1;
				 ++vertice;
			 }
			
			 // 1.2 onnode ijk
			 if(xx0>=xc-eps && xx0<xc+eps)
			 {
				 a->onnode(i,j,k)+=1;
				 a->onnode(i-1,j,k)+=1;
				 a->onnode(i,j-1,k)+=1;
				 a->onnode(i-1,j-1,k)+=1;
				 a->onnode(i,j,k-1)+=1;
				 a->onnode(i-1,j,k-1)+=1;
				 a->onnode(i,j-1,k-1)+=1;
				 a->onnode(i-1,j-1,k-1)+=1;
				 ++vertice;
			 }
		 }

		// 2 yyo
		 if(yy0>=yc+eps && yy0<yc+p->DY[JP]-eps)
		 if(yy0>=ysmall-p->DY[JM1] && yy0<=ylarge+p->DY[JP1])
		 {
				 a->onnode(i,j,k)+=1;
				 a->onnode(i,j,k-1)+=1;
				 a->onnode(i-1,j,k)+=1;
				 a->onnode(i-1,j,k-1)+=1;
				 ++vertice;
		 }

		 // 3 zz0
		 if(zz0>=zc+eps && zz0<zc+p->DZ[KP]-eps)
		 if(zz0>=zsmall-p->DZ[KM1] && zz0<=zlarge+p->DZ[KP1])
		 {
				 a->onnode(i,j,k)+=1;
				 a->onnode(i,j-1,k)+=1;
				 a->onnode(i-1,j,k)+=1;
				 a->onnode(i-1,j-1,k)+=1;
				 ++vertice;
		 }
     }
     }

	cceout<<"vertices: "<<vertice<<endl;
// 2nd round: cut cells

     NODELOOP
     {
     xc = p->XN[IP];
     yc = p->YN[JP];
     zc = p->ZN[KP];
	 

     if(xc>=xsmall-p->DX[IM1] && xc<=xlarge+p->DX[IP1])
     if(yc>=ysmall-p->DY[JM1] && yc<=ylarge+p->DY[JP1])
     if(zc>=zsmall-p->DZ[KM1] && zc<=zlarge+p->DZ[KP1])
     {
		 xx0 = pent->fx(p,a,i,j,k);
		 yy0 = pent->fy(p,a,i,j,k);
		 zz0 = pent->fz(p,a,i,j,k);
		
		 //1
		 if(xx0>=xc-eps && xx0<xc+p->DX[IP]-eps)
		 if(xx0>=xsmall-p->DX[IM1] && xx0<=xlarge+p->DX[IP1])
		 {
			 // 1.1 xx0
			 if(xx0>=xc+eps && xx0<xc+p->DX[IP]-eps)
			 {
				 ++ptcount;
				 a->ccpoint[ptcount][0]=xx0;
				 a->ccpoint[ptcount][1]=yc;
				 a->ccpoint[ptcount][2]=zc;

				 if(a->onnode(i,j,k)>2)
				 addcell(p,a,pent,i,j,k);

				 if(a->onnode(i,j-1,k)>2)
				 addcell(p,a,pent,i,j-1,k);

				 if(a->onnode(i,j,k-1)>2)
				 addcell(p,a,pent,i,j,k-1);

				 if(a->onnode(i,j-1,k-1)>2)
				 addcell(p,a,pent,i,j-1,k-1);
			 }

			 // 1.2 onnode ijk
			 if(xx0>=xc-eps && xx0<xc+eps)
			 {
				 ++ptcount;
				 a->ccpoint[ptcount][0]=xx0;
				 a->ccpoint[ptcount][1]=yc;
				 a->ccpoint[ptcount][2]=zc;

				 if(a->onnode(i,j,k)>2)
				 addcell(p,a,pent,i,j,k);

				 if(a->onnode(i-1,j,k)>2)
				 addcell(p,a,pent,i-1,j,k);

				 if(a->onnode(i,j-1,k)>2)
				 addcell(p,a,pent,i,j-1,k);

				 if(a->onnode(i-1,j-1,k)>2)
				 addcell(p,a,pent,i-1,j-1,k);

				 if(a->onnode(i,j,k-1)>2)
				 addcell(p,a,pent,i,j,k-1);

				 if(a->onnode(i-1,j,k-1)>2)
				 addcell(p,a,pent,i-1,j,k-1);

				 if(a->onnode(i,j-1,k-1)>2)
				 addcell(p,a,pent,i,j-1,k-1);

				 if(a->onnode(i-1,j-1,k-1)>2)
				 addcell(p,a,pent,i-1,j-1,k-1);
			 }
		 }

		// 2 yyo
		 if(yy0>=yc+eps && yy0<yc+p->DY[JP]-eps)
		 if(yy0>=ysmall-p->DY[JM1] && yy0<=ylarge+p->DY[JP1])
		 {
				 ++ptcount;
				 a->ccpoint[ptcount][0]=xc;
				 a->ccpoint[ptcount][1]=yy0;
				 a->ccpoint[ptcount][2]=zc;

				 if(a->onnode(i,j,k)>2)
				 addcell(p,a,pent,i,j,k);

				 if(a->onnode(i,j,k-1)>2)
				 addcell(p,a,pent,i,j,k-1);

				 if(a->onnode(i-1,j,k)>2)
				 addcell(p,a,pent,i-1,j,k);

				 if(a->onnode(i-1,j,k-1)>2)
				 addcell(p,a,pent,i-1,j,k-1);
		 }

		 // 3 zz0
		 if(zz0>=zc+eps && zz0<zc+p->DZ[KP]-eps)
		 if(zz0>=zsmall-p->DZ[KM1] && zz0<=zlarge+p->DZ[KP1])
		 {
				 ++ptcount;
				 a->ccpoint[ptcount][0]=xc;
				 a->ccpoint[ptcount][1]=yc;
				 a->ccpoint[ptcount][2]=zz0;

				 if(a->onnode(i,j,k)>2)
				 addcell(p,a,pent,i,j,k);

				 if(a->onnode(i,j-1,k)>2)
				 addcell(p,a,pent,i,j-1,k);

				 if(a->onnode(i-1,j,k)>2)
				 addcell(p,a,pent,i-1,j,k);

				 if(a->onnode(i-1,j-1,k)>2)
				 addcell(p,a,pent,i-1,j-1,k);
		 }
     }
     }

    a->facetcount=count;
    a->ccpointcount=ptcount;

    cceout<<"facet: "<<a->facetcount<<" ccpoint: "<<a->ccpointcount<<" onnode: "<<onnode<<" onnodefill: "<<onnode_fill<<endl;
}

