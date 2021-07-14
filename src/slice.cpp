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

#include"slice.h"
#include"dive.h"
#include"lexer.h"
#include"inverse_dist.h"
#include"inverse_dist_local.h"

slice::slice(lexer *p, dive *a)
{
}

slice::~slice()
{
}

void slice::start(lexer* p, dive* a)
{
    cout<<"slice"<<endl;
    
    XYMALOOP
    a->flagslice(i,j)=-10;
    
    
    LOOP
    {
        if(a->flag(i,j,k)==1 && a->solid(i,j,k)>0)
        a->flagslice(i,j)=1;
    }
}

