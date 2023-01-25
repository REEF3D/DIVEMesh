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

#include"kriging.h"
#include"dive.h"
#include"lexer.h"

void kriging::rearrange(lexer *p)
{
	// A
	for(q=0;q<p->Np;++q)
	row[q] = A[0][q];
	
	for(n=0;n<p->Np-1;++n)
	for(q=0;q<p->Np;++q)
	A[n][q] = A[n+1][q];
	
	for(q=0;q<p->Np;++q)
	A[p->Np-1][q]=row[q];
}

void kriging::rearrange_b(lexer *p)
{
	// b
	val = b[0];
	
	for(n=0;n<p->Np-1;++n)
	b[n] = b[n+1];
	
	b[p->Np-1] = val;
}

