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
	xmin=ymin=1.0e15;
	xmax=ymax=-1.0e15;
	mean=0.0;
	
	
	for(n=0; n<p->Np; ++n)
	{
	xmin = MIN(xmin,X[n]);
	xmax = MAX(xmax,X[n]);
	
	ymin = MIN(ymin,Y[n]);
	ymax = MAX(ymax,Y[n]);
	
	mean += F[n];
	}
	
	range = p->D18*sqrt(pow(xmax-xmin,2.0) + pow(ymax-ymin,2.0));
	
	mean/=double(p->Np);
	
	variance=0.0;
	for(n=0; n<p->Np; ++n)
	variance += pow(F[n] - mean, 2.0);
	
	variance/=double(p->Np);
	
	cout<<"mean: "<<mean<<"  variance: "<<variance<<"  range: "<<range<<endl;
}

kriging::~kriging()
{
}

void kriging::start(lexer* p, dive* a, int numpt, double *X, double *Y, double *F, double *XC, double *YC, int kx, int ky, double **f)
{
    //p->Np=numpt;
	cout<<"kriging  p->Np: "<<p->Np<<endl;
	
	p->Darray(A,p->Np+1,p->Np+1);
	p->Darray(B,p->Np+1,p->Np+1);

	p->Darray(b,p->Np+1);
	p->Darray(x,p->Np+1);
	p->Darray(s,p->Np+1);
	p->Darray(row,p->Np+1);

    
    

	
	
	cout<<"fill Aij"<<endl;
	for(n=0; n<p->Np; ++n)
	for(q=0; q<p->Np; ++q)
	{
		dist = sqrt(pow(X[n]-X[q],2.0) + pow(Y[n]-Y[q],2.0));
        	
		A[n][q] = semivariogram(dist); 
	}

	n=p->Np;
	for(q=0; q<p->Np; ++q)
	A[n][q] = 1.0; 
	
	q=p->Np;
	for(n=0; n<p->Np; ++n)
	A[n][q] = 1.0; 
	
	A[p->Np][p->Np] = 0.0; 	
	
	rearrange(p);
	
	cout<<"matrix solver"<<endl;
	invert(p,A,B,x,b);
	
	
	cout<<"mainloop kriging"<<endl<<endl;
	
	for(i=0;i<kx;++i)
    for(j=0;j<ky;++j)
	f[i][j] = 0.0;
	
	count=0;
	for(i=0;i<kx;++i)
    for(j=0;j<ky;++j)
	{
	xc = XC[IP];
    yc = YC[JP];
	
		for(n=0; n<p->Np; ++n)
		{
			dist = sqrt(pow(xc-X[n],2.0) + pow(yc-Y[n],2.0));
		
			b[n] = semivariogram(dist);
            
		}
		
		b[p->Np]=1.0;
		
		rearrange_b(p);

	
	matvec(p,B,b,x);
	
		val=0.0;
		for(n=0; n<p->Np; ++n)
        {
		val += x[n];
		}
        if(count%1000==0)
		cout<<"ij_iter  "<<count<<"   Weights: "<<val<<endl;
		
	for(n=0; n<p->Np; ++n)
	f[i][j] += x[n] * F[n];
	
	++count;
    
    if(count%1000==0)
    cout<<count<<endl;
	}

}






