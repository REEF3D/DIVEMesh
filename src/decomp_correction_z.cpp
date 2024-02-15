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
	
void decomp::partition_correct_z(lexer* p, dive* a)
{

	int q,kk;
	double diff_p;
	
	zcount[0]=0;
	
	// z-partition
	for(cc=1;cc<=a->mz;++cc)
	{
		zcount[cc]=0;
		for(k=a->znode[cc-1];k<a->znode[cc];++k)
		for(i=0;i<a->knox;++i)
		for(j=0;j<a->knoy;++j)
		if(a->flag(i,j,k)>0 && a->solid(i,j,k)>0)
		++zcount[cc];
	}
	
	for(k=0;k<a->knoz;++k)
	zcross[k]=0;
	
	for(i=0;i<a->knox;++i)
	for(j=0;j<a->knoy;++j)
	for(k=0;k<a->knoz;++k)
	if(a->flag(i,j,k)>0 && a->solid(i,j,k)>0)
	++zcross[k];
	
	zcross_m=0;
	for(k=0;k<a->knoz;++k)
	zcross_m+=zcross[k];
	
	zcross_m=zcross_m/a->knoz;
	
		
	zaverage=0;
	for(cc=1;cc<=a->mz;++cc)
	zaverage+=zcount[cc];
	
	zaverage/=a->mz;
	
	cout<<"zaverage: "<<zaverage<<endl;
	cout<<"zcross_m: "<<zcross_m<<endl;
	
	zcount_sum=0;
	for(cc=1;cc<=a->mz;++cc)
	zcount_sum+=zcount[cc];
	
	for(cc=1;cc<=a->mz;++cc)
	cout<<"old zcount"<<cc<<" :"<<zcount[cc]<<"  znode: "<<a->znode[cc]<<"  zorig: "<<a->zorig[cc]<<endl;
	
	cout<<"zcount_sum: "<<zcount_sum<<endl;
	
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
	for(cc=1;cc<=a->mz;++cc)
	{
		for(kk=0;kk<a->knoz;++kk)
		{

			a->znode[cc]=kk;
			
			zcount[cc]=0;
			for(k=a->znode[cc-1];k<a->znode[cc];++k)
			for(i=0;i<a->knox;++i)
			for(j=0;j<a->knoy;++j)
			if(a->flag(i,j,k)>0 && a->solid(i,j,k)>0)
			++zcount[cc];
			
			if(zcount[cc]>zaverage)
			{	
			diff_p=zcount[cc]-zaverage;
			
			//if(diff_p>zcross_m/2)
			--a->znode[cc];
			
			break;
			}
			
		}
	}
	
	a->znode[a->mz]=a->knoz;
	
	// check last
	for(cc=1;cc<=a->mz;++cc)
	{
		zcount[cc]=0;
		for(k=a->znode[cc-1];k<a->znode[cc];++k)
		for(i=0;i<a->knox;++i)
		for(j=0;j<a->knoy;++j)
		if(a->flag(i,j,k)>0 && a->solid(i,j,k)>0)
		++zcount[cc];
	}
	
	int fac,mincell,kloc;
	double diff;
	
	mincell=1e9;
	for(cc=1;cc<=a->mz;++cc)
	mincell=MIN(mincell,zcount[cc]);
	
	if(zcount[a->mz]>zaverage+zcross_m/2)
	{
	
		for(cc=1;cc<=a->mz;++cc)
		cout<<"inter zcount"<<cc<<" :"<<zcount[cc]<<"  znode: "<<a->znode[cc]<<"  zorig: "<<a->zorig[cc]<<endl;
	
		diff = zcount[a->mz]-zaverage;
		fac = diff/zcross_m;
		
		cout<<zcount[a->mz]<<"  ACTION!!!  fac: "<<fac<<" mincell: "<<mincell<<endl;
		
		count=0;
		do{
			mincell=1e9;
			for(cc=1;cc<=a->mz;++cc)
			if(zcount[cc]<mincell)
			{
			kloc=cc;
			mincell=zcount[aa];
			}
			
			cout<<"Mincell: "<<mincell<<"  kloc: "<<kloc<<endl;
			
			for(kk=kloc;kk<a->mz;++kk)
			++a->znode[kk];


			for(cc=1;cc<=a->mz;++cc)
			{
				zcount[cc]=0;
				for(k=a->znode[cc-1];k<a->znode[cc];++k)
				for(i=0;i<a->knox;++i)
				for(j=0;j<a->knoy;++j)
				if(a->flag(i,j,k)>0 && a->solid(i,j,k)>0)
				++zcount[cc];
			}
			
			
		if(zcount[a->mz]<zaverage+zcross_m/5)
		break;
		++count;
		
		}while(zcount[a->mz]>zaverage+zcross_m/2);
	}
	
	// 
	int maxcell,kloc_max,kloc_min;
		count=0;
		do{
			mincell=1e9;
			for(cc=1;cc<a->mz;++cc)
			if(zcount[cc]<mincell)
			{
			kloc_min=cc;
			mincell=zcount[cc];
			}
			
			maxcell=-1e9;
			for(cc=1;cc<a->mz;++cc)
			if(zcount[cc]>maxcell)
			{
			kloc_max=cc;
			maxcell=zcount[cc];
			}
			
			cout<<"Maxcell: "<<maxcell<<"  kloc: "<<kloc_max<<"  Mincell: "<<mincell<<"  kloc: "<<kloc_min<<endl;
			
			if(kloc_max<kloc_min)
			for(kk=kloc_max;kk<kloc_min;++kk)
			--a->znode[kk];
			
			if(kloc_max>kloc_min)
			for(kk=kloc_min;kk<kloc_max;++kk)
			++a->znode[kk];


			for(cc=1;cc<=a->mz;++cc)
			{
				zcount[cc]=0;
				for(k=a->znode[cc-1];k<a->znode[cc];++k)
				for(i=0;i<a->knox;++i)
				for(j=0;j<a->knoy;++j)
				if(a->flag(i,j,k)>0 && a->solid(i,j,k)>0)
				++zcount[cc];
			}
			
			maxcell=-1e9;
			for(cc=1;cc<a->mz;++cc)
			if(zcount[cc]>maxcell)
			{
			kloc_max=cc;
			maxcell=zcount[cc];
			}
			

		++count;
		
		}while(maxcell>zaverage+zcross_m/2 && count<p->M10*5);
	
	//count again
	for(cc=1;cc<=a->mz;++cc)
	{
		zcount[cc]=0;
		for(k=a->znode[cc-1];k<a->znode[cc];++k)
		for(i=0;i<a->knox;++i)
		for(j=0;j<a->knoy;++j)
		if(a->flag(i,j,k)>0 && a->solid(i,j,k)>0)
		++zcount[cc];
	}
	
	for(cc=0;cc<=a->mz;++cc)
	a->zorig[cc] = p->ZN[a->znode[cc]+marge]+p->zmin;
	
	zcount_sum=0;
	for(cc=1;cc<=a->mz;++cc)
	zcount_sum+=zcount[cc];
	
	
	for(cc=1;cc<=a->mz;++cc)
	cout<<"new zcount"<<cc<<" :"<<zcount[cc]<<"  znode: "<<a->znode[cc]<<"  zorig: "<<a->zorig[cc]<<endl;
	
	cout<<"ccount_sum: "<<zcount_sum<<endl;
	
	
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
	
    
    for(bb=0;bb<=a->my;++bb)
	cout<<"new ycount"<<bb<<" :"<<ycount[bb]<<"  xnode: "<<a->ynode[bb]<<"  xorig: "<<a->yorig[bb]<<endl;
	
	cout<<"ycount_sum: "<<ycount_sum<<endl;
}
