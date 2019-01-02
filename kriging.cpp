/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2019 Hans Bihs

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

kriging::kriging(lexer *p, dive *a) 
{
	
	pointcheck(p,a);
	cout<<"D10 = "<<p->D10<<endl;
	
	numpt = p->D10 + 1;
	
	xmin=ymin=1.0e15;
	xmax=ymax=-1.0e15;
	mean=0.0;
	
	
	for(n=0; n<p->D10; ++n)
	{
	xmin = MIN(xmin,p->D10_x[n]);
	xmax = MAX(xmax,p->D10_x[n]);
	
	ymin = MIN(ymin,p->D10_y[n]);
	ymax = MAX(ymax,p->D10_y[n]);
	
	mean += p->D10_data[n];
	}
	
	range = p->D18*sqrt(pow(xmax-xmin,2.0) + pow(ymax-ymin,2.0));
	
	mean/=double(p->D10);
	
	variance=0.0;
	for(n=0; n<p->D10; ++n)
	variance += pow(p->D10_data[n] - mean, 2.0);
	
	variance/=double(p->D10);
	
	cout<<"mean: "<<mean<<"  variance: "<<variance<<"  range: "<<range<<endl;
}

kriging::~kriging()
{
}

void kriging::start(lexer* p, dive* a)
{
	cout<<"kriging"<<endl;
	
	p->Darray(A,numpt,numpt);
	p->Darray(B,numpt,numpt);

	p->Darray(b,numpt);
	p->Darray(x,numpt);
	p->Darray(s,numpt);
	p->Darray(row,numpt);

	
	
	cout<<"fill Aij"<<endl;
	for(n=0; n<p->D10; ++n)
	for(q=0; q<p->D10; ++q)
	{
		dist = sqrt(pow(p->D10_x[n]-p->D10_x[q],2.0) + pow(p->D10_y[n]-p->D10_y[q],2.0));
		
		A[n][q] = semivariogram(dist); 
	}

	n=p->D10;
	for(q=0; q<p->D10; ++q)
	A[n][q] = 1.0; 
	
	q=p->D10;
	for(n=0; n<p->D10; ++n)
	A[n][q] = 1.0; 
	
	A[p->D10][p->D10] = 0.0; 	
	
	rearrange(p);
	
	cout<<"matrix solver"<<endl;
	invert(p,A,B,x,b);
	
	
	cout<<"mainloop kriging"<<endl<<endl;
	
	XYLOOP
	a->data(i,j) = 0.0;
	
	count=0;
	XYLOOP
	{
	xc = p->XP[IP];
    yc = p->YP[JP];
	
		for(n=0; n<p->D10; ++n)
		{
			dist = sqrt(pow(xc-p->D10_x[n],2.0) + pow(yc-p->D10_y[n],2.0));
		
			b[n] = semivariogram(dist);
		}
		
		b[p->D10]=1.0;
		
		rearrange_b(p);

	
	matvec(p,B,b,x);
	//backsubstitution(p,A,b);
	
	//solve(p,B,x,b);
	
	
		val=0.0;
		for(n=0; n<p->D10; ++n)
		val += x[n];
		
		cout<<"ij_iter  "<<count<<"   Weights: "<<val<<endl;
		
	for(n=0; n<p->D10; ++n)
	a->data(i,j) += x[n] * p->D10_data[n];
	
	++count;
	}

}






