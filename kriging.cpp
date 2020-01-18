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

// source:

kriging::kriging(lexer *p, dive *a, int numpt, double *X, double *Y, double *F)
{
	Np = numpt;
    
    p->Iarray(flag,Np+1);
	pointcheck(p,a,X,Y,F);
	//cout<<"D10 = "<<Np<<endl;
	
	
	xmin=ymin=1.0e15;
	xmax=ymax=-1.0e15;
	mean=0.0;
	
	
	for(n=0; n<Np; ++n)
	{
	xmin = MIN(xmin,X[n]);
	xmax = MAX(xmax,X[n]);
	
	ymin = MIN(ymin,Y[n]);
	ymax = MAX(ymax,Y[n]);
	
	mean += F[n];
	}
	
	range = p->D18*sqrt(pow(xmax-xmin,2.0) + pow(ymax-ymin,2.0));
	
	mean/=double(Np);
	
	variance=0.0;
	for(n=0; n<Np; ++n)
	variance += pow(F[n] - mean, 2.0);
	
	variance/=double(Np);
	
	cout<<"mean: "<<mean<<"  variance: "<<variance<<"  range: "<<range<<endl;
}

kriging::~kriging()
{
}

void kriging::start(lexer* p, dive* a, int numpt, double *X, double *Y, double *F, field2d &f)
{
    //Np=numpt;
	cout<<"kriging  Np: "<<Np<<endl;
	
	p->Darray(A,Np+1,Np+1);
	p->Darray(B,Np+1,Np+1);

	p->Darray(b,Np+1);
	p->Darray(x,Np+1);
	p->Darray(s,Np+1);
	p->Darray(row,Np+1);

    
    

	
	
	cout<<"fill Aij"<<endl;
	for(n=0; n<Np; ++n)
	for(q=0; q<Np; ++q)
	{
		dist = sqrt(pow(X[n]-X[q],2.0) + pow(Y[n]-Y[q],2.0));
        	
		A[n][q] = semivariogram(dist); 
	}

	n=Np;
	for(q=0; q<Np; ++q)
	A[n][q] = 1.0; 
	
	q=Np;
	for(n=0; n<Np; ++n)
	A[n][q] = 1.0; 
	
	A[Np][Np] = 0.0; 	
	
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
	
		for(n=0; n<Np; ++n)
		{
			dist = sqrt(pow(xc-X[n],2.0) + pow(yc-Y[n],2.0));
		
			b[n] = semivariogram(dist);
            
		}
		
		b[Np]=1.0;
		
		rearrange_b(p);

	
	matvec(p,B,b,x);
	//backsubstitution(p,A,b);
	//solve(p,B,x,b);
	
	
		val=0.0;
		for(n=0; n<Np; ++n)
        {
		val += x[n];
		}
		cout<<"ij_iter  "<<count<<"   Weights: "<<val<<endl;
		
	for(n=0; n<Np; ++n)
	f(i,j) += x[n] * F[n];
	
	++count;
    
    if(count%1000==0)
    cout<<count<<endl;
	}

}






