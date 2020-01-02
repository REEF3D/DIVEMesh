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

#include"objects.h"
#include"dive.h"
#include"lexer.h"
#include"box.h"
#include"cylinder_y.h"
#include"cylinder_z.h"
#include"conical.h"
#include"wedge_x.h"
#include"wedge_y.h"
#include"cce3D.h"

objects::objects(lexer *p, dive *a)
{
    cout<<"objects_ini"<<endl;

    pcce = new cce3D(p,a);

    pent = new entity*[p->obj_count];

    count=0;
	
	delta=count;
    for(n=0;n<p->O10;++n)
    {
    pent[n+delta] = new box(p,n,1);
    ++count;
    }

    delta=count;
    for(n=0;n<p->O32;++n)
    {
    pent[n+delta] = new cylinder_y(p,n,0);
    ++count;
    }

    delta=count;
    for(n=0;n<p->O33;++n)
    {
    pent[n+delta] = new cylinder_z(p,n,0);
    ++count;
    }
	
	delta=count;
    for(n=0;n<p->O43;++n)
    {
    pent[n+delta] = new conical(p,n,0);
    ++count;
    }

    delta=count;
    for(n=0;n<p->O61;++n)
    {
    pent[n+delta] = new wedge_x(p,n,0);
    ++count;
    }
	
	delta=count;
    for(n=0;n<p->O62;++n)
    {
    pent[n+delta] = new wedge_y(p,n,0);
    ++count;
    }
}

objects::~objects()
{
}

void objects::start(lexer* p, dive* a)
{
    cout<<"objects  "<<p->obj_count<<endl;

    for(n=0;n<p->obj_count;++n)
    pcce->start(p,a,pent[n]);

    LOOP
    for(n=0;n<p->obj_count;++n)
    {
    ival=pent[n]->flag_val(i,j,k);

    if(ival<0)
    a->flag(i,j,k)=-21;
    }

}




