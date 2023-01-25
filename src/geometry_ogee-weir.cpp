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

#include"geometry.h"
#include"dive.h"
#include"lexer.h"

void geometry::ogee_weir(lexer* p, dive* a,int rank, int &ts, int &te,
                double xs, double ys, double zs, double Pd, double b, double H0, double Kval, double nval,
                double xc, double yc, double R1, double R2)
{
	double xl;
	double xorig,yorig,zorig;
	double ds,xstep;
	double x1,x2,y1,y2,z1,z2;
	double x0,y0,z0;
	int snum;

    /*
	xs = p->S121_x[rank];
    ys = p->S121_y[rank];
    zs = p->S121_z[rank];
	Pd = p->S121_Pd[rank];
	b = p->S121_b[rank];
	H0 = p->S121_H0[rank];

	Kval = p->S122_K[rank];
	nval = p->S122_n[rank];
	xc = p->S122_xc[rank]*H0;
	yc = p->S122_yc[rank]*H0;

	R1 = p->S123_R1[rank]*H0;
	R2 = p->S123_R2[rank]*H0;*/

	xorig = xs + xc;
	yorig = ys;
	zorig = Pd;

	x0 = xs + xc;
	y0 = ys;
	z0 = zs;

	// find xe from formula

	xl =  pow((zorig-zs)/Kval * pow(H0,nval-1.0),1.0/nval);
	xe =  xl + xs + xc;

	//cout<<"OGEE Pd: "<<Pd<<" H0: "<<H0<<" K: "<<Kval<<" n: "<<nval<<endl;

	//cout<<"OGEE xe: "<<xe<<endl;

// Vert

// Upstream Face
	// Tri 1
	ts=p->tricount;
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;

	p->tri_x[p->tricount][0] = xs;
	p->tri_y[p->tricount][0] = ys;
	p->tri_z[p->tricount][0] = zs;

	p->tri_x[p->tricount][1] = xs;
	p->tri_y[p->tricount][1] = ys;
	p->tri_z[p->tricount][1] = zs+Pd-yc;

	p->tri_x[p->tricount][2] = xs;
	p->tri_y[p->tricount][2] = ys+b;
	p->tri_z[p->tricount][2] = zs+Pd-yc;
	++p->tricount;

	// Tri 2
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;

	p->tri_x[p->tricount][0] = xs;
	p->tri_y[p->tricount][0] = ys+b;
	p->tri_z[p->tricount][0] = zs+Pd-yc;

	p->tri_x[p->tricount][1] = xs;
	p->tri_y[p->tricount][1] = ys;
	p->tri_z[p->tricount][1] = zs;

	p->tri_x[p->tricount][2] = xs;
	p->tri_y[p->tricount][2] = ys+b;
	p->tri_z[p->tricount][2] = zs;
	++p->tricount;

// Bootom
	// Tri 3
	p->trivec_x[p->tricount] = 1.0;
	p->trivec_y[p->tricount] = 0.0;
	p->trivec_z[p->tricount] = 0.0;

	p->tri_x[p->tricount][0] = xs;
	p->tri_y[p->tricount][0] = ys;
	p->tri_z[p->tricount][0] = zs;

	p->tri_x[p->tricount][1] = xe;
	p->tri_y[p->tricount][1] = ys;
	p->tri_z[p->tricount][1] = zs;

	p->tri_x[p->tricount][2] = xe;
	p->tri_y[p->tricount][2] = ys+b;
	p->tri_z[p->tricount][2] = zs;
	++p->tricount;

	// Tri 4
	p->trivec_x[p->tricount] = 1.0;
	p->trivec_y[p->tricount] = 0.0;
	p->trivec_z[p->tricount] = 0.0;

	p->tri_x[p->tricount][0] = xe;
	p->tri_y[p->tricount][0] = ys+b;
	p->tri_z[p->tricount][0] = zs;

	p->tri_x[p->tricount][1] = xs;
	p->tri_y[p->tricount][1] = ys+b;
	p->tri_z[p->tricount][1] = zs;

	p->tri_x[p->tricount][2] = xs;
	p->tri_y[p->tricount][2] = ys;
	p->tri_z[p->tricount][2] = zs;
	++p->tricount;

// Side Triangle
	// Tri 5
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = 1.0;
	p->trivec_z[p->tricount] = 0.0;

	p->tri_x[p->tricount][0] = xs;
	p->tri_y[p->tricount][0] = ys;
	p->tri_z[p->tricount][0] = zs;

	p->tri_x[p->tricount][1] = xs+xc;
	p->tri_y[p->tricount][1] = ys;
	p->tri_z[p->tricount][1] = zs;

	p->tri_x[p->tricount][2] = xs;
	p->tri_y[p->tricount][2] = ys;
	p->tri_z[p->tricount][2] = zs+Pd-yc;
	++p->tricount;

	// Tri 6
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = 1.0;
	p->trivec_z[p->tricount] = 0.0;

	p->tri_x[p->tricount][0] = xs;
	p->tri_y[p->tricount][0] = ys+b;
	p->tri_z[p->tricount][0] = zs;

	p->tri_x[p->tricount][1] = xs+xc;
	p->tri_y[p->tricount][1] = ys+b;
	p->tri_z[p->tricount][1] = zs;

	p->tri_x[p->tricount][2] = xs;
	p->tri_y[p->tricount][2] = ys+b;
	p->tri_z[p->tricount][2] = zs+Pd-yc;
	++p->tricount;

// Ogee

	snum = 200;
	ds = xl/double(snum);
	xstep=0.0;

	//cout<<" ogee: "<<ds<<" yc: "<<yc<<endl;

	for(n=0;n<snum;++n)
	{
	x1 = xorig + xstep;
	xstep+=ds;
	x2 = xorig + xstep;
	y1 = ys;
	y2 = ys + b;
	z1 = zorig - Kval*H0*pow((x1-xorig)/H0,nval); //((Kval*pow(x1,nval))/pow(H0,nval-1.0);
	z2 = zorig - Kval*H0*pow((x2-xorig)/H0,nval); //(Kval*pow(x2,nval))/pow(H0,nval-1.0);

	//cout<<" x1: "<<x1<<" x2: "<<x2<<" z1: "<<z1<<" z2: "<<z2<<endl;

	// Tri top 1
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = 0.0;
	p->trivec_z[p->tricount] = 1.0;

	p->tri_x[p->tricount][0] = x1;
	p->tri_y[p->tricount][0] = y1;
	p->tri_z[p->tricount][0] = z1;

	p->tri_x[p->tricount][1] = x2;
	p->tri_y[p->tricount][1] = y1;
	p->tri_z[p->tricount][1] = z2;

	p->tri_x[p->tricount][2] = x1;
	p->tri_y[p->tricount][2] = y2;
	p->tri_z[p->tricount][2] = z1;
	++p->tricount;

	// Tri top 2
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = 0.0;
	p->trivec_z[p->tricount] = 1.0;

	p->tri_x[p->tricount][0] = x2;
	p->tri_y[p->tricount][0] = y1;
	p->tri_z[p->tricount][0] = z2;

	p->tri_x[p->tricount][1] = x2;
	p->tri_y[p->tricount][1] = y2;
	p->tri_z[p->tricount][1] = z2;

	p->tri_x[p->tricount][2] = x1;
	p->tri_y[p->tricount][2] = y2;
	p->tri_z[p->tricount][2] = z1;
	++p->tricount;

	// Tri side 3
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;

	p->tri_x[p->tricount][0] = x0;
	p->tri_y[p->tricount][0] = y0;
	p->tri_z[p->tricount][0] = z0;

	p->tri_x[p->tricount][1] = x2;
	p->tri_y[p->tricount][1] = y1;
	p->tri_z[p->tricount][1] = z2;

	p->tri_x[p->tricount][2] = x1;
	p->tri_y[p->tricount][2] = y1;
	p->tri_z[p->tricount][2] = z1;
	++p->tricount;

	// Tri side 2
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = 1.0;
	p->trivec_z[p->tricount] = 0.0;

	p->tri_x[p->tricount][0] = x0;
	p->tri_y[p->tricount][0] = y0+b;
	p->tri_z[p->tricount][0] = z0;

	p->tri_x[p->tricount][1] = x2;
	p->tri_y[p->tricount][1] = y2;
	p->tri_z[p->tricount][1] = z2;

	p->tri_x[p->tricount][2] = x1;
	p->tri_y[p->tricount][2] = y2;
	p->tri_z[p->tricount][2] = z1;
	++p->tricount;
	}

	snum = 20;
	xstep=0.0;
	double ta,tb,tc,gamma;
	double xm,zm;

	ta = R1;
	tc = sqrt(xc*xc + yc*yc);

	gamma = acos(1.0 - tc*tc/(2.0*ta*ta));

	//cout<<" ogee: "<<tc<<" gamma: "<<gamma<<endl;

	gamma=0.5*gamma;

	ds = gamma/double(snum);

	double phi=0.0;

	xm = xorig;
	zm = zorig - R1;

	for(n=0;n<snum;++n)
	{

	x1 = R1*sin(phi) + xm;
	y1 = ys;
	z1 = R1*cos(phi) + zm;

	phi-=ds;

	x2 = R1*sin(phi) + xm;
	y2 = ys + b;
	z2 = R1*cos(phi) + zm;

	//cout<<" x1: "<<x1<<" x2: "<<x2<<" z1: "<<z1<<" z2: "<<z2<<endl;

	// Tri side 3
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;

	p->tri_x[p->tricount][0] = x0;
	p->tri_y[p->tricount][0] = y0;
	p->tri_z[p->tricount][0] = z0;

	p->tri_x[p->tricount][1] = x1;
	p->tri_y[p->tricount][1] = y1;
	p->tri_z[p->tricount][1] = z1;

	p->tri_x[p->tricount][2] = x2;
	p->tri_y[p->tricount][2] = y1;
	p->tri_z[p->tricount][2] = z2;
	++p->tricount;

	// Tri side 2
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = 1.0;
	p->trivec_z[p->tricount] = 0.0;

	p->tri_x[p->tricount][0] = x0;
	p->tri_y[p->tricount][0] = y0+b;
	p->tri_z[p->tricount][0] = z0;

	p->tri_x[p->tricount][1] = x1;
	p->tri_y[p->tricount][1] = y2;
	p->tri_z[p->tricount][1] = z1;

	p->tri_x[p->tricount][2] = x2;
	p->tri_y[p->tricount][2] = y2;
	p->tri_z[p->tricount][2] = z2;
	++p->tricount;

	// Tri top 1
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = 0.0;
	p->trivec_z[p->tricount] = 1.0;

	p->tri_x[p->tricount][0] = x1;
	p->tri_y[p->tricount][0] = y1;
	p->tri_z[p->tricount][0] = z1;

	p->tri_x[p->tricount][1] = x2;
	p->tri_y[p->tricount][1] = y1;
	p->tri_z[p->tricount][1] = z2;

	p->tri_x[p->tricount][2] = x2;
	p->tri_y[p->tricount][2] = y2;
	p->tri_z[p->tricount][2] = z2;
	++p->tricount;

	// Tri top 2
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = 0.0;
	p->trivec_z[p->tricount] = 1.0;

	p->tri_x[p->tricount][0] = x1;
	p->tri_y[p->tricount][0] = y1;
	p->tri_z[p->tricount][0] = z1;

	p->tri_x[p->tricount][1] = x1;
	p->tri_y[p->tricount][1] = y2;
	p->tri_z[p->tricount][1] = z1;

	p->tri_x[p->tricount][2] = x2;
	p->tri_y[p->tricount][2] = y2;
	p->tri_z[p->tricount][2] = z2;
	++p->tricount;
	}


//-----
	phi=-gamma;
	double alpha, xm2,zm2,xe2,ze2;

	xe2 = xm + R1*sin(-gamma);
	ze2 = zm + R1*cos(-gamma);

	xm2 = xm + (R1-R2)*sin(-gamma);
	zm2 = zm + (R1-R2)*cos(-gamma);

	snum = 20;

	ta = R2;
	tc = sqrt((xe2-xs)*(xe2-xs) + (yc-zorig+ze2)*(yc-zorig+ze2));

	gamma = acos(1.0 - tc*tc/(2.0*ta*ta));

	//cout<<" ogee: "<<tc<<" gamma: "<<gamma<<endl;

	ds = gamma/double(snum);



	for(n=0;n<snum;++n)
	{

	x1 = R2*sin(phi) + xm2;
	y1 = ys;
	z1 = R2*cos(phi) + zm2;

	phi-=ds;

	x2 = R2*sin(phi) + xm2;
	y2 = ys + b;
	z2 = R2*cos(phi) + zm2;

	//cout<<" x1: "<<x1<<" x2: "<<x2<<" z1: "<<z1<<" z2: "<<z2<<endl;

	// Tri side 3
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;

	p->tri_x[p->tricount][0] = x0;
	p->tri_y[p->tricount][0] = y0;
	p->tri_z[p->tricount][0] = z0;

	p->tri_x[p->tricount][1] = x1;
	p->tri_y[p->tricount][1] = y1;
	p->tri_z[p->tricount][1] = z1;

	p->tri_x[p->tricount][2] = x2;
	p->tri_y[p->tricount][2] = y1;
	p->tri_z[p->tricount][2] = z2;
	++p->tricount;

	// Tri side 2
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = 1.0;
	p->trivec_z[p->tricount] = 0.0;

	p->tri_x[p->tricount][0] = x0;
	p->tri_y[p->tricount][0] = y0+b;
	p->tri_z[p->tricount][0] = z0;

	p->tri_x[p->tricount][1] = x1;
	p->tri_y[p->tricount][1] = y2;
	p->tri_z[p->tricount][1] = z1;

	p->tri_x[p->tricount][2] = x2;
	p->tri_y[p->tricount][2] = y2;
	p->tri_z[p->tricount][2] = z2;
	++p->tricount;

	// Tri top 1
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = 0.0;
	p->trivec_z[p->tricount] = 1.0;

	p->tri_x[p->tricount][0] = x1;
	p->tri_y[p->tricount][0] = y1;
	p->tri_z[p->tricount][0] = z1;

	p->tri_x[p->tricount][1] = x2;
	p->tri_y[p->tricount][1] = y1;
	p->tri_z[p->tricount][1] = z2;

	p->tri_x[p->tricount][2] = x2;
	p->tri_y[p->tricount][2] = y2;
	p->tri_z[p->tricount][2] = z2;
	++p->tricount;

	// Tri top 2
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = 0.0;
	p->trivec_z[p->tricount] = 1.0;

	p->tri_x[p->tricount][0] = x1;
	p->tri_y[p->tricount][0] = y1;
	p->tri_z[p->tricount][0] = z1;

	p->tri_x[p->tricount][1] = x1;
	p->tri_y[p->tricount][1] = y2;
	p->tri_z[p->tricount][1] = z1;

	p->tri_x[p->tricount][2] = x2;
	p->tri_y[p->tricount][2] = y2;
	p->tri_z[p->tricount][2] = z2;
	++p->tricount;
	}

	te=p->tricount;

	//cout<<"tricount: "<<p->tricount<<endl;
}
