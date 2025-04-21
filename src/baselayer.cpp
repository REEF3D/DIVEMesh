/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2025 Hans Bihs

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

#include"baselayer.h"
#include"dive.h"
#include"lexer.h"
#include"box_bl.h"

baselayer::baselayer(lexer *p, dive *a)
{
    cout<<"baselayer_ini "<<endl;

	for(n=0;n<p->B10;++n)
    {
    pent = new box_bl(p,n,1);
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
    a->flag(i,j,k)=-21;

    LOOP
    {
    a->flag(i,j,k)=1;
    }
}
