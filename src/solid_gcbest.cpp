/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2022 Hans Bihs

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

#include"solid.h"
#include"dive.h"
#include"lexer.h"


void solid::gcb_estimate(lexer *p, dive *a)
{
    int qn;
    n=0;

    LOOP
    {
		if(a->solid_dist(i,j,k)>=0.0)
		if(a->solid_dist(i-1,j,k)<0.0 || a->solid_dist(i+1,j,k)<0.0 || a->solid_dist(i,j-1,k)<0.0 || a->solid_dist(i,j+1,k)<0.0 || a->solid_dist(i,j,k-1)<0.0 || a->solid_dist(i,j,k+1)<0.0)
		++n;
    }

	for(qn=0; qn<p->M10;qn++)
    {
	a->solid_gcb[qn]=0;
    a->solid_gcbextra[qn]=0;
    }
    
    // gcb_est
	n=0;
	NLOOP
	{
		SUBLOOP
		{
		if(a->solid_dist(i,j,k)>=0.0)
		if(a->solid_dist(i-1,j,k)<0.0 || a->solid_dist(i+1,j,k)<0.0 || a->solid_dist(i,j-1,k)<0.0 || a->solid_dist(i,j+1,k)<0.0 || a->solid_dist(i,j,k-1)<0.0 || a->solid_dist(i,j,k+1)<0.0)
		++a->solid_gcb[n];
		}
	++n;
	}
    
    // gcbextra_est
    intfield fgc(p);
    
    MALOOP
    fgc(i,j,k)=0;
    
    LOOP
    if(a->solid_dist(i,j,k)>=0.0)
    ++fgc(i,j,k);
    
    int count;
	n=0;
	NLOOP
	{
		SUBLOOP
		{
            if(a->solid_dist(i,j,k)>0.0)
            {
                if(a->solid_dist(i-1,j,k)<0.0) 
                {
                ++fgc(i-1,j,k);
                ++fgc(i-2,j,k);
                ++fgc(i-3,j,k);
                }
                
                if(a->solid_dist(i+1,j,k)<0.0)
                {
                ++fgc(i+1,j,k);
                ++fgc(i+2,j,k);
                ++fgc(i+3,j,k);
                }
                
                if(a->solid_dist(i,j-1,k)<0.0)
                {
                ++fgc(i,j-1,k);
                ++fgc(i,j-2,k);
                ++fgc(i,j-3,k);
                }
                
                if(a->solid_dist(i,j+1,k)<0.0)
                {
                ++fgc(i,j+1,k);
                ++fgc(i,j+2,k);
                ++fgc(i,j+3,k);
                }
                
                if(a->solid_dist(i,j,k-1)<0.0)
                {
                ++fgc(i,j,k-1);
                ++fgc(i,j,k-2);
                ++fgc(i,j,k-3);
                }
                
                if(a->solid_dist(i,j,k+1)<0.0)
                {
                ++fgc(i,j,k+1);
                ++fgc(i,j,k+2);
                ++fgc(i,j,k+3);
                }
            
            }

		}
	++n;
	}
    
    for(q=0;q<a->para1count;q++)
    {
    i=a->para1sf[q][0];
    j=a->para1sf[q][1];
    k=a->para1sf[q][2];
    
    ++fgc(i-1,j,k);
    ++fgc(i-2,j,k);
    ++fgc(i-3,j,k);
    }
    
    for(q=0;q<a->para2count;q++)
    {
    i=a->para2sf[q][0];
    j=a->para2sf[q][1];
    k=a->para2sf[q][2];
    
    ++fgc(i,j+1,k);
    ++fgc(i,j+2,k);
    ++fgc(i,j+3,k);
    }
    
    for(q=0;q<a->para3count;q++)
    {
    i=a->para3sf[q][0];
    j=a->para3sf[q][1];
    k=a->para3sf[q][2];
    
    ++fgc(i,j-1,k);
    ++fgc(i,j-2,k);
    ++fgc(i,j-3,k);
    }
    
    for(q=0;q<a->para4count;q++)
    {
    i=a->para4sf[q][0];
    j=a->para4sf[q][1];
    k=a->para4sf[q][2];
    
    ++fgc(i,j+1,k);
    ++fgc(i,j+2,k);
    ++fgc(i,j+3,k);
    }
    
    for(q=0;q<a->para5count;q++)
    {
    i=a->para5sf[q][0];
    j=a->para5sf[q][1];
    k=a->para5sf[q][2];
    
    ++fgc(i,j,k-1);
    ++fgc(i,j,k-2);
    ++fgc(i,j,k-3);
    }
    
    for(q=0;q<a->para6count;q++)
    {
    i=a->para6sf[q][0];
    j=a->para6sf[q][1];
    k=a->para6sf[q][2];
    
    ++fgc(i,j,k+1);
    ++fgc(i,j,k+2);
    ++fgc(i,j,k+3);
    }
    
    
    
    // -------
    n=0;
	NLOOP
	{
		SUBLOOP
		{
            
        if(fgc(i,j,k)>=2)
        ++a->solid_gcbextra[n];
        }
	++n;
	}
    
    //for(n=0;n<p->M10;++n)
    //cout<<n<<" a->solid_gcbextra[n]: "<<a->solid_gcbextra[n]<<endl;
}



