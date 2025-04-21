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

#include"intfield.h"
#include"lexer.h"

intfield::intfield(lexer *p)
{
	p->Iarray(feld,p->knox+2*xma,p->knoy+2*yma,p->knoz+2*zma);

	dx=xma;
	dy=yma;
	dz=zma;
}

int& intfield::operator()(int ii, int jj, int kk)
{
	return feld[ii+dx][jj+dy][kk+dz];
}


