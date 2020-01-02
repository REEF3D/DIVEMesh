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

#include"baselayer.h"
#include"dive.h"
#include"lexer.h"
#include"box_bl.h"
#include"sphere_bl.h"
#include"pipe_x_bl.h"
#include"pipe_y_bl.h"
#include"pipe_z_bl.h"
#include"cce3D.h"

baselayer::baselayer(lexer *p, dive *a)
{
    cout<<"baselayer_ini "<<endl;



    int delta;

    pcce = new cce3D(p,a);

    pent = new entity*[p->bl_count];


    count=0;

	delta=count;
	for(n=0;n<p->B10;++n)
    {
    pent[n+delta] = new box_bl(p,n,1);
    ++count;
    }

	delta=count;
    for(n=0;n<p->B22;++n)
    {
    pent[n+delta] = new sphere_bl(p,n,1);
    ++count;
    }

    delta=count;
    for(n=0;n<p->B31;++n)
    {
    pent[n+delta] = new pipe_x_bl(p,n,1);
    ++count;
    }

    delta=count;
    for(n=0;n<p->B32;++n)
    {
    pent[n+delta] = new pipe_y_bl(p,n,1);
    ++count;
    }

    delta=count;
    for(n=0;n<p->B33;++n)
    {
    pent[n+delta] = new pipe_z_bl(p,n,1);
    ++count;
    }
}

baselayer::~baselayer()
{
}

void baselayer::start(lexer* p, dive* a)
{
    cout<<"baselayer"<<endl;

    MALOOP
    a->flag(i,j,k)=1;

    for(n=0;n<p->bl_count;++n)
    pcce->start(p,a,pent[n]);

    MALOOP
    a->flag(i,j,k)=-21;

    LOOP
    for(n=0;n<p->bl_count;++n)
    {
    ival=pent[n]->flag_val(i,j,k);
    if(ival<0)
    a->flag(i,j,k)=-21;

    if(ival>0)
    a->flag(i,j,k)=1;
    }
}
