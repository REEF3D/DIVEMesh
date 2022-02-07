/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2022 Hans Bihs

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
#include"field2d.h"

// source:

void kriging::ini(lexer *p, dive *a, int numpt, double *X, double *Y, double *F)
{    	
	xmin=ymin=1.0e15;
	xmax=ymax=-1.0e15;
	mean=0.0;
	
	
	for(n=0; n<numpt; ++n)
	{
	xmin = MIN(xmin,X[n]);
	xmax = MAX(xmax,X[n]);
	
	ymin = MIN(ymin,Y[n]);
	ymax = MAX(ymax,Y[n]);
	
	mean += F[n];
	}
	
	range = p->D18*sqrt(pow(xmax-xmin,2.0) + pow(ymax-ymin,2.0));
	
	mean/=double(numpt);
	
	variance=0.0;
	for(n=0; n<numpt; ++n)
	variance += pow(F[n] - mean, 2.0);
	
	variance/=double(numpt);
	
	cout<<"Np: "<<numpt<<"  mean: "<<mean<<"  variance: "<<variance<<"  range: "<<range<<endl;
}



