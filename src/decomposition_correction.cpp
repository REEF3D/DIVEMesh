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
--------------------------------------------------------------------*/

#include"decomposition.h"

void decomp::partition_correction(lexer* p, dive* a)
{
    cout<<" maindir: "<<maindir<<endl;
    
    
	if(maindir==1)
	partition_correct_x(p,a);
	
	if(maindir==2)
	partition_correct_y(p,a);
	
	if(maindir==3)
	partition_correct_z(p,a);
	
}
	
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
	
	ddout<<"xaverage: "<<xaverage<<endl;
	ddout<<"xcross_m: "<<xcross_m<<endl;
	
	xcount_sum=0;
	for(aa=1;aa<=a->mx;++aa)
	xcount_sum+=xcount[aa];
	
	for(aa=0;aa<=a->mx;++aa)
	ddout<<"old xcount"<<aa<<" :"<<xcount[aa]<<"  xnode: "<<a->xnode[aa]<<"  xorig: "<<a->xorig[aa]<<endl;
	
	ddout<<"xcount_sum: "<<xcount_sum<<endl;
	
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
		ddout<<"inter xcount"<<aa<<" :"<<xcount[aa]<<"  xnode: "<<a->xnode[aa]<<"  xorig: "<<a->xorig[aa]<<endl;
	
		diff = xcount[a->mx]-xaverage;
		fac = diff/xcross_m;
		
		ddout<<xcount[a->mx]<<"  ACTION!!!  fac: "<<fac<<" mincell: "<<mincell<<endl;
		
		count=0;
		do{
			
			mincell=1e9;
			for(aa=1;aa<a->mx;++aa)
			if(xcount[aa]<mincell)
			{
			iloc=aa;
			mincell=xcount[aa];
			}
			
			ddout<<"Mincell: "<<mincell<<"  iloc: "<<iloc<<endl;
			
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
			mincell=xcount[aa];
			}
			
			maxcell=-1e9;
			for(aa=1;aa<=a->mx;++aa)
			if(xcount[aa]>maxcell)
			{
			iloc_max=aa;
			maxcell=xcount[aa];
			}
			
			ddout<<"Maxcell: "<<maxcell<<"  iloc: "<<iloc_max<<"  Mincell: "<<mincell<<"  iloc: "<<iloc_min<<endl;
			
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
	ddout<<"new xcount"<<aa<<" :"<<xcount[aa]<<"  xnode: "<<a->xnode[aa]<<"  xorig: "<<a->xorig[aa]<<endl;
	
	ddout<<"xcount_sum: "<<xcount_sum<<endl;
	
	
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

	
void decomp::partition_correct_y(lexer* p, dive* a)
{
	int q,jj;
	double diff_p;
	
	ycount[0]=0;
	
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
        //cout<<j<<" "<<bb<<endl;
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
		
		}while(maxcell>yaverage+ycross_m/2 && count<p->M10*5);


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
	a->yorig[bb] = p->YN[a->ynode[bb]+marge]+p->ymin;
	

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
	
	ddout<<"zaverage: "<<zaverage<<endl;
	ddout<<"zcross_m: "<<zcross_m<<endl;
	
	zcount_sum=0;
	for(cc=1;cc<=a->mz;++cc)
	zcount_sum+=zcount[cc];
	
	for(cc=1;cc<=a->mz;++cc)
	ddout<<"old zcount"<<cc<<" :"<<zcount[cc]<<"  znode: "<<a->znode[cc]<<"  zorig: "<<a->zorig[cc]<<endl;
	
	ddout<<"zcount_sum: "<<zcount_sum<<endl;
	
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
		ddout<<"inter zcount"<<cc<<" :"<<zcount[cc]<<"  znode: "<<a->znode[cc]<<"  zorig: "<<a->zorig[cc]<<endl;
	
		diff = zcount[a->mz]-zaverage;
		fac = diff/zcross_m;
		
		ddout<<zcount[a->mz]<<"  ACTION!!!  fac: "<<fac<<" mincell: "<<mincell<<endl;
		
		count=0;
		do{
			mincell=1e9;
			for(cc=1;cc<=a->mz;++cc)
			if(zcount[cc]<mincell)
			{
			kloc=cc;
			mincell=zcount[aa];
			}
			
			ddout<<"Mincell: "<<mincell<<"  kloc: "<<kloc<<endl;
			
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
			
			ddout<<"Maxcell: "<<maxcell<<"  kloc: "<<kloc_max<<"  Mincell: "<<mincell<<"  kloc: "<<kloc_min<<endl;
			
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
	ddout<<"new zcount"<<cc<<" :"<<zcount[cc]<<"  znode: "<<a->znode[cc]<<"  zorig: "<<a->zorig[cc]<<endl;
	
	ddout<<"ccount_sum: "<<zcount_sum<<endl;
	
	
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
	
    
    for(bb=0;bb<=a->my;++bb)
	ddout<<"new ycount"<<bb<<" :"<<ycount[bb]<<"  xnode: "<<a->ynode[bb]<<"  xorig: "<<a->yorig[bb]<<endl;
	
	ddout<<"ycount_sum: "<<ycount_sum<<endl;
}
