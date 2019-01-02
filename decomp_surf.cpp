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

void decomp::parasurface(lexer* p, dive* a)
{
    a->para1count=0;
    a->para2count=0;
    a->para3count=0;
    a->para4count=0;
    a->para5count=0;
    a->para6count=0;


    LOOP
    {
    if(a->subgrid(i-1,j,k)!=a->subgrid(i,j,k) && a->flag(i-1,j,k)>0 && a->flag(i,j,k)>0)
    {
    a->para1sf[a->para1count][0]=i;
    a->para1sf[a->para1count][1]=j;
    a->para1sf[a->para1count][2]=k;
    a->para1count++;
    }

    if(a->subgrid(i+1,j,k)!=a->subgrid(i,j,k) && a->flag(i+1,j,k)>0 && a->flag(i,j,k)>0)
    {
    a->para4sf[a->para4count][0]=i;
    a->para4sf[a->para4count][1]=j;
    a->para4sf[a->para4count][2]=k;
    a->para4count++;
    }

    if(a->subgrid(i,j-1,k)!=a->subgrid(i,j,k) && a->flag(i,j-1,k)>0 && a->flag(i,j,k)>0)
    {
    a->para3sf[a->para3count][0]=i;
    a->para3sf[a->para3count][1]=j;
    a->para3sf[a->para3count][2]=k;
    a->para3count++;
    }

    if(a->subgrid(i,j+1,k)!=a->subgrid(i,j,k) && a->flag(i,j+1,k)>0 && a->flag(i,j,k)>0)
    {
    a->para2sf[a->para2count][0]=i;
    a->para2sf[a->para2count][1]=j;
    a->para2sf[a->para2count][2]=k;
    a->para2count++;
    }

    if(a->subgrid(i,j,k-1)!=a->subgrid(i,j,k) && a->flag(i,j,k-1)>0 && a->flag(i,j,k)>0)
    {
    a->para5sf[a->para5count][0]=i;
    a->para5sf[a->para5count][1]=j;
    a->para5sf[a->para5count][2]=k;
    a->para5count++;
    }

    if(a->subgrid(i,j,k+1)!=a->subgrid(i,j,k) && a->flag(i,j,k+1)>0 && a->flag(i,j,k)>0)
    {
    a->para6sf[a->para6count][0]=i;
    a->para6sf[a->para6count][1]=j;
    a->para6sf[a->para6count][2]=k;
    a->para6count++;
    }

    }
	
	ddout<<"para1: "<<a->para1count<<" para2: "<<a->para2count<<" para3: "<<a->para3count<<" para4: "<<a->para4count<<" para5: "<<a->para5count<<" para6: "<<a->para6count<<endl;
}

void decomp::paravoidsurface(lexer* p, dive* a)
{
    a->paravoid1count=0;
    a->paravoid2count=0;
    a->paravoid3count=0;
    a->paravoid4count=0;
    a->paravoid5count=0;
    a->paravoid6count=0;

    LOOP
    {
    if(a->subgrid(i-1,j,k)!=a->subgrid(i,j,k) && ((a->flag(i-1,j,k)>0 && a->flag(i,j,k)<0) || (a->flag(i-1,j,k)<0 && a->flag(i,j,k)>0)) 
	&& a->solid(i-1,j,k)>=0)
    {
    a->para1void[a->paravoid1count][0]=i;
    a->para1void[a->paravoid1count][1]=j;
    a->para1void[a->paravoid1count][2]=k;
	
	if(a->flag(i-1,j,k)<0 && a->flag(i,j,k)>0)
	a->para1void[a->paravoid1count][3]=1;
	
	if(a->flag(i-1,j,k)>0 && a->flag(i,j,k)<0)
	a->para1void[a->paravoid1count][3]=0;
	
    a->paravoid1count++;
    }

    if(a->subgrid(i+1,j,k)!=a->subgrid(i,j,k) && ((a->flag(i+1,j,k)>0 && a->flag(i,j,k)<0) || (a->flag(i+1,j,k)<0 && a->flag(i,j,k)>0))
	&& a->solid(i+1,j,k)>=0)
    {
    a->para4void[a->paravoid4count][0]=i;
    a->para4void[a->paravoid4count][1]=j;
    a->para4void[a->paravoid4count][2]=k;
	
	if(a->flag(i+1,j,k)<0 && a->flag(i,j,k)>0)
	a->para4void[a->paravoid4count][3]=1;
	
	if(a->flag(i+1,j,k)>0 && a->flag(i,j,k)<0)
	a->para4void[a->paravoid4count][3]=0;
	
    a->paravoid4count++;
    }

    if(a->subgrid(i,j-1,k)!=a->subgrid(i,j,k) && ((a->flag(i,j-1,k)>0 && a->flag(i,j,k)<0) || (a->flag(i,j-1,k)<0 && a->flag(i,j,k)>0))
	&& a->solid(i,j-1,k)>=0)
    {
    a->para3void[a->paravoid3count][0]=i;
    a->para3void[a->paravoid3count][1]=j;
    a->para3void[a->paravoid3count][2]=k;
	
	if(a->flag(i,j-1,k)<0 && a->flag(i,j,k)>0)
	a->para3void[a->paravoid3count][3]=1;
	
	if(a->flag(i,j-1,k)>0 && a->flag(i,j,k)<0)
	a->para3void[a->paravoid3count][3]=0;
	
    a->paravoid3count++;
    }

    if(a->subgrid(i,j+1,k)!=a->subgrid(i,j,k) && ((a->flag(i,j+1,k)>0 && a->flag(i,j,k)<0) || (a->flag(i,j+1,k)<0 && a->flag(i,j,k)>0))
	&& a->solid(i,j+1,k)>=0)
    {
    a->para2void[a->paravoid2count][0]=i;
    a->para2void[a->paravoid2count][1]=j;
    a->para2void[a->paravoid2count][2]=k;
	
	if(a->flag(i,j+1,k)<0 && a->flag(i,j,k)>0)
	a->para2void[a->paravoid2count][3]=1;
	
	if(a->flag(i,j+1,k)>0 && a->flag(i,j,k)<0)
	a->para2void[a->paravoid2count][3]=0;
	
    a->paravoid2count++;
    }

    if(a->subgrid(i,j,k-1)!=a->subgrid(i,j,k) && ((a->flag(i,j,k-1)>0 && a->flag(i,j,k)<0) || (a->flag(i,j,k-1)<0 && a->flag(i,j,k)>0))
	&& a->solid(i,j,k-1)>=0)
    {
    a->para5void[a->paravoid5count][0]=i;
    a->para5void[a->paravoid5count][1]=j;
    a->para5void[a->paravoid5count][2]=k;
	
	if(a->flag(i,j,k-1)<0 && a->flag(i,j,k)>0)
	a->para5void[a->paravoid5count][3]=1;
	
	if(a->flag(i,j,k-1)>0 && a->flag(i,j,k)<0)
	a->para5void[a->paravoid5count][3]=0;
	
    a->paravoid5count++;
    }

    if(a->subgrid(i,j,k+1)!=a->subgrid(i,j,k) && ((a->flag(i,j,k+1)>0 && a->flag(i,j,k)<0) || (a->flag(i,j,k+1)<0 && a->flag(i,j,k)>0))
	&& a->solid(i,j,k+1)>=0)
    {
    a->para6void[a->paravoid6count][0]=i;
    a->para6void[a->paravoid6count][1]=j;
    a->para6void[a->paravoid6count][2]=k;
	
	if(a->flag(i,j,k+1)<0 && a->flag(i,j,k)>0)
	a->para6void[a->paravoid6count][3]=1;
	
	if(a->flag(i,j,k+1)>0 && a->flag(i,j,k)<0)
	a->para6void[a->paravoid6count][1]=0;
	
    a->paravoid6count++;
    }

    }
	
	
}


