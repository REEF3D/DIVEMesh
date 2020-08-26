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
#include"inverse_dist.h"
#include"inverse_dist_local.h"
#include"kriging.h"

geodat::geodat(lexer *p, dive *a)
{
    dd=3;
    
    printcount=0;

    for(n=0; n<p->G10; ++n)
    {
    p->G10_x[n] *= p->G12_x;
    p->G10_y[n] *= p->G12_y;
    p->G10_z[n] *= p->G12_z;
    }

    for(n=0; n<p->G10; ++n)
    {
    p->G10_x[n] += p->G11_x;
    p->G10_y[n] += p->G11_y;
    p->G10_z[n] += p->G11_z;
    }
	
	if(p->G23==1)
	for(n=0; n<p->G10; ++n)
	p->G10_z[n] *= -1.0;
    
    
    if(p->G15==1)
    pipol = new inverse_dist(p,a);
    
    if(p->G15==2)
    pipol = new inverse_dist_local(p,a);
    
    if(p->G15==3)
    pipol = new kriging(p,a,p->G10,p->G10_x,p->G10_y,p->G10_z);
    
    p->Np=p->G10;
     print(p,a);
     
     p->Darray(XC,p->knox+14);
     p->Darray(YC,p->knoy+14);
     
}

geodat::~geodat()
{
}

void geodat::start(lexer* p, dive* a)
{
    cout<<"geodat  Np_0: "<<p->G10<<endl;
    p->Np=p->G10;
    
    setup_ijk(p,a,p->G10_x,p->G10_y,p->G10_z,p->XP,p->YP,p->knox,p->knoy);
    pointcheck(p,a,p->G10_x,p->G10_y,p->G10_z);
    
    print(p,a);
    
    coarsen(p,a);

    pipol->start(p,a,Np,p->G10_x,p->G10_y,p->G10_z,XC,YC,kx,ky,topof);
    
    prolong(p,a);
    
    dryside(p,a);
	
	XYLOOP
	a->bedlevel(i,j) = MAX(a->bedlevel(i,j),a->topo(i,j));
}

void geodat::gcb_estimate(lexer *p, dive *a)
{
	int qn;
    double zval;
    
    intfield gd(p);
	
	for(qn=0; qn<p->M10;qn++)
	a->geodat_gcb[qn]=0;
    
    MALOOP
    gd(i,j,k)=-1;
    
    LOOP
    {
    zval = p->ZP[KP] + p->zmin;
 
    if(zval>=a->topo(i,j))
    gd(i,j,k)=1;
    }

	n=0;
	NLOOP
	{
		SUBLOOP
		{
            if(gd(i,j,k)==1 && (gd(i-1,j,k)==-1 || gd(i+1,j,k)==-1 || gd(i,j-1,k)==-1 || gd(i,j+1,k)==-1 || gd(i,j,k-1)==-1 || gd(i,j,k+1)==-1))
            ++a->geodat_gcb[n];

		}
	++n;
	}
    
    //for(qn=0; qn<p->M10;qn++)
	//cout<<qn<<" gcb_estimate: "<<a->geodat_gcb[qn]<<endl;
	
}

void geodat::dryside(lexer *p, dive *a)
{
    if(p->G24==1)
    XYLOOP
    if(a->topo(i,j)>p->G24_h)
    a->topo(i,j) += p->G24_dz;
    
    if(p->G25==1)
    XYLOOP
    if(a->topo(i,j)>p->G25_h)
    a->topo(i,j) *= p->G25_fz;  
    
    // smoothing
    k=0;
	XYLOOP
	if(a->flag(i,j,k)>0)
	{
	
		if(a->flag(i-1,j,k)<0)
		a->topo(i-1,j) = a->topo(i,j);
		
		if(a->flag(i+1,j,k)<0)
		a->topo(i+1,j) = a->topo(i,j);
		
		if(a->flag(i,j-1,k)<0)
		a->topo(i,j-1) = a->topo(i,j);
		
		if(a->flag(i,j+1,k)<0)
		a->topo(i,j+1) = a->topo(i,j);
	}
    
    k=0;
	for(n=0;n<p->G31;++n)
	XYLOOP
	if(a->flag(i,j,k)>0)
    a->topo(i,j) = p->G32*a->topo(i,j) + 0.25*(1.0-p->G32)*(a->topo(i-1,j) + a->topo(i+1,j) + a->topo(i,j-1) + a->topo(i,j+1)); 
}



