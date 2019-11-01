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

#include"driver.h"
#include"driver_headers.h"

driver::driver()
{
	cout<<endl<<endl;
	cout<<"DIVEMesh (c) 2008-2019 Hans Bihs"<<endl<<endl;

	cout<<":: Open-Source Meshing"<<endl<<endl;
    cout<<endl<<"v_191101" <<endl<<endl;       

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
    if(p->bl_count>0)
    pbase->start(p,a);

// Freecoor
    if(p->fc_count>0)
    pfree->start(p,a);

// Objects
    if(p->obj_count>0)
	{
    pobj->start(p,a);
	objgeo->start(p,a);
	objprint->start(p,a);
	}

// Solid
	if(p->solid_count>0||p->S1==1)
	psolid->start(p,a);


	if(p->solid_count>0||p->S1==1)
	{
	print_stl printer_stl(p,a);

	printer_stl.start(p,a);
	if(p->S6==1)
	printer_stl.start_stl(p,a);
	}

// Geodata
    if(p->G10>0)
    pgeo->start(p,a);

	if(p->D10>0)
    pdata->start(p,a);


// Slice
    pslice->start(p,a);

// Bedlevel
    //pbed->start(p,a);

// Post-Proc
    pbc->makebc(p,a);
    psurf->start(p,a);

// Decomp
    pdd->start(p,a);

	if(p->solid_count>0||p->S1==1)
	psolid->gcb_estimate(p,a);

    if(p->G10>0)
	pgeo->gcb_estimate(p,a);
    
// Hydrodynamic Coupling
    if(p->H10==4)
    pwcp->start(p,a);


    pprint->start(p,a);

    analytics(p,a);
}
