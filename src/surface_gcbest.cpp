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

#include"surface.h"
#include"lexer.h"
#include"dive.h"

void surface::gcb_estimate(lexer* p, dive* a)
{
    for(qn=0; qn<p->M10;qn++)
    {
    a->tot_gcbextra[qn]=0;
    }
    
    
    // gcbextra_est
    int count;
	n=0;
	NLOOP
	{
		SUBLOOP
		{
            count=0;
            if(a->solid_dist(i,j,k)<0.0 && a->topo_dist(i,j,k)<0.0) 
            {
                if(a->solid_dist(i-1,j,k)>0.0 && a->topo_dist(i-1,j,k)>0.0) 
                ++count;
                
                if(a->solid_dist(i+1,j,k)>0.0 && a->topo_dist(i+1,j,k)>0.0)
                ++count;
                
                if(a->solid_dist(i,j-1,k)>0.0 && a->topo_dist(i,j-1,k)>0.0)
                ++count;
                
                if(a->solid_dist(i,j+1,k)>0.0 && a->topo_dist(i,j+1,k)>0.0)
                ++count;
                
                if(a->solid_dist(i,j,k-1)>0.0 && a->topo_dist(i,j,k-1)>0.0)
                ++count;
                
                if(a->solid_dist(i,j,k+1)>0.0 && a->topo_dist(i,j,k+1)>0.0)
                ++count;
            
            if(count>=2)
            ++a->tot_gcbextra[n];
            }
		}
	++n;
	}
}
