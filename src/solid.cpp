/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2024 Hans Bihs

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

solid::solid(lexer *p, dive *a) : geometry(p,a)
{
	cout<<"solid ini";


	cout<<"."<<endl;

	if(p->S9==1)
	p->S9_1=1;

	if(p->S9==2)
	p->S9_1=-1;

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
	a->solid_dist(i,j,k)=1.0e9;
	}

    if(p->S2==1)
	LOOP
	a->flag(i,j,k)=1;

    ts_stl=tri_start;
    te_stl=tri_end;
    p->tricount=p->trinum_stl;

	if(p->S1==1)
    for(rayiter=0; rayiter<2; ++rayiter)
    {
    tri_start=ts_stl;
    tri_end=te_stl;
    

    stl_preproc(p,a,tri_start,tri_end);
	ray_cast(p,a,tri_start,tri_end,a->solid,a->solid_dist,a->solidbed);

    if(rayiter==0)
    stl_postproc(p,a,tri_start,tri_end,a->solid,a->solid_dist,p->S9_1);
    }

    ts_stl=tri_start;
    te_stl=tri_end;
    tricount_stl=p->tricount;
    
    for(rayiter=0; rayiter<2; ++rayiter)
    {
    tri_start=ts_stl;
    tri_end=te_stl;
    p->tricount=tricount_stl;

        for(qn=0;qn<p->S10;++qn)
        {
        box(p,a,qn,tri_start,tri_end,p->S10_xs[qn],p->S10_xe[qn],p->S10_ys[qn],p->S10_ye[qn],p->S10_zs[qn],p->S10_ze[qn]);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->solid,a->solid_dist,a->solidbed);
        }

        for(qn=0;qn<p->S11;++qn)
        {
        box_array(p,a,a->solid,a->solid_dist,a->solidbed,qn,tri_start,tri_end,p->S11_xs[qn],p->S11_ys[qn],p->S11_zs[qn],
                p->S11_L[qn],p->S11_G[qn],p->S11_ni[qn],p->S11_nj[qn],p->S11_nk[qn]);
        }
        
        for(qn=0;qn<p->S12;++qn)
        {
        beam(p,a,qn,tri_start,tri_end,p->S12_xs[qn],
                p->S12_ys[qn],p->S12_zs[qn],p->S12_xe[qn],p->S12_ye[qn],p->S12_ze[qn],p->S12_b[qn],p->S12_h[qn]);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->solid,a->solid_dist,a->solidbed);
        }

        for(qn=0;qn<p->S32;++qn)
        {
        cylinder_y(p,a,qn,tri_start,tri_end,p->S32_xm[qn],p->S32_zm[qn],p->ymin,p->ymax,p->S32_r[qn],p->S32_r[qn]);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->solid,a->solid_dist,a->solidbed);
        }

        for(qn=0;qn<p->S33;++qn)
        {
        cylinder_z(p,a,qn,tri_start,tri_end,p->S33_xm[qn],p->S33_ym[qn],p->zmin,p->zmax,p->S33_r[qn],p->S33_r[qn]);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->solid,a->solid_dist,a->solidbed);
        }

        for(qn=0;qn<p->S37;++qn)
        {
        jacket_member_norm(p,a,qn,tri_start,tri_end,p->S37_xm1[qn],
                p->S37_ym1[qn],p->S37_zm1[qn],p->S37_r1[qn],p->S37_xm2[qn],p->S37_ym2[qn],p->S37_zm2[qn],p->S37_r2[qn]);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->solid,a->solid_dist,a->solidbed);
        }

        for(qn=0;qn<p->S41;++qn)
        {
        cone_x(p,a,qn,tri_start,tri_end,p->S41_ym[qn],p->S41_zm[qn],p->S41_x1[qn],p->S41_x2[qn],p->S41_r1[qn],p->S41_r2[qn]);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->solid,a->solid_dist,a->solidbed);
        }

        for(qn=0;qn<p->S42;++qn)
        {
        cone_y(p,a,qn,tri_start,tri_end,p->S42_xm[qn],p->S42_zm[qn],p->S42_y1[qn],p->S42_y2[qn],p->S42_r1[qn],p->S42_r2[qn]);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->solid,a->solid_dist,a->solidbed);
        }

        for(qn=0;qn<p->S43;++qn)
        {
        cone_z(p,a,qn,tri_start,tri_end,p->S43_xm[qn],p->S43_ym[qn],p->S43_z1[qn],p->S43_z2[qn],p->S43_r1[qn],p->S43_r2[qn]);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->solid,a->solid_dist,a->solidbed);
        }
 
        for(qn=0;qn<p->S51;++qn)
        {
        sphere(p,a,qn,tri_start,tri_end,p->S51_xm[qn],p->S51_ym[qn],p->S51_zm[qn],p->S51_r[qn]);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->solid,a->solid_dist,a->solidbed);
        }

        for(qn=0;qn<p->S52;++qn)
        {
        ellipsoid(p,a,qn,tri_start,tri_end,p->S52_xm[qn],p->S52_ym[qn],p->S52_zm[qn],p->S52_a[qn],p->S52_b[qn],p->S52_c[qn]);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->solid,a->solid_dist,a->solidbed);
        }

        for(qn=0;qn<p->S53;++qn)
        {
        ellipsoid_semi(p,a,qn,tri_start,tri_end,p->S53_xm[qn],p->S53_ym[qn],p->S53_zm[qn],p->S53_a[qn],p->S53_b[qn],p->S53_c[qn],p->S53_h[qn]);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->solid,a->solid_dist,a->solidbed);
        }

        for(qn=0;qn<p->S54;++qn)
        {
        ellipsoid_semi_rot(p,a,qn,tri_start,tri_end,p->S54_xm[qn],p->S54_ym[qn],p->S54_zm[qn],p->S54_a[qn],p->S54_b[qn],p->S54_c[qn],p->S54_h[qn]);
        rotate_triangle_ellipsoid(p,a,qn,tri_start,tri_end,p->S54_xm[qn],p->S54_ym[qn],p->S54_zm[qn]);
        ray_cast(p,a,tri_start,tri_end,a->solid,a->solid_dist,a->solidbed);
        }

        for(qn=0;qn<p->S61;++qn)
        {
        wedge_x(p,a,qn,tri_start,tri_end,p->S61_xs[qn],p->S61_xe[qn],p->S61_ys[qn],p->S61_ye[qn],p->S61_zs[qn],p->S61_ze[qn]);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->solid,a->solid_dist,a->solidbed);
        }

        for(qn=0;qn<p->S62;++qn)
        {
        wedge_y(p,a,qn,tri_start,tri_end,p->S62_xs[qn],p->S62_xe[qn],p->S62_ys[qn],p->S62_ye[qn],p->S62_zs[qn],p->S62_ze[qn]);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->solid,a->solid_dist,a->solidbed);
        }

        for(qn=0;qn<p->S63;++qn)
        {
        wedge_z(p,a,qn,tri_start,tri_end,p->S63_xs[qn],p->S63_xe[qn],p->S63_ys[qn],p->S63_ye[qn],p->S63_zs[qn],p->S63_ze[qn]);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->solid,a->solid_dist,a->solidbed);
        }

        for(qn=0;qn<p->S81;++qn)
        {
        tetrahedon(p,a,qn,tri_start,tri_end,p->S81_xyz);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->solid,a->solid_dist,a->solidbed);
        }

        for(qn=0;qn<p->S82;++qn)
        {
        pyramid(p,a,qn,tri_start,tri_end,p->S82_xyz);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->solid,a->solid_dist,a->solidbed);
        }

        for(qn=0;qn<p->S83;++qn)
        {
        wedge(p,a,qn,tri_start,tri_end,p->S83_xyz);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->solid,a->solid_dist,a->solidbed);
        }

        for(qn=0;qn<p->S84;++qn)
        {
        hexahedron(p,a,qn,tri_start,tri_end,p->S84_xyz);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->solid,a->solid_dist,a->solidbed);
        }

        for(qn=0;qn<p->S121;++qn)
        {
        ogee_weir(p,a,qn,tri_start,tri_end,p->S121_x[qn],p->S121_y[qn],p->S121_z[qn],p->S121_Pd[qn],p->S121_b[qn],
                p->S121_H0[qn],p->S122_K[qn],p->S122_n[qn],p->S122_xc[qn],p->S122_yc[qn],p->S123_R1[qn],p->S123_R2[qn]);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->solid,a->solid_dist,a->solidbed);
        }

        for(qn=0;qn<p->S131;++qn)
        {
        semicyl_y(p,a,qn,tri_start,tri_end,p->S131_xm[qn],p->S131_zm[qn],p->S131_y1[qn],p->S131_y2[qn],p->S131_r1[qn],p->S131_r2[qn]);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->solid,a->solid_dist,a->solidbed);
        }
        
        for(qn=0;qn<p->S141;++qn)
        {
        arch(p,a,qn,tri_start,tri_end,p->S141_xs[qn],p->S141_xe[qn],p->S141_ys[qn],p->S141_ye[qn],p->S141_zs[qn],p->S141_ze[qn],p->S141_r[qn]);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->solid,a->solid_dist,a->solidbed);
        }

        for(qn=0;qn<p->S201;++qn)
        {
        plate_x(p,a,qn,tri_start,tri_end,p->S201_x[qn],p->S201_ys[qn],p->S201_ye[qn],p->S201_zs[qn],p->S201_ze[qn]);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast_x_gcb(p,a,tri_start,tri_end,a->solid,a->solid_dist);
        }

        if(p->S300>0)
        {
        fluvial_box(p,a,qn,tri_start,tri_end);
        rotate_triangle(p,a,tri_start,tri_end);

            if(p->S301==1)
            {
            int temp=p->S18;
            p->S18=2;
            ray_cast(p,a,tri_start,tri_end,a->solid,a->solid_dist,a->solidbed);
            p->S18_1=temp;
            }

            if(p->S301==2)
            {
            ray_cast(p,a,tri_start,tri_end,a->solid,a->solid_dist,a->solidbed);
            }
        }
    }
    
    // finalize solid_dist
    LOOP
    {
        if(a->solid(i,j,k)==-1)
        a->solid_dist(i,j,k)=-fabs(a->solid_dist(i,j,k));


        if(a->solid(i,j,k)==1)
        a->solid_dist(i,j,k)=fabs(a->solid_dist(i,j,k));
    }


    LOOP
	{
		if(a->solid_dist(i,j,k)>10.0*p->DXM)
		a->solid_dist(i,j,k)=10.0*p->DXM;

		if(a->solid_dist(i,j,k)<-10.0*p->DXM)
		a->solid_dist(i,j,k)=-10.0*p->DXM;
	}

    LOOP
    if(a->solid_dist(i,j,k)!=a->solid_dist(i,j,k))
    cout<<"SOLID NAN: "<<a->solid_dist(i,j,k)<<endl;


	cout<<"solid_trinum: "<<p->trinum<<"  solid_tricount: "<<p->tricount<<endl;

}


