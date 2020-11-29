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

#include"surface.h"
#include"lexer.h"
#include"dive.h"

surface::surface()
{
}

surface::~surface()
{
}

void surface::start(lexer* p, dive* a)
{
	mem_alloc(p,a);
    normalvec(p,a);
    direction(p,a);
    makesurf(p,a);
    makesurf_plate(p,a);
    makedist(p,a);
    ccactive(p,a);
    makesurfsolid(p,a);
}

void surface::mem_alloc(lexer* p, dive* a)
{
    cout<<"surface"<<endl;
    a->surfcount=0;
	
	surfnum=0;

    LOOP
    if(a->flag(i,j,k)==-20)
    a->flag(i,j,k)=-21;
	
	LOOP
    if(a->flag(i,j,k)>0)
    {
        if(a->flag(i-1,j,k)<0)
        ++surfnum;
		
        if(a->flag(i+1,j,k)<0)
        ++surfnum;
		
        if(a->flag(i,j-1,k)<0)
        ++surfnum;
		
		if(a->flag(i,j+1,k)<0)
        ++surfnum;
		
        if(a->flag(i,j,k-1)<0)
        ++surfnum;
		
        if(a->flag(i,j,k+1)<0)
        ++surfnum;
    }
    
    mem_alloc_plate(p,a);
	
	cout<<"surfnum: "<<surfnum<<"  surfnum_solid: "<<a->surfcount_solid<<endl;
    
	 
	a->Iarray(a->surf,surfnum+a->surfcount_solid,5);
	a->Iarray(a->surfdir,surfnum+a->surfcount_solid,3);
	a->Darray(a->gcn,surfnum+a->surfcount_solid,3);
	a->Darray(a->gcd,surfnum+a->surfcount_solid);
}
	
void surface::makesurf(lexer* p, dive* a)
{
//-------
    
    LOOP
    if(a->flag(i,j,k)>0)
    {
        if(a->flag(i-1,j,k)<0)
        {
        a->surf[a->surfcount][0]=i;
        a->surf[a->surfcount][1]=j;
        a->surf[a->surfcount][2]=k;
        a->surf[a->surfcount][3]=1;
        a->surf[a->surfcount][4]=fabs(a->flag(i-1,j,k));
        a->surfcount++;
        }
		
        if(a->flag(i+1,j,k)<0)
        {
        a->surf[a->surfcount][0]=i;
        a->surf[a->surfcount][1]=j;
        a->surf[a->surfcount][2]=k;
        a->surf[a->surfcount][3]=4;
        a->surf[a->surfcount][4]=fabs(a->flag(i+1,j,k));
        a->surfcount++;
        }
		
        if(a->flag(i,j-1,k)<0)
        {
        a->surf[a->surfcount][0]=i;
        a->surf[a->surfcount][1]=j;
        a->surf[a->surfcount][2]=k;
        a->surf[a->surfcount][3]=3;
        a->surf[a->surfcount][4]=fabs(a->flag(i,j-1,k));
        a->surfcount++;
        }
		
		if(a->flag(i,j+1,k)<0)
        {
        a->surf[a->surfcount][0]=i;
        a->surf[a->surfcount][1]=j;
        a->surf[a->surfcount][2]=k;
        a->surf[a->surfcount][3]=2;
        a->surf[a->surfcount][4]=fabs(a->flag(i,j+1,k));
        a->surfcount++;
        }
		
        if(a->flag(i,j,k-1)<0)
        {
        a->surf[a->surfcount][0]=i;
        a->surf[a->surfcount][1]=j;
        a->surf[a->surfcount][2]=k;
        a->surf[a->surfcount][3]=5;
        a->surf[a->surfcount][4]=fabs(a->flag(i,j,k-1));
        a->surfcount++;
        }
		
        if(a->flag(i,j,k+1)<0)
        {
        a->surf[a->surfcount][0]=i;
        a->surf[a->surfcount][1]=j;
        a->surf[a->surfcount][2]=k;
        a->surf[a->surfcount][3]=6;
        a->surf[a->surfcount][4]=fabs(a->flag(i,j,k+1));
        a->surfcount++;
        }
    }
    
}

void surface::ccactive(lexer* p, dive* a)
{
    cout<<"\t ccactive"<<endl;

    LOOP
    {
        n=a->confac(i,j,k);

        if(n>0)
        {

            if(a->flag(i,j,k)<0)
            a->ccstate[n]=0;

            if(a->flag(i,j,k)>0)
            a->ccstate[n]=1;

        }
    }
}
