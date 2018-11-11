/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2018 Hans Bihs

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

#include"bc.h"

bc::bc()
{
}

bc::~bc()
{
}

void bc::makebc(lexer* p, dive* a)
{
    cout<<"bc";

    inflow = p->C11;
    right = p->C12;
    left = p->C13;
    outflow = p->C14;
    bottom = p->C15;
    top = p->C16;

    LOOP
    if(a->flag(i,j,k)>0)
	{
        if(i==x1)
        a->flag(i-1,j,k)=-inflow;

        if(i==p->knox-1+x1)
        a->flag(i+1,j,k)=-outflow;

        if(j==y1)
        a->flag(i,j-1,k)=-left;

        if(j==p->knoy-1+y1)
        a->flag(i,j+1,k)=-right;

        if(k==z1)
        a->flag(i,j,k-1)=-bottom;

        if(k==p->knoz-1+z1)
        a->flag(i,j,k+1)=-top;
	}

	cout<<"."<<endl;

}

