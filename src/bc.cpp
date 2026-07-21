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

#include"bc.h"

using namespace std;

void bc::makebc(lexer* p, dive* a)
{
    // Boundary Conditions
    // 1 = inflow, 2 = outflow,
    // 3 = symmetry,
    // 6 = wave generation, 7 = numerical beach
    // 21 = wall

    cout<<"bc";

    int inflow = p->C11;
    int right = p->C12;
    int left = p->C13;
    int outflow = p->C14;
    int bottom = p->C15;
    int top = p->C16;

    if(p->knoy==1)
    {
        right = 3;
        left = 3;
    }

    LOOP
    if(a->flag(i,j,k)>0)
    {
        if(i==0)
        a->flag(i-1,j,k)=-inflow;

        if(i==p->knox-1)
        a->flag(i+1,j,k)=-outflow;

        if(j==0)
        a->flag(i,j-1,k)=-left;

        if(j==p->knoy-1)
        a->flag(i,j+1,k)=-right;

        if(k==0)
        a->flag(i,j,k-1)=-bottom;

        if(k==p->knoz-1)
        a->flag(i,j,k+1)=-top;
    }

    cout<<"."<<endl;
}
