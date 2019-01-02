/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2019 Hans Bihs

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
#include"field2d.h"

decomp::decomp()
{

    ddout.open("DIVEMesh-Decomposition.txt");
}

decomp::~decomp()
{
}

void decomp::start(lexer* p, dive* a)
{
    cout<<"decomposition"<<endl;
	
	p->Iarray(subcell,p->M10+10);
	
	p->Iarray(xcount,p->M10+10);
	p->Iarray(ycount,p->M10+10);
	p->Iarray(zcount,p->M10+10);
	
	p->Iarray(xcross,a->knox+10);
	p->Iarray(ycross,a->knoy+10);
	p->Iarray(zcross,a->knoz+10);


    MALOOP
    if(a->flag(i,j,k)<0)
    a->flag(i,j,k)=-1;
	
	if(p->M20==1)
	{
    nodecalc(p,a);
    costfunc(p,a);
    partition(p,a);
    print_partition(p,a);
	}
	
	if(p->M20==2)
	{
	nodecalc(p,a);
    costfunc(p,a);
	partition_analyse(p,a);
    nodecalc(p,a);
    costfunc(p,a);
    partition(p,a);
	partition_correction(p,a);
	partition_voidcheck(p,a);
	}
	
	neighbors(p,a);
	knoxcalc(p,a);
	mem_alloc(p,a);
    parasurface(p,a);	
	paravoidsurface(p,a);
    paracosurface(p,a);
    cornersurface(p,a);
    surfcount(p,a);
	voidsurfcount(p,a);
    ccsurf(p,a);
    cornercount(p,a);

    
    paraslicesurface(p,a);
    paraslicecosurface(p,a);
    slicesurfcount(p,a);
    slicecornercount(p,a);
	
	cout<<"partition: "<<a->mx<<" "<<a->my<<" "<<a->mz<<" "<<endl;
}


int decomp::partition_check(lexer* p, dive* a)
{
    int checker=0;
    alpha=0.75;

    for(n=0;n<nodes+5;n++)
    partcount[n]=0;

    LOOP
    {
    if(a->flag(i,j,k)==1)
    partcount[a->subgrid(i,j,k)]++;
    }

    maxel=int(active/p->M10);

    count=0;

    for(n=1;n<=a->mx*a->my*a->mz;n++)
    {
    if(partcount[n]>int(maxel*alpha))
    count++;
    }

    if(count==p->M10)
    checker=1;

    return checker;
}

void decomp::neighbors(lexer* p,dive* a)
{
	p->Iarray(a->sgfield, a->mx+2, a->my+2, a->mz+2);

    NMALOOP
    a->sgfield[aa][bb][cc]=-1;

    NLOOP
    a->sgfield[aa][bb][cc]=PARANUM;

//    NLOOP
//    cout<<a->sgfield[aa][bb][cc]<<endl;

    count=0;
    NLOOP
    {
    count++;

    a->nbpara1[count]=a->sgfield[aa-1][bb][cc]-1;
     a->nbpara2[count]=a->sgfield[aa][bb+1][cc]-1;
      a->nbpara3[count]=a->sgfield[aa][bb-1][cc]-1;
       a->nbpara4[count]=a->sgfield[aa+1][bb][cc]-1;
        a->nbpara5[count]=a->sgfield[aa][bb][cc-1]-1;
         a->nbpara6[count]=a->sgfield[aa][bb][cc+1]-1;

    }
	
	// MPI_GRAPH
	count=0;
	for(n=1;n<p->M10+1;++n)
	{
		if(a->nbpara1[n]>-1)
		{
		a->mpi_edges[count]=a->nbpara1[n];
		++count;
		}
		
		if(a->nbpara2[n]>-1)
		{
		a->mpi_edges[count]=a->nbpara2[n];
		++count;
		}
		
		if(a->nbpara3[n]>-1)
		{
		a->mpi_edges[count]=a->nbpara3[n];
		++count;
		}
		
		if(a->nbpara4[n]>-1)
		{
		a->mpi_edges[count]=a->nbpara4[n];
		++count;
		}
		
		if(a->nbpara5[n]>-1)
		{
		a->mpi_edges[count]=a->nbpara5[n];
		++count;
		}
		
		if(a->nbpara6[n]>-1)
		{
		a->mpi_edges[count]=a->nbpara6[n];
		++count;
		}
		
		a->mpi_index[n]=count;
	}
	a->mpi_edgenum=count;
}

void decomp::knoxcalc(lexer* p, dive*a)
{
    for(n=0;n<=p->M10;n++)
    {
    a->subknox[n]=0;
    a->subknoy[n]=0;
    a->subknoz[n]=0;
    }

 n=0;
 NLOOP
 {
     ++n;

     SUBLOOP
     {
     a->subknox[n]=MAX(i-a->xnode[aa-1]+1,a->subknox[n]);
     a->subknoy[n]=MAX(j-a->ynode[bb-1]+1,a->subknoy[n]);
     a->subknoz[n]=MAX(k-a->znode[cc-1]+1,a->subknoz[n]);
     }
  }
}

void decomp::mem_alloc(lexer *p, dive *a)
{
	int xsurf,ysurf,zsurf;
	int xco,yco,zco;
	
	xsurf = 3*p->knoy*p->knoz*(a->mx);
	ysurf = 3*p->knox*p->knoz*(a->my);
	zsurf = 3*p->knox*p->knoy*(a->mz);
	
	xco = yco = zco = 0;
	
	for(n=1;n<=p->M10;++n)
    {
	xco += 3*(a->subknoy[n]+a->subknoz[n] + 4);
	yco += 3*(a->subknox[n]+a->subknoz[n] + 4);
	zco += 3*(a->subknox[n]+a->subknoy[n] + 4);
    }
	
	ddout<<endl;
	ddout<<"xsurf: "<<xsurf<<"  ysurf: "<<ysurf<<"  zsurf: "<<zsurf<<endl;
	ddout<<"xco: "<<xco<<"  yco: "<<yco<<"  zco: "<<zco<<endl<<endl;


	a->Iarray(a->para1sf,xsurf,3);
	a->Iarray(a->para2sf,ysurf,3);
	a->Iarray(a->para3sf,ysurf,3);
	a->Iarray(a->para4sf,xsurf,3);
	a->Iarray(a->para5sf,zsurf,3);
	a->Iarray(a->para6sf,zsurf,3);

	a->Iarray(a->para1void,xsurf,4);
	a->Iarray(a->para2void,ysurf,4);
	a->Iarray(a->para3void,ysurf,4);
	a->Iarray(a->para4void,xsurf,4);
	a->Iarray(a->para5void,zsurf,4);
	a->Iarray(a->para6void,zsurf,4);

	a->Iarray(a->para1co,xco,7);
	a->Iarray(a->para2co,yco,7);
	a->Iarray(a->para3co,yco,7);
	a->Iarray(a->para4co,xco,7);
	a->Iarray(a->para5co,zco,7);
	a->Iarray(a->para6co,zco,7);
    
    // Slice
    
    int xslicesurf,yslicesurf;
	int xsliceco,ysliceco;
    
    xslicesurf = 3*p->knoy*(a->mx);
	yslicesurf = 3*p->knox*(a->my);

	
	xsliceco = ysliceco = 0;
	
	for(n=1;n<=p->M10;++n)
    {
	xsliceco += 3*(a->subknoy[n]+a->subknoz[n] + 4);
	ysliceco += 3*(a->subknox[n]+a->subknoz[n] + 4);
    }
    
    a->Iarray(a->paraslice1sf,xsurf,2);
	a->Iarray(a->paraslice2sf,ysurf,2);
	a->Iarray(a->paraslice3sf,ysurf,2);
	a->Iarray(a->paraslice4sf,xsurf,2);


	a->Iarray(a->paracoslice1sf,xco,4);
	a->Iarray(a->paracoslice2sf,yco,4);
	a->Iarray(a->paracoslice3sf,yco,4);
	a->Iarray(a->paracoslice4sf,xco,4);

}


