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
--------------------------------------------------------------------*/

#include"solid.h"
#include"dive.h"
#include"lexer.h"


void solid::arch(lexer* p, dive* a, int rank, int &ts, int &te)
{	
	ts=p->tricount;
	
	
	double r,ym,Um,dy,dz,ds,phi,ycorr,zcorr;
    int Nr,N3,Ndiff;
    int N3_1,N3_2,N3_3;
    
	xs = p->S141_xs[rank];
    xe = p->S141_xe[rank];

    ys = p->S141_ys[rank];
    ye = p->S141_ye[rank];

    zs = p->S141_zs[rank];
    ze = p->S141_ze[rank]; 

    r = p->S141_r[rank]; 
    
    ym = 0.5*(ye-ys)+ys;
    Um = PI*r;
    Nr = 2*int(Um/(p->DXM));
    N3 = int(Nr/3);
    Ndiff = Nr - 3*N3;
    
    N3_1=N3_2=N3_3 = N3;
    
    if(fabs(Ndiff)==1)
    N3_3 += Ndiff;
    
    if(fabs(Ndiff)==2)
    {
    N3_2 += Ndiff/fabs(Ndiff);
    N3_3 += Ndiff/fabs(Ndiff);
    }
    
    if(fabs(Ndiff)==3)
    {
    N3_1 += Ndiff/fabs(Ndiff);
    N3_2 += Ndiff/fabs(Ndiff);
    N3_3 += Ndiff/fabs(Ndiff);
    }
	
    ds = (PI)/double(Nr);
    phi=0.0;
	dy = (ye-ys)/double(N3_2);
    dz = (ze-zs)/double(N3_1);
	
	
	cout<<"ARCH: "<<N3_1<<endl;
	

// Bottom plate right
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = xs;
	p->tri_y[p->tricount][0] = ys;
	p->tri_z[p->tricount][0] = zs;
	
	p->tri_x[p->tricount][1] = xe;
	p->tri_y[p->tricount][1] = ys;
	p->tri_z[p->tricount][1] = zs;
	
	p->tri_x[p->tricount][2] = xe;
	p->tri_y[p->tricount][2] = ym-r;
	p->tri_z[p->tricount][2] = zs;
	++p->tricount;
	
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = xs;
	p->tri_y[p->tricount][0] = ys;
	p->tri_z[p->tricount][0] = zs;
	
	p->tri_x[p->tricount][1] = xs;
	p->tri_y[p->tricount][1] = ym-r;
	p->tri_z[p->tricount][1] = zs;
	
	p->tri_x[p->tricount][2] = xe;
	p->tri_y[p->tricount][2] = ym-r;
	p->tri_z[p->tricount][2] = zs;
	++p->tricount;
	
// Bottom plate left
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = xs;
	p->tri_y[p->tricount][0] = ye;
	p->tri_z[p->tricount][0] = zs;
	
	p->tri_x[p->tricount][1] = xe;
	p->tri_y[p->tricount][1] = ye;
	p->tri_z[p->tricount][1] = zs;
	
	p->tri_x[p->tricount][2] = xe;
	p->tri_y[p->tricount][2] = ym+r;
	p->tri_z[p->tricount][2] = zs;
	++p->tricount;
	
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = xs;
	p->tri_y[p->tricount][0] = ye;
	p->tri_z[p->tricount][0] = zs;
	
	p->tri_x[p->tricount][1] = xs;
	p->tri_y[p->tricount][1] = ym+r;
	p->tri_z[p->tricount][1] = zs;
	
	p->tri_x[p->tricount][2] = xe;
	p->tri_y[p->tricount][2] = ym+r;
	p->tri_z[p->tricount][2] = zs;
	++p->tricount;
	
	// Top plate
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = xs;
	p->tri_y[p->tricount][0] = ys;
	p->tri_z[p->tricount][0] = ze;
	
	p->tri_x[p->tricount][1] = xe;
	p->tri_y[p->tricount][1] = ys;
	p->tri_z[p->tricount][1] = ze;
	
	p->tri_x[p->tricount][2] = xe;
	p->tri_y[p->tricount][2] = ye;
	p->tri_z[p->tricount][2] = ze;
	++p->tricount;
	
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = xs;
	p->tri_y[p->tricount][0] = ys;
	p->tri_z[p->tricount][0] = ze;
	
	p->tri_x[p->tricount][1] = xs;
	p->tri_y[p->tricount][1] = ye;
	p->tri_z[p->tricount][1] = ze;
	
	p->tri_x[p->tricount][2] = xe;
	p->tri_y[p->tricount][2] = ye;
	p->tri_z[p->tricount][2] = ze;
	++p->tricount;
	
// ---------------------------------------------------------------
// Left arch
// ---------------------------------------------------------------

    for(int qn=0;qn<N3_1;++qn)
    {
    zcorr = zs + dz*double(qn); 
    
    phi = PI-ds*double(qn);
	
	//cout<<zcorr<<" "<<phi<<endl;
    
    //back 1
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = xs;
	p->tri_y[p->tricount][0] = ys;
	p->tri_z[p->tricount][0] = zcorr;
	
	p->tri_x[p->tricount][1] = xs;
	p->tri_y[p->tricount][1] = ys;
	p->tri_z[p->tricount][1] = zcorr + dz;
	
	p->tri_x[p->tricount][2] = xs;
	p->tri_y[p->tricount][2] = ym + r*cos(phi);
	p->tri_z[p->tricount][2] = zs + r*sin(phi);
	++p->tricount;
    
    //back 2
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = xs;
	p->tri_y[p->tricount][0] = ys;
	p->tri_z[p->tricount][0] = zcorr + dz;
	
	p->tri_x[p->tricount][1] = xs;
	p->tri_y[p->tricount][1] = ym + r*cos(phi-ds);
	p->tri_z[p->tricount][1] = zs + r*sin(phi-ds);
	
	p->tri_x[p->tricount][2] = xs;
	p->tri_y[p->tricount][2] = ym + r*cos(phi);
	p->tri_z[p->tricount][2] = zs + r*sin(phi);
	++p->tricount;
    
    //front 1
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = xe;
	p->tri_y[p->tricount][0] = ys;
	p->tri_z[p->tricount][0] = zcorr;
	
	p->tri_x[p->tricount][1] = xe;
	p->tri_y[p->tricount][1] = ys;
	p->tri_z[p->tricount][1] = zcorr + dz;
	
	p->tri_x[p->tricount][2] = xe;
	p->tri_y[p->tricount][2] = ym + r*cos(phi);
	p->tri_z[p->tricount][2] = zs + r*sin(phi);
	++p->tricount;
    
    //front 2
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = xe;
	p->tri_y[p->tricount][0] = ys;
	p->tri_z[p->tricount][0] = zcorr + dz;
	
	p->tri_x[p->tricount][1] = xe;
	p->tri_y[p->tricount][1] = ym + r*cos(phi-ds);
	p->tri_z[p->tricount][1] = zs + r*sin(phi-ds);
	
	p->tri_x[p->tricount][2] = xe;
	p->tri_y[p->tricount][2] = ym + r*cos(phi);
	p->tri_z[p->tricount][2] = zs + r*sin(phi);
	++p->tricount;
    
    //inside 1
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = xs;
	p->tri_y[p->tricount][0] = ym + r*cos(phi);
	p->tri_z[p->tricount][0] = zs + r*sin(phi);
	
	p->tri_x[p->tricount][1] = xe;
	p->tri_y[p->tricount][1] = ym + r*cos(phi-ds);
	p->tri_z[p->tricount][1] = zs + r*sin(phi-ds);
	
	p->tri_x[p->tricount][2] = xe;
	p->tri_y[p->tricount][2] = ym + r*cos(phi);
	p->tri_z[p->tricount][2] = zs + r*sin(phi);
	++p->tricount;
    
    //inside 2
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = xs;
	p->tri_y[p->tricount][0] = ym + r*cos(phi);
	p->tri_z[p->tricount][0] = zs + r*sin(phi);
	
	p->tri_x[p->tricount][1] = xs;
	p->tri_y[p->tricount][1] = ym + r*cos(phi-ds);
	p->tri_z[p->tricount][1] = zs + r*sin(phi-ds);
	
	p->tri_x[p->tricount][2] = xe;
	p->tri_y[p->tricount][2] = ym + r*cos(phi-ds);
	p->tri_z[p->tricount][2] = zs + r*sin(phi-ds);
	++p->tricount;
    
    //outside 1
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = xs;
	p->tri_y[p->tricount][0] = ys;
	p->tri_z[p->tricount][0] = zcorr;
	
	p->tri_x[p->tricount][1] = xe;
	p->tri_y[p->tricount][1] = ys;
	p->tri_z[p->tricount][1] = zcorr;
	
	p->tri_x[p->tricount][2] = xe;
	p->tri_y[p->tricount][2] = ys;
	p->tri_z[p->tricount][2] = zcorr + dz;
	++p->tricount;
    
    //outside 2
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = xs;
	p->tri_y[p->tricount][0] = ys;
	p->tri_z[p->tricount][0] = zcorr;
	
	p->tri_x[p->tricount][1] = xs;
	p->tri_y[p->tricount][1] = ys;
	p->tri_z[p->tricount][1] = zcorr + dz;
	
	p->tri_x[p->tricount][2] = xe;
	p->tri_y[p->tricount][2] = ys;
	p->tri_z[p->tricount][2] = zcorr + dz;
	++p->tricount;
    }
    
	
// ---------------------------------------------------------------
// Middle Arch
// ---------------------------------------------------------------

    for(int qn=0;qn<N3_2;++qn)
    {
    ycorr = ys + dy*double(qn); 
    
    phi = PI-ds*double(qn+N3_1);
	
    
    //back 1
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = xs;
	p->tri_y[p->tricount][0] = ycorr;
	p->tri_z[p->tricount][0] = ze;
	
	p->tri_x[p->tricount][1] = xs;
	p->tri_y[p->tricount][1] = ycorr + dy;
	p->tri_z[p->tricount][1] = ze;
	
	p->tri_x[p->tricount][2] = xs;
	p->tri_y[p->tricount][2] = ym + r*cos(phi);
	p->tri_z[p->tricount][2] = zs + r*sin(phi);
	++p->tricount;
    
    //back 2
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = xs;
	p->tri_y[p->tricount][0] = ycorr + dy;
	p->tri_z[p->tricount][0] = ze;
	
	p->tri_x[p->tricount][1] = xs;
	p->tri_y[p->tricount][1] = ym + r*cos(phi-ds);
	p->tri_z[p->tricount][1] = zs + r*sin(phi-ds);
	
	p->tri_x[p->tricount][2] = xs;
	p->tri_y[p->tricount][2] = ym + r*cos(phi);
	p->tri_z[p->tricount][2] = zs + r*sin(phi);
	++p->tricount;
    
	//front 1
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = xe;
	p->tri_y[p->tricount][0] = ycorr;
	p->tri_z[p->tricount][0] = ze;
	
	p->tri_x[p->tricount][1] = xe;
	p->tri_y[p->tricount][1] = ycorr + dy;
	p->tri_z[p->tricount][1] = ze;
	
	p->tri_x[p->tricount][2] = xe;
	p->tri_y[p->tricount][2] = ym + r*cos(phi);
	p->tri_z[p->tricount][2] = zs + r*sin(phi);
	++p->tricount;
    
    //front 2
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = xe;
	p->tri_y[p->tricount][0] = ycorr + dy;
	p->tri_z[p->tricount][0] = ze;
	
	p->tri_x[p->tricount][1] = xe;
	p->tri_y[p->tricount][1] = ym + r*cos(phi-ds);
	p->tri_z[p->tricount][1] = zs + r*sin(phi-ds);
	
	p->tri_x[p->tricount][2] = xe;
	p->tri_y[p->tricount][2] = ym + r*cos(phi);
	p->tri_z[p->tricount][2] = zs + r*sin(phi);
	++p->tricount;
    
    //inside 1
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = xs;
	p->tri_y[p->tricount][0] = ym + r*cos(phi);
	p->tri_z[p->tricount][0] = zs + r*sin(phi);
	
	p->tri_x[p->tricount][1] = xe;
	p->tri_y[p->tricount][1] = ym + r*cos(phi-ds);
	p->tri_z[p->tricount][1] = zs + r*sin(phi-ds);
	
	p->tri_x[p->tricount][2] = xe;
	p->tri_y[p->tricount][2] = ym + r*cos(phi);
	p->tri_z[p->tricount][2] = zs + r*sin(phi);
	++p->tricount;
    
    //inside 2
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = xs;
	p->tri_y[p->tricount][0] = ym + r*cos(phi);
	p->tri_z[p->tricount][0] = zs + r*sin(phi);
	
	p->tri_x[p->tricount][1] = xs;
	p->tri_y[p->tricount][1] = ym + r*cos(phi-ds);
	p->tri_z[p->tricount][1] = zs + r*sin(phi-ds);
	
	p->tri_x[p->tricount][2] = xe;
	p->tri_y[p->tricount][2] = ym + r*cos(phi-ds);
	p->tri_z[p->tricount][2] = zs + r*sin(phi-ds);
	++p->tricount;
    }
	
	
// ---------------------------------------------------------------
// Right arch
// ---------------------------------------------------------------
	
	dz = (ze-zs)/double(N3_3);
	
    for(int qn=0;qn<N3_3;++qn)
    {
    zcorr = ze - dz*double(qn); 
    
    phi = PI-ds*double(qn+N3_1+N3_2);
	
	//cout<<zcorr<<" "<<phi<<endl;
    
    //back 1
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = xs;
	p->tri_y[p->tricount][0] = ye;
	p->tri_z[p->tricount][0] = zcorr - dz;
	
	p->tri_x[p->tricount][1] = xs;
	p->tri_y[p->tricount][1] = ye;
	p->tri_z[p->tricount][1] = zcorr;
	
	p->tri_x[p->tricount][2] = xs;
	p->tri_y[p->tricount][2] = ym + r*cos(phi-ds);
	p->tri_z[p->tricount][2] = zs + r*sin(phi-ds);
	++p->tricount;
    
    //back 2
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = xs;
	p->tri_y[p->tricount][0] = ye;
	p->tri_z[p->tricount][0] = zcorr;
	
	p->tri_x[p->tricount][1] = xs;
	p->tri_y[p->tricount][1] = ym + r*cos(phi);
	p->tri_z[p->tricount][1] = zs + r*sin(phi);
	
	p->tri_x[p->tricount][2] = xs;
	p->tri_y[p->tricount][2] = ym + r*cos(phi-ds);
	p->tri_z[p->tricount][2] = zs + r*sin(phi-ds);
	++p->tricount;
    
    //front 1
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = xe;
	p->tri_y[p->tricount][0] = ye;
	p->tri_z[p->tricount][0] = zcorr - dz;
	
	p->tri_x[p->tricount][1] = xe;
	p->tri_y[p->tricount][1] = ye;
	p->tri_z[p->tricount][1] = zcorr;
	
	p->tri_x[p->tricount][2] = xe;
	p->tri_y[p->tricount][2] = ym + r*cos(phi-ds);
	p->tri_z[p->tricount][2] = zs + r*sin(phi-ds);
	++p->tricount;
    
    //front 2
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = xe;
	p->tri_y[p->tricount][0] = ye;
	p->tri_z[p->tricount][0] = zcorr;
	
	p->tri_x[p->tricount][1] = xe;
	p->tri_y[p->tricount][1] = ym + r*cos(phi);
	p->tri_z[p->tricount][1] = zs + r*sin(phi);
	
	p->tri_x[p->tricount][2] = xe;
	p->tri_y[p->tricount][2] = ym + r*cos(phi-ds);
	p->tri_z[p->tricount][2] = zs + r*sin(phi-ds);
	++p->tricount;
    
    //inside 1
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = xs;
	p->tri_y[p->tricount][0] = ym + r*cos(phi);
	p->tri_z[p->tricount][0] = zs + r*sin(phi);
	
	p->tri_x[p->tricount][1] = xe;
	p->tri_y[p->tricount][1] = ym + r*cos(phi-ds);
	p->tri_z[p->tricount][1] = zs + r*sin(phi-ds);
	
	p->tri_x[p->tricount][2] = xe;
	p->tri_y[p->tricount][2] = ym + r*cos(phi);
	p->tri_z[p->tricount][2] = zs + r*sin(phi);
	++p->tricount;
    
    //inside 2
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = xs;
	p->tri_y[p->tricount][0] = ym + r*cos(phi);
	p->tri_z[p->tricount][0] = zs + r*sin(phi);
	
	p->tri_x[p->tricount][1] = xs;
	p->tri_y[p->tricount][1] = ym + r*cos(phi-ds);
	p->tri_z[p->tricount][1] = zs + r*sin(phi-ds);
	
	p->tri_x[p->tricount][2] = xe;
	p->tri_y[p->tricount][2] = ym + r*cos(phi-ds);
	p->tri_z[p->tricount][2] = zs + r*sin(phi-ds);
	++p->tricount;
    
    //outside 1
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = xs;
	p->tri_y[p->tricount][0] = ye;
	p->tri_z[p->tricount][0] = zcorr - dz;
	
	p->tri_x[p->tricount][1] = xe;
	p->tri_y[p->tricount][1] = ye;
	p->tri_z[p->tricount][1] = zcorr - dz;
	
	p->tri_x[p->tricount][2] = xe;
	p->tri_y[p->tricount][2] = ye;
	p->tri_z[p->tricount][2] = zcorr;
	++p->tricount;
    
    //outside 2
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = xs;
	p->tri_y[p->tricount][0] = ye;
	p->tri_z[p->tricount][0] = zcorr - dz;
	
	p->tri_x[p->tricount][1] = xs;
	p->tri_y[p->tricount][1] = ye;
	p->tri_z[p->tricount][1] = zcorr;
	
	p->tri_x[p->tricount][2] = xe;
	p->tri_y[p->tricount][2] = ye;
	p->tri_z[p->tricount][2] = zcorr;
	++p->tricount;
    }




	te=p->tricount;
}

