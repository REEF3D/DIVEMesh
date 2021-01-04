/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2021 Hans Bihs

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

void solid::ellipsoid_semi_rot(lexer *p, dive *a, int rank, int &ts, int &te )
{
    double U,ds,dt,phi,theta;
	double xm,ym,zm,ra,rb,rc,h;
	double rmax;
	int snum,tnum;
	int vertice_mem, center1_num,center2_num;
	int vertice_start=a->vertice_num;
	double Ax,Ay,Az;
	double Bx,By,Bz;
	double Nx,Ny,Nz,norm;
	
	xm=p->S54_xm[rank];
    ym=p->S54_ym[rank];
    zm=p->S54_zm[rank];

	
    ra=p->S54_a[rank];
	rb=p->S54_b[rank];    
    rc=p->S54_c[rank];   

    h=p->S54_h[rank];   
	
	rmax = MAX3(ra,rb,rc);
	
	U = 2.0 * PI * rmax;
	
	ds = p->S19*(U*p->DXM);
	
	snum = int(U/ds);
    
    tnum= snum/4 -1;
	

// Vertices	
	ds = (2.0*PI)/double(snum);
    
    dt = ds;
	
	phi=-0.5*PI;
	theta=0.0*PI;
    
	ts=p->tricount;

    
    // middle section / hexahedrons
	for(n=tnum+1;n<snum/2;++n)
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
        
        
        
    // base 
        phi=-0.5*PI;
        for(q=0;q<snum;++q)
        {	
        //side		
        // 1st triangle
        p->tri_x[p->tricount][0] = xm + ra*cos(phi);
        p->tri_y[p->tricount][0] = ym + rb*sin(phi);
        p->tri_z[p->tricount][0] = zm - h;
        
        p->tri_x[p->tricount][1] = xm + ra*cos(phi);
        p->tri_y[p->tricount][1] = ym + rb*sin(phi);
        p->tri_z[p->tricount][1] = zm;
        
        p->tri_x[p->tricount][2] = xm + ra*cos(phi+ds);
        p->tri_y[p->tricount][2] = ym + rb*sin(phi+ds);
        p->tri_z[p->tricount][2] = zm;
        
        p->trivec_x[p->tricount] = 0.0;
        p->trivec_y[p->tricount] = 0.0;
        p->trivec_z[p->tricount] = 0.0;
        
        ++p->tricount;
        
        // 2nd triangle
        p->tri_x[p->tricount][0] = xm + ra*cos(phi);
        p->tri_y[p->tricount][0] = ym + rb*sin(phi);
        p->tri_z[p->tricount][0] = zm - h;
        
        p->tri_x[p->tricount][1] = xm + ra*cos(phi+ds);
        p->tri_y[p->tricount][1] = ym + rb*sin(phi+ds);
        p->tri_z[p->tricount][1] = zm;
        
        p->tri_x[p->tricount][2] = xm + ra*cos(phi+ds);
        p->tri_y[p->tricount][2] = ym + rb*sin(phi+ds);
        p->tri_z[p->tricount][2] = zm - h;
        
        p->trivec_x[p->tricount] = 0.0;
        p->trivec_y[p->tricount] = 0.0;
        p->trivec_z[p->tricount] = 0.0;
        
        ++p->tricount;
            
        phi+=ds;
        }
    
    // bottom plate /triangles
    
        phi=-0.5*PI;
        theta=0.5*PI-dt;
        for(q=0;q<snum;++q)
        {	
        p->tri_x[p->tricount][0] = xm;
        p->tri_y[p->tricount][0] = ym;
        p->tri_z[p->tricount][0] = zm - h;
        
        p->tri_x[p->tricount][1] = xm + ra*cos(phi);
        p->tri_y[p->tricount][1] = ym + rb*sin(phi);
        p->tri_z[p->tricount][1] = zm - h;
        
        p->tri_x[p->tricount][2] = xm + ra*cos(phi+ds);
        p->tri_y[p->tricount][2] = ym + rb*sin(phi+ds);
        p->tri_z[p->tricount][2] = zm - h;
        
        p->trivec_x[p->tricount] = 0.0;
        p->trivec_y[p->tricount] = 0.0;
        p->trivec_z[p->tricount] = 0.0;
        
        ++p->tricount;
        
        phi+=ds;
        }
    
    // end point
		
	
	te=p->tricount;
}

void solid::rotate_triangle_ellipsoid(lexer* p, dive* a, int qn, int ts, int te)
{
	for(int qr=ts;qr<te;++qr)
	{
		rotation_ellipsoid(p,qn,p->tri_x[qr][0],p->tri_y[qr][0],p->tri_z[qr][0]);
		rotation_ellipsoid(p,qn,p->tri_x[qr][1],p->tri_y[qr][1],p->tri_z[qr][1]);
		rotation_ellipsoid(p,qn,p->tri_x[qr][2],p->tri_y[qr][2],p->tri_z[qr][2]);
	}
	
}

void solid::rotation_ellipsoid(lexer *p, int qn, double &xvec,double &yvec,double &zvec)
{
	double a,b,c;
    double xm,ym,zm;
    
    double phi=p->S54_phi[qn]*(PI/180.0);
    double theta=p->S54_theta[qn]*(PI/180.0);
    double psi=p->S54_psi[qn]*(PI/180.0);
    
    xm=p->S54_xm[qn];
    ym=p->S54_ym[qn];
    zm=p->S54_zm[qn];
	
	// phi
	a = xvec-xm;
	
	b = (yvec-ym)*cos(phi) - (zvec-zm)*sin(phi); 
	
	c = (yvec-ym)*sin(phi) + (zvec-zm)*cos(phi); 
	
	xvec=a+xm;
	yvec=b+ym;
	zvec=c+zm;	
	
	// theta
	a = (xvec-xm)*cos(theta) + (zvec-zm)*sin(theta); 
	
	b = yvec-ym;
	
	c = -(xvec-xm)*sin(theta) + (zvec-zm)*cos(theta); 
	
	xvec=a+xm;
	yvec=b+ym;
	zvec=c+zm;	
	
	// psi
	a = (xvec-xm)*cos(psi) - (yvec-ym)*sin(psi); 
	
	b = (xvec-xm)*sin(psi) + (yvec-ym)*cos(psi);
	
	c = zvec-zm;
	
	xvec=a+xm;
	yvec=b+ym;
	zvec=c+zm;	
	
}
