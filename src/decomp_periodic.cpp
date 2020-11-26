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
    
    // serial or parallel periodic BC
    if(p->C21>1)
    {
        if(a->mx==1)
        p->C21=1;
        
        if(a->mx>1)
        {
        p->C21=2;
        xper=1;
        }
    }
    
    if(p->C22>1)
    {
        if(a->my==1)
        p->C22=1;
        
        if(a->my>1)
        {
        p->C22=2;
        yper=1;
        }
    }
    
    if(p->C23>1)
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
    if(p->C21==3)
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
        }

        i=p->knox-1;
        for(j=0;j<a->knoy;++j)
        for(k=0;k<a->knoz;++k)
        {
        a->para4sf[a->para4count][0]=i;
        a->para4sf[a->para4count][1]=j;
        a->para4sf[a->para4count][2]=k;
        a->para4count++;
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
        }

        j=p->knoy-1;
        for(i=0;i<a->knox;++i)
        for(k=0;k<a->knoz;++k)
        {
        a->para2sf[a->para2count][0]=i;
        a->para2sf[a->para2count][1]=j;
        a->para2sf[a->para2count][2]=k;
        a->para2count++;
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
        }

        k=p->knoz-1;
        for(i=0;i<a->knox;++i)
        for(j=0;j<a->knoy;++j)
        {
        a->para6sf[a->para6count][0]=i;
        a->para6sf[a->para6count][1]=j;
        a->para6sf[a->para6count][2]=k;
        a->para6count++;
        }
    }
}