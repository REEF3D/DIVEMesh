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

#include"topo.h"
#include"dive.h"
#include"lexer.h"

void topo::gcb_estimate(lexer *p, dive *a)
{
    n=0;

    LOOP
    {
		if(a->topo_dist(i,j,k)>=0.0)
		if(a->topo_dist(i-1,j,k)<0.0 || a->topo_dist(i+1,j,k)<0.0 || a->topo_dist(i,j-1,k)<0.0 || a->topo_dist(i,j+1,k)<0.0 || a->topo_dist(i,j,k-1)<0.0 || a->topo_dist(i,j,k+1)<0.0)
		++n;
    }

	int qn;

	for(qn=0; qn<p->M10;qn++)
    {
	a->topo_gcb[qn]=0;
    a->topo_gcbextra[qn]=0;
    }
    
    // gcb_est
	n=0;
	NLOOP
	{
		SUBLOOP
		{
		if(a->topo_dist(i,j,k)>=0.0)
		if(a->topo_dist(i-1,j,k)<0.0 || a->topo_dist(i+1,j,k)<0.0 || a->topo_dist(i,j-1,k)<0.0 || a->topo_dist(i,j+1,k)<0.0 || a->topo_dist(i,j,k-1)<0.0 || a->topo_dist(i,j,k+1)<0.0)
		++a->topo_gcb[n];
		}
	++n;
	}
    
    // gcbextra_est
    intfield fgc(p);
    
    MALOOP
    fgc(i,j,k)=0;
    
    
    
    int count;
	n=0;
	NLOOP
	{
		SUBLOOP
		{
            if(a->topo_dist(i,j,k)>0.0)
            {
                if(a->topo_dist(i-1,j,k)<0.0) 
                {
                ++fgc(i-1,j,k);
                ++fgc(i-2,j,k);
                ++fgc(i-3,j,k);
                }
                
                if(a->topo_dist(i+1,j,k)<0.0)
                {
                ++fgc(i+1,j,k);
                ++fgc(i+2,j,k);
                ++fgc(i+3,j,k);
                }
                
                if(a->topo_dist(i,j-1,k)<0.0)
                {
                ++fgc(i,j-1,k);
                ++fgc(i,j-2,k);
                ++fgc(i,j-3,k);
                }
                
                if(a->topo_dist(i,j+1,k)<0.0)
                {
                ++fgc(i,j+1,k);
                ++fgc(i,j+2,k);
                ++fgc(i,j+3,k);
                }
                
                if(a->topo_dist(i,j,k-1)<0.0)
                {
                ++fgc(i,j,k-1);
                ++fgc(i,j,k-2);
                ++fgc(i,j,k-3);
                }
                
                if(a->topo_dist(i,j,k+1)<0.0)
                {
                ++fgc(i,j,k+1);
                ++fgc(i,j,k+2);
                ++fgc(i,j,k+3);
                }
            
            }
            /*
            count=0;
            if(a->topo_dist(i,j,k)<0.0)
            {
                if(a->topo_dist(i-1,j,k)>0.0) 
                ++count;
                
                if(a->topo_dist(i+1,j,k)>0.0)
                ++count;
                
                if(a->topo_dist(i,j-1,k)>0.0)
                ++count;
                
                if(a->topo_dist(i,j+1,k)>0.0)
                ++count;
                
                if(a->topo_dist(i,j,k-1)>0.0)
                ++count;
                
                if(a->topo_dist(i,j,k+1)>0.0)
                ++count;
            
            if(count>=2)
            ++a->topo_gcbextra[n];
            }*/
		}
	++n;
	}
    
    
    n=0;
	NLOOP
	{
		SUBLOOP
		{
            
        if(fgc(i,j,k)>=2)
        ++a->topo_gcbextra[n];
        }
	++n;
	}
    
    //for(n=0;n<p->M10;++n)
    //cout<<n<<" a->topo_gcbextra[n]: "<<a->topo_gcbextra[n]<<endl;
}
