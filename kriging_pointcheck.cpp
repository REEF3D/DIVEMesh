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

#include"kriging.h"
#include"dive.h"
#include"lexer.h"

void kriging::pointcheck(lexer *p, dive *a)
{
	double epsi=1.0e-15;
	double xdiff,ydiff,ddiff;
	int count=0;
	
	for(n=0; n<p->D10; ++n)
	{
		for(q=0; q<p->D10; ++q)
		if(n!=q)
		{
		xdiff = fabs(p->D10_x[n]-p->D10_x[q]);
		ydiff = fabs(p->D10_y[n]-p->D10_y[q]);
		ddiff = fabs(p->D10_data[n]-p->D10_data[q]);
		
			if(xdiff<epsi && ydiff<epsi)
			{
			p->D10_x[q] = p->D10_x[p->D10-1];
			p->D10_y[q] = p->D10_y[p->D10-1];
			p->D10_data[q] = p->D10_data[p->D10-1];
			--p->D10;
			--q;
			++count;
			
			cout<<"double data entry "<<count<<endl;
			}
		}
	}
}