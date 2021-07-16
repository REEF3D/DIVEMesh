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
    cout<<"fluvial box start"<<endl;
    
    countds=1;
    numds=0;
    x0=0.0; // add origin afterwards
    y0=0.0; // add origin
    xe=x0;
    ye=y0;
    phi0 = 0.0;

    
    

    p->Darray(xl,p->S300_ds);
    p->Darray(yl,p->S300_ds);
    p->Darray(xr,p->S300_ds);
    p->Darray(yr,p->S300_ds);
    
    
    
    
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
    G300 = p->S300;
    G300_ds = p->S300_ds;
    
    G300_ord = p->S300_ord;
    G301 = p->S301;
    
    G305 = G305;
    G306 = G306;
    G307_fh = G307_fh;
    G307_bh = G307_bh;
    G308_x = G308_x;
    G308_y = G308_y;
    G308_z = G308_z;
    G309_x = G309_x;
    G309_y = G309_y;
    G309_z = G309_z;
    
    G310 = p->S310;
    G310_l = p->S310_l;

    G320 = p->S320;
    G320_r = p->S320_r;
    G320_phi = p->S320_phi;
    
    G330 = p->S330;
    G330_r = p->S330_r;
    G330_phi = p->S330_phi;
    
    G340 = p->S340;
    G340_teta = p->S340_teta;
    G340_L = p->S340_L;
    G340_N = p->S340_N;
    G340_ds = p->S340_ds;
}







