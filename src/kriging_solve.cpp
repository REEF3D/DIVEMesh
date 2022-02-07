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

void kriging::solve(lexer *p,double **A, double *x, double *b)
{
	// LU decomp
	for (r=0; r<p->Np; r++) 
	{
	
	aii=1.0/(fabs(A[r][r])>1.0e-19?A[r][r]:1.0e-19);
	
		for (n=r+1; n<p->Np; n++) 	
		{
		A[n][r]=A[n][r]*aii;
		
			for (q=r+1; q<p->Np; q++) 
			A[n][q]-=A[r][q]*A[n][r];
		}
	}
	
	// forward substitution
	for (q=0;q<p->Np;++q) 
	{
		for (n=0;n<q;++n) 
		b[q]-=A[q][n]*b[n];
	}
	
	// backward substitution
	for (q=p->Np-1;q>=0;q--) 
	{ 
		for (n=1+q; n < p->Np; n++) 
		b[q]-=A[q][n]*b[n];
	
	b[q]=b[q]/(fabs(A[q][q])>1.0e-19?A[q][q]:1.0e-19);
	}
}

void kriging::invert(lexer *p,double **A,double **B, double *x, double *b)
{
	cout<<"    decomp"<<endl;
	// LU decomp
	decomp(p,A,B);
	
	cout<<"    invert"<<endl;
    
	// invert
	for(q=0;q<p->Np;++q) 
	{	
        if(q%1000==0)
		cout<<"column: "<<q<<endl;
		
		for(n=0;n<p->Np;++n)
		s[n]=0.0;
		
		s[q]=1.0;
		
		backsubstitution(p,A,s);
		
		for(n=0;n<p->Np;++n)
		B[n][q] = s[n];
	}
	
}

void kriging::decomp(lexer *p,double **A,double **B)
{
	// LU decomp
	for(r=0; r<p->Np; ++r) 
	{
    if(r%1000==0)
    cout<<"decomp: "<<r<<endl;
	
	aii=1.0/(fabs(A[r][r])>1.0e-19?A[r][r]:1.0e-19);
	
		for(n=r+1; n<p->Np; ++n) 	
		{
		A[n][r]=A[n][r]*aii;
		
			for(q=r+1; q<p->Np; q++) 
			A[n][q]-=A[r][q]*A[n][r];
		}
	}
}

void kriging::backsubstitution(lexer *p,double **A, double *b)
{
	int qq,nn;
	
	// forward substitution
	for(qq=0;qq<p->Np;++qq) 
	{	
		for (nn=0;nn<qq;++nn) 
		b[qq]-=A[qq][nn]*b[nn]; 
	}
	
	// backward substitution
	for (qq=p->Np-1;qq>=0;qq--) 
	{ 
		for (nn=1+qq; nn < p->Np; nn++) 
		b[qq]-=A[qq][nn]*b[nn];
	
	b[qq]=b[qq]/(fabs(A[qq][qq])>1.0e-19?A[qq][qq]:1.0e-19);
	}

}

void kriging::matvec(lexer *p,double **A, double *b, double *x)
{
	int qq,nn;
	
	for(nn=0;nn<p->Np;++nn) 
	{	
		x[nn]=0.0;
		
		for(qq=0;qq<p->Np;++qq)
		x[nn]+=A[nn][qq]*b[qq];
	}
}



