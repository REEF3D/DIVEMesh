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

#include"decomposition.h"

void decomp::periodic_ini(lexer* p, dive* a)
{
    xper=yper=zper=0;
    
    if(p->C21>1)
    {
        if(a->mx==1)
        p->C21=1;
        
        if(a->mx>1)
        {
        p->C21=2;
        xper=1;
        }
    }
    
    if(p->C22>1)
    {
        if(a->my==1)
        p->C22=1;
        
        if(a->my>1)
        {
        p->C22=2;
        yper=1;
        }
    }
    
    if(p->C23>1)
    {
        if(a->mz==1)
        p->C23=1;
        
        if(a->mz>1)
        {
        p->C23=2;
        zper=1;
        }
    }
    
    
}

void decomp::periodic_surf(lexer* p, dive* a)
{
    
}