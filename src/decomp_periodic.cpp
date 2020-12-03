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

#include"decomposition.h"

void decomp::periodic_ini(lexer* p, dive* a)
{
    xper=yper=zper=0;
    cout<<"C21: "<<p->C21<<endl;
    // serial or parallel periodic BC
    if(p->C21>=1)
    {
        
        if(a->mx==1)
        p->C21=1;
        
        if(a->mx>1)
        {
        p->C21=2;
        xper=1;
        }
    }
    
    if(p->C22>=1)
    {
        if(a->my==1)
        p->C22=1;
        
        if(a->my>1)
        {
        p->C22=2;
        yper=1;
        }
    }
    
    if(p->C23>=1)
    {
        if(a->mz==1)
        p->C23=1;
        
        if(a->mz>1)
        {
        p->C23=2;
        zper=1;
        }
    }
    
    
}

void decomp::periodic_nb(lexer* p, dive* a)
{


    // x-dir parallel periodic BC
    if(p->C21==2)
    {
        count=0;
        NLOOP
        {
        count++;

        if(aa==1)
        a->nbpara1[count]=a->sgfield[a->mx][bb][cc]-1;
        
        if(aa==a->mx)
        a->nbpara4[count]=a->sgfield[1][bb][cc]-1;
        }
    }
    
    // y-dir parallel periodic BC
    if(p->C22==2)
    {
        count=0;
        NLOOP
        {
        count++;

        if(bb==1)
        a->nbpara3[count]=a->sgfield[aa][a->my][cc]-1;
        
        if(bb==a->my)
        a->nbpara2[count]=a->sgfield[aa][1][cc]-1;
        }
    }
    
    // z-dir parallel periodic BC
    if(p->C23==2)
    {
        count=0;
        NLOOP
        {
        count++;

        if(cc==1)
        a->nbpara5[count]=a->sgfield[aa][bb][a->mz]-1;
        
        if(cc==a->mz)
        a->nbpara6[count]=a->sgfield[aa][bb][11]-1;
        }
    }

    
}

void decomp::periodic_surf(lexer* p, dive* a)
{
    a->periodicXall[0]=a->para1count;
    a->periodicXall[1]=a->para2count;
    a->periodicXall[2]=a->para3count;
    a->periodicXall[3]=a->para4count;
    a->periodicXall[4]=a->para5count;
    a->periodicXall[5]=a->para6count;
    
    int periodic_count=0;
    // parasurf parallel periodic BC
    if(p->C21==2)
    {
        i=0;
        for(j=0;j<a->knoy;++j)
        for(k=0;k<a->knoz;++k)
        {
        a->para1sf[a->para1count][0]=i;
        a->para1sf[a->para1count][1]=j;
        a->para1sf[a->para1count][2]=k;
        a->para1count++;
        ++periodic_count;
        }

        i=p->knox-1;
        for(j=0;j<a->knoy;++j)
        for(k=0;k<a->knoz;++k)
        {
        a->para4sf[a->para4count][0]=i;
        a->para4sf[a->para4count][1]=j;
        a->para4sf[a->para4count][2]=k;
        a->para4count++;
        ++periodic_count;
        }
    }
    
    
    if(p->C22==2)
    {
        j=0;
        for(i=0;i<a->knox;++i)
        for(k=0;k<a->knoz;++k)
        {
        a->para3sf[a->para3count][0]=i;
        a->para3sf[a->para3count][1]=j;
        a->para3sf[a->para3count][2]=k;
        a->para3count++;
        ++periodic_count;
        }

        j=p->knoy-1;
        for(i=0;i<a->knox;++i)
        for(k=0;k<a->knoz;++k)
        {
        a->para2sf[a->para2count][0]=i;
        a->para2sf[a->para2count][1]=j;
        a->para2sf[a->para2count][2]=k;
        a->para2count++;
        ++periodic_count;
        }
    }
    
    
    if(p->C23==2)
    {
        k=0;
        for(i=0;i<a->knox;++i)
        for(j=0;j<a->knoy;++j)
        {
        a->para5sf[a->para5count][0]=i;
        a->para5sf[a->para5count][1]=j;
        a->para5sf[a->para5count][2]=k;
        a->para5count++;
        ++periodic_count;
        }

        k=p->knoz-1;
        for(i=0;i<a->knox;++i)
        for(j=0;j<a->knoy;++j)
        {
        a->para6sf[a->para6count][0]=i;
        a->para6sf[a->para6count][1]=j;
        a->para6sf[a->para6count][2]=k;
        a->para6count++;
        ++periodic_count;
        }
    }
    
    if(p->C21>0||p->C22>0||p->C23>0)
    cout<<"periodic parasf: "<<periodic_count<<endl;
}

void decomp::periodic_cosurf(lexer* p, dive* a)
{
    int r;
	int paracell[3][3][3];
	
// CORNERS
    a->paraco1count=0;
    a->paraco2count=0;
    a->paraco3count=0;
    a->paraco4count=0;
    a->paraco5count=0;
    a->paraco6count=0;
	
	
	
    LOOP
    {
		
		for(n=0;n<3;++n)
		for(q=0;q<3;++q)
		for(r=0;r<3;++r)
		paracell[n][q][r]=0;
	
//  1
    if(a->subgrid(i-1,j,k)!=a->subgrid(i,j,k)
    && a->flag(i,j,k)>0
    && a->flag(i-1,j,k)>0
    && ((a->flag(i,j-1,k)<0  && a->flag(i-1,j-1,k)<0)
        ||(a->subgrid(i,j-1,k)!=a->subgrid(i,j,k)  && a->subgrid(i-1,j-1,k)!=a->subgrid(i-1,j,k))))
	paracell[0][0][1]+=1;

    if(a->subgrid(i-1,j,k)!=a->subgrid(i,j,k)
    && a->flag(i,j,k)>0
    && a->flag(i-1,j,k)>0
    && ((a->flag(i,j+1,k)<0  && a->flag(i-1,j+1,k)<0)
        ||(a->subgrid(i,j+1,k)!=a->subgrid(i,j,k)  && a->subgrid(i-1,j+1,k)!=a->subgrid(i-1,j,k))))
    paracell[0][2][1]+=1;

    if(a->subgrid(i-1,j,k)!=a->subgrid(i,j,k)
    && a->flag(i,j,k)>0
    && a->flag(i-1,j,k)>0
    && ((a->flag(i,j,k-1)<0  && a->flag(i-1,j,k-1)<0)
        ||(a->subgrid(i,j,k-1)!=a->subgrid(i,j,k)  && a->subgrid(i-1,j,k-1)!=a->subgrid(i-1,j,k))))
	paracell[0][1][0]+=1;

    if(a->subgrid(i-1,j,k)!=a->subgrid(i,j,k)
    && a->flag(i,j,k)>0
    && a->flag(i-1,j,k)>0
    && ((a->flag(i,j,k+1)<0  && a->flag(i-1,j,k+1)<0)
        ||(a->subgrid(i,j,k+1)!=a->subgrid(i,j,k)  && a->subgrid(i-1,j,k+1)!=a->subgrid(i-1,j,k))))
    paracell[0][1][2]+=1;

//  4
    if(a->subgrid(i+1,j,k)!=a->subgrid(i,j,k)   // ok
    && a->flag(i,j,k)>0 //ok
    && a->flag(i+1,j,k)>0 //ok
    && ((a->flag(i,j-1,k)<0  && a->flag(i+1,j-1,k)<0)
        ||(a->subgrid(i,j-1,k)!=a->subgrid(i,j,k)  && a->subgrid(i+1,j-1,k)!=a->subgrid(i+1,j,k))))
	paracell[2][0][1]+=1;

    if(a->subgrid(i+1,j,k)!=a->subgrid(i,j,k)
    && a->flag(i,j,k)>0
    && a->flag(i+1,j,k)>0
    && ((a->flag(i,j+1,k)<0  && a->flag(i+1,j+1,k)<0)
        ||(a->subgrid(i,j+1,k)!=a->subgrid(i,j,k)  && a->subgrid(i+1,j+1,k)!=a->subgrid(i+1,j,k))))
	paracell[2][2][1]+=1;

    if(a->subgrid(i+1,j,k)!=a->subgrid(i,j,k)
    && a->flag(i,j,k)>0
    && a->flag(i+1,j,k)>0
    && ((a->flag(i,j,k-1)<0  && a->flag(i+1,j,k-1)<0)
        ||(a->subgrid(i,j,k-1)!=a->subgrid(i,j,k)  && a->subgrid(i+1,j,k-1)!=a->subgrid(i+1,j,k))))
	paracell[2][1][0]+=1;

    if(a->subgrid(i+1,j,k)!=a->subgrid(i,j,k)
    && a->flag(i,j,k)>0
    && a->flag(i+1,j,k)>0
    && ((a->flag(i,j,k+1)<0  && a->flag(i+1,j,k+1)<0)
        ||(a->subgrid(i,j,k+1)!=a->subgrid(i,j,k)  && a->subgrid(i+1,j,k+1)!=a->subgrid(i+1,j,k))))
	paracell[2][1][2]+=1;

//  3
    if(a->subgrid(i,j-1,k)!=a->subgrid(i,j,k)
    && a->flag(i,j,k)>0
    && a->flag(i,j-1,k)>0
    && ((a->flag(i-1,j,k)<0  && a->flag(i-1,j-1,k)<0)
        ||(a->subgrid(i-1,j,k)!=a->subgrid(i,j,k)  && a->subgrid(i-1,j-1,k)!=a->subgrid(i,j-1,k))))
	paracell[0][0][1]+=1;

    if(a->subgrid(i,j-1,k)!=a->subgrid(i,j,k)
    && a->flag(i,j,k)>0
    && a->flag(i,j-1,k)>0
    && ((a->flag(i+1,j,k)<0  && a->flag(i+1,j-1,k)<0)
        ||(a->subgrid(i+1,j,k)!=a->subgrid(i,j,k)  && a->subgrid(i+1,j-1,k)!=a->subgrid(i,j-1,k))))
	paracell[2][0][1]+=1;

    if(a->subgrid(i,j-1,k)!=a->subgrid(i,j,k)
    && a->flag(i,j,k)>0
    && a->flag(i,j-1,k)>0
    && ((a->flag(i,j,k-1)<0  && a->flag(i,j-1,k-1)<0)
        ||(a->subgrid(i,j,k-1)!=a->subgrid(i,j,k)  && a->subgrid(i,j-1,k-1)!=a->subgrid(i,j-1,k))))
    paracell[1][0][0]+=1;

    if(a->subgrid(i,j-1,k)!=a->subgrid(i,j,k)
    && a->flag(i,j,k)>0
    && a->flag(i,j-1,k)>0
    && ((a->flag(i,j,k+1)<0  && a->flag(i,j-1,k+1)<0)
        ||(a->subgrid(i,j,k+1)!=a->subgrid(i,j,k)  && a->subgrid(i,j-1,k+1)!=a->subgrid(i,j-1,k))))
    paracell[1][0][2]+=1;

//  2
    if(a->subgrid(i,j+1,k)!=a->subgrid(i,j,k)

    && a->flag(i,j,k)>0
    && a->flag(i,j+1,k)>0
    && ((a->flag(i-1,j,k)<0  && a->flag(i-1,j+1,k)<0)
        ||(a->subgrid(i-1,j,k)!=a->subgrid(i,j,k)  && a->subgrid(i-1,j+1,k)!=a->subgrid(i,j+1,k))))
    paracell[0][2][1]+=1;

    if(a->subgrid(i,j+1,k)!=a->subgrid(i,j,k)
    && a->flag(i,j,k)>0
    && a->flag(i,j+1,k)>0
    && ((a->flag(i+1,j,k)<0  && a->flag(i+1,j+1,k)<0)
        ||(a->subgrid(i+1,j,k)!=a->subgrid(i,j,k)  && a->subgrid(i+1,j+1,k)!=a->subgrid(i,j+1,k))))
    paracell[2][2][1]+=1;

    if(a->subgrid(i,j+1,k)!=a->subgrid(i,j,k)
    && a->flag(i,j,k)>0
    && a->flag(i,j+1,k)>0
    && ((a->flag(i,j,k-1)<0  && a->flag(i,j+1,k-1)<0)
        ||(a->subgrid(i,j,k-1)!=a->subgrid(i,j,k)  && a->subgrid(i,j+1,k-1)!=a->subgrid(i,j+1,k))))
    paracell[1][2][0]+=1;

    if(a->subgrid(i,j+1,k)!=a->subgrid(i,j,k)
    && a->flag(i,j,k)>0
    && a->flag(i,j+1,k)>0
    && ((a->flag(i,j,k+1)<0  && a->flag(i,j+1,k+1)<0)
        ||(a->subgrid(i,j,k+1)!=a->subgrid(i,j,k)  && a->subgrid(i,j+1,k+1)!=a->subgrid(i,j+1,k))))
    paracell[1][2][2]+=1;

//  5
    if(a->subgrid(i,j,k-1)!=a->subgrid(i,j,k)
    && a->flag(i,j,k)>0
    && a->flag(i,j,k-1)>0
    && ((a->flag(i-1,j,k)<0  && a->flag(i-1,j,k-1)<0)
        ||(a->subgrid(i-1,j,k)!=a->subgrid(i,j,k)  && a->subgrid(i-1,j,k-1)!=a->subgrid(i,j,k-1))))
    paracell[0][1][0]+=1;

    if(a->subgrid(i,j,k-1)!=a->subgrid(i,j,k)
    && a->flag(i,j,k)>0
    && a->flag(i,j,k-1)>0
    && ((a->flag(i+1,j,k)<0  && a->flag(i+1,j,k-1)<0)
        ||(a->subgrid(i+1,j,k)!=a->subgrid(i,j,k)  && a->subgrid(i+1,j,k-1)!=a->subgrid(i,j,k-1))))
    paracell[2][1][0]+=1;

    if(a->subgrid(i,j,k-1)!=a->subgrid(i,j,k)
    && a->flag(i,j,k)>0
    && a->flag(i,j,k-1)>0
    && ((a->flag(i,j-1,k)<0  && a->flag(i,j-1,k-1)<0)
        ||(a->subgrid(i,j-1,k)!=a->subgrid(i,j,k)  && a->subgrid(i,j-1,k-1)!=a->subgrid(i,j,k-1))))
    paracell[1][0][0]+=1;

    if(a->subgrid(i,j,k-1)!=a->subgrid(i,j,k)
    && a->flag(i,j,k)>0
    && a->flag(i,j,k-1)>0
    && ((a->flag(i,j+1,k)<0  && a->flag(i,j+1,k-1)<0)
        ||(a->subgrid(i,j+1,k)!=a->subgrid(i,j,k)  && a->subgrid(i,j+1,k-1)!=a->subgrid(i,j,k-1))))
    paracell[1][2][0]+=1;

//  6
    if(a->subgrid(i,j,k+1)!=a->subgrid(i,j,k)
    && a->flag(i,j,k)>0
    && a->flag(i,j,k+1)>0
    && ((a->flag(i-1,j,k)<0  && a->flag(i-1,j,k+1)<0)
        ||(a->subgrid(i-1,j,k)!=a->subgrid(i,j,k)  && a->subgrid(i-1,j,k+1)!=a->subgrid(i,j,k+1))))
    paracell[0][1][2]+=1;

    if(a->subgrid(i,j,k+1)!=a->subgrid(i,j,k)
    && a->flag(i,j,k)>0
    && a->flag(i,j,k+1)>0
    && ((a->flag(i+1,j,k)<0  && a->flag(i+1,j,k+1)<0)
        ||(a->subgrid(i+1,j,k)!=a->subgrid(i,j,k)  && a->subgrid(i+1,j,k+1)!=a->subgrid(i,j,k+1))))
    paracell[2][1][2]+=1;

    if(a->subgrid(i,j,k+1)!=a->subgrid(i,j,k)
    && a->flag(i,j,k)>0
    && a->flag(i,j,k+1)>0
    && ((a->flag(i,j-1,k)<0  && a->flag(i,j-1,k+1)<0)
        ||(a->subgrid(i,j-1,k)!=a->subgrid(i,j,k)  && a->subgrid(i,j-1,k+1)!=a->subgrid(i,j,k+1))))
    paracell[1][0][2]+=1;

    if(a->subgrid(i,j,k+1)!=a->subgrid(i,j,k)
    && a->flag(i,j,k)>0
    && a->flag(i,j,k+1)>0
    && ((a->flag(i,j+1,k)<0  && a->flag(i,j+1,k+1)<0)
        ||(a->subgrid(i,j+1,k)!=a->subgrid(i,j,k)  && a->subgrid(i,j+1,k+1)!=a->subgrid(i,j,k+1))))
    paracell[1][2][2]+=1;
		
//-----------------------------------------------------------------------------------------------
//  1
    if(a->subgrid(i-1,j,k)!=a->subgrid(i,j,k)
    && a->flag(i,j,k)>0
    && a->flag(i-1,j,k)>0
    && ((a->flag(i,j-1,k)<0  && a->flag(i-1,j-1,k)<0)
        ||(a->subgrid(i,j-1,k)!=a->subgrid(i,j,k)  && a->subgrid(i-1,j-1,k)!=a->subgrid(i-1,j,k))))
    {
    a->para1co[a->paraco1count][0]=i;
    a->para1co[a->paraco1count][1]=j-1;
    a->para1co[a->paraco1count][2]=k;
    a->para1co[a->paraco1count][3]=a->subgrid(i,j,k);
	a->para1co[a->paraco1count][4]=3;
	a->para1co[a->paraco1count][6]=paracell[0][0][1];
	++a->paraco1count;
    }

    if(a->subgrid(i-1,j,k)!=a->subgrid(i,j,k)
    && a->flag(i,j,k)>0
    && a->flag(i-1,j,k)>0
    && ((a->flag(i,j+1,k)<0  && a->flag(i-1,j+1,k)<0)
        ||(a->subgrid(i,j+1,k)!=a->subgrid(i,j,k)  && a->subgrid(i-1,j+1,k)!=a->subgrid(i-1,j,k))))
    {
    a->para1co[a->paraco1count][0]=i;
    a->para1co[a->paraco1count][1]=j+1;
    a->para1co[a->paraco1count][2]=k;
    a->para1co[a->paraco1count][3]=a->subgrid(i,j,k);
	a->para1co[a->paraco1count][4]=2;
	a->para1co[a->paraco1count][6]=paracell[0][2][1];
    a->paraco1count++;
    }

    if(a->subgrid(i-1,j,k)!=a->subgrid(i,j,k)
    && a->flag(i,j,k)>0
    && a->flag(i-1,j,k)>0
    && ((a->flag(i,j,k-1)<0  && a->flag(i-1,j,k-1)<0)
        ||(a->subgrid(i,j,k-1)!=a->subgrid(i,j,k)  && a->subgrid(i-1,j,k-1)!=a->subgrid(i-1,j,k))))
    {
    a->para1co[a->paraco1count][0]=i;
    a->para1co[a->paraco1count][1]=j;
    a->para1co[a->paraco1count][2]=k-1;
    a->para1co[a->paraco1count][3]=a->subgrid(i,j,k);
	a->para1co[a->paraco1count][4]=5;
	a->para1co[a->paraco1count][6]=paracell[0][1][0];
    a->paraco1count++;
    }

    if(a->subgrid(i-1,j,k)!=a->subgrid(i,j,k)
    && a->flag(i,j,k)>0
    && a->flag(i-1,j,k)>0
    && ((a->flag(i,j,k+1)<0  && a->flag(i-1,j,k+1)<0)
        ||(a->subgrid(i,j,k+1)!=a->subgrid(i,j,k)  && a->subgrid(i-1,j,k+1)!=a->subgrid(i-1,j,k))))
    {
    a->para1co[a->paraco1count][0]=i;
    a->para1co[a->paraco1count][1]=j;
    a->para1co[a->paraco1count][2]=k+1;
    a->para1co[a->paraco1count][3]=a->subgrid(i,j,k);
	a->para1co[a->paraco1count][4]=6;
	a->para1co[a->paraco1count][6]=paracell[0][1][2];
    a->paraco1count++;
    }

//  4
    if(a->subgrid(i+1,j,k)!=a->subgrid(i,j,k)   // ok
    && a->flag(i,j,k)>0 //ok
    && a->flag(i+1,j,k)>0 //ok
    && ((a->flag(i,j-1,k)<0  && a->flag(i+1,j-1,k)<0)
        ||(a->subgrid(i,j-1,k)!=a->subgrid(i,j,k)  && a->subgrid(i+1,j-1,k)!=a->subgrid(i+1,j,k))))
    {
    a->para4co[a->paraco4count][0]=i;
    a->para4co[a->paraco4count][1]=j-1;
    a->para4co[a->paraco4count][2]=k;
    a->para4co[a->paraco4count][3]=a->subgrid(i,j,k);
	a->para4co[a->paraco4count][4]=3;
	a->para4co[a->paraco4count][6]=paracell[2][0][1];
    a->paraco4count++;
    }


    if(a->subgrid(i+1,j,k)!=a->subgrid(i,j,k)
    && a->flag(i,j,k)>0
    && a->flag(i+1,j,k)>0
    && ((a->flag(i,j+1,k)<0  && a->flag(i+1,j+1,k)<0)
        ||(a->subgrid(i,j+1,k)!=a->subgrid(i,j,k)  && a->subgrid(i+1,j+1,k)!=a->subgrid(i+1,j,k))))
    {
    a->para4co[a->paraco4count][0]=i;
    a->para4co[a->paraco4count][1]=j+1;
    a->para4co[a->paraco4count][2]=k;
    a->para4co[a->paraco4count][3]=a->subgrid(i,j,k);
	a->para4co[a->paraco4count][4]=2;
	a->para4co[a->paraco4count][6]=paracell[2][2][1];
    a->paraco4count++;
    }

    if(a->subgrid(i+1,j,k)!=a->subgrid(i,j,k)
    && a->flag(i,j,k)>0
    && a->flag(i+1,j,k)>0
    && ((a->flag(i,j,k-1)<0  && a->flag(i+1,j,k-1)<0)
        ||(a->subgrid(i,j,k-1)!=a->subgrid(i,j,k)  && a->subgrid(i+1,j,k-1)!=a->subgrid(i+1,j,k))))
    {
    a->para4co[a->paraco4count][0]=i;
    a->para4co[a->paraco4count][1]=j;
    a->para4co[a->paraco4count][2]=k-1;
    a->para4co[a->paraco4count][3]=a->subgrid(i,j,k);
	a->para4co[a->paraco4count][4]=5;
	a->para4co[a->paraco4count][6]=paracell[2][1][0];
    a->paraco4count++;
    }

    if(a->subgrid(i+1,j,k)!=a->subgrid(i,j,k)
    && a->flag(i,j,k)>0
    && a->flag(i+1,j,k)>0
    && ((a->flag(i,j,k+1)<0  && a->flag(i+1,j,k+1)<0)
        ||(a->subgrid(i,j,k+1)!=a->subgrid(i,j,k)  && a->subgrid(i+1,j,k+1)!=a->subgrid(i+1,j,k))))
    {
    a->para4co[a->paraco4count][0]=i;
    a->para4co[a->paraco4count][1]=j;
    a->para4co[a->paraco4count][2]=k+1;
    a->para4co[a->paraco4count][3]=a->subgrid(i,j,k);
	a->para4co[a->paraco4count][4]=6;
	a->para4co[a->paraco4count][6]=paracell[2][1][2];
    a->paraco4count++;
    }

//  3
    if(a->subgrid(i,j-1,k)!=a->subgrid(i,j,k)
    && a->flag(i,j,k)>0
    && a->flag(i,j-1,k)>0
    && ((a->flag(i-1,j,k)<0  && a->flag(i-1,j-1,k)<0)
        ||(a->subgrid(i-1,j,k)!=a->subgrid(i,j,k)  && a->subgrid(i-1,j-1,k)!=a->subgrid(i,j-1,k))))
    {
    a->para3co[a->paraco3count][0]=i-1;
    a->para3co[a->paraco3count][1]=j;
    a->para3co[a->paraco3count][2]=k;
    a->para3co[a->paraco3count][3]=a->subgrid(i,j,k);
	a->para3co[a->paraco3count][4]=1;
	a->para3co[a->paraco3count][6]=paracell[0][0][1];
    a->paraco3count++;
    }

    if(a->subgrid(i,j-1,k)!=a->subgrid(i,j,k)
    && a->flag(i,j,k)>0
    && a->flag(i,j-1,k)>0
    && ((a->flag(i+1,j,k)<0  && a->flag(i+1,j-1,k)<0)
        ||(a->subgrid(i+1,j,k)!=a->subgrid(i,j,k)  && a->subgrid(i+1,j-1,k)!=a->subgrid(i,j-1,k))))
    {
    a->para3co[a->paraco3count][0]=i+1;
    a->para3co[a->paraco3count][1]=j;
    a->para3co[a->paraco3count][2]=k;
    a->para3co[a->paraco3count][3]=a->subgrid(i,j,k);
	a->para3co[a->paraco3count][4]=4;
	a->para3co[a->paraco3count][6]=paracell[2][0][1];
    a->paraco3count++;
    }

    if(a->subgrid(i,j-1,k)!=a->subgrid(i,j,k)
    && a->flag(i,j,k)>0
    && a->flag(i,j-1,k)>0
    && ((a->flag(i,j,k-1)<0  && a->flag(i,j-1,k-1)<0)
        ||(a->subgrid(i,j,k-1)!=a->subgrid(i,j,k)  && a->subgrid(i,j-1,k-1)!=a->subgrid(i,j-1,k))))
    {
    a->para3co[a->paraco3count][0]=i;
    a->para3co[a->paraco3count][1]=j;
    a->para3co[a->paraco3count][2]=k-1;
    a->para3co[a->paraco3count][3]=a->subgrid(i,j,k);
	a->para3co[a->paraco3count][4]=5;
	a->para3co[a->paraco3count][6]=paracell[1][0][0];
    a->paraco3count++;
    }

    if(a->subgrid(i,j-1,k)!=a->subgrid(i,j,k)
    && a->flag(i,j,k)>0
    && a->flag(i,j-1,k)>0
    && ((a->flag(i,j,k+1)<0  && a->flag(i,j-1,k+1)<0)
        ||(a->subgrid(i,j,k+1)!=a->subgrid(i,j,k)  && a->subgrid(i,j-1,k+1)!=a->subgrid(i,j-1,k))))
    {
    a->para3co[a->paraco3count][0]=i;
    a->para3co[a->paraco3count][1]=j;
    a->para3co[a->paraco3count][2]=k+1;
    a->para3co[a->paraco3count][3]=a->subgrid(i,j,k);
	a->para3co[a->paraco3count][4]=6;
	a->para3co[a->paraco3count][6]=paracell[1][0][2];
    a->paraco3count++;
    }

//  2
    if(a->subgrid(i,j+1,k)!=a->subgrid(i,j,k)

    && a->flag(i,j,k)>0
    && a->flag(i,j+1,k)>0
    && ((a->flag(i-1,j,k)<0  && a->flag(i-1,j+1,k)<0)
        ||(a->subgrid(i-1,j,k)!=a->subgrid(i,j,k)  && a->subgrid(i-1,j+1,k)!=a->subgrid(i,j+1,k))))
    {
    a->para2co[a->paraco2count][0]=i-1;
    a->para2co[a->paraco2count][1]=j;
    a->para2co[a->paraco2count][2]=k;
    a->para2co[a->paraco2count][3]=a->subgrid(i,j,k);
	a->para2co[a->paraco2count][4]=1;
	a->para2co[a->paraco2count][6]=paracell[0][2][1];
    a->paraco2count++;
    }

    if(a->subgrid(i,j+1,k)!=a->subgrid(i,j,k)
    && a->flag(i,j,k)>0
    && a->flag(i,j+1,k)>0
    && ((a->flag(i+1,j,k)<0  && a->flag(i+1,j+1,k)<0)
        ||(a->subgrid(i+1,j,k)!=a->subgrid(i,j,k)  && a->subgrid(i+1,j+1,k)!=a->subgrid(i,j+1,k))))
    {
    a->para2co[a->paraco2count][0]=i+1;
    a->para2co[a->paraco2count][1]=j;
    a->para2co[a->paraco2count][2]=k;
    a->para2co[a->paraco2count][3]=a->subgrid(i,j,k);
	a->para2co[a->paraco2count][4]=4;
	a->para2co[a->paraco2count][6]=paracell[2][2][1];
    a->paraco2count++;
    }

    if(a->subgrid(i,j+1,k)!=a->subgrid(i,j,k)
    && a->flag(i,j,k)>0
    && a->flag(i,j+1,k)>0
    && ((a->flag(i,j,k-1)<0  && a->flag(i,j+1,k-1)<0)
        ||(a->subgrid(i,j,k-1)!=a->subgrid(i,j,k)  && a->subgrid(i,j+1,k-1)!=a->subgrid(i,j+1,k))))
    {
    a->para2co[a->paraco2count][0]=i;
    a->para2co[a->paraco2count][1]=j;
    a->para2co[a->paraco2count][2]=k-1;
    a->para2co[a->paraco2count][3]=a->subgrid(i,j,k);
	a->para2co[a->paraco2count][4]=5;
	a->para2co[a->paraco2count][6]=paracell[1][2][0];
    a->paraco2count++;
    }

    if(a->subgrid(i,j+1,k)!=a->subgrid(i,j,k)
    && a->flag(i,j,k)>0
    && a->flag(i,j+1,k)>0
    && ((a->flag(i,j,k+1)<0  && a->flag(i,j+1,k+1)<0)
        ||(a->subgrid(i,j,k+1)!=a->subgrid(i,j,k)  && a->subgrid(i,j+1,k+1)!=a->subgrid(i,j+1,k))))
    {
    a->para2co[a->paraco2count][0]=i;
    a->para2co[a->paraco2count][1]=j;
    a->para2co[a->paraco2count][2]=k+1;
    a->para2co[a->paraco2count][3]=a->subgrid(i,j,k);
	a->para2co[a->paraco2count][4]=6;
	a->para2co[a->paraco2count][6]=paracell[1][2][2];
    a->paraco2count++;
    }

//  5
    if(a->subgrid(i,j,k-1)!=a->subgrid(i,j,k)
    && a->flag(i,j,k)>0
    && a->flag(i,j,k-1)>0
    && ((a->flag(i-1,j,k)<0  && a->flag(i-1,j,k-1)<0)
        ||(a->subgrid(i-1,j,k)!=a->subgrid(i,j,k)  && a->subgrid(i-1,j,k-1)!=a->subgrid(i,j,k-1))))
    {
    a->para5co[a->paraco5count][0]=i-1;
    a->para5co[a->paraco5count][1]=j;
    a->para5co[a->paraco5count][2]=k;
    a->para5co[a->paraco5count][3]=a->subgrid(i,j,k);
	a->para5co[a->paraco5count][4]=1;
	a->para5co[a->paraco5count][6]=paracell[0][1][0];
    a->paraco5count++;
    }

    if(a->subgrid(i,j,k-1)!=a->subgrid(i,j,k)
    && a->flag(i,j,k)>0
    && a->flag(i,j,k-1)>0
    && ((a->flag(i+1,j,k)<0  && a->flag(i+1,j,k-1)<0)
        ||(a->subgrid(i+1,j,k)!=a->subgrid(i,j,k)  && a->subgrid(i+1,j,k-1)!=a->subgrid(i,j,k-1))))
    {
    a->para5co[a->paraco5count][0]=i+1;
    a->para5co[a->paraco5count][1]=j;
    a->para5co[a->paraco5count][2]=k;
    a->para5co[a->paraco5count][3]=a->subgrid(i,j,k);
	a->para5co[a->paraco5count][4]=4;
	a->para5co[a->paraco5count][6]=paracell[2][1][0];
    a->paraco5count++;
    }

    if(a->subgrid(i,j,k-1)!=a->subgrid(i,j,k)
    && a->flag(i,j,k)>0
    && a->flag(i,j,k-1)>0
    && ((a->flag(i,j-1,k)<0  && a->flag(i,j-1,k-1)<0)
        ||(a->subgrid(i,j-1,k)!=a->subgrid(i,j,k)  && a->subgrid(i,j-1,k-1)!=a->subgrid(i,j,k-1))))
    {
    a->para5co[a->paraco5count][0]=i;
    a->para5co[a->paraco5count][1]=j-1;
    a->para5co[a->paraco5count][2]=k;
    a->para5co[a->paraco5count][3]=a->subgrid(i,j,k);
	a->para5co[a->paraco5count][4]=3;
	a->para5co[a->paraco5count][6]=paracell[1][0][0];
    a->paraco5count++;
    }

    if(a->subgrid(i,j,k-1)!=a->subgrid(i,j,k)
    && a->flag(i,j,k)>0
    && a->flag(i,j,k-1)>0
    && ((a->flag(i,j+1,k)<0  && a->flag(i,j+1,k-1)<0)
        ||(a->subgrid(i,j+1,k)!=a->subgrid(i,j,k)  && a->subgrid(i,j+1,k-1)!=a->subgrid(i,j,k-1))))
    {
    a->para5co[a->paraco5count][0]=i;
    a->para5co[a->paraco5count][1]=j+1;
    a->para5co[a->paraco5count][2]=k;
    a->para5co[a->paraco5count][3]=a->subgrid(i,j,k);
	a->para5co[a->paraco5count][4]=2;
	a->para5co[a->paraco5count][6]=paracell[1][2][0];
    a->paraco5count++;
    }

//  6
    if(a->subgrid(i,j,k+1)!=a->subgrid(i,j,k)
    && a->flag(i,j,k)>0
    && a->flag(i,j,k+1)>0
    && ((a->flag(i-1,j,k)<0  && a->flag(i-1,j,k+1)<0)
        ||(a->subgrid(i-1,j,k)!=a->subgrid(i,j,k)  && a->subgrid(i-1,j,k+1)!=a->subgrid(i,j,k+1))))
    {
    a->para6co[a->paraco6count][0]=i-1;
    a->para6co[a->paraco6count][1]=j;
    a->para6co[a->paraco6count][2]=k;
    a->para6co[a->paraco6count][3]=a->subgrid(i,j,k);
	a->para6co[a->paraco6count][4]=1;
	a->para6co[a->paraco6count][6]=paracell[0][1][2];
    a->paraco6count++;
    }

    if(a->subgrid(i,j,k+1)!=a->subgrid(i,j,k)
    && a->flag(i,j,k)>0
    && a->flag(i,j,k+1)>0
    && ((a->flag(i+1,j,k)<0  && a->flag(i+1,j,k+1)<0)
        ||(a->subgrid(i+1,j,k)!=a->subgrid(i,j,k)  && a->subgrid(i+1,j,k+1)!=a->subgrid(i,j,k+1))))
    {
    a->para6co[a->paraco6count][0]=i+1;
    a->para6co[a->paraco6count][1]=j;
    a->para6co[a->paraco6count][2]=k;
    a->para6co[a->paraco6count][3]=a->subgrid(i,j,k);
	a->para6co[a->paraco6count][4]=4;
	a->para6co[a->paraco6count][6]=paracell[2][1][2];
    a->paraco6count++;
    }

    if(a->subgrid(i,j,k+1)!=a->subgrid(i,j,k)
    && a->flag(i,j,k)>0
    && a->flag(i,j,k+1)>0
    && ((a->flag(i,j-1,k)<0  && a->flag(i,j-1,k+1)<0)
        ||(a->subgrid(i,j-1,k)!=a->subgrid(i,j,k)  && a->subgrid(i,j-1,k+1)!=a->subgrid(i,j,k+1))))
    {
    a->para6co[a->paraco6count][0]=i;
    a->para6co[a->paraco6count][1]=j-1;
    a->para6co[a->paraco6count][2]=k;
    a->para6co[a->paraco6count][3]=a->subgrid(i,j,k);
	a->para6co[a->paraco6count][4]=3;
	a->para6co[a->paraco6count][6]=paracell[1][0][2];
    a->paraco6count++;
    }

    if(a->subgrid(i,j,k+1)!=a->subgrid(i,j,k)
    && a->flag(i,j,k)>0
    && a->flag(i,j,k+1)>0
    && ((a->flag(i,j+1,k)<0  && a->flag(i,j+1,k+1)<0)
        ||(a->subgrid(i,j+1,k)!=a->subgrid(i,j,k)  && a->subgrid(i,j+1,k+1)!=a->subgrid(i,j,k+1))))
    {
    a->para6co[a->paraco6count][0]=i;
    a->para6co[a->paraco6count][1]=j+1;
    a->para6co[a->paraco6count][2]=k;
    a->para6co[a->paraco6count][3]=a->subgrid(i,j,k);
	a->para6co[a->paraco6count][4]=2;
	a->para6co[a->paraco6count][6]=paracell[1][2][2];
    a->paraco6count++;
    }
	
	
    }
    
}


void decomp::periodic_count(lexer* p, dive* a)
{
    for(i=0;i<a->periodicXall[0];i++)
    {
    n=a->subgrid(a->para1sf[i][0],a->para1sf[i][1],a->para1sf[i][2]);
    a->periodicX[n][0]++;
    }

    for(i=0;i<a->periodicXall[1];i++)
    {
    n=a->subgrid(a->para2sf[i][0],a->para2sf[i][1],a->para2sf[i][2]);
    a->periodicX[n][1]++;
    }

    for(i=0;i<a->periodicXall[2];i++)
    {
    n=a->subgrid(a->para3sf[i][0],a->para3sf[i][1],a->para3sf[i][2]);
    a->periodicX[n][2]++;
    }

    for(i=0;i<a->periodicXall[3];i++)
    {
    n=a->subgrid(a->para4sf[i][0],a->para4sf[i][1],a->para4sf[i][2]);
    a->periodicX[n][3]++;
    }

    for(i=0;i<a->periodicXall[4];i++)
    {
    n=a->subgrid(a->para5sf[i][0],a->para5sf[i][1],a->para5sf[i][2]);
    a->periodicX[n][4]++;
    }

    for(i=0;i<a->periodicXall[5];i++)
    {
    n=a->subgrid(a->para6sf[i][0],a->para6sf[i][1],a->para6sf[i][2]);
    a->periodicX[n][5]++;
    }
    
    
    
}