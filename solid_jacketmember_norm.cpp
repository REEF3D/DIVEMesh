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

#include"solid.h"
#include"lexer.h"
#include"dive.h"

void solid::jacket_member_norm(lexer *p, dive *a, int rank, int &ts, int &te )
{
    double U,ds,eta;
	double xm1,ym1,zm1,r1;
    double xm2,ym2,zm2,r2;
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

    dX = p->S37_xm2[rank]-p->S37_xm1[rank];
    dY = p->S37_ym2[rank]-p->S37_ym1[rank];
    dZ = p->S37_zm2[rank]-p->S37_zm1[rank];
      

    
    length = sqrt(dX*dX + dY*dY + dZ*dZ);
    
    xm1=p->S37_xm1[rank];
    ym1=p->S37_ym1[rank];
	zm1=p->S37_zm1[rank];
    r1=p->S37_r1[rank];
    
	xm2=p->S37_xm1[rank]+length;
    ym2=p->S37_ym1[rank];
	zm2=p->S37_zm1[rank];
    r2=p->S37_r2[rank];
    
    
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

    

	rmax = MAX(r1,r2);
	
	U = 2.0 * PI * rmax;
	
	ds = p->S19*(U*p->DXM);
	
	snum = int(U/ds);
	
	//ds = U/double(snum);

// Vertices	
	ds = (2.0*PI)/double(snum);
	
	eta=0.0;
	
	ts=p->tricount;
	
	for(n=0;n<snum;++n)
	{
	//bottom circle
	p->trivec_x[p->tricount] = -1.0;
	p->trivec_y[p->tricount] = 0.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = xm1;
	p->tri_y[p->tricount][0] = ym1;
	p->tri_z[p->tricount][0] = zm1;
	
	p->tri_x[p->tricount][1] = xm1;
	p->tri_y[p->tricount][1] = ym1 + r1*sin(eta);
	p->tri_z[p->tricount][1] = zm1 + r1*cos(eta);
	
	p->tri_x[p->tricount][2] = xm1;
	p->tri_y[p->tricount][2] = ym1 + r1*sin(eta+ds);
	p->tri_z[p->tricount][2] = zm1 + r1*cos(eta+ds);
	++p->tricount;
		
	//top circle
	p->trivec_x[p->tricount] = 1.0;
	p->trivec_y[p->tricount] = 0.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = xm2;
	p->tri_y[p->tricount][0] = ym2;
	p->tri_z[p->tricount][0] = zm2;
	
	p->tri_x[p->tricount][1] = xm2;
	p->tri_y[p->tricount][1] = ym2 + r2*sin(eta);
	p->tri_z[p->tricount][1] = zm2 + r2*cos(eta);
	
	p->tri_x[p->tricount][2] = xm2;
	p->tri_y[p->tricount][2] = ym2 + r2*sin(eta+ds);
	p->tri_z[p->tricount][2] = zm2 + r2*cos(eta+ds);
	++p->tricount;
	
	//side		
	// 1st triangle
	p->tri_x[p->tricount][0] = xm1;
	p->tri_y[p->tricount][0] = ym1 + r1*sin(eta);
	p->tri_z[p->tricount][0] = zm1 + r1*cos(eta);
	
	p->tri_x[p->tricount][1] = xm2;
	p->tri_y[p->tricount][1] = ym2 + r2*sin(eta+ds);
	p->tri_z[p->tricount][1] = zm2 + r2*cos(eta+ds);
	
	p->tri_x[p->tricount][2] = xm1;
	p->tri_y[p->tricount][2] = ym1 + r1*sin(eta+ds);
	p->tri_z[p->tricount][2] = zm1 + r1*cos(eta+ds);
	
	Ax = p->tri_x[p->tricount][0]-p->tri_x[p->tricount][2];
	Ay = p->tri_y[p->tricount][0]-p->tri_x[p->tricount][2];
	Az = p->tri_z[p->tricount][0]-p->tri_x[p->tricount][2];
		
	Bx = p->tri_x[p->tricount][1]-p->tri_x[p->tricount][2];
	By = p->tri_y[p->tricount][1]-p->tri_x[p->tricount][2];
	Bz = p->tri_z[p->tricount][1]-p->tri_x[p->tricount][2];
		
	Nx = Ay*Bz - Az*By;
	Ny = Az*Bx - Ax*Bz;
	Nz = Ax*By - Ay*Bx;
	
	norm = sqrt(Nx*Nx + Ny*Ny + Nz*Nz);
	
	p->trivec_x[p->tricount] = Nx/norm;
	p->trivec_y[p->tricount] = Ny/norm;
	p->trivec_z[p->tricount] = Nz/norm;
	
	++p->tricount;
	
	// 2nd triangle
	p->tri_x[p->tricount][0] = xm1;
	p->tri_y[p->tricount][0] = ym1 + r1*sin(eta);
	p->tri_z[p->tricount][0] = zm1 + r1*cos(eta);
	
	p->tri_x[p->tricount][1] = xm2;
	p->tri_y[p->tricount][1] = ym2 + r2*sin(eta+ds);
	p->tri_z[p->tricount][1] = zm2 + r2*cos(eta+ds);
	
	p->tri_x[p->tricount][2] = xm2;
	p->tri_y[p->tricount][2] = ym2 + r2*sin(eta);
	p->tri_z[p->tricount][2] = zm2 + r2*cos(eta);
		
	p->trivec_x[p->tricount] = Nx/norm;
	p->trivec_y[p->tricount] = Ny/norm;
	p->trivec_z[p->tricount] = Nz/norm;
	
	
	++p->tricount;
		
	eta+=ds;
	}
    te=p->tricount;
    
    
    xrot=xm1;
	yrot=ym1;
	zrot=zm1;

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
