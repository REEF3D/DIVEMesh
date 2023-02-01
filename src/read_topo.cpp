/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2023 Hans Bihs

This file is part of DIVEMesh.

DIVEMesh is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by
the Free Toftware Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNETT FOR A PARTICULAR PURPOTE. Tee the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, see <http://www.gnu.org/licenses/>.
--------------------------------------------------------------------
Author: Hans Bihs
--------------------------------------------------------------------*/

#include"lexer.h"

void lexer::topo_preproc()
{
	double r1,r2,rmax,U,ds;
	int snum;
	
	for(n=0;n<T10;++n)
	trinum_topo+=12;
	
	for(n=0;n<T11;++n)
	trinum_topo+=12*T11_ni[n]*T11_nj[n]*T11_nj[n];
    
    for(n=0; n<T32;++n)
	{
	rmax = T32_r[n];
	
	U = 2.0 * PI * rmax;
	
	ds = T19*(U*DXM);
	
	snum = int(U/ds);
	
	trinum_topo+=6*snum;
	}
	
	for(n=0; n<T33;++n)
	{
	rmax = T33_r[n];
	
	U = 2.0 * PI * rmax;
	
	ds = T19*(U*DXM);
	
	snum = int(U/ds);
	
    cout<<"TNUM: "<<snum<<endl;
	trinum_topo+=6*snum;
	}
    
    for(n=0; n<T37;++n)
	{
	r1=T37_r1[n];
	r2=T37_r2[n];    
	
	rmax = MAX(r1,r2);
	
	U = 2.0 * PI * rmax;
	
	ds = T19*(U*DXM);
	
	snum = int(U/ds);
	
	trinum_topo+=6*snum;
	}
	
	for(n=0; n<T41;++n)
	{
	r1=T41_r1[n];
	r2=T41_r2[n];    
	
	rmax = MAX(r1,r2);
	
	U = 2.0 * PI * rmax;
	
	ds = T19*(U*DXM);
	
	snum = int(U/ds);
	
	trinum_topo+=6*snum;
	}
	
	for(n=0; n<T42;++n)
	{
	r1=T42_r1[n];
	r2=T42_r2[n];    
	
	rmax = MAX(r1,r2);
	
	U = 2.0 * PI * rmax;
	
	ds = T19*(U*DXM);
	
	snum = int(U/ds);
	
	trinum_topo+=6*snum;
	}
	
	for(n=0; n<T43;++n)
	{
	r1=T43_r1[n];
	r2=T43_r2[n];    
	
	rmax = MAX(r1,r2);
	
	U = 2.0 * PI * rmax;
	
	ds = T19*(U*DXM);
	
	snum = int(U/ds);
	
	trinum_topo+=6*snum;
	}
    
    for(n=0; n<T51;++n)
    {
	double rmax = T51_r[n];
	
	U = 2.0 * PI * rmax;
	
	ds = T19*(U*DXM);
	
	snum = int(U/ds);
    
    trinum_topo+=snum*snum*2;
    }
    
    for(n=0; n<T52;++n)
    {
    double ra=T52_a[n];
	double rb=T52_b[n];    
    double rc=T52_c[n];    
	
	double rmax = MAX3(ra,rb,rc);
	
	U = 2.0 * PI * rmax;
	
	ds = T19*(U*DXM);
	
	snum = int(U/ds);
    
    trinum_topo+=snum*snum*2;
    }
    
    for(n=0; n<T53;++n)
    {
    double ra=T53_a[n];
	double rb=T53_b[n];    
    double rc=T53_c[n];    
	
	double rmax = MAX3(ra,rb,rc);
	
	U = 2.0 * PI * rmax;
	
	ds = T19*(U*DXM);
	
	snum = int(U/ds);
    
    trinum_topo+=snum*snum*2;
    }
    
    for(n=0; n<T54;++n)
    {
    double ra=T54_a[n];
	double rb=T54_b[n];    
    double rc=T54_c[n];    
	
	double rmax = MAX3(ra,rb,rc);
	
	U = 2.0 * PI * rmax;
	
	ds = T19*(U*DXM);
	
	snum = int(U/ds);
    
    trinum_topo+=snum*snum*2;
    }
	
	for(n=0;n<T61;++n)
	trinum_topo+=10;
	
	for(n=0;n<T62;++n)
	trinum_topo+=10;
	
	for(n=0;n<T63;++n)
	trinum_topo+=10;
    
    for(n=0;n<T81;++n)
	trinum_topo+=4;
    
    for(n=0;n<T82;++n)
	trinum_topo+=6;
    
    for(n=0;n<T83;++n)
	trinum_topo+=8;
    
    for(n=0;n<T84;++n)
	trinum_topo+=12;
	
	for(n=0;n<T121;++n)
	trinum_topo+=966;
    
    for(n=0;n<T201;++n)
	trinum_topo+=12;
    
    for(n=0;n<T202;++n)
	trinum_topo+=12;
    
    for(n=0;n<T203;++n)
	trinum_topo+=12;
	
	for(n=0; n<T131;++n)
	{
	r1=T131_r1[n];
	r2=T131_r2[n];    
	
	rmax = MAX(r1,r2);
	
	U = 2.0 * PI * rmax;
	
	ds = T19*(U*DXM);
	
	snum = int(U/ds);
	
	trinum_topo+=6*snum;
	}
	
	for(n=0;n<T141;++n)
	trinum_topo+=10966;
    
    if(T300>0)
    {
        double length=0.0;
        int ds_count=0;
            
        for(n=0;n<T310;++n)
        {
        ds_count+=1;
        T300_ds += 1;
        }
        
        for(n=0;n<T320;++n)
        {
        T320_phi[n] = T320_phi[n]*PI/180.0;
        length = (T320_r[n])*T320_phi[n];
        ds_count = int(length/(T305*DXM));
        
        T300_ds += ds_count;
        }

        for(n=0;n<T330;++n)
        {
        T330_phi[n] = T330_phi[n]*PI/180.0;
        length = (T330_r[n])*T330_phi[n];  
        ds_count = int(length/(T305*DXM));  
        
        T300_ds += ds_count;
        }
        
        for(n=0;n<T340;++n)
        {
        T340_teta[n] = T340_teta[n]*PI/180.0;
        ds_count = int((T340_L[n]*T340_N[n])/(T305*DXM));  
        
        T300_ds += ds_count;
        }
    
    
    T300_ds +=1;
    trinum_topo+=16*T300_ds;
    
    cout<<"fluvial box dsnum_ini: "<<T300_ds<<" trinum_topo: "<<trinum_topo<<endl;
    }
}

