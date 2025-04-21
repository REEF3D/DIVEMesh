/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2025 Hans Bihs

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

void decomp::partition_correct_y(lexer* p, dive* a)
{
	int q,jj;
	double diff_p;
	
	ycount[0]=0;
    
	cout<<"starting y-dir partition correction"<<endl;
    
	// y-partition
	for(bb=1;bb<=a->my;++bb)
	{
		ycount[bb]=0;
		for(j=a->ynode[bb-1];j<a->ynode[bb];++j)
		for(i=0;i<a->knox;++i)
		for(k=0;k<a->knoz;++k)
		if(a->flag(i,j,k)>0 && a->solid(i,j,k)>0)
		++ycount[bb];
	}

    
	for(j=0;j<a->knoy;++j)
	ycross[j]=0;
	
	for(i=0;i<a->knox;++i)
	for(j=0;j<a->knoy;++j)
	for(k=0;k<a->knoz;++k)
	if(a->flag(i,j,k)>0 && a->solid(i,j,k)>0)
	++ycross[j];

	ycross_m=0;
	for(j=0;j<a->knoy;++j)
	ycross_m+=ycross[j];

	ycross_m=ycross_m/a->knoy;
	
    
	yaverage=0;
	for(bb=1;bb<=a->my;++bb)
	yaverage+=ycount[bb];
    
	
	yaverage/=a->my;

	ddout<<"yaverage: "<<yaverage<<endl;
	ddout<<"ycross_m: "<<ycross_m<<endl;
	
	ycount_sum=0;
	for(bb=1;bb<=a->my;++bb)
	ycount_sum+=ycount[bb];
    

	for(bb=1;bb<=a->my;++bb)
	ddout<<"old ycount"<<bb<<" :"<<ycount[bb]<<"  ynode: "<<a->ynode[bb]<<"  yorig: "<<a->yorig[bb]<<endl;
	
	ddout<<"ycount_sum: "<<xcount_sum<<endl;
	
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
	ddout<<"old subcell_count: "<<subcell[q]<<endl;

	// re-partition
	for(bb=1;bb<=a->my;++bb)
	{
		for(jj=0;jj<a->knoy;++jj)
		{

			a->ynode[bb]=jj;
			
			ycount[bb]=0;
			for(j=a->ynode[bb-1];j<a->ynode[bb];++j)
			for(i=0;i<a->knox;++i)
			for(k=0;k<a->knoz;++k)
			if(a->flag(i,j,k)>0 && a->solid(i,j,k)>0)
			++ycount[bb];
			
			if(ycount[bb]>yaverage)
			{	
			diff_p=ycount[bb]-yaverage;
			
			//if(diff_p>ycross_m/2)
			--a->ynode[bb];
			
			break;
			}
			
		}
	}


	a->ynode[a->my]=a->knoy;

	// check last
	for(bb=1;bb<=a->my;++bb)
	{
		ycount[bb]=0;
		for(j=a->ynode[bb-1];j<a->ynode[bb];++j)
		for(i=0;i<a->knox;++i)
		for(k=0;k<a->knoz;++k)
        //ddout<<j<<" "<<bb<<endl;
		if(a->flag(i,j,k)>0 && a->solid(i,j,k)>0)
		++ycount[bb];
	}
	int fac,mincell,jloc;
	double diff;
	
    
    
	mincell=1e9;
	for(bb=1;bb<a->my;++bb)
	mincell=MIN(mincell,ycount[bb]);
    
	
	if(ycount[a->my]>yaverage+ycross_m/2)
	{
	
		for(bb=0;bb<=a->my;++bb)
		ddout<<"inter ycount"<<bb<<" :"<<ycount[bb]<<"  ynode: "<<a->ynode[bb]<<"  yorig: "<<a->yorig[bb]<<endl;
	
		diff = ycount[a->my]-yaverage;
		fac = diff/ycross_m;
		
		ddout<<ycount[a->my]<<"  ACTION!!!  fac: "<<fac<<" mincell: "<<mincell<<endl;
		
		count=0;
		do{
			mincell=1e9;
			for(bb=1;bb<a->my;++bb)
			if(ycount[bb]<mincell)
			{
			jloc=bb;
			mincell=ycount[bb];
			}
			
			ddout<<"Mincell: "<<mincell<<"  jloc: "<<jloc<<endl;
			
			for(jj=jloc;jj<a->my;++jj)
			++a->ynode[jj];


			for(bb=1;bb<=a->my;++bb)
			{
				ycount[bb]=0;
				for(j=a->ynode[bb-1];j<a->ynode[bb];++j)
				for(i=0;i<a->knox;++i)
				for(k=0;k<a->knoz;++k)
				if(a->flag(i,j,k)>0 && a->solid(i,j,k)>0)
				++ycount[bb];
			}
			
		if(ycount[a->my]<yaverage+ycross_m/5)
		break;
		++count;
		
		}while(ycount[a->my]>yaverage+ycross_m/2);
	}
	
	// 
    int maxiter = MAX(a->mx,a->my);
    
	int maxcell,jloc_max,jloc_min;
		count=0;
		do{
			mincell=1e9;
			for(bb=1;bb<a->my;++bb)
			if(ycount[bb]<mincell)
			{
			jloc_min=bb;
			mincell=ycount[bb];
			}
			
			maxcell=-1e9;
			for(bb=1;bb<a->my;++bb)
			if(ycount[bb]>maxcell)
			{
			jloc_max=bb;
			maxcell=ycount[bb];
			}
			
			ddout<<"Maxcell: "<<maxcell<<"  jloc: "<<jloc_max<<"  Mincell: "<<mincell<<"  jloc: "<<jloc_min<<endl;
			
			if(jloc_max<jloc_min)
			for(jj=jloc_max;jj<jloc_min;++jj)
			--a->ynode[jj];
			
			if(jloc_max>jloc_min)
			for(jj=jloc_min;jj<jloc_max;++jj)
			++a->ynode[jj];


			for(bb=1;bb<=a->my;++bb)
			{
				ycount[bb]=0;
				for(j=a->ynode[bb-1];j<a->ynode[bb];++j)
				for(i=0;i<a->knox;++i)
				for(k=0;k<a->knoz;++k)
				if(a->flag(i,j,k)>0 && a->solid(i,j,k)>0)
				++ycount[bb];
			}
			
			maxcell=-1e9;
			for(bb=1;bb<a->my;++bb)
			if(ycount[bb]>maxcell)
			{
			jloc_max=bb;
			maxcell=ycount[bb];
			}
			

		++count;
		
		}while(maxcell>yaverage+ycross_m/2 && count<maxiter);


	//count again
	for(bb=1;bb<=a->my;++bb)
	{
		ycount[bb]=0;
		for(j=a->ynode[bb-1];j<a->ynode[bb];++j)
		for(i=0;i<a->knox;++i)
		for(k=0;k<a->knoz;++k)
		if(a->flag(i,j,k)>0 && a->solid(i,j,k)>0)
		++ycount[bb];
	}
    

	for(bb=0;bb<=a->my;++bb)
	a->yorig[bb] = p->YN[a->ynode[bb]+marge];
	

	ycount_sum=0;
	for(bb=1;bb<=a->my;++bb)
	ycount_sum+=ycount[bb];
	
    
	for(bb=0;bb<=a->my;++bb)
	ddout<<"new ycount"<<bb<<" :"<<ycount[bb]<<"  ynode: "<<a->ynode[bb]<<"  yorig: "<<a->yorig[bb]<<endl;
	
	ddout<<"ycount_sum: "<<ycount_sum<<endl;


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
	ddout<<q<<" new subcell_count: "<<subcell[q]<<endl;
}

