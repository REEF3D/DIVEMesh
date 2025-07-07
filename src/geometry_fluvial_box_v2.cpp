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

#include"geometry.h"
#include"dive.h"
#include"lexer.h"

void geometry::fluvial_box_v2(lexer *p, dive *a, int rank, int &ts, int &te)
{
     // add the rest of the geometry geometry
    ts=p->tricount;
    
    // Front Face
	// Tri 1
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = box_xs;
	p->tri_y[p->tricount][0] = box_ye;
	p->tri_z[p->tricount][0] = box_zs;
	
	p->tri_x[p->tricount][1] = box_xs;
	p->tri_y[p->tricount][1] = yl[0];
	p->tri_z[p->tricount][1] = box_ze;
	
	p->tri_x[p->tricount][2] = box_xs;
	p->tri_y[p->tricount][2] = yl[0];
	p->tri_z[p->tricount][2] = box_zs;
	++p->tricount;
    
    //cout<<"TRIVEC: 001"<<endl;
	
	// Tri 2
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = box_xs;
	p->tri_y[p->tricount][0] = box_ye;
	p->tri_z[p->tricount][0] = box_zs;
	
	p->tri_x[p->tricount][1] = box_xs;
	p->tri_y[p->tricount][1] = box_ye;
	p->tri_z[p->tricount][1] = box_ze;
	
	p->tri_x[p->tricount][2] = box_xs;
	p->tri_y[p->tricount][2] = yl[0];
	p->tri_z[p->tricount][2] = box_ze;
	++p->tricount;
    
    // Tri 3
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = box_xs;
	p->tri_y[p->tricount][0] = yl[0];
	p->tri_z[p->tricount][0] = box_zs;
	
	p->tri_x[p->tricount][1] = box_xs;
	p->tri_y[p->tricount][1] = yl[0];
	p->tri_z[p->tricount][1] = box_zs+G307_bh;
	
	p->tri_x[p->tricount][2] = box_xs;
	p->tri_y[p->tricount][2] = yr[0];
	p->tri_z[p->tricount][2] = box_zs+G307_bh;
	++p->tricount;
    
    // Tri 4
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = box_xs;
	p->tri_y[p->tricount][0] = yl[0];
	p->tri_z[p->tricount][0] = box_zs;
	
	p->tri_x[p->tricount][1] = box_xs;
	p->tri_y[p->tricount][1] = yr[0];
	p->tri_z[p->tricount][1] = box_zs;
	
	p->tri_x[p->tricount][2] = box_xs;
	p->tri_y[p->tricount][2] = yr[0];
	p->tri_z[p->tricount][2] = box_zs+G307_bh;
	++p->tricount;
    
    // Tri 5
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = box_xs;
	p->tri_y[p->tricount][0] = yr[0];
	p->tri_z[p->tricount][0] = box_zs;
	
	p->tri_x[p->tricount][1] = box_xs;
	p->tri_y[p->tricount][1] = box_ys;
	p->tri_z[p->tricount][1] = box_ze;
	
	p->tri_x[p->tricount][2] = box_xs;
	p->tri_y[p->tricount][2] = box_ys;
	p->tri_z[p->tricount][2] = box_zs;
	++p->tricount;
    
    // Tri 6
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = box_xs;
	p->tri_y[p->tricount][0] = yr[0];
	p->tri_z[p->tricount][0] = box_zs;
	
	p->tri_x[p->tricount][1] = box_xs;
	p->tri_y[p->tricount][1] = yr[0];
	p->tri_z[p->tricount][1] = box_ze;
	
	p->tri_x[p->tricount][2] = box_xs;
	p->tri_y[p->tricount][2] = box_ys;
	p->tri_z[p->tricount][2] = box_ze;
	++p->tricount;
    
    
    
    // Back Face
	// Tri 1
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = box_xe;
	p->tri_y[p->tricount][0] = box_ye;
	p->tri_z[p->tricount][0] = box_zs;
	
	p->tri_x[p->tricount][1] = box_xe;
	p->tri_y[p->tricount][1] = yl[numds-1];
	p->tri_z[p->tricount][1] = box_ze;
	
	p->tri_x[p->tricount][2] = box_xe;
	p->tri_y[p->tricount][2] = yl[numds-1];
	p->tri_z[p->tricount][2] = box_zs;
	++p->tricount;
	
	// Tri 2
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = box_xe;
	p->tri_y[p->tricount][0] = box_ye;
	p->tri_z[p->tricount][0] = box_zs;
	
	p->tri_x[p->tricount][1] = box_xe;
	p->tri_y[p->tricount][1] = box_ye;
	p->tri_z[p->tricount][1] = box_ze;
	
	p->tri_x[p->tricount][2] = box_xe;
	p->tri_y[p->tricount][2] = yl[numds-1];
	p->tri_z[p->tricount][2] = box_ze;
	++p->tricount;
    
    // Tri 3
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = box_xe;
	p->tri_y[p->tricount][0] = yl[numds-1];
	p->tri_z[p->tricount][0] = box_zs;
	
	p->tri_x[p->tricount][1] = box_xe;
	p->tri_y[p->tricount][1] = yl[numds-1];
	p->tri_z[p->tricount][1] = box_zs+G307_bh;
	
	p->tri_x[p->tricount][2] = box_xe;
	p->tri_y[p->tricount][2] = yr[numds-1];
	p->tri_z[p->tricount][2] = box_zs+G307_bh;
	++p->tricount;
    
    // Tri 4
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = box_xe;
	p->tri_y[p->tricount][0] = yl[numds-1];
	p->tri_z[p->tricount][0] = box_zs;
	
	p->tri_x[p->tricount][1] = box_xe;
	p->tri_y[p->tricount][1] = yr[numds-1];
	p->tri_z[p->tricount][1] = box_zs;
	
	p->tri_x[p->tricount][2] = box_xe;
	p->tri_y[p->tricount][2] = yr[numds-1];
	p->tri_z[p->tricount][2] = box_zs+G307_bh;
	++p->tricount;
    
    // Tri 5
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = box_xe;
	p->tri_y[p->tricount][0] = yr[numds-1];
	p->tri_z[p->tricount][0] = box_zs;
	
	p->tri_x[p->tricount][1] = box_xe;
	p->tri_y[p->tricount][1] = box_ys;
	p->tri_z[p->tricount][1] = box_ze;
	
	p->tri_x[p->tricount][2] = box_xe;
	p->tri_y[p->tricount][2] = box_ys;
	p->tri_z[p->tricount][2] = box_zs;
	++p->tricount;
    
    // Tri 6
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = box_xe;
	p->tri_y[p->tricount][0] = yr[numds-1];
	p->tri_z[p->tricount][0] = box_zs;
	
	p->tri_x[p->tricount][1] = box_xe;
	p->tri_y[p->tricount][1] = yr[numds-1];
	p->tri_z[p->tricount][1] = box_ze;
	
	p->tri_x[p->tricount][2] = box_xe;
	p->tri_y[p->tricount][2] = box_ys;
	p->tri_z[p->tricount][2] = box_ze;
	++p->tricount;
    
    //cout<<"TRIVEC: 002"<<endl;
    
    for(n=0; n<numds-1;++n)
    {

        // Face 1
        // Tri 1
        p->trivec_x[p->tricount] = 0.0;
        p->trivec_y[p->tricount] = -1.0;
        p->trivec_z[p->tricount] = 0.0;
        
        p->tri_x[p->tricount][0] = xr[n];
        p->tri_y[p->tricount][0] = box_ys;
        p->tri_z[p->tricount][0] = box_zs;
        
        p->tri_x[p->tricount][1] = xr[n+1];
        p->tri_y[p->tricount][1] = box_ys;
        p->tri_z[p->tricount][1] = box_zs;
        
        p->tri_x[p->tricount][2] = xl[n];
        p->tri_y[p->tricount][2] = box_ye;
        p->tri_z[p->tricount][2] = box_zs;
        ++p->tricount;
        
        // Tri 2
        p->trivec_x[p->tricount] = 0.0;
        p->trivec_y[p->tricount] = -1.0;
        p->trivec_z[p->tricount] = 0.0;
        
        p->tri_x[p->tricount][0] = xr[n+1];
        p->tri_y[p->tricount][0] = box_ys;
        p->tri_z[p->tricount][0] = box_zs;
        
        p->tri_x[p->tricount][1] = xl[n+1];
        p->tri_y[p->tricount][1] = box_ye;
        p->tri_z[p->tricount][1] = box_zs;
        
        p->tri_x[p->tricount][2] = xl[n];
        p->tri_y[p->tricount][2] = box_ye;
        p->tri_z[p->tricount][2] = box_zs;
        ++p->tricount;
        
        
        // Face 2
        // Tri 1
        p->trivec_x[p->tricount] = 0.0;
        p->trivec_y[p->tricount] = -1.0;
        p->trivec_z[p->tricount] = 0.0;
        
        p->tri_x[p->tricount][0] = xr[n];
        p->tri_y[p->tricount][0] = box_ys;
        p->tri_z[p->tricount][0] = box_zs;
        
        p->tri_x[p->tricount][1] = xr[n+1];
        p->tri_y[p->tricount][1] = box_ys;
        p->tri_z[p->tricount][1] = box_zs;
        
        p->tri_x[p->tricount][2] = xr[n];
        p->tri_y[p->tricount][2] = box_ys;
        p->tri_z[p->tricount][2] = box_ze;
        ++p->tricount;
        
        // Tri 2
        p->trivec_x[p->tricount] = 0.0;
        p->trivec_y[p->tricount] = -1.0;
        p->trivec_z[p->tricount] = 0.0;
        
        p->tri_x[p->tricount][0] = xr[n+1];
        p->tri_y[p->tricount][0] = box_ys;
        p->tri_z[p->tricount][0] = box_zs;
        
        p->tri_x[p->tricount][1] = xr[n+1];
        p->tri_y[p->tricount][1] = box_ys;
        p->tri_z[p->tricount][1] = box_ze;
        
        p->tri_x[p->tricount][2] = xr[n];
        p->tri_y[p->tricount][2] = box_ys;
        p->tri_z[p->tricount][2] = box_ze;
        ++p->tricount;
        
        
        // Face 3
        // Tri 1
        p->trivec_x[p->tricount] = 0.0;
        p->trivec_y[p->tricount] = -1.0;
        p->trivec_z[p->tricount] = 0.0;
        
        p->tri_x[p->tricount][0] = xr[n];
        p->tri_y[p->tricount][0] = box_ys;
        p->tri_z[p->tricount][0] = box_ze;
        
        p->tri_x[p->tricount][1] = xr[n+1];
        p->tri_y[p->tricount][1] = box_ys;
        p->tri_z[p->tricount][1] = box_ze;
        
        p->tri_x[p->tricount][2] = xr[n];
        p->tri_y[p->tricount][2] = yr[n];
        p->tri_z[p->tricount][2] = box_ze;
        ++p->tricount;
        
        // Tri 2
        p->trivec_x[p->tricount] = 0.0;
        p->trivec_y[p->tricount] = -1.0;
        p->trivec_z[p->tricount] = 0.0;
        
        p->tri_x[p->tricount][0] = xr[n+1];
        p->tri_y[p->tricount][0] = box_ys;
        p->tri_z[p->tricount][0] = box_ze;
        
        p->tri_x[p->tricount][1] = xr[n+1];
        p->tri_y[p->tricount][1] = yr[n+1];
        p->tri_z[p->tricount][1] = box_ze;
        
        p->tri_x[p->tricount][2] = xr[n];
        p->tri_y[p->tricount][2] = yr[n];
        p->tri_z[p->tricount][2] = box_ze;
        ++p->tricount;
        
        
        // Face 4
        // Tri 1
        p->trivec_x[p->tricount] = 0.0;
        p->trivec_y[p->tricount] = -1.0;
        p->trivec_z[p->tricount] = 0.0;
        
        p->tri_x[p->tricount][0] = xr[n];
        p->tri_y[p->tricount][0] = yr[n];
        p->tri_z[p->tricount][0] = box_zs+G307_bh;
        
        p->tri_x[p->tricount][1] = xr[n+1];
        p->tri_y[p->tricount][1] = yr[n+1];
        p->tri_z[p->tricount][1] = box_zs+G307_bh;
        
        p->tri_x[p->tricount][2] = xr[n];
        p->tri_y[p->tricount][2] = yr[n];
        p->tri_z[p->tricount][2] = box_ze;
        ++p->tricount;
        
        // Tri 2
        p->trivec_x[p->tricount] = 0.0;
        p->trivec_y[p->tricount] = -1.0;
        p->trivec_z[p->tricount] = 0.0;
        
        p->tri_x[p->tricount][0] = xr[n+1];
        p->tri_y[p->tricount][0] = yr[n+1];
        p->tri_z[p->tricount][0] = box_zs+G307_bh;
        
        p->tri_x[p->tricount][1] = xr[n+1];
        p->tri_y[p->tricount][1] = yr[n+1];
        p->tri_z[p->tricount][1] = box_ze;
        
        p->tri_x[p->tricount][2] = xr[n];
        p->tri_y[p->tricount][2] = yr[n];
        p->tri_z[p->tricount][2] = box_ze;
        ++p->tricount;
        
        
        // Face 5
        // Tri 1
        p->trivec_x[p->tricount] = 0.0;
        p->trivec_y[p->tricount] = -1.0;
        p->trivec_z[p->tricount] = 0.0;
        
        p->tri_x[p->tricount][0] = xr[n];
        p->tri_y[p->tricount][0] = yr[n];
        p->tri_z[p->tricount][0] = box_zs+G307_bh;
        
        p->tri_x[p->tricount][1] = xr[n+1];
        p->tri_y[p->tricount][1] = yr[n+1];
        p->tri_z[p->tricount][1] = box_zs+G307_bh;
        
        p->tri_x[p->tricount][2] = xl[n];
        p->tri_y[p->tricount][2] = yl[n];
        p->tri_z[p->tricount][2] = box_zs+G307_bh;
        ++p->tricount;
        
        // Tri 2
        p->trivec_x[p->tricount] = 0.0;
        p->trivec_y[p->tricount] = -1.0;
        p->trivec_z[p->tricount] = 0.0;
        
        p->tri_x[p->tricount][0] = xr[n+1];
        p->tri_y[p->tricount][0] = yr[n+1];
        p->tri_z[p->tricount][0] = box_zs+G307_bh;
        
        p->tri_x[p->tricount][1] = xl[n+1];
        p->tri_y[p->tricount][1] = yl[n+1];
        p->tri_z[p->tricount][1] = box_zs+G307_bh;
        
        p->tri_x[p->tricount][2] = xl[n];
        p->tri_y[p->tricount][2] = yl[n];
        p->tri_z[p->tricount][2] = box_zs+G307_bh;
        ++p->tricount;
        
        
        // Face 6
        // Tri 1
        p->trivec_x[p->tricount] = 0.0;
        p->trivec_y[p->tricount] = -1.0;
        p->trivec_z[p->tricount] = 0.0;
        
        p->tri_x[p->tricount][0] = xl[n];
        p->tri_y[p->tricount][0] = yl[n];
        p->tri_z[p->tricount][0] = box_zs+G307_bh;
        
        p->tri_x[p->tricount][1] = xl[n+1];
        p->tri_y[p->tricount][1] = yl[n+1];
        p->tri_z[p->tricount][1] = box_zs+G307_bh;
        
        p->tri_x[p->tricount][2] = xl[n];
        p->tri_y[p->tricount][2] = yl[n];
        p->tri_z[p->tricount][2] = box_ze;
        ++p->tricount;
        
        // Tri 2
        p->trivec_x[p->tricount] = 0.0;
        p->trivec_y[p->tricount] = -1.0;
        p->trivec_z[p->tricount] = 0.0;
        
        p->tri_x[p->tricount][0] = xl[n+1];
        p->tri_y[p->tricount][0] = yl[n+1];
        p->tri_z[p->tricount][0] = box_zs+G307_bh;
        
        p->tri_x[p->tricount][1] = xl[n+1];
        p->tri_y[p->tricount][1] = yl[n+1];
        p->tri_z[p->tricount][1] = box_ze;
        
        p->tri_x[p->tricount][2] = xl[n];
        p->tri_y[p->tricount][2] = yl[n];
        p->tri_z[p->tricount][2] = box_ze;
        ++p->tricount;
        
        
        // Face 7
        // Tri 1
        p->trivec_x[p->tricount] = 0.0;
        p->trivec_y[p->tricount] = -1.0;
        p->trivec_z[p->tricount] = 0.0;
        
        p->tri_x[p->tricount][0] = xl[n];
        p->tri_y[p->tricount][0] = yl[n];
        p->tri_z[p->tricount][0] = box_ze;
        
        p->tri_x[p->tricount][1] = xl[n+1];
        p->tri_y[p->tricount][1] = yl[n+1];
        p->tri_z[p->tricount][1] = box_ze;
        
        p->tri_x[p->tricount][2] = xl[n];
        p->tri_y[p->tricount][2] = box_ye;
        p->tri_z[p->tricount][2] = box_ze;
        ++p->tricount;
        
        // Tri 2
        p->trivec_x[p->tricount] = 0.0;
        p->trivec_y[p->tricount] = -1.0;
        p->trivec_z[p->tricount] = 0.0;
        
        p->tri_x[p->tricount][0] = xl[n+1];
        p->tri_y[p->tricount][0] = yl[n+1];
        p->tri_z[p->tricount][0] = box_ze;
        
        p->tri_x[p->tricount][1] = xl[n+1];
        p->tri_y[p->tricount][1] = box_ye;
        p->tri_z[p->tricount][1] = box_ze;
        
        p->tri_x[p->tricount][2] = xl[n];
        p->tri_y[p->tricount][2] = box_ye;
        p->tri_z[p->tricount][2] = box_ze;
        ++p->tricount;
        
        
        // Face 8
        // Tri 1
        p->trivec_x[p->tricount] = 0.0;
        p->trivec_y[p->tricount] = -1.0;
        p->trivec_z[p->tricount] = 0.0;
        
        p->tri_x[p->tricount][0] = xl[n];
        p->tri_y[p->tricount][0] = box_ye;
        p->tri_z[p->tricount][0] = box_zs;
        
        p->tri_x[p->tricount][1] = xl[n+1];
        p->tri_y[p->tricount][1] = box_ye;
        p->tri_z[p->tricount][1] = box_zs;
        
        p->tri_x[p->tricount][2] = xl[n];
        p->tri_y[p->tricount][2] = box_ye;
        p->tri_z[p->tricount][2] = box_ze;
        ++p->tricount;
        
        // Tri 2
        p->trivec_x[p->tricount] = 0.0;
        p->trivec_y[p->tricount] = -1.0;
        p->trivec_z[p->tricount] = 0.0;
        
        p->tri_x[p->tricount][0] = xl[n+1];
        p->tri_y[p->tricount][0] = box_ye;
        p->tri_z[p->tricount][0] = box_zs;
        
        p->tri_x[p->tricount][1] = xl[n+1];
        p->tri_y[p->tricount][1] = box_ye;
        p->tri_z[p->tricount][1] = box_ze;
        
        p->tri_x[p->tricount][2] = xl[n];
        p->tri_y[p->tricount][2] = box_ye;
        p->tri_z[p->tricount][2] = box_ze;
        ++p->tricount;
        
        //cout<<"TRIVEC: 003 "<<p->tricount<<endl;
    }
    
    te=p->tricount;
    
}