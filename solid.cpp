/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2019 Hans Bihs

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
#include"dive.h"
#include"lexer.h"

solid::solid(lexer *p, dive *a) : cutl(p),cutr(p),epsi(1.6)
{
	cout<<"solid ini";
	

	a->vnum=0;
	
	cout<<"."<<endl;
	
	if(p->S9==1)
	p->S9_1=1.0;
	
	if(p->S9==2)
	p->S9_1=-1.0;
	
	if(p->S121>0)
	{
		if(p->S122<p->S121)
		for(qn=0;qn<p->S121;++qn)
		{
		p->S122_K[qn] = 0.5;
		p->S122_n[qn] = 1.85;
		p->S122_xc[qn] = 0.22;
		p->S122_yc[qn] = 0.075;
		}
		
		if(p->S123<p->S121)
		for(qn=0;qn<p->S121;++qn)
		{
		p->S123_R1[qn] = 0.45;
		p->S123_R2[qn] = 0.2;
		}
	}
    
    if(p->S201>0)
    {
    maxpt = MAX(a->knox,MAX(a->knoy,a->knoz));
    p->Darray(is_R,maxpt,maxpt,maxpt);
    p->Iarray(is_num,maxpt,maxpt);
    
    a->surfnum_solid = maxpt*maxpt;
    
    p->Iarray(a->surf_solid,a->surfnum_solid,5);
    }
    
	
	xrot=p->S5_x;
	yrot=p->S5_y;
	zrot=p->S5_z;
	phi=(PI/180.0)*p->S5_phi;
	theta=(PI/180.0)*p->S5_theta;
	psi=(PI/180.0)*p->S5_psi;
    

    
}

solid::~solid()
{
}

void solid::start(lexer* p, dive* a)
{
    if(p->S15==1)
    { 
	xrot=p->G14_x;
	yrot=p->G14_y;
	zrot=0.0;
	phi=0.0;
	theta=0.0;
	psi=p->G13_phi;
    
    cout<<"SOLID psi: "<<psi<<endl;
    } 
    
    cout<<"solid "<<endl;
    
    MALOOP
	{
	cutl(i,j,k)=0;
	cutr(i,j,k)=0;
	a->solid_dist(i,j,k)=1.0e9;
	}
    
    if(p->S2==1)
	LOOP
	a->flag(i,j,k)=1;
	
	if(p->S1==1)
    {
    stl_preproc(p,a,tri_start,tri_end);
	ray_cast(p,a,tri_start,tri_end);
    stl_postproc(p,a,tri_start,tri_end);
    }
	
	for(qn=0;qn<p->S10;++qn)
	{
	box(p,a,qn,tri_start,tri_end);
	rotate_triangle(p,a,tri_start,tri_end);
	ray_cast(p,a,tri_start,tri_end);
	}
	
	for(qn=0;qn<p->S11;++qn)
	{
	box_array(p,a,qn,tri_start,tri_end);
	}
	
	for(qn=0;qn<p->S32;++qn)
	{
	cylinder_y(p,a,qn,tri_start,tri_end);
	rotate_triangle(p,a,tri_start,tri_end);
	ray_cast(p,a,tri_start,tri_end);
	}
    
    for(qn=0;qn<p->S33;++qn)
	{
	cylinder_z(p,a,qn,tri_start,tri_end);
	rotate_triangle(p,a,tri_start,tri_end);
	ray_cast(p,a,tri_start,tri_end);
	}
    
    for(qn=0;qn<p->S34;++qn)
	{
	jacket_member_x(p,a,qn,tri_start,tri_end);
	rotate_triangle(p,a,tri_start,tri_end);
	ray_cast(p,a,tri_start,tri_end);
	}
    
    for(qn=0;qn<p->S35;++qn)
	{
	jacket_member_y(p,a,qn,tri_start,tri_end);
	rotate_triangle(p,a,tri_start,tri_end);
	ray_cast(p,a,tri_start,tri_end);
	}
    
    for(qn=0;qn<p->S36;++qn)
	{
	jacket_member_z(p,a,qn,tri_start,tri_end);
	rotate_triangle(p,a,tri_start,tri_end);
	ray_cast(p,a,tri_start,tri_end);
	}
    
    for(qn=0;qn<p->S37;++qn)
	{
	jacket_member_norm(p,a,qn,tri_start,tri_end);
	rotate_triangle(p,a,tri_start,tri_end);
	ray_cast(p,a,tri_start,tri_end);
	}
    
    for(qn=0;qn<p->S38;++qn)
	{
	jacket_member_vert(p,a,qn,tri_start,tri_end);
	rotate_triangle(p,a,tri_start,tri_end);
	ray_cast(p,a,tri_start,tri_end);
	}
	
	for(qn=0;qn<p->S41;++qn)
	{
	cone_x(p,a,qn,tri_start,tri_end);
	rotate_triangle(p,a,tri_start,tri_end);
	ray_cast(p,a,tri_start,tri_end);
	}
	
	for(qn=0;qn<p->S42;++qn)
	{
	cone_y(p,a,qn,tri_start,tri_end);
	rotate_triangle(p,a,tri_start,tri_end);
	ray_cast(p,a,tri_start,tri_end);
	}
	
	for(qn=0;qn<p->S43;++qn)
	{
	cone_z(p,a,qn,tri_start,tri_end);
	rotate_triangle(p,a,tri_start,tri_end);
	ray_cast(p,a,tri_start,tri_end);
	}
    
    for(qn=0;qn<p->S51;++qn)
	{
	sphere(p,a,qn,tri_start,tri_end);
	rotate_triangle(p,a,tri_start,tri_end);
	ray_cast(p,a,tri_start,tri_end);
	}
    
    for(qn=0;qn<p->S52;++qn)
	{
	ellipsoid(p,a,qn,tri_start,tri_end);
	rotate_triangle(p,a,tri_start,tri_end);
	ray_cast(p,a,tri_start,tri_end);
	}
    
    for(qn=0;qn<p->S53;++qn)
	{
	ellipsoid_semi(p,a,qn,tri_start,tri_end);
	rotate_triangle(p,a,tri_start,tri_end);
	ray_cast(p,a,tri_start,tri_end);
	}
    
    for(qn=0;qn<p->S54;++qn)
	{
	ellipsoid_semi_rot(p,a,qn,tri_start,tri_end);
	rotate_triangle_ellipsoid(p,a,qn,tri_start,tri_end);
	ray_cast(p,a,tri_start,tri_end);
	}
	
	for(qn=0;qn<p->S61;++qn)
	{
	wedge_x(p,a,qn,tri_start,tri_end);
	rotate_triangle(p,a,tri_start,tri_end);
	ray_cast(p,a,tri_start,tri_end);
	}
	
	for(qn=0;qn<p->S62;++qn)
	{
	wedge_y(p,a,qn,tri_start,tri_end);
	rotate_triangle(p,a,tri_start,tri_end);
	ray_cast(p,a,tri_start,tri_end);
	}
	
	for(qn=0;qn<p->S63;++qn)
	{
	wedge_z(p,a,qn,tri_start,tri_end);
	rotate_triangle(p,a,tri_start,tri_end);
	ray_cast(p,a,tri_start,tri_end);
	}
    
    for(qn=0;qn<p->S81;++qn)
	{
	tetrahedon(p,a,qn,tri_start,tri_end);
    rotate_triangle(p,a,tri_start,tri_end);
	ray_cast(p,a,tri_start,tri_end);
	}
	
	for(qn=0;qn<p->S82;++qn)
	{
	pyramid(p,a,qn,tri_start,tri_end);
    rotate_triangle(p,a,tri_start,tri_end);
	ray_cast(p,a,tri_start,tri_end);
	}
	
	for(qn=0;qn<p->S83;++qn)
	{
	wedge(p,a,qn,tri_start,tri_end);
    rotate_triangle(p,a,tri_start,tri_end);
	ray_cast(p,a,tri_start,tri_end);
	}
	
	for(qn=0;qn<p->S84;++qn)
	{
	hexahedron(p,a,qn,tri_start,tri_end);
    rotate_triangle(p,a,tri_start,tri_end);
	ray_cast(p,a,tri_start,tri_end);
	}
	
	for(qn=0;qn<p->S121;++qn)
	{
	ogee_weir(p,a,qn,tri_start,tri_end);
	rotate_triangle(p,a,tri_start,tri_end);
	ray_cast(p,a,tri_start,tri_end);
	}
	
	for(qn=0;qn<p->S131;++qn)
	{
	semicyl_y(p,a,qn,tri_start,tri_end);
	rotate_triangle(p,a,tri_start,tri_end);
	ray_cast(p,a,tri_start,tri_end);
	}
	
	for(qn=0;qn<p->S141;++qn)
	{
	arch(p,a,qn,tri_start,tri_end);
	rotate_triangle(p,a,tri_start,tri_end);
	ray_cast(p,a,tri_start,tri_end);
	}
    
    for(qn=0;qn<p->S201;++qn)
	{
	plate_x(p,a,qn,tri_start,tri_end);
    rotate_triangle(p,a,tri_start,tri_end);
	ray_cast_x_gcb(p,a,tri_start,tri_end);
	}
	
    if(p->S300>0)
	{
	fluvial_box(p,a,qn,tri_start,tri_end);
    rotate_triangle(p,a,tri_start,tri_end);
	ray_cast_x_gcb(p,a,tri_start,tri_end);
	}
    
    // finalize solid_dist
    LOOP
	{
		if(a->solid_dist(i,j,k)>10.0*p->DXM)
		a->solid_dist(i,j,k)=10.0*p->DXM;
		
		if(a->solid_dist(i,j,k)<-10.0*p->DXM)
		a->solid_dist(i,j,k)=-10.0*p->DXM;
	}
	

	cout<<"solid_trinum: "<<p->trinum<<"  solid_tricount: "<<p->tricount<<endl;

}


void solid::gcb_estimate(lexer *p, dive *a)
{
    n=0;
    
    LOOP
    {
		if(a->solid(i,j,k)==1)
		if(a->solid(i-1,j,k)==-1 || a->solid(i+1,j,k)==-1 || a->solid(i,j-1,k)==-1 || a->solid(i,j+1,k)==-1 || a->solid(i,j,k-1)==-1 || a->solid(i,j,k+1)==-1)
		++n;
    }
    
    //cout<<"solid_gcb_est: "<<n<<endl;
        
        
	int qn;
	
	for(qn=0; qn<p->M10;qn++)
	a->solid_gcb[qn]=0;
	
	n=0;
	NLOOP
	{
		SUBLOOP
		{
		if(a->solid(i,j,k)==1)
		if(a->solid(i-1,j,k)==-1 || a->solid(i+1,j,k)==-1 || a->solid(i,j-1,k)==-1 || a->solid(i,j+1,k)==-1 || a->solid(i,j,k-1)==-1 || a->solid(i,j,k+1)==-1)
		++a->solid_gcb[n];
		}
	++n;
	}
    /*
    n=0;
    NLOOP
    {
	cout<<n<<" solid_gcb_est: "<<a->solid_gcb[n]<<endl;
    ++n;
    }*/
}


