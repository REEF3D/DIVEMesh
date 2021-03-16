/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2021 Hans Bihs

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

void solid::stl_preproc(lexer* p, dive* a, int &ts, int &te)
{
   ts=0;
   te=p->tricount;
}

void solid::stl_postproc(lexer* p, dive* a, int &ts, int &te)
{
    LOOP
	{
	a->solid(i,j,k)*=p->S9_1;
    a->solid_dist(i,j,k)*=double(p->S9_1);
	}
}
