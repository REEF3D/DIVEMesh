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
Author: Hans Bihs
--------------------------------------------------------------------*/

#include"solid.h"
#include"lexer.h"
#include"dive.h"

void solid::cone_y(lexer *p, dive *a, int rank, int &ts, int &te )
{
    double U,ds,phi;
	double xm,zm,y1,y2,r1,r2;
	double rmax;
	int snum;
	int vertice_mem, center1_num,center2_num;
	int vertice_start=a->vertice_num;
	double Ax,Ay,Az;
	double Bx,By,Bz;
	double Nx,Ny,Nz,norm;
	
	xm=p->S42_xm[rank];
    zm=p->S42_zm[rank];
	
	y1=p->S42_y1[rank];
	y2=p->S42_y2[rank];
	
    r1=p->S42_r1[rank];
	r2=p->S42_r2[rank];    
	
	rmax = MAX(r1,r2);
	
	U = 2.0 * PI * rmax;
	
	ds = p->S19*(U*p->DXM);
	
	snum = int(U/ds);
	
	//ds = U/double(snum);

// Vertices	
	ds = (2.0*PI)/double(snum);
	
	phi=0.0;
	
	ts=p->tricount;
	
	for(n=0;n<snum;++n)
	{
	//bottom circle
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = 0.0;
	p->trivec_z[p->tricount] = -1.0;
	
	p->tri_x[p->tricount][0] = xm;
	p->tri_y[p->tricount][0] = y1;
	p->tri_z[p->tricount][0] = zm;
	
	p->tri_x[p->tricount][1] = xm + r1*cos(phi);
	p->tri_y[p->tricount][1] = y1;
	p->tri_z[p->tricount][1] = zm + r1*sin(phi);
	
	p->tri_x[p->tricount][2] = xm + r1*cos(phi+ds);
	p->tri_y[p->tricount][2] = y1;
	p->tri_z[p->tricount][2] = zm + r1*sin(phi+ds);
	++p->tricount;
		
	//top circle
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = 0.0;
	p->trivec_z[p->tricount] = -1.0;
	
	p->tri_x[p->tricount][0] = xm;
	p->tri_y[p->tricount][0] = y2;
	p->tri_z[p->tricount][0] = zm;
	
	p->tri_x[p->tricount][1] = xm + r2*cos(phi);
	p->tri_y[p->tricount][1] = y2;
	p->tri_z[p->tricount][1] = zm + r2*sin(phi);
	
	p->tri_x[p->tricount][2] = xm + r2*cos(phi+ds);
	p->tri_y[p->tricount][2] = y2;
	p->tri_z[p->tricount][2] = zm + r2*sin(phi+ds);
	++p->tricount;
	
	//side		
	// 1st triangle
	p->tri_x[p->tricount][0] = xm + r1*cos(phi);
	p->tri_y[p->tricount][0] = y1;
	p->tri_z[p->tricount][0] = zm + r1*sin(phi);
	
	p->tri_x[p->tricount][1] = xm + r2*cos(phi+ds);
	p->tri_y[p->tricount][1] = y2;
	p->tri_z[p->tricount][1] = zm + r2*sin(phi+ds);
	
	p->tri_x[p->tricount][2] = xm + r1*cos(phi+ds);
	p->tri_y[p->tricount][2] = y1;
	p->tri_z[p->tricount][2] = zm + r1*sin(phi+ds);
	
	Ax = p->tri_x[p->tricount][0]-p->tri_x[p->tricount][2];
	Ay = p->tri_y[p->tricount][0]-p->tri_x[p->tricount][2];
	Az = p->tri_z[p->tricount][0]-p->tri_x[p->tricount][2];
		
	Bx = p->tri_x[p->tricount][1]-p->tri_x[p->tricount][2];
	By = p->tri_y[p->tricount][1]-p->tri_x[p->tricount][2];
	Bz = p->tri_z[p->tricount][1]-p->tri_x[p->tricount][2];
		
	Nx = Ay*Bz - Az*By;
	Ny = Az*Bx - Ax*Bz;
	Nz = Ax*By - Ay*Bx;
	
	norm = sqrt(Nx*Nx + Ny*Ny + Nz*Nz);
	
	p->trivec_x[p->tricount] = Nx/norm;
	p->trivec_y[p->tricount] = Ny/norm;
	p->trivec_z[p->tricount] = Nz/norm;
	
	++p->tricount;
	
	// 2nd triangle
	p->tri_x[p->tricount][0] = xm + r1*cos(phi);
	p->tri_y[p->tricount][0] = y1;
	p->tri_z[p->tricount][0] = zm + r1*sin(phi);
	
	p->tri_x[p->tricount][1] = xm + r2*cos(phi+ds);
	p->tri_y[p->tricount][1] = y2;
	p->tri_z[p->tricount][1] = zm + r2*sin(phi+ds);
	
	p->tri_x[p->tricount][2] = xm + r2*cos(phi);
	p->tri_y[p->tricount][2] = y2;
	p->tri_z[p->tricount][2] = zm + r2*sin(phi);
		
	p->trivec_x[p->tricount] = Nx/norm;
	p->trivec_y[p->tricount] = Ny/norm;
	p->trivec_z[p->tricount] = Nz/norm;
	
	
	++p->tricount;
		
	phi+=ds;
	}
		
	
	te=p->tricount;
}
