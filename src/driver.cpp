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

#include"driver.h"
#include"driver_headers.h"
#include<sys/stat.h>

driver::driver()
{
	cout<<endl<<endl;
	cout<<"DIVEMesh (c) 2008-2024 Hans Bihs"<<endl<<endl;

	cout<<":: Open-Source Meshing"<<endl<<endl;
    cout<<endl<<"v_241006" <<endl<<endl;

    mkdir("./DIVEMesh_Log",0777);

	p = new lexer();
	a = new dive(p);
	logic(p);
}

driver::~driver()
{
}

void driver::mainloop()
{
    cout<<"mainloop"<<endl;

    pini->start(p,a);

// BASELAYER

// baselayer new
    pbase->start(p,a);

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

	if(p->D10>0)
    pdata->start(p,a);

// Topo
	if(p->topo_count>0)
	ptopo->start(p,a);

    if(p->topo_count>0)
	{
	print_stl print_topo(p,a);

	print_topo.topo_vtp(p,a);
	if(p->S6==1)
	print_topo.topo_stl(p,a);
	}

// Solid
    if(p->S1==1)
	p->read_stl();

	if(p->solid_count>0||p->S1==1)
	psolid->start(p,a);

	if(p->solid_count>0||p->S1==1)
	{
	print_stl print_solid(p,a);

	print_solid.solid_vtp(p,a);
	if(p->S6==1)
	print_solid.solid_stl(p,a);
	}

// Slice
    pslice->start(p,a);

// Bedlevel
    pbed->start(p,a);

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

    pvtu->start(p,a);
    pprint->start(p,a);

    analytics(p,a);
}
