/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2023 Hans Bihs

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

#include"porous.h"
#include"dive.h"
#include"lexer.h"


porous::porous(lexer *p, dive *a) : geometry(p,a), porous_dist(p), porousbed(p)
{
	cout<<"porous structures ini";

	cout<<"."<<endl;

	if(p->V9==1)
	p->V9_1=1;

	if(p->V9==2)
	p->V9_1=-1;


	xrot=p->V5_x;
	yrot=p->V5_y;
	zrot=p->V5_z;
    
	phi=(PI/180.0)*p->V5_phi;
	theta=(PI/180.0)*p->V5_theta;
	psi=(PI/180.0)*p->V5_psi;
}

porous::~porous()
{
}

void porous::start(lexer* p, dive* a)
{
    if(p->V15==1)
    {
	xrot=p->G14_x;
	yrot=p->G14_y;
	zrot=0.0;
	phi=0.0;
	theta=0.0;
	psi=p->G13_phi;

    cout<<"POROUS psi: "<<psi<<endl;
    }

    cout<<"porous "<<endl;

	LOOP
	a->porous(i,j,k)=0;

    ts_stl=tri_start;
    te_stl=tri_end;
    p->tricount=p->trinum_stl;

    // STL
	if(p->V1==1)
    for(rayiter=0; rayiter<2; ++rayiter)
    {
    tri_start=ts_stl;
    tri_end=te_stl;
    

    stl_preproc(p,a,tri_start,tri_end);
	ray_cast(p,a,tri_start,tri_end,a->porous,porous_dist,porousbed);

    if(rayiter==0)
    stl_postproc(p,a,tri_start,tri_end,a->porous,porous_dist,p->V9_1);
    }

    ts_stl=tri_start;
    te_stl=tri_end;
    tricount_stl=p->tricount;
    
    // porous objects
    for(rayiter=0; rayiter<2; ++rayiter)
    {
    tri_start=ts_stl;
    tri_end=te_stl;
    p->tricount=tricount_stl;

        for(qn=0;qn<p->V10;++qn)
        {
        box(p,a,qn,tri_start,tri_end,p->V10_xs[qn],p->V10_xe[qn],p->V10_ys[qn],p->V10_ye[qn],p->V10_zs[qn],p->V10_ze[qn]);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->porous,porous_dist,porousbed);
        }

        for(qn=0;qn<p->V11;++qn)
        {
        box_array(p,a,a->porous,porous_dist,porousbed,qn,tri_start,tri_end,p->V11_xs[qn],p->V11_ys[qn],p->V11_zs[qn],
                p->V11_L[qn],p->V11_G[qn],p->V11_ni[qn],p->V11_nj[qn],p->V11_nk[qn]);
        }

        for(qn=0;qn<p->V32;++qn)
        {
        cylinder_y(p,a,qn,tri_start,tri_end,p->V32_xm[qn],p->V32_zm[qn],p->ymin,p->ymax,p->V32_r[qn],p->V32_r[qn]);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->porous,porous_dist,porousbed);
        }

        for(qn=0;qn<p->V33;++qn)
        {
        cylinder_z(p,a,qn,tri_start,tri_end,p->V33_xm[qn],p->V33_ym[qn],p->zmin,p->zmax,p->V33_r[qn],p->V33_r[qn]);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->porous,porous_dist,porousbed);
        }

        for(qn=0;qn<p->V37;++qn)
        {
        jacket_member_norm(p,a,qn,tri_start,tri_end,p->V37_xm1[qn],
                p->V37_ym1[qn],p->V37_ym1[qn],p->V37_r1[qn],p->V37_xm2[qn],p->V37_ym2[qn],p->V37_ym2[qn],p->V37_r1[qn]);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->porous,porous_dist,porousbed);
        }

        for(qn=0;qn<p->V41;++qn)
        {
        cone_x(p,a,qn,tri_start,tri_end,p->V41_ym[qn],p->V41_zm[qn],p->V41_x1[qn],p->V41_x2[qn],p->V41_r1[qn],p->V41_r2[qn]);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->porous,porous_dist,porousbed);
        }

        for(qn=0;qn<p->V42;++qn)
        {
        cone_y(p,a,qn,tri_start,tri_end,p->V42_xm[qn],p->V42_zm[qn],p->V42_y1[qn],p->V42_y2[qn],p->V42_r1[qn],p->V42_r2[qn]);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->porous,porous_dist,porousbed);
        }

        for(qn=0;qn<p->V43;++qn)
        {
        cone_z(p,a,qn,tri_start,tri_end,p->V43_xm[qn],p->V43_ym[qn],p->V43_z1[qn],p->V43_z2[qn],p->V43_r1[qn],p->V43_r2[qn]);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->porous,porous_dist,porousbed);
        }
 
        for(qn=0;qn<p->V51;++qn)
        {
        sphere(p,a,qn,tri_start,tri_end,p->V51_xm[qn],p->V51_ym[qn],p->V51_zm[qn],p->V51_r[qn]);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->porous,porous_dist,porousbed);
        }

        for(qn=0;qn<p->V61;++qn)
        {
        wedge_x(p,a,qn,tri_start,tri_end,p->V61_xs[qn],p->V61_xe[qn],p->V61_ys[qn],p->V61_ye[qn],p->V61_zs[qn],p->V61_ze[qn]);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->porous,porous_dist,porousbed);
        }

        for(qn=0;qn<p->V62;++qn)
        {
        wedge_y(p,a,qn,tri_start,tri_end,p->V62_xs[qn],p->V62_xe[qn],p->V62_ys[qn],p->V62_ye[qn],p->V62_zs[qn],p->V62_ze[qn]);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->porous,porous_dist,porousbed);
        }

        for(qn=0;qn<p->V63;++qn)
        {
        wedge_z(p,a,qn,tri_start,tri_end,p->V63_xs[qn],p->V63_xe[qn],p->V63_ys[qn],p->V63_ye[qn],p->V63_zs[qn],p->V63_ze[qn]);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->porous,porous_dist,porousbed);
        }

        for(qn=0;qn<p->V81;++qn)
        {
        tetrahedon(p,a,qn,tri_start,tri_end,p->V81_xyz);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->porous,porous_dist,porousbed);
        }

        for(qn=0;qn<p->V82;++qn)
        {
        pyramid(p,a,qn,tri_start,tri_end,p->V82_xyz);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->porous,porous_dist,porousbed);
        }

        for(qn=0;qn<p->V83;++qn)
        {
        wedge(p,a,qn,tri_start,tri_end,p->V83_xyz);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->porous,porous_dist,porousbed);
        }

        for(qn=0;qn<p->V84;++qn)
        {
        hexahedron(p,a,qn,tri_start,tri_end,p->V84_xyz);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->porous,porous_dist,porousbed);
        }

        for(qn=0;qn<p->V131;++qn)
        {
        semicyl_y(p,a,qn,tri_start,tri_end,p->V131_xm[qn],p->V131_zm[qn],p->V131_y1[qn],p->V131_y2[qn],p->V131_r1[qn],p->V131_r2[qn]);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->porous,porous_dist,porousbed);
        }

    }
    

    // finalize porous_dist
    LOOP
    {
        if(a->porous(i,j,k)==-1)
        porous_dist(i,j,k)=-fabs(porous_dist(i,j,k));


        if(a->porous(i,j,k)==1)
        porous_dist(i,j,k)=fabs(porous_dist(i,j,k));
    }


    LOOP
	{
		if(porous_dist(i,j,k)>10.0*p->DXM)
		porous_dist(i,j,k)=10.0*p->DXM;

		if(porous_dist(i,j,k)<-10.0*p->DXM)
		porous_dist(i,j,k)=-10.0*p->DXM;
	}

    LOOP
    if(porous_dist(i,j,k)!=porous_dist(i,j,k))
    cout<<"POROUS NAN: "<<porous_dist(i,j,k)<<endl;


	cout<<"porous_trinum: "<<p->trinum<<"  porous_tricount: "<<p->tricount<<endl;

}


