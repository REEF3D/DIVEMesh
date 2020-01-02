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

#include"solid.h"
#include"lexer.h"
#include"dive.h"

void solid::ellipsoid(lexer *p, dive *a, int rank, int &ts, int &te )
{
    double U,ds,dt,phi,theta;
	double xm,ym,zm,ra,rb,rc;
	double rmax;
	int snum;
	int vertice_mem, center1_num,center2_num;
	int vertice_start=a->vertice_num;
	double Ax,Ay,Az;
	double Bx,By,Bz;
	double Nx,Ny,Nz,norm;
	
	xm=p->S52_xm[rank];
    ym=p->S52_ym[rank];
    zm=p->S52_zm[rank];

	
    ra=p->S52_a[rank];
	rb=p->S52_b[rank];    
    rc=p->S52_c[rank];    
	
	rmax = MAX3(ra,rb,rc);
	
	U = 2.0 * PI * rmax;
	
	ds = p->S19*(U*p->DXM);
	
	snum = int(U/ds);
	

// Vertices	
	ds = (2.0*PI)/double(snum);
    
    dt = ds;
	
	phi=-0.5*PI;
	theta=-0.5*PI;
    
	ts=p->tricount;
	
        // bottom start /triangles
        for(q=0;q<snum;++q)
        {	
        p->tri_x[p->tricount][0] = xm;
        p->tri_y[p->tricount][0] = ym;
        p->tri_z[p->tricount][0] = zm-rc;
        
        p->tri_x[p->tricount][1] = xm + ra*cos(theta+dt)*cos(phi);
        p->tri_y[p->tricount][1] = ym + rb*cos(theta+dt)*sin(phi);
        p->tri_z[p->tricount][1] = zm + rc*sin(theta+dt);
        
        p->tri_x[p->tricount][2] = xm + ra*cos(theta+dt)*cos(phi+ds);
        p->tri_y[p->tricount][2] = ym + rb*cos(theta+dt)*sin(phi+ds);
        p->tri_z[p->tricount][2] = zm + rc*sin(theta+dt);
        
        p->trivec_x[p->tricount] = 0.0;
        p->trivec_y[p->tricount] = 0.0;
        p->trivec_z[p->tricount] = 0.0;
        
        ++p->tricount;
        
        phi+=ds;
        }
    
    theta+=dt;
    
    // middle section / hexahedrons
	for(n=1;n<snum/2-1;++n)
    {   
        phi=-0.5*PI;
        for(q=0;q<snum;++q)
        {	
        //side		
        // 1st triangle
        p->tri_x[p->tricount][0] = xm + ra*cos(theta)*cos(phi);
        p->tri_y[p->tricount][0] = ym + rb*cos(theta)*sin(phi);
        p->tri_z[p->tricount][0] = zm + rc*sin(theta);
        
        p->tri_x[p->tricount][1] = xm + ra*cos(theta+dt)*cos(phi);
        p->tri_y[p->tricount][1] = ym + rb*cos(theta+dt)*sin(phi);
        p->tri_z[p->tricount][1] = zm + rc*sin(theta+dt);
        
        p->tri_x[p->tricount][2] = xm + ra*cos(theta+dt)*cos(phi+ds);
        p->tri_y[p->tricount][2] = ym + rb*cos(theta+dt)*sin(phi+ds);
        p->tri_z[p->tricount][2] = zm + rc*sin(theta+dt);
        
        p->trivec_x[p->tricount] = 0.0;
        p->trivec_y[p->tricount] = 0.0;
        p->trivec_z[p->tricount] = 0.0;
        
        ++p->tricount;
        
        // 2nd triangle
        p->tri_x[p->tricount][0] = xm + ra*cos(theta)*cos(phi);
        p->tri_y[p->tricount][0] = ym + rb*cos(theta)*sin(phi);
        p->tri_z[p->tricount][0] = zm + rc*sin(theta);
        
        p->tri_x[p->tricount][1] = xm + ra*cos(theta+dt)*cos(phi+ds);
        p->tri_y[p->tricount][1] = ym + rb*cos(theta+dt)*sin(phi+ds);
        p->tri_z[p->tricount][1] = zm + rc*sin(theta+dt);
        
        p->tri_x[p->tricount][2] = xm + ra*cos(theta)*cos(phi+ds);
        p->tri_y[p->tricount][2] = ym + rb*cos(theta)*sin(phi+ds);
        p->tri_z[p->tricount][2] = zm + rc*sin(theta);
        
        p->trivec_x[p->tricount] = 0.0;
        p->trivec_y[p->tricount] = 0.0;
        p->trivec_z[p->tricount] = 0.0;
        
        ++p->tricount;
            
        phi+=ds;
        }
    theta+=dt;
	}
    
    // top start /triangles
    
        phi=-0.5*PI;
        theta=0.5*PI-dt;
        for(q=0;q<snum;++q)
        {	
        p->tri_x[p->tricount][0] = xm;
        p->tri_y[p->tricount][0] = ym;
        p->tri_z[p->tricount][0] = zm+rc;
        
        p->tri_x[p->tricount][1] = xm + ra*cos(theta)*cos(phi);
        p->tri_y[p->tricount][1] = ym + rb*cos(theta)*sin(phi);
        p->tri_z[p->tricount][1] = zm + rc*sin(theta);
        
        p->tri_x[p->tricount][2] = xm + ra*cos(theta)*cos(phi+ds);
        p->tri_y[p->tricount][2] = ym + rb*cos(theta)*sin(phi+ds);
        p->tri_z[p->tricount][2] = zm + rc*sin(theta);
        
        p->trivec_x[p->tricount] = 0.0;
        p->trivec_y[p->tricount] = 0.0;
        p->trivec_z[p->tricount] = 0.0;
        
        ++p->tricount;
        
        phi+=ds;
        }
    
    // end point
		
	
	te=p->tricount;
}
