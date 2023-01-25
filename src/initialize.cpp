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

#include "initialize.h"

initialize::initialize()
{
}

initialize::~initialize()
{
}

void initialize::start(lexer* p, dive* a)
{
    MALOOP
    {
    a->flag(i,j,k)=-21;
	a->solid(i,j,k)=-10;
    a->subgrid(i,j,k)=0;
    a->solid_dist(i,j,k)=0.0;
    }

    LOOP
	{
    a->flag(i,j,k)=1;
	a->solid(i,j,k)=1;
	}

	XYLOOP
    {
    a->bedlevel(i,j)=p->zmin;
    a->solidbed(i,j)=-1.0e10;
    a->topobed(i,j)=p->zmin;
    }

}
