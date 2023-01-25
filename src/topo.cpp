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

#include"topo.h"
#include"dive.h"
#include"lexer.h"

topo::topo(lexer *p, dive *a) : geometry(p,a)
{
	cout<<"topo ini";

	a->vnum=0;

	cout<<"."<<endl;

	if(p->T9==1)
	p->T9_1=1;

	if(p->T9==2)
	p->T9_1=-1;

	if(p->T121>0)
	{
		if(p->T122<p->T121)
		for(qn=0;qn<p->T121;++qn)
		{
		p->T122_K[qn] = 0.5;
		p->T122_n[qn] = 1.85;
		p->T122_xc[qn] = 0.22;
		p->T122_yc[qn] = 0.075;
		}

		if(p->T123<p->T121)
		for(qn=0;qn<p->T121;++qn)
		{
		p->T123_R1[qn] = 0.45;
		p->T123_R2[qn] = 0.2;
		}
	}

    if(p->T201>0)
    {
    maxpt = MAX(a->knox,MAX(a->knoy,a->knoz));
    p->Darray(is_R,maxpt,maxpt,maxpt);
    p->Iarray(is_num,maxpt,maxpt);

    a->surfnum_solid = maxpt*maxpt;

    p->Iarray(a->surf_solid,a->surfnum_solid,5);
    }

	xrot=p->T5_x;
	yrot=p->T5_y;
	zrot=p->T5_z;
    
	phi=(PI/180.0)*p->T5_phi;
	theta=(PI/180.0)*p->T5_theta;
	psi=(PI/180.0)*p->T5_psi;
}

topo::~topo()
{
}

void topo::start(lexer* p, dive* a)
{
    if(p->T15==1)
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
	a->topo_dist(i,j,k)=1.0e9;
	}

    if(p->T2==1)
	LOOP
	a->flag(i,j,k)=1;

    ts_stl=tri_start;
    te_stl=tri_end;
    tricount_stl=p->tricount;

	if(p->T1==1)
    for(rayiter=0; rayiter<2; ++rayiter)
    {
    tri_start=ts_stl;
    tri_end=te_stl;
    p->tricount=tricount_stl;

    stl_preproc(p,a,tri_start,tri_end);
	ray_cast(p,a,tri_start,tri_end,a->topo,a->topo_dist,a->topobed);

    if(rayiter==0)
    stl_postproc(p,a,tri_start,tri_end,a->topo,a->topo_dist,p->T9_1);
    }

    ts_stl=tri_start;
    te_stl=tri_end;
    tricount_stl=p->tricount;

    for(rayiter=0; rayiter<2; ++rayiter)
    {
    tri_start=ts_stl;
    tri_end=te_stl;
    p->tricount=tricount_stl;

        for(qn=0;qn<p->T10;++qn)
        {
        box(p,a,qn,tri_start,tri_end,p->T10_xs[qn],p->T10_xe[qn],p->T10_ys[qn],p->T10_ye[qn],p->T10_zs[qn],p->T10_ze[qn]);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->topo,a->topo_dist,a->topobed);
        }

        for(qn=0;qn<p->T11;++qn)
        {
        box_array(p,a,a->topo,a->topo_dist,a->topobed,qn,tri_start,tri_end,p->T11_xs[qn],p->T11_ys[qn],p->T11_zs[qn],
                p->T11_L[qn],p->T11_G[qn],p->T11_ni[qn],p->T11_nj[qn],p->T11_nk[qn]);
        }

        for(qn=0;qn<p->T32;++qn)
        {
        cylinder_y(p,a,qn,tri_start,tri_end,p->T32_xm[qn],p->T32_zm[qn],p->ymin,p->ymax,p->T32_r[qn],p->T32_r[qn]);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->topo,a->topo_dist,a->topobed);
        }

        for(qn=0;qn<p->T33;++qn)
        {
        cylinder_z(p,a,qn,tri_start,tri_end,p->T33_xm[qn],p->T33_ym[qn],p->zmin,p->zmax,p->T33_r[qn],p->T33_r[qn]);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->topo,a->topo_dist,a->topobed);
        }

        for(qn=0;qn<p->T37;++qn)
        {
        jacket_member_norm(p,a,qn,tri_start,tri_end,p->T37_xm1[qn],
                p->T37_ym1[qn],p->T37_ym1[qn],p->T37_r1[qn],p->T37_xm2[qn],p->T37_ym2[qn],p->T37_ym2[qn],p->T37_r1[qn]);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->topo,a->topo_dist,a->topobed);
        }

        for(qn=0;qn<p->T41;++qn)
        {
        cone_x(p,a,qn,tri_start,tri_end,p->T41_ym[qn],p->T41_zm[qn],p->T41_x1[qn],p->T41_x2[qn],p->T41_r1[qn],p->T41_r2[qn]);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->topo,a->topo_dist,a->topobed);
        }

        for(qn=0;qn<p->T42;++qn)
        {
        cone_y(p,a,qn,tri_start,tri_end,p->T42_xm[qn],p->T42_zm[qn],p->T42_y1[qn],p->T42_y2[qn],p->T42_r1[qn],p->T42_r2[qn]);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->topo,a->topo_dist,a->topobed);
        }

        for(qn=0;qn<p->T43;++qn)
        {
        cone_z(p,a,qn,tri_start,tri_end,p->T43_xm[qn],p->T43_ym[qn],p->T43_z1[qn],p->T43_z2[qn],p->T43_r1[qn],p->T43_r2[qn]);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->topo,a->topo_dist,a->topobed);
        }
 
        for(qn=0;qn<p->T51;++qn)
        {
        sphere(p,a,qn,tri_start,tri_end,p->T51_xm[qn],p->T51_ym[qn],p->T51_zm[qn],p->T51_r[qn]);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->topo,a->topo_dist,a->topobed);
        }

        for(qn=0;qn<p->T52;++qn)
        {
        ellipsoid(p,a,qn,tri_start,tri_end,p->T52_xm[qn],p->T52_ym[qn],p->T52_zm[qn],p->T52_a[qn],p->T52_b[qn],p->T52_c[qn]);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->topo,a->topo_dist,a->topobed);
        }

        for(qn=0;qn<p->T53;++qn)
        {
        ellipsoid_semi(p,a,qn,tri_start,tri_end,p->T53_xm[qn],p->T53_ym[qn],p->T53_zm[qn],p->T53_a[qn],p->T53_b[qn],p->T53_c[qn],p->T53_h[qn]);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->topo,a->topo_dist,a->topobed);
        }

        for(qn=0;qn<p->T54;++qn)
        {
        ellipsoid_semi_rot(p,a,qn,tri_start,tri_end,p->T54_xm[qn],p->T54_ym[qn],p->T54_zm[qn],p->T54_a[qn],p->T54_b[qn],p->T54_c[qn],p->T54_h[qn]);
        rotate_triangle_ellipsoid(p,a,qn,tri_start,tri_end,p->T54_xm[qn],p->T54_ym[qn],p->T54_zm[qn]);
        ray_cast(p,a,tri_start,tri_end,a->topo,a->topo_dist,a->topobed);
        }

        for(qn=0;qn<p->T61;++qn)
        {
        wedge_x(p,a,qn,tri_start,tri_end,p->T61_xs[qn],p->T61_xe[qn],p->T61_ys[qn],p->T61_ye[qn],p->T61_zs[qn],p->T61_ze[qn]);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->topo,a->topo_dist,a->topobed);
        }

        for(qn=0;qn<p->T62;++qn)
        {
        wedge_y(p,a,qn,tri_start,tri_end,p->T62_xs[qn],p->T62_xe[qn],p->T62_ys[qn],p->T62_ye[qn],p->T62_zs[qn],p->T62_ze[qn]);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->topo,a->topo_dist,a->topobed);
        }

        for(qn=0;qn<p->T63;++qn)
        {
        wedge_z(p,a,qn,tri_start,tri_end,p->T63_xs[qn],p->T63_xe[qn],p->T63_ys[qn],p->T63_ye[qn],p->T63_zs[qn],p->T63_ze[qn]);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->topo,a->topo_dist,a->topobed);
        }

        for(qn=0;qn<p->T81;++qn)
        {
        tetrahedon(p,a,qn,tri_start,tri_end,p->T81_xyz);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->topo,a->topo_dist,a->topobed);
        }

        for(qn=0;qn<p->T82;++qn)
        {
        pyramid(p,a,qn,tri_start,tri_end,p->T82_xyz);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->topo,a->topo_dist,a->topobed);
        }

        for(qn=0;qn<p->T83;++qn)
        {
        wedge(p,a,qn,tri_start,tri_end,p->T83_xyz);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->topo,a->topo_dist,a->topobed);
        }

        for(qn=0;qn<p->T84;++qn)
        {
        hexahedron(p,a,qn,tri_start,tri_end,p->T84_xyz);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->topo,a->topo_dist,a->topobed);
        }

        for(qn=0;qn<p->T121;++qn)
        {
        ogee_weir(p,a,qn,tri_start,tri_end,p->T121_x[qn],p->T121_y[qn],p->T121_z[qn],p->T121_Pd[qn],p->T121_b[qn],
                p->T121_H0[qn],p->T122_K[qn],p->T122_n[qn],p->T122_xc[qn],p->T122_yc[qn],p->T123_R1[qn],p->T123_R2[qn]);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->topo,a->topo_dist,a->topobed);
        }

        for(qn=0;qn<p->T131;++qn)
        {
        semicyl_y(p,a,qn,tri_start,tri_end,p->T131_xm[qn],p->T131_zm[qn],p->T131_y1[qn],p->T131_y2[qn],p->T131_r1[qn],p->T131_r2[qn]);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->topo,a->topo_dist,a->topobed);
        }
        
        for(qn=0;qn<p->T141;++qn)
        {
        arch(p,a,qn,tri_start,tri_end,p->T141_xs[qn],p->T141_xe[qn],p->T141_ys[qn],p->T141_ye[qn],p->T141_zs[qn],p->T141_ze[qn],p->T141_r[qn]);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast(p,a,tri_start,tri_end,a->topo,a->topo_dist,a->topobed);
        }

        for(qn=0;qn<p->T201;++qn)
        {
        plate_x(p,a,qn,tri_start,tri_end,p->T201_x[qn],p->T201_ys[qn],p->T201_ye[qn],p->T201_zs[qn],p->T201_ze[qn]);
        rotate_triangle(p,a,tri_start,tri_end);
        ray_cast_x_gcb(p,a,tri_start,tri_end,a->topo,a->topo_dist);
        }
        
        /*
        if(p->T300>0)
        {
        fluvial_box(p,a,qn,tri_start,tri_end);
        rotate_triangle(p,a,tri_start,tri_end);

            if(p->T301==1)
            {
            int temp=p->T18;
            p->T18=2;
            ray_cast(p,a,tri_start,tri_end,a->topo,a->topo_dist,a->topobed);
            p->T18_1=temp;
            }

            if(p->T301==2)
            {
            ray_cast(p,a,tri_start,tri_end,a->topo,a->topo_dist,a->topobed);
            }
        }*/
    }

    // finalize solid_dist
    LOOP
    {
        if(a->topo(i,j,k)==-1)
        a->topo_dist(i,j,k)=-fabs(a->topo_dist(i,j,k));


        if(a->topo(i,j,k)==1)
        a->topo_dist(i,j,k)=fabs(a->topo_dist(i,j,k));
    }


    LOOP
	{
		if(a->topo_dist(i,j,k)>10.0*p->DXM)
		a->topo_dist(i,j,k)=10.0*p->DXM;

		if(a->topo_dist(i,j,k)<-10.0*p->DXM)
		a->topo_dist(i,j,k)=-10.0*p->DXM;
	}

    LOOP
    if(a->topo_dist(i,j,k)!=a->topo_dist(i,j,k))
    cout<<"TOPO NAN: "<<a->topo_dist(i,j,k)<<endl;



	cout<<"solid_trinum: "<<p->trinum<<"  solid_tricount: "<<p->tricount<<endl;
}
