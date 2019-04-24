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

#include"lexer.h"

void lexer::solid_preproc()
{
	double r1,r2,rmax,U,ds;
	int snum;
	
	trinum=0;
	tricount=0;
	
	for(n=0;n<S10;++n)
	trinum+=12;
	
	for(n=0;n<S11;++n)
	trinum+=12*S11_ni[n]*S11_nj[n]*S11_nj[n];
    
    for(n=0; n<S32;++n)
	{
	rmax = S32_r[n];
	
	U = 2.0 * PI * rmax;
	
	ds = S19*(U*DXM);
	
	snum = int(U/ds);
	
	trinum+=6*snum;
	}
	
	for(n=0; n<S33;++n)
	{
	rmax = S33_r[n];
	
	U = 2.0 * PI * rmax;
	
	ds = S19*(U*DXM);
	
	snum = int(U/ds);
	
    cout<<"SNUM: "<<snum<<endl;
	trinum+=6*snum;
	}
    
    for(n=0; n<S34;++n)
	{
	r1=S34_r1[n];
	r2=S34_r2[n];    
	
	rmax = MAX(r1,r2);
	
	U = 2.0 * PI * rmax;
	
	ds = S19*(U*DXM);
	
	snum = int(U/ds);
	
	trinum+=6*snum;
	}
    
    for(n=0; n<S35;++n)
	{
	r1=S35_r1[n];
	r2=S35_r2[n];    
	
	rmax = MAX(r1,r2);
	
	U = 2.0 * PI * rmax;
	
	ds = S19*(U*DXM);
	
	snum = int(U/ds);
	
	trinum+=6*snum;
	}
    
    for(n=0; n<S36;++n)
	{
	r1=S36_r1[n];
	r2=S36_r2[n];    
	
	rmax = MAX(r1,r2);
	
	U = 2.0 * PI * rmax;
	
	ds = S19*(U*DXM);
	
	snum = int(U/ds);
	
	trinum+=6*snum;
	}
    
    for(n=0; n<S37;++n)
	{
	r1=S37_r1[n];
	r2=S37_r2[n];    
	
	rmax = MAX(r1,r2);
	
	U = 2.0 * PI * rmax;
	
	ds = S19*(U*DXM);
	
	snum = int(U/ds);
	
	trinum+=6*snum;
	}
    
    for(n=0; n<S38;++n)
	{
	r1=S38_r1[n];
	r2=S38_r2[n];    
	
	rmax = MAX(r1,r2);
	
	U = 2.0 * PI * rmax;
	
	ds = S19*(U*DXM);
	
	snum = int(U/ds);
	
	trinum+=6*snum;
	}
	
	for(n=0; n<S41;++n)
	{
	r1=S41_r1[n];
	r2=S41_r2[n];    
	
	rmax = MAX(r1,r2);
	
	U = 2.0 * PI * rmax;
	
	ds = S19*(U*DXM);
	
	snum = int(U/ds);
	
	trinum+=6*snum;
	}
	
	for(n=0; n<S42;++n)
	{
	r1=S42_r1[n];
	r2=S42_r2[n];    
	
	rmax = MAX(r1,r2);
	
	U = 2.0 * PI * rmax;
	
	ds = S19*(U*DXM);
	
	snum = int(U/ds);
	
	trinum+=6*snum;
	}
	
	for(n=0; n<S43;++n)
	{
	r1=S43_r1[n];
	r2=S43_r2[n];    
	
	rmax = MAX(r1,r2);
	
	U = 2.0 * PI * rmax;
	
	ds = S19*(U*DXM);
	
	snum = int(U/ds);
	
	trinum+=6*snum;
	}
    
    for(n=0; n<S51;++n)
    {
	double rmax = S51_r[n];
	
	U = 2.0 * PI * rmax;
	
	ds = S19*(U*DXM);
	
	snum = int(U/ds);
    
    trinum+=snum*snum*2;
    }
    
    for(n=0; n<S52;++n)
    {
    double ra=S52_a[n];
	double rb=S52_b[n];    
    double rc=S52_c[n];    
	
	double rmax = MAX3(ra,rb,rc);
	
	U = 2.0 * PI * rmax;
	
	ds = S19*(U*DXM);
	
	snum = int(U/ds);
    
    trinum+=snum*snum*2;
    }
    
    for(n=0; n<S53;++n)
    {
    double ra=S53_a[n];
	double rb=S53_b[n];    
    double rc=S53_c[n];    
	
	double rmax = MAX3(ra,rb,rc);
	
	U = 2.0 * PI * rmax;
	
	ds = S19*(U*DXM);
	
	snum = int(U/ds);
    
    trinum+=snum*snum*2;
    }
    
    for(n=0; n<S54;++n)
    {
    double ra=S54_a[n];
	double rb=S54_b[n];    
    double rc=S54_c[n];    
	
	double rmax = MAX3(ra,rb,rc);
	
	U = 2.0 * PI * rmax;
	
	ds = S19*(U*DXM);
	
	snum = int(U/ds);
    
    trinum+=snum*snum*2;
    }
	
	for(n=0;n<S61;++n)
	trinum+=10;
	
	for(n=0;n<S62;++n)
	trinum+=10;
	
	for(n=0;n<S63;++n)
	trinum+=10;
    
    for(n=0;n<S81;++n)
	trinum+=4;
    
    for(n=0;n<S82;++n)
	trinum+=6;
    
    for(n=0;n<S83;++n)
	trinum+=8;
    
    for(n=0;n<S84;++n)
	trinum+=12;
	
	for(n=0;n<S121;++n)
	trinum+=966;
    
    for(n=0;n<S201;++n)
	trinum+=12;
    
    for(n=0;n<S202;++n)
	trinum+=12;
    
    for(n=0;n<S203;++n)
	trinum+=12;
	
	for(n=0; n<S131;++n)
	{
	r1=S131_r1[n];
	r2=S131_r2[n];    
	
	rmax = MAX(r1,r2);
	
	U = 2.0 * PI * rmax;
	
	ds = S19*(U*DXM);
	
	snum = int(U/ds);
	
	trinum+=6*snum;
	}
	
	for(n=0;n<S141;++n)
	trinum+=10966;
    
    if(S300>0)
    {
        double length=0.0;
        int ds_count=0;
            
        for(n=0;n<S310;++n)
        {
        ds_count+=1;
        S300_ds += 1;
        }
        
        for(n=0;n<S320;++n)
        {
        S320_phi[n] = S320_phi[n]*PI/180.0;
        length = (S320_r[n])*S320_phi[n];
        ds_count = int(length/(S305*DXM));
        
        S300_ds += ds_count;
        }

        for(n=0;n<S330;++n)
        {
        S330_phi[n] = S330_phi[n]*PI/180.0;
        length = (S330_r[n])*S330_phi[n];  
        ds_count = int(length/(S305*DXM));  
        
        S300_ds += ds_count;
        }
        
        for(n=0;n<S340;++n)
        {
        S340_teta[n] = S340_teta[n]*PI/180.0;
        ds_count = int((S340_L[n]*S340_N[n])/(S305*DXM));  
        
        S300_ds += ds_count;
        }
    
    
    S300_ds +=1;
    trinum+=16*S300_ds;
    
    cout<<"fluvial box dsnum_ini: "<<S300_ds<<" trinum: "<<trinum<<endl;
    }
    
	
	if(S1==0)
	{
	// create arrays
	Darray(tri_x,trinum,3);
	Darray(tri_y,trinum,3);
	Darray(tri_z,trinum,3);
	
	Darray(trivec_x,trinum);
	Darray(trivec_y,trinum);
	Darray(trivec_z,trinum);
	}
	
}

