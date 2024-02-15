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

#include"decomp.h"

void decomp::partition_correct_x(lexer* p, dive* a)
{	
	int q,ii;
	double diff_p;
	int fac,mincell,maxcell,iloc,iloc_min,iloc_max;
	double diff;
	
	xcount[0]=0;

	
	// x-partition
	for(aa=1;aa<=a->mx;++aa)
	{
		xcount[aa]=0;
		for(i=a->xnode[aa-1];i<a->xnode[aa];++i)
		for(j=0;j<a->knoy;++j)
		for(k=0;k<a->knoz;++k)
		if(a->flag(i,j,k)>0 && a->solid(i,j,k)>0)
		++xcount[aa];
	}
	
	for(i=0;i<a->knox;++i)
	xcross[i]=0;
	
	for(i=0;i<a->knox;++i)
	for(j=0;j<a->knoy;++j)
	for(k=0;k<a->knoz;++k)
	if(a->flag(i,j,k)>0 && a->solid(i,j,k)>0)
	++xcross[i];
	
	xcross_m=0;
	for(i=0;i<a->knox;++i)
	xcross_m+=xcross[i];
	
	xcross_m=xcross_m/a->knox;
	
		
	xaverage=0;
	for(aa=1;aa<=a->mx;++aa)
	xaverage+=xcount[aa];
	
	xaverage/=a->mx;
	
	cout<<"xaverage: "<<xaverage<<endl;
	cout<<"xcross_m: "<<xcross_m<<endl;
	
	xcount_sum=0;
	for(aa=1;aa<=a->mx;++aa)
	xcount_sum+=xcount[aa];
	
	for(aa=0;aa<=a->mx;++aa)
	cout<<"old xcount"<<aa<<" :"<<xcount[aa]<<"  xnode: "<<a->xnode[aa]<<"  xorig: "<<a->xorig[aa]<<endl;
	
	cout<<"xcount_sum: "<<xcount_sum<<endl;
	
	for(q=0;q<p->M10;++q)
	subcell[q]=0;

	
	q=0;
	NLOOP
	{
    SUBLOOP
	if(a->flag(i,j,k)>0 && a->solid(i,j,k)>0)
	++subcell[q];
	
	++q;
	}
	
	for(q=0;q<p->M10;++q)
	cout<<"old subcell_count: "<<subcell[q]<<endl;
	
	// re-partition
	for(aa=1;aa<=a->mx;++aa)
	{
		for(ii=0;ii<a->knox;++ii)
		{

			a->xnode[aa]=ii;
			
			xcount[aa]=0;
			for(i=a->xnode[aa-1];i<a->xnode[aa];++i)
			for(j=0;j<a->knoy;++j)
			for(k=0;k<a->knoz;++k)
			if(a->flag(i,j,k)>0 && a->solid(i,j,k)>0)
			++xcount[aa];
			
			if(xcount[aa]>xaverage)
			{	
			diff_p=xcount[aa]-xaverage;
			
			//if(diff_p>xcross_m/2)
			--a->xnode[aa];
			
			break;
			}
		}
	}
	
	a->xnode[a->mx]=a->knox;
	
	// check last
	for(aa=1;aa<=a->mx;++aa)
	{
		xcount[aa]=0;
		for(i=a->xnode[aa-1];i<a->xnode[aa];++i)
		for(j=0;j<a->knoy;++j)
		for(k=0;k<a->knoz;++k)
		if(a->flag(i,j,k)>0 && a->solid(i,j,k)>0)
		++xcount[aa];
	}
	
	
	mincell=1e9;
	for(aa=1;aa<a->mx;++aa)
	mincell=MIN(mincell,xcount[aa]);
	
	if(xcount[a->mx]>xaverage+xcross_m/2)
	{
	
		for(aa=0;aa<=a->mx;++aa)
		cout<<"inter xcount"<<aa<<" :"<<xcount[aa]<<"  xnode: "<<a->xnode[aa]<<"  xorig: "<<a->xorig[aa]<<endl;
	
		diff = xcount[a->mx]-xaverage;
		fac = diff/xcross_m;
		
		cout<<xcount[a->mx]<<"  ACTION!!!  fac: "<<fac<<" mincell: "<<mincell<<endl;
		
		count=0;
		do{
			
			mincell=1e9;
			for(aa=1;aa<a->mx;++aa)
			if(xcount[aa]<mincell)
			{
			iloc=aa;
			mincell=xcount[aa];
			}
			
			cout<<"Mincell: "<<mincell<<"  iloc: "<<iloc<<endl;
			
			for(ii=iloc;ii<a->mx;++ii)
			++a->xnode[ii];


			for(aa=1;aa<=a->mx;++aa)
			{
			xcount[aa]=0;
			for(i=a->xnode[aa-1];i<a->xnode[aa];++i)
			for(j=0;j<a->knoy;++j)
			for(k=0;k<a->knoz;++k)
			if(a->flag(i,j,k)>0 && a->solid(i,j,k)>0)
			++xcount[aa];
			}
			
			
		if(xcount[a->mx]<xaverage+xcross_m/5)
		break;
		++count;
		
		}while(xcount[a->mx]>xaverage+xcross_m/2);
		
		// 
		count=0;
		do{
			mincell=1e9;
			for(aa=1;aa<=a->mx;++aa)
			if(xcount[aa]<mincell)
			{
			iloc_min=aa;
			mincell=MIN(mincell,xcount[aa]);
			}
			
			maxcell=-1e9;
			for(aa=1;aa<=a->mx;++aa)
			if(xcount[aa]>maxcell)
			{
			iloc_max=aa;
			maxcell=MAX(maxcell,xcount[aa]);
			}
			
			cout<<"count: "<<count<<" Maxcell: "<<maxcell<<" xaverage+xcross_m/2: "<<xaverage+xcross_m/2<<"  iloc_max: "<<iloc_max<<"  Mincell: "<<mincell<<"  iloc_min: "<<iloc_min<<endl;
			
			if(iloc_max<iloc_min)
			for(ii=iloc_max;ii<iloc_min;++ii)
			--a->xnode[ii];
			
			if(iloc_max>iloc_min)
			for(ii=iloc_min;ii<iloc_max;++ii)
			++a->xnode[ii];


			for(aa=1;aa<=a->mx;++aa)
			{
			xcount[aa]=0;
			for(i=a->xnode[aa-1];i<a->xnode[aa];++i)
			for(j=0;j<a->knoy;++j)
			for(k=0;k<a->knoz;++k)
			if(a->flag(i,j,k)>0 && a->solid(i,j,k)>0)
			++xcount[aa];
			}
			
			maxcell=-1e9;
			for(aa=1;aa<=a->mx;++aa)
			if(xcount[aa]>maxcell)
			{
			iloc_max=aa;
			maxcell=xcount[aa];
			}
			

		++count;
		
		}while(maxcell>xaverage+xcross_m/2 && count<p->M10*5);
	}
	
	//count again
	for(aa=1;aa<=a->mx;++aa)
	{
		xcount[aa]=0;
		for(i=a->xnode[aa-1];i<a->xnode[aa];++i)
		for(j=0;j<a->knoy;++j)
		for(k=0;k<a->knoz;++k)
		if(a->flag(i,j,k)>0 && a->solid(i,j,k)>0)
		++xcount[aa];
	}
	
	for(aa=0;aa<=a->mx;++aa)
    a->xorig[aa] = p->XN[a->xnode[aa]+marge];
	
    
	xcount_sum=0;
	for(aa=1;aa<=a->mx;++aa)
	xcount_sum+=xcount[aa];
	
	
	for(aa=0;aa<=a->mx;++aa)
	cout<<"new xcount"<<aa<<" :"<<xcount[aa]<<"  xnode: "<<a->xnode[aa]<<"  xorig: "<<a->xorig[aa]<<endl;
	
	cout<<"xcount_sum: "<<xcount_sum<<endl;
	
	
	MALOOP
    a->subgrid(i,j,k)=-1;

    NLOOP
    SUBLOOP
    {
    a->subgrid(i,j,k)=PARANUM;
    a->subslice(i,j)=PARANUM;
    }
	

	for(q=0;q<p->M10;++q)
	subcell[q]=0;

	
	q=0;
	NLOOP
	{
    SUBLOOP
	if(a->flag(i,j,k)>0 && a->solid(i,j,k)>0)
	++subcell[q];
	
	++q;
	}
	
	for(q=0;q<p->M10;++q)
	cout<<q<<" new subcell_count: "<<subcell[q]<<endl;
	

}

	