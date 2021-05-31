/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2021 Hans Bihs

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

#include"spline.h"
#include"lexer.h"
#include"dive.h"
/*
void spline::spline_coeff(double *t, double *f, int *i_support, int num_support, double *a, double *b, double *c, double *D)
{


    int i,k;

	double *e,*f,*g,*r,*w;

	double h;

	e=new double [maxPt+1];
	f=new double [maxPt+1];
	g=new double [maxPt+1];
	r=new double [maxPt+1];
	w=new double [maxPt+1];



	// form the tridiagonal system

    e[0]=0; e[1]=0;

	f[0]=0; g[0]=0; r[0]=0;

	g[nPt-2]=0;

    for (k=1;k<=nPt-2;k++)

	{

        e[k+1]=ipt[k+1].x-ipt[k].x;
		f[k]=2*(ipt[k+1].x-ipt[k-1].x);
		g[k]=ipt[k+1].x-ipt[k].x;
		r[k]=6*((ipt[k+1].y-ipt[k].y)/(ipt[k+1].x-ipt[k].x)
			+(ipt[k-1].y-ipt[k].y)/(ipt[k].x-ipt[k-1].x));

	}



	// Thomas algorithm to solve the system

    w[0]=0; w[nPt-1]=0;

	for (k=2;k<=nPt-2;k++)

    {

		e[k]/=f[k-1];

		f[k]-=e[k]*g[k-1];

	}

    for (k=2;k<=nPt-2;k++)

    	r[k]-=e[k]*r[k-1];

    w[nPt-2]=r[nPt-2]/f[nPt-2];

    for (k=nPt-3;k>=1;k--)

    	w[k]=(r[k]-g[k]*w[k+1])/f[k];

    for (k=1;k<=nPt-1;k++)

    {

        A[k]=w[k-1]/(6*(ipt[k].x-ipt[k-1].x));

        B[k]=w[k]/(6*(ipt[k].x-ipt[k-1].x));

        C[k]=ipt[k-1].y/(ipt[k].x-ipt[k-1].x)

			-w[k-1]/6*(ipt[k].x-ipt[k-1].x);

        D[k]=ipt[k].y/(ipt[k].x-ipt[k-1].x)

			-w[k]/6*(ipt[k].x-ipt[k-1].x);

    }

	h=(ipt[nPt-1].x-ipt[0].x)/m;

	pt[0].x=ipt[0].x;

	pt[0].y=ipt[0].y;



	for (i=0;i<=m;i++)

	{

		for (k=1;k<=nPt-1;k++)

			if (pt[i].x>=ipt[k-1].x && pt[i].x<=ipt[k].x)

				pt[i].y=A[k]*pow(ipt[k].x-pt[i].x,3)+B[k]*pow(pt[i].x-ipt[k-1].x,3)

					+C[k]*(ipt[k].x-pt[i].x)+D[k]*(pt[i].x-ipt[k-1].x);

		if (i<m)

			pt[i+1].x=pt[i].x+h;

	}



}
*/
