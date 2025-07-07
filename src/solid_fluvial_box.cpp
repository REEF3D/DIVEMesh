/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2025 Hans Bihs

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

#include"solid.h"
#include"dive.h"
#include"lexer.h"

void solid::fluvial_box(lexer *p, dive *a, int rank, int &ts, int &te)
{
    // 307 depth
    // 308 origin xy
    // 309 min. left and right margins
    
    // 310 straight
    // 320 left bend
    // 330 right bend
    
    /*
    1. read, order decides 
    2. two lines define: left and right bank
    3. for fluvial box xs,xe,ys,ye: add margin
    4. fill bank curves:
        a. go along x-axis, fill yl or yr coordinates
        b. 
    
    */
    fluvial_box_parameterfill(p,a);
     
    cout<<"fluvial box start"<<endl;
    
    countds=1;
    numds=0;
    x0=0.0; // add origin afterwards
    y0=0.0; // add origin
    xe=x0;
    ye=y0;
    phi0 = 0.0;
    
    // FILL SEGMENTS
    fluvial_box_fill_segments(p, a, rank, ts, te);
    
    // BOX MOVE
    fluvial_box_move(p,a);
    
    // BOX EXTEND AND MARGINS
    fluvial_box_extend(p,a);
    
    // FLUVIAL BOX V1
    if(p->S301==1)
    fluvial_box_v1(p,a,rank,ts,te);
    
    // FLUVIAL BOX V2
    if(p->S301==2)
    fluvial_box_v2(p,a,rank,ts,te);
    
    p->del_Darray(xl,p->S300_ds);
    p->del_Darray(yl,p->S300_ds);
    p->del_Darray(xr,p->S300_ds);
    p->del_Darray(yr,p->S300_ds);
    
    
    cout<<"fluvial box end  "<<te<<endl<<endl<<endl;
    
}

void solid::fluvial_box_parameterfill(lexer *p, dive *a)
{
    
    G300_ds = p->S300_ds;
    
    p->Darray(xl,G300_ds);
    p->Darray(yl,G300_ds);
    p->Darray(xr,G300_ds);
    p->Darray(yr,G300_ds);
    
    G300 = p->S300;
    p->Iarray(G300_ord,G300);
    
    for(int n=0;n<G300;++n)
    G300_ord[n] = p->S300_ord[n];
    
    
    G301 = p->S301;
    
    G305 = p->S305;
    G306 = p->S306;
    G307_fh = p->S307_fh;
    G307_bh = p->S307_bh;
    G308_x = p->S308_x;
    G308_y = p->S308_y;
    G308_z = p->S308_z;
    G309_x = p->S309_x;
    G309_y = p->S309_y;
    G309_z = p->S309_z;
    
    G310 = p->S310;
    p->Darray(G310_l,G310);
    
    for(int n=0;n<G310;++n)
    G310_l[n] = p->S310_l[n];


    G320 = p->S320;
    p->Darray(G320_r,G320);
    p->Darray(G320_phi,G320);
    
    for(int n=0;n<G320;++n)
    {
    G320_r[n] = p->S320_r[n];
    G320_phi[n] = p->S320_phi[n];
    }
    
    
    G330 = p->S330;
    p->Darray(G330_r,G330);
    p->Darray(G330_phi,G330);
    
    for(int n=0;n<G330;++n)
    {
    G330_r[n] = p->S330_r[n];
    G330_phi[n] = p->S330_phi[n];
    }
    
    G340 = p->S340;
    p->Darray(G340_teta,G340);
    p->Darray(G340_L,G340);
    p->Darray(G340_N,G340);
    p->Darray(G340_ds,G340);
    
    for(int n=0;n<G340;++n)
    {
    G340_teta[n] = p->S340_teta[n];
    G340_L[n] = p->S340_L[n];
    G340_N[n] = p->S340_N[n];
    G340_ds[n] = p->S340_ds[n];
    }
    
    
    
    
    
    /*
    int S300,S300_ds;
    int *S300_ord;
    int S301;
    double S305,S306,S307_fh,S307_bh,S308_x,S308_y,S308_z,S309_x,S309_y,S309_z;
    int S310;
    double *S310_l;
    int S320;
    double *S320_r,*S320_phi;
    int S330;
    double *S330_r,*S330_phi;
    int S340;
    double *S340_teta,*S340_L,*S340_N,*S340_ds;*/
    
    
    
    
}







