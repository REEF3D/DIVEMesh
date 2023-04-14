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
#include"lexer.h"
#include"dive.h"

void geometry::beam(lexer *p, dive *a, int rank, int &ts, int &te, 
                double xs, double ys, double zs, double xe, double ye, double ze, double b, double h)
{
    
    double U,ds,eta;
	
	double rmax;
	int snum;
	int vertice_mem, center1_num,center2_num;
	int vertice_start=a->vertice_num;
	double Ax,Ay,Az;
	double Bx,By,Bz;
	double Nx,Ny,Nz,norm;
    double alpha,beta,gamma;
    double dX,dY,dZ,ddX,ddY,ddZ;
    double eps = 1.0e-10;
    double length;
    double xvec1,yvec1,zvec1;
    double alpha1,beta1,gamma1;
    double x1,y1,z1;
    double x2,y2,z2;
    double a1,b1,c1;
    double a2,b2,c2;
    double off_x,off_y,off_z;
    
    dX = xe-xs;
    dY = ye-ys;
    dZ = ze-zs;

    length = sqrt(dX*dX + dY*dY + dZ*dZ);

    alpha=beta=gamma=0.0;

    // alpha
    angle_calc(dX,dY,dZ,alpha,beta,gamma);

    a1=0.0;
    b1=0.0;
    c1=0.0;
    a2=0.0;
    b2=0.0;
    c2=0.0;
    //LOOP

    double ee=0.000001;
    int count=0;
    do
    {
        x1=length;
        y1=0.0;
        z1=0.0;

      rotation(x1,y1,z1,a1,b1,c1);
      angle_calc(x1,y1,z1,a2,b2,c2);

      if(a2>alpha+ee || a2<alpha-ee)
      a1 = a1 - 0.5*(a2-alpha);

      if(b2>beta+ee || b2<beta-ee)
      b1 = b1 - 0.5*(b2-beta);

      if(c2>gamma+ee || c2<gamma-ee)
      c1 = c1 - 0.5*(c2-gamma);


      if(a2<=alpha+ee && a2>=alpha-ee)
      if(b2<=beta+ee && b2>=beta-ee)
      if(c2<=gamma+ee && c2>=gamma-ee)
      break;

     ++count;
    }while(count<500);

    cout<<"iteration: "<<count<<endl;
    cout<<"alpha: "<<alpha*(180.0/PI)<<" beta: "<<beta*(180.0/PI)<<" gamma: "<<gamma*(180.0/PI)<<endl;
    cout<<"a1: "<<a1*(180.0/PI)<<" b1: "<<b1*(180.0/PI)<<" c1: "<<c1*(180.0/PI)<<endl;

    cout<<"dX: "<<dX<<" dY: "<<dY<<" dZ: "<<dZ<<endl;
    cout<<"x1: "<<x1<<" y1: "<<y1<<" z1: "<<z1<<endl;


	ts=p->tricount;

	// Vert
    
    
    // redefine xs,xe
    off_x = xs;
    off_y = ys;
    off_z = zs;
    
    xs = 0.0 + off_x;
    xe = length + off_x;
    ys = -0.5*b + off_y;
    ye = 0.5*b + off_y;
    zs = -0.5*h + off_z;
    ze = 0.5*h + off_z;
    

// Face 3
	// Tri 1
	ts=p->tricount;
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = xe;
	p->tri_y[p->tricount][0] = ys;
	p->tri_z[p->tricount][0] = zs;
	
	p->tri_x[p->tricount][1] = xs;
	p->tri_y[p->tricount][1] = ys;
	p->tri_z[p->tricount][1] = ze;
	
	p->tri_x[p->tricount][2] = xs;
	p->tri_y[p->tricount][2] = ys;
	p->tri_z[p->tricount][2] = zs;
	++p->tricount;
	
	// Tri 2
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = xe;
	p->tri_y[p->tricount][0] = ys;
	p->tri_z[p->tricount][0] = zs;
	
	p->tri_x[p->tricount][1] = xe;
	p->tri_y[p->tricount][1] = ys;
	p->tri_z[p->tricount][1] = ze;
	
	p->tri_x[p->tricount][2] = xs;
	p->tri_y[p->tricount][2] = ys;
	p->tri_z[p->tricount][2] = ze;
	++p->tricount;

// Face 4	
	// Tri 3
	p->trivec_x[p->tricount] = 1.0;
	p->trivec_y[p->tricount] = 0.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = xe;
	p->tri_y[p->tricount][0] = ys;
	p->tri_z[p->tricount][0] = zs;
	
	p->tri_x[p->tricount][1] = xe;
	p->tri_y[p->tricount][1] = ys;
	p->tri_z[p->tricount][1] = ze;
	
	p->tri_x[p->tricount][2] = xe;
	p->tri_y[p->tricount][2] = ye;
	p->tri_z[p->tricount][2] = ze;
	++p->tricount;
	
	// Tri 4
	p->trivec_x[p->tricount] = 1.0;
	p->trivec_y[p->tricount] = 0.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = xe;
	p->tri_y[p->tricount][0] = ys;
	p->tri_z[p->tricount][0] = zs;
	
	p->tri_x[p->tricount][1] = xe;
	p->tri_y[p->tricount][1] = ye;
	p->tri_z[p->tricount][1] = zs;
	
	p->tri_x[p->tricount][2] = xe;
	p->tri_y[p->tricount][2] = ye;
	p->tri_z[p->tricount][2] = ze;
	++p->tricount;

// Face 2	
	// Tri 5
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = 1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = xe;
	p->tri_y[p->tricount][0] = ye;
	p->tri_z[p->tricount][0] = zs;
	
	p->tri_x[p->tricount][1] = xs;
	p->tri_y[p->tricount][1] = ye;
	p->tri_z[p->tricount][1] = ze;
	
	p->tri_x[p->tricount][2] = xs;
	p->tri_y[p->tricount][2] = ye;
	p->tri_z[p->tricount][2] = zs;
	++p->tricount;
	
	// Tri 6
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = 1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = xe;
	p->tri_y[p->tricount][0] = ye;
	p->tri_z[p->tricount][0] = zs;
	
	p->tri_x[p->tricount][1] = xe;
	p->tri_y[p->tricount][1] = ye;
	p->tri_z[p->tricount][1] = ze;
	
	p->tri_x[p->tricount][2] = xs;
	p->tri_y[p->tricount][2] = ye;
	p->tri_z[p->tricount][2] = ze;
	++p->tricount;

// Face 1	
	// Tri 7
	p->trivec_x[p->tricount] = -1.0;
	p->trivec_y[p->tricount] = 0.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = xs;
	p->tri_y[p->tricount][0] = ys;
	p->tri_z[p->tricount][0] = zs;
	
	p->tri_x[p->tricount][1] = xs;
	p->tri_y[p->tricount][1] = ys;
	p->tri_z[p->tricount][1] = ze;
	
	p->tri_x[p->tricount][2] = xs;
	p->tri_y[p->tricount][2] = ye;
	p->tri_z[p->tricount][2] = ze;
	++p->tricount;
	
	// Tri 8
	p->trivec_x[p->tricount] = -1.0;
	p->trivec_y[p->tricount] = 0.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = xs;
	p->tri_y[p->tricount][0] = ys;
	p->tri_z[p->tricount][0] = zs;
	
	p->tri_x[p->tricount][1] = xs;
	p->tri_y[p->tricount][1] = ye;
	p->tri_z[p->tricount][1] = zs;
	
	p->tri_x[p->tricount][2] = xs;
	p->tri_y[p->tricount][2] = ye;
	p->tri_z[p->tricount][2] = ze;
	++p->tricount;

// Face 5	
	// Tri 9
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = 0.0;
	p->trivec_z[p->tricount] = -1.0;
	
	p->tri_x[p->tricount][0] = xe;
	p->tri_y[p->tricount][0] = ys;
	p->tri_z[p->tricount][0] = zs;
	
	p->tri_x[p->tricount][1] = xs;
	p->tri_y[p->tricount][1] = ye;
	p->tri_z[p->tricount][1] = zs;
	
	p->tri_x[p->tricount][2] = xs;
	p->tri_y[p->tricount][2] = ys;
	p->tri_z[p->tricount][2] = zs;
	++p->tricount;
	
	// Tri 10
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = 0.0;
	p->trivec_z[p->tricount] = -1.0;
	
	p->tri_x[p->tricount][0] = xe;
	p->tri_y[p->tricount][0] = ys;
	p->tri_z[p->tricount][0] = zs;
	
	p->tri_x[p->tricount][1] = xe;
	p->tri_y[p->tricount][1] = ye;
	p->tri_z[p->tricount][1] = zs;
	
	p->tri_x[p->tricount][2] = xs;
	p->tri_y[p->tricount][2] = ye;
	p->tri_z[p->tricount][2] = zs;
	++p->tricount;
	
// Face 6
	// Tri 11
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = 0.0;
	p->trivec_z[p->tricount] = 1.0;
	
	p->tri_x[p->tricount][0] = xe;
	p->tri_y[p->tricount][0] = ys;
	p->tri_z[p->tricount][0] = ze;
	
	p->tri_x[p->tricount][1] = xs;
	p->tri_y[p->tricount][1] = ye;
	p->tri_z[p->tricount][1] = ze;
	
	p->tri_x[p->tricount][2] = xs;
	p->tri_y[p->tricount][2] = ys;
	p->tri_z[p->tricount][2] = ze;
	++p->tricount;
	
	// Tri 12
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = 0.0;
	p->trivec_z[p->tricount] = 1.0;
	
	p->tri_x[p->tricount][0] = xe;
	p->tri_y[p->tricount][0] = ys;
	p->tri_z[p->tricount][0] = ze;
	
	p->tri_x[p->tricount][1] = xe;
	p->tri_y[p->tricount][1] = ye;
	p->tri_z[p->tricount][1] = ze;
	
	p->tri_x[p->tricount][2] = xs;
	p->tri_y[p->tricount][2] = ye;
	p->tri_z[p->tricount][2] = ze;
	++p->tricount;
	
    te=p->tricount;


    xrot=xs;
	yrot=ys;
	zrot=zs;

    psi=c1;
    theta=b1;
    phi=a1;


    rotate_triangle(p,a,ts,te);

    xrot=p->S31_x;
	yrot=p->S31_y;
	zrot=p->S31_z;
	phi=(PI/180.0)*p->S31_phi;
	theta=(PI/180.0)*p->S31_theta;
	psi=(PI/180.0)*p->S31_psi;


    rotate_triangle(p,a,ts,te);

    xrot=p->S5_x;
	yrot=p->S5_y;
	zrot=p->S5_z;
	phi=(PI/180.0)*p->S5_phi;
	theta=(PI/180.0)*p->S5_theta;
	psi=(PI/180.0)*p->S5_psi;
    

}
