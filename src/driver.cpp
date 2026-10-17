/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2026 Hans Bihs

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

#include"driver.h"
#include"driver_headers.h"
#include<sys/stat.h>

driver::driver()
{
    cout<<endl<<endl;
    cout<<"DIVEMesh (c) 2008-2026 Hans Bihs"<<endl<<endl;

    cout<<":: Open-Source Meshing"<<endl<<endl;
    cout<<endl<<"v_260115" <<endl<<endl;

    mkdir("./DIVEMesh_Log",0777);


    p = new lexer();

    p->read_input();
    p->read_preproc();

    // multi-block grid (R 20 1): block 0 with its ring is the grid of the run
    multiblock *mb = nullptr;
    if(p->R20==1)
    {
        mb = new multiblock;
        if(!mb->start(p))
        exit(1);
        mb_box(p,*mb);
    }

    a = new dive(p);

    if(mb!=nullptr)
    {
        geo_export &g = a->gex;
        g.curv.ni = mb->box_ni();
        g.curv.nj = mb->box_nj();
        g.curv.par = {0.0,0.0,0.0,0.0,mb->spacing()};
        g.curv.x = mb->X0;
        g.curv.y = mb->Y0;
        g.curv.zb = mb->Z0;
        g.blk_ring = mb->W;
        g.blks.resize(mb->b.size());
        for(size_t q=0; q<mb->b.size(); ++q)
        {
            const multiblock::block &B = mb->b[q];
            geo_export::mblock &G = g.blks[q];
            G.ni = B.ni; G.nj = B.nj;
            for(int f=0; f<4; ++f)
            G.ring[f] = B.ring[f];
            for(const multiblock::seg &S : B.segs)
            {
                const int v[geo_export::SEGI] = {S.face,S.lo,S.hi,S.nbr,S.nface,S.perm[0],S.perm[1],S.sign[0],S.sign[1],S.off[0],S.off[1]};
                G.seg.insert(G.seg.end(),v,v+geo_export::SEGI);
            }
            if(q>0)
            {
                G.x = B.x; G.y = B.y; G.zb = B.zb;
            }
        }
        delete mb;
    }

    logic(p);
}

driver::~driver()
{
}

void driver::mainloop()
{
    cout<<"mainloop"<<endl;

    pini->start(p,a);

// Geometry Pipeline
    //Solid
        // geodat
        // STL
        // solids
    //Topo
        // geodat
        // STL
        // solids

// Geodata
    if(p->G10>0 && p->G9==1)
    pgeo->start(p,a,a->topobed,a->topo_dist);

    if(p->G10>0 && p->G9==2)
    pgeo->start(p,a,a->solidbed,a->solid_dist);

    // geodat bed level for REEF3D, before the S/T entities raise topobed/solidbed
    if(p->G10>0)
    XYLOOP
    a->geobed(i,j) = (p->G9==2) ? a->solidbed(i,j) : a->topobed(i,j);

    if(p->D10>0)
    pdata->start(p,a);

// Topo
    if(p->topo_count>0)
    ptopo->start(p,a);

    if(p->topo_count>0)
    {
        print_3D print_topo(p,a);

        print_topo.topo_vtp(p,a);
        if(p->S6==1)
        print_topo.topo_stl(p,a);
    }

// Solid
    if(p->S1==1)
    p->read_stl();

    if(p->solid_count>0 || p->S1==1)
    psolid->start(p,a);

    if(p->solid_count>0 || p->S1==1)
    {
        print_3D print_solid(p,a);

        print_solid.solid_vtp(p,a);
        if(p->S6==1)
        print_solid.solid_stl(p,a);

        if(p->S90==1)
        {
            print_stl_geodat print_geo(p,a);
            print_geo.print_geo(p,a);
        }
    }

// Slice
    pslice->start(p,a);

// Bedlevel
    pbed->start(p,a);

// River corridor grid (R 1 1): extra output, the Cartesian grid is unchanged
// R 1 2: the logical box of the corridor grid becomes the grid of the run (second pass)
    if(p->R1>=1 && p->curv_box==0)
    {
        corridor pcorr(p,a);
        pcorr.start(p,a);

        if(p->R1==2)
        {
            curv_box(p,pcorr);
            return;
        }
    }

// Decomp
    pdd->start(p,a);

    pbc->makebc(p,a);
    psurf->start(p,a);

// GCB Estimate
    if(p->topo_count>0 || (p->G10>0&&p->G9==1))
    ptopo->gcb_estimate(p,a);

    if(p->solid_count>0 || p->S1==1 || (p->G10>0&&p->G9==2))
    psolid->gcb_estimate(p,a);

    psurf->gcb_estimate(p,a);

// Hydrodynamic Coupling
    if(p->H10>0)
    phdc->start(p,a);

    pvts->start(p,a);
    pprint->start(p,a);

    analytics(p,a);
}

// R 20 1: the box of block 0 with its ring (cells of the mean spacing, the vertical of the
// Cartesian grid), walls all around; no geodat, solids or topography (bed levels: the nodes)
void driver::mb_box(lexer *p, multiblock &mb)
{
    const double hm = mb.spacing();

    p->curv_box = 1;

    p->B2 = 1;
    p->B2_knox = mb.box_ni();
    p->B2_knoy = mb.box_nj();
    p->B2_knoz = p->knoz;
    p->B101 = p->B102 = 0;
    p->xmin = 0.0;
    p->xmax = hm*double(mb.box_ni());
    p->ymin = 0.0;
    p->ymax = hm*double(mb.box_nj());
    p->global_orig_x = p->xmin + p->B3_dx;
    p->global_orig_y = p->ymin + p->B3_dy;

    // faces of block 0 with an interface: the outer edge of the ring is a wall; the other faces keep
    // their boundary types (C 11 -i, C 14 +i, C 13 -j, C 12 +j: in- and outflow of the run)
    const int ctype[4] = {p->C11,p->C14,p->C13,p->C12};
    int c[4];
    for(int f=0; f<4; ++f)
    c[f] = (mb.b[0].ring[f]>0) ? 21 : ctype[f];
    p->C11 = c[0];
    p->C14 = c[1];
    p->C13 = c[2];
    p->C12 = c[3];

    p->G10 = 0;
    p->D10 = 0;
    p->S1 = 0;
    p->solidprint = p->topoprint = 0;

    p->createspace();
    p->gridspacing();
}

// R 1 2: second pass on the logical box of the corridor grid (ni x nj cells of the mean spacing,
// the vertical of the Cartesian grid), inflow at i = 0, outflow at i = ni, banks at j = 0, nj;
// no geodat, solids or topography (the bed levels are the CURV node bed levels in REEF3D G 50 1)
void driver::curv_box(lexer *p, corridor &c)
{
    geo_export::curvgrid curv = a->gex.curv;

    const double hm = c.mean_spacing();

    cout<<endl<<"corridor grid (R 1 2): second pass, logical box "<<c.cells_i()<<" x "<<c.cells_j()<<" x "<<p->knoz
        <<", spacing "<<hm<<" m"<<endl<<endl;

    p->curv_box = 1;

    p->B2 = 1;
    p->B2_knox = c.cells_i();
    p->B2_knoy = c.cells_j();
    p->B2_knoz = p->knoz;
    p->B101 = p->B102 = 0;
    p->xmin = 0.0;
    p->xmax = hm*double(c.cells_i());
    p->ymin = 0.0;
    p->ymax = hm*double(c.cells_j());
    p->global_orig_x = p->xmin + p->B3_dx;
    p->global_orig_y = p->ymin + p->B3_dy;

    p->C11 = c.code_in;
    p->C14 = c.code_out;
    p->C12 = p->C13 = 21;

    p->G10 = 0;
    p->D10 = 0;
    p->S1 = 0;
    p->solidprint = p->topoprint = 0;

    p->createspace();
    p->gridspacing();

    a = new dive(p);
    a->gex.curv = curv;

    logic(p);
}
