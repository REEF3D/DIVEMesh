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

void decomp::periodic_surfco(lexer* p, dive* a)
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

/*    
#define ALOOP for(aa=1;aa<=a->mx;++aa)
#define BLOOP for(bb=1;bb<=a->my;++bb)
#define CLOOP for(cc=1;cc<=a->mz;++cc)
#define NLOOP ALOOP BLOOP CLOOP


#define SILOOP for(i=a->xnode[aa-1];i<a->xnode[aa];++i)
#define SJLOOP for(j=a->ynode[bb-1];j<a->ynode[bb];++j)
#define SKLOOP for(k=a->znode[cc-1];k<a->znode[cc];++k)
#define SUBLOOP SILOOP SJLOOP SKLOOP
*/
/*
    if(p->C21==2)
    {
    aa==0;
    i=0;
        
        for(bb=1;bb<=a->my;++bb)
        for(cc=1;cc<=a->mz;++cc)
        {
        // 1 
        j=a->ynode[bb-1];
        for(k=a->znode[cc-1];k<a->znode[cc];++k)
        {
            
        }


        }    
            
            
    
    
    }*/
	
    LOOP
    {
		
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
