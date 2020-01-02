/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2020 Hans Bihs

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

void driver::logic(lexer* p)
{
	
	p->bl_count = p->B10 + p->B22 + p->B31 + p->B32 + p->B33;	
	p->fc_count = p->F11 + p->F21;
	p->obj_count = p->O10 + p->O32 + p->O33 + p->O43 + p->O61 + p->O62;
	p->solid_count = p->S10 + p->S11 + p->S32 + p->S33 + p->S34 + p->S35 + p->S36 + p->S37 + p->S38  + p->S39
            + p->S41 + p->S42 + p->S43
            + p->S51 + p->S52 + p->S53 + p->S54 + p->S61 
            + p->S62 + p->S81 + p->S82 + p->S83 + p->S84 + p->S63 + p->S121 + p->S131 + p->S141
            + p->S201 + p->S202 + p->S203 + p->S300;

    pini=new initialize;

    pbc=new bc();
    psurf= new surface();
    pdd=new decomp();
    pprint=new print_binary(p);

    if(p->fc_count>0)
    pfree = new freecoor(p,a);
    
    if(p->obj_count>0)
	{
    pobj = new objects(p,a);
	objgeo = new objects_geometry();
	objprint = new print_objects(p,a);
	}

    if(p->bl_count>0)
    pbase = new baselayer(p,a);

    if(p->G10>0)
    pgeo = new geodat(p,a);
    
    pbed = new bedlevel(p,a);
    
    if(p->H10>0)
    pwcp = new wcp(p,a);
	
	if(p->D10>0)
    pdata = new data(p,a);
    
    pslice = new slice(p,a);
	
	if(p->solid_count>0||p->S1==1)
	{
	psolid = new solid(p,a);
	p->solidprint=1;
	}

    cout<<"."<<endl;
	
	
    mainloop();

}
