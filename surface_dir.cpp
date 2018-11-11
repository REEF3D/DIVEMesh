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

#include"surface.h"
#include"lexer.h"
#include"dive.h"

void surface::direction(lexer* p, dive* a)
{

    LOOP
    if(a->numfac(i,j,k)>0)
    {
    q=a->confac(i,j,k);

    a->surfdir[q][0]=a->xdir(i,j,k);
    a->surfdir[q][1]=a->ydir(i,j,k);
    a->surfdir[q][2]=a->zdir(i,j,k);

    if(a->surfdir[q][0]==1)
    a->gcn[q][0] = fabs(a->gcn[q][0]);

    if(a->surfdir[q][0]==4)
    a->gcn[q][0] = -fabs(a->gcn[q][0]);

    if(a->surfdir[q][1]==3)
    a->gcn[q][1] = fabs(a->gcn[q][1]);

    if(a->surfdir[q][1]==2)
    a->gcn[q][1] = -fabs(a->gcn[q][1]);

    if(a->surfdir[q][2]==5)
    a->gcn[q][2] = fabs(a->gcn[q][2]);

    if(a->surfdir[q][2]==6)
    a->gcn[q][2] = -fabs(a->gcn[q][2]);
	
		if(a->numfac(i,j,k)==1)
		{
		a->gcn[q][0]=0.0;
		a->gcn[q][1]=0.0;
		a->gcn[q][2]=0.0;
		
		if(a->surfdir[q][0]==1)
		a->gcn[q][0] = 1.0;

		if(a->surfdir[q][0]==4)
		a->gcn[q][0] = -1.0;

		if(a->surfdir[q][1]==3)
		a->gcn[q][1] = 1.0;

		if(a->surfdir[q][1]==2)
		a->gcn[q][1] = -1.0;

		if(a->surfdir[q][2]==5)
		a->gcn[q][2] = 1.0;

		if(a->surfdir[q][2]==6)
		a->gcn[q][2] = -1.0;
						
		}
    }
}




