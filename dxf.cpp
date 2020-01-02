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

#include<iostream>
#include<fstream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

#include"dxf.h"
#include"lexer.h"
#include"dive.h"
#include"line.h"
#include"spline.h"
#include"cce.h"
#include"flag_indicate.h"
#include"surfdir_indicate.h"

dxf::dxf(lexer *p, dive *a)
{
	cout<<"freecoor_ini"<<endl;

    pcce = new cce(p,a);
    pflag = new flag_indicate;
    psurf = new surfdir_indicate;
	
	num_ent_l = p->F11 + p->F31;
	num_ent_r = p->F21 + p->F41;

    pel = new entity*[num_ent_l];
    per = new entity*[num_ent_r];

	p->Iarray(left_ent,num_ent_l,2);
	p->Iarray(right_ent,num_ent_r,2);
    

	//
    for(n=0;n<p->F11;++n)
    pel[n] = new line(p,n,1);
	
	for(n=p->F11;n<p->F31+p->F11;++n)
    pel[n] = new line(p,n,1);

    for(n=0;n<p->F21;++n)
    per[n] = new line(p,n,2);	

    for(n=p->F21;n<p->F41+p->F21;++n)
    per[n] = new line(p,n,2);

}

dxf::~dxf()
{
}

void dxf::start(lexer *p, dive *a)
{
	cout<<"dxf"<<endl;
	
	reader(p,a);

    for(n=0;n<p->F11;++n)
    pcce->start(p,a,pel[n]);

    for(n=0;n<p->F21;++n)
    pcce->start(p,a,per[n]);

    for(n=0;n<p->F11;++n)
    pflag->indicate(p,a,pel[n]);

    for(n=0;n<p->F21;++n)
    pflag->indicate(p,a,per[n]);

    pflag->finalize(p,a);
	
}
