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

#include"boundary_geometry.h"
#include"lexer.h"
#include"dive.h"

boundary_geometry::boundary_geometry()
{
}

boundary_geometry::~boundary_geometry()
{
}

void boundary_geometry::start(lexer* p, dive* a)
{
	a->vertice_num=0;
	a->polygon_num=0;
	a->polygon_sum=0;
	
	for(qn=0;qn<p->O10;++qn)
	box(p,a,qn);
	
	for(qn=0;qn<p->O43;++qn)
	conical(p,a,qn);
	
	for(qn=0;qn<p->O33;++qn)
	cylinder_z(p,a,qn);
	
	a->polygon_offset[0]=0;
	
	for(n=1;n<a->polygon_num;++n)
	{
	a->polygon_offset[n] = a->polygon_offset[n-1] + a->numvert[n];
	}
	
	for(n=0;n<a->polygon_num;++n)
	a->polygon_sum+=a->numvert[n];
}

void boundary_geometry::box(lexer* p, dive* a,int rank)
{	
	
	double U,ds,phi;
	double xs,ys,zs,xe,ye,ze;
	double rmax;
	int snum;
	int vertice_mem,center1_num,center2_num;
	int vertice_start=a->vertice_num;
	

	xs = p->O10_xs[rank];
    xe = p->O10_xe[rank];

    ys = p->O10_ys[rank];
    ye = p->O10_ye[rank];

    zs = p->O10_zs[rank];
    ze = p->O10_ze[rank];    
	


// Vertices	
	a->vertice[a->vertice_num][0] = xs;
	a->vertice[a->vertice_num][1] = ys;
	a->vertice[a->vertice_num][2] = zs;
	++a->vertice_num;
	
	a->vertice[a->vertice_num][0] = xe;
	a->vertice[a->vertice_num][1] = ys;
	a->vertice[a->vertice_num][2] = zs;
	++a->vertice_num;
	
	a->vertice[a->vertice_num][0] = xe;
	a->vertice[a->vertice_num][1] = ye;
	a->vertice[a->vertice_num][2] = zs;
	++a->vertice_num;
	
	a->vertice[a->vertice_num][0] = xs;
	a->vertice[a->vertice_num][1] = ye;
	a->vertice[a->vertice_num][2] = zs;
	++a->vertice_num;
	
	a->vertice[a->vertice_num][0] = xs;
	a->vertice[a->vertice_num][1] = ys;
	a->vertice[a->vertice_num][2] = ze;
	++a->vertice_num;
	
	a->vertice[a->vertice_num][0] = xe;
	a->vertice[a->vertice_num][1] = ys;
	a->vertice[a->vertice_num][2] = ze;
	++a->vertice_num;
	
	a->vertice[a->vertice_num][0] = xe;
	a->vertice[a->vertice_num][1] = ye;
	a->vertice[a->vertice_num][2] = ze;
	++a->vertice_num;
	
	a->vertice[a->vertice_num][0] = xs;
	a->vertice[a->vertice_num][1] = ye;
	a->vertice[a->vertice_num][2] = ze;
	++a->vertice_num;
	
	
		
// Polygon

	a->polygon[a->polygon_num][0] = 0 + vertice_start;
	a->polygon[a->polygon_num][1] = 1 + vertice_start;
	a->polygon[a->polygon_num][2] = 2 + vertice_start;
	a->polygon[a->polygon_num][3] = 3 + vertice_start;
	a->numvert[a->polygon_num] = 4;
	++a->polygon_num;
	
	a->polygon[a->polygon_num][0] = 0 + vertice_start;
	a->polygon[a->polygon_num][1] = 1 + vertice_start;
	a->polygon[a->polygon_num][2] = 5 + vertice_start;
	a->polygon[a->polygon_num][3] = 4 + vertice_start;
	a->numvert[a->polygon_num] = 4;
	++a->polygon_num;
	
	a->polygon[a->polygon_num][0] = 1 + vertice_start;
	a->polygon[a->polygon_num][1] = 2 + vertice_start;
	a->polygon[a->polygon_num][2] = 6 + vertice_start;
	a->polygon[a->polygon_num][3] = 5 + vertice_start;
	a->numvert[a->polygon_num] = 4;
	++a->polygon_num;
	
	a->polygon[a->polygon_num][0] = 2 + vertice_start;
	a->polygon[a->polygon_num][1] = 3 + vertice_start;
	a->polygon[a->polygon_num][2] = 7 + vertice_start;
	a->polygon[a->polygon_num][3] = 6 + vertice_start;
	a->numvert[a->polygon_num] = 4;
	++a->polygon_num;
	
	a->polygon[a->polygon_num][0] = 3 + vertice_start;
	a->polygon[a->polygon_num][1] = 0 + vertice_start;
	a->polygon[a->polygon_num][2] = 4 + vertice_start;
	a->polygon[a->polygon_num][3] = 7 + vertice_start;
	a->numvert[a->polygon_num] = 4;
	++a->polygon_num;
	
	a->polygon[a->polygon_num][0] = 4 + vertice_start;
	a->polygon[a->polygon_num][1] = 5 + vertice_start;
	a->polygon[a->polygon_num][2] = 6 + vertice_start;
	a->polygon[a->polygon_num][3] = 7 + vertice_start;
	a->numvert[a->polygon_num] = 4;
	++a->polygon_num;
					
}


void boundary_geometry::cylinder_z(lexer* p, dive* a,int rank)
{	
	
	double U,ds,phi;
	double xm,ym,z1,z2,r1,r2;
	double rmax;
	int snum;
	int vertice_mem,center1_num,center2_num;
	int vertice_start=a->vertice_num;
	
	xm=p->O33_xm[rank];
    ym=p->O33_ym[rank];
	
	z1=-p->zmin;
	z2=p->zmax-p->zmin;
	
    r1=p->O33_r[rank];
	r2=p->O33_r[rank];    
	
	rmax = MAX(r1,r2);
	
	U = 2.0 * PI * rmax;
	
	ds = 0.1*(U*p->dx);
	
	snum = int(U/ds);
	
	//ds = U/double(snum);

// Vertices	
	ds = (2.0*PI)/double(snum);
	
	++snum;
	phi=0.0;
	
	cout<<"snum: "<<snum<<" U: "<<U<<endl;
	
	//bottom circle
	for(n=0;n<snum;++n)
	{
	a->vertice[a->vertice_num][0] = xm + r1*cos(phi);
	a->vertice[a->vertice_num][1] = ym + r1*sin(phi);
	a->vertice[a->vertice_num][2] = z1;
	phi+=ds;
	++a->vertice_num;
	}
	
	vertice_mem = a->vertice_num;
	//top circle
	phi=0.0;
	for(n=0;n<snum;++n)
	{
	a->vertice[a->vertice_num][0] = xm + r2*cos(phi);
	a->vertice[a->vertice_num][1] = ym + r2*sin(phi);
	a->vertice[a->vertice_num][2] = z2;
	phi+=ds;
	++a->vertice_num;
	}
	
	// bottom center
	a->vertice[a->vertice_num][0] = xm;
	a->vertice[a->vertice_num][1] = ym;
	a->vertice[a->vertice_num][2] = z1;
	center1_num = a->vertice_num;
	++a->vertice_num;
	
	// top center
	a->vertice[a->vertice_num][0] = xm;
	a->vertice[a->vertice_num][1] = ym;
	a->vertice[a->vertice_num][2] = z2;
	center2_num = a->vertice_num;
	++a->vertice_num;
	
		
// Polygon
	//SIDE
	for(n=0;n<snum;++n)
	{
	a->polygon[a->polygon_num][0] = n + vertice_start;
	a->polygon[a->polygon_num][1] = n+1 + vertice_start;
	a->polygon[a->polygon_num][2] = n + 1 + vertice_mem;
	a->polygon[a->polygon_num][3] = n + vertice_mem;
	a->numvert[a->polygon_num] = 4;
	++a->polygon_num;
	}
	
	//BOTTOM
	for(n=0;n<snum;++n)
	{
	a->polygon[a->polygon_num][0] = n + vertice_start;
	a->polygon[a->polygon_num][1] = n + 1 + vertice_start;
	a->polygon[a->polygon_num][2] = center1_num;
	a->numvert[a->polygon_num] = 3;
	++a->polygon_num;
	}
	
	//BOTTOM
	for(n=0;n<snum;++n)
	{
	a->polygon[a->polygon_num][0] = n + vertice_mem;
	a->polygon[a->polygon_num][1] = n + 1 + vertice_mem;
	a->polygon[a->polygon_num][2] = center2_num;
	a->numvert[a->polygon_num] = 3;
	++a->polygon_num;
	}					
}

void boundary_geometry::conical(lexer* p, dive* a, int rank)
{	
	double U,ds,phi;
	double xm,ym,z1,z2,r1,r2;
	double rmax;
	int snum;
	int vertice_mem, center1_num,center2_num;
	int vertice_start=a->vertice_num;
	
	xm=p->O43_xm[rank];
    ym=p->O43_ym[rank];
	
	z1=p->O43_z1[rank];
	z2=p->O43_z2[rank];
	
    r1=p->O43_r1[rank];
	r2=p->O43_r2[rank];    
	
	rmax = MAX(r1,r2);
	
	U = 2.0 * PI * rmax;
	
	ds = 0.1*(U*p->dx);
	
	snum = int(U/ds);
	
	//ds = U/double(snum);

// Vertices	
	ds = (2.0*PI)/double(snum);
	
	++snum;
	phi=0.0;
	
	cout<<"snum: "<<snum<<" U: "<<U<<endl;
	
	//bottom circle
	for(n=0;n<snum;++n)
	{
	a->vertice[a->vertice_num][0] = xm + r1*cos(phi);
	a->vertice[a->vertice_num][1] = ym + r1*sin(phi);
	a->vertice[a->vertice_num][2] = z1;
	phi+=ds;
	++a->vertice_num;
	}
	
	vertice_mem = a->vertice_num;
	//top circle
	phi=0.0;
	for(n=0;n<snum;++n)
	{
	a->vertice[a->vertice_num][0] = xm + r2*cos(phi);
	a->vertice[a->vertice_num][1] = ym + r2*sin(phi);
	a->vertice[a->vertice_num][2] = z2;
	phi+=ds;
	++a->vertice_num;
	}
	
	// bottom center
	a->vertice[a->vertice_num][0] = xm;
	a->vertice[a->vertice_num][1] = ym;
	a->vertice[a->vertice_num][2] = z1;
	center1_num = a->vertice_num;
	++a->vertice_num;
	
	// top center
	a->vertice[a->vertice_num][0] = xm;
	a->vertice[a->vertice_num][1] = ym;
	a->vertice[a->vertice_num][2] = z2;
	center2_num = a->vertice_num;
	++a->vertice_num;
	
		
// Polygon
	//SIDE
	for(n=0;n<snum;++n)
	{
	a->polygon[a->polygon_num][0] = n + vertice_start;
	a->polygon[a->polygon_num][1] = n+1 + vertice_start;
	a->polygon[a->polygon_num][2] = n + 1 + vertice_mem;
	a->polygon[a->polygon_num][3] = n + vertice_mem;
	a->numvert[a->polygon_num] = 4;
	++a->polygon_num;
	}
	
	//BOTTOM
	for(n=0;n<snum;++n)
	{
	a->polygon[a->polygon_num][0] = n + vertice_start;
	a->polygon[a->polygon_num][1] = n + 1 + vertice_start;
	a->polygon[a->polygon_num][2] = center1_num;
	a->numvert[a->polygon_num] = 3;
	++a->polygon_num;
	}
	
	//BOTTOM
	for(n=0;n<snum;++n)
	{
	a->polygon[a->polygon_num][0] = n + vertice_mem;
	a->polygon[a->polygon_num][1] = n + 1 + vertice_mem;
	a->polygon[a->polygon_num][2] = center2_num;
	a->numvert[a->polygon_num] = 3;
	++a->polygon_num;
	}					
}


