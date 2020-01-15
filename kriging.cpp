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
#include"field2d.h"

kriging::kriging(lexer *p, dive *a, int numpt, double *X, double *Y, double *F)
{
	
	pointcheck(p,a);
	//cout<<"D10 = "<<numpt<<endl;
	
	
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
	
	cout<<"mean: "<<mean<<"  variance: "<<variance<<"  range: "<<range<<endl;
}

kriging::~kriging()
{
}

void kriging::start(lexer* p, dive* a, int numpt, double *X, double *Y, double *F, field2d &f)
{
	cout<<"kriging"<<endl;
	
	p->Darray(A,numpt+1,numpt+1);
	p->Darray(B,numpt+1,numpt+1);

	p->Darray(b,numpt+1);
	p->Darray(x,numpt+1);
	p->Darray(s,numpt+1);
	p->Darray(row,numpt+1);

	
	
	cout<<"fill Aij"<<endl;
	for(n=0; n<numpt; ++n)
	for(q=0; q<numpt; ++q)
	{
		dist = sqrt(pow(X[n]-X[q],2.0) + pow(Y[n]-Y[q],2.0));
        
        dist = sqrt(pow(X[n]-X[q],2.0) + pow(Y[n]-Y[q],2.0));
		
		A[n][q] = semivariogram(dist); 
	}

	n=numpt;
	for(q=0; q<numpt; ++q)
	A[n][q] = 1.0; 
	
	q=numpt;
	for(n=0; n<numpt; ++n)
	A[n][q] = 1.0; 
	
	A[numpt][numpt] = 0.0; 	
	
	rearrange(p);
	
	cout<<"matrix solver"<<endl;
	invert(p,A,B,x,b);
	
	
	cout<<"mainloop kriging"<<endl<<endl;
	
	XYLOOP
	f(i,j) = 0.0;
	
	count=0;
	XYLOOP
	{
	xc = p->XP[IP];
    yc = p->YP[JP];
	
		for(n=0; n<numpt; ++n)
		{
			dist = sqrt(pow(xc-X[n],2.0) + pow(yc-Y[n],2.0));
		
			b[n] = semivariogram(dist);
		}
		
		b[numpt]=1.0;
		
		rearrange_b(p);

	
	matvec(p,B,b,x);
	backsubstitution(p,A,b);
	
	solve(p,B,x,b);
	
	
		val=0.0;
		for(n=0; n<numpt; ++n)
		val += x[n];
		
		cout<<"ij_iter  "<<count<<"   Weights: "<<val<<endl;
		
	for(n=0; n<numpt; ++n)
	f(i,j) += x[n] * F[n];
	
	++count;
    
    if(count%1000==0)
    cout<<count<<endl;
	}

}






