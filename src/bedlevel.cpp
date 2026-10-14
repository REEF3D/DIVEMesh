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

#include"bedlevel.h"
#include"dive.h"
#include"lexer.h"

using namespace std;

bedlevel::bedlevel(lexer *p, dive *a)
{
}

void bedlevel::start(lexer* p, dive* a)
{
    cout<<"bedlevel"<<endl;

    // geodat (G 10): the interpolated bed is the base level, not limited by the B 10 z range
    // (no floor at zmin); solids and topo entities raise it. topobed starts at zmin, and the ray
    // cast only writes levels above zmin, so with G 9 2 (geodat in solidbed) topobed counts
    // only where a topo entity has raised it
    if(p->G10>0)
    {
        XYLOOP
        {
            const double tb = (p->G9==2 && a->topobed(i,j)<=p->zmin) ? -1.0e10 : a->topobed(i,j);

            a->bedlevel(i,j) = MAX(a->geobed(i,j),MAX(a->solidbed(i,j),tb));
        }
    }

    // no geodat: base level zmin (initialize)
    if(p->G10==0)
    XYLOOP
    {
        a->bedlevel(i,j) = MAX(a->bedlevel(i,j),MAX(a->solidbed(i,j),a->topobed(i,j)));
    }
}
