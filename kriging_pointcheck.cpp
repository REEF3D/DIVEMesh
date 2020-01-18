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

void kriging::pointcheck(lexer *p, dive *a, double *X, double *Y, double *F)
{
	double epsi=p->G18*p->DXYM;
	double xdiff,ydiff,ddiff;
	int count=0;
    
    for(n=0; n<Np; ++n)
    flag[n]=0;
	
	for(n=0; n< Np; ++n)
	{
		for(q=0; q< Np; ++q)
		if(n!=q)
		{
		xdiff = fabs(X[n]-X[q]);
		ydiff = fabs(Y[n]-Y[q]);
		ddiff = fabs(F[n]-F[q]);
		
			if(xdiff<epsi && ydiff<epsi)
			{
			X[q] = X[Np-1];
			Y[q] = Y[Np-1];
			F[q] = F[Np-1];
			-- Np;
			--q;
			++count;
			
			cout<<"double data entry "<<count<<endl;
			}
		}
	}
}