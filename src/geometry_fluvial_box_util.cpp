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

#include"geometry.h"
#include"dive.h"
#include"lexer.h"

void geometry::fluvial_box_move(lexer *p, dive *a)
{
    for(n=0;n<numds;++n)
    {
    xl[n] += G308_x;
    xr[n] += G308_x;
    
    yl[n] += G308_y;
    yr[n] += G308_y;
    }
    
}


void geometry::fluvial_box_extend(lexer *p, dive *a)
{
    double xmin,xmax,ymin,ymax;
    
    xmin=1.0e8;
    xmax=-1.0e8;
    ymin=1.0e8;
    ymax=-1.0e8;
    
    for(n=0;n<numds;++n)
    {
    xmin = MIN(xmin,xl[n]);
    xmin = MIN(xmin,xr[n]);
    
    xmax = MAX(xmax,xl[n]);
    xmax = MAX(xmax,xr[n]);
    
    
    ymin = MIN(ymin,yl[n]);
    ymin = MIN(ymin,yr[n]);
    
    ymax = MAX(ymax,yl[n]);
    ymax = MAX(ymax,yr[n]);
    }
    
    
    
    box_xs = xmin;
    box_xe = xmax + G309_x;
    
    box_ys = ymin - G309_y;
    box_ye = ymax + G309_y;
    
    box_zs = -G307_bh - G309_z;
    box_ze =  G307_fh + G309_z;
    
    cout<<"fluvial box extend - xs: "<<box_xs<<" xe: "<<box_xe<<" ys: "<<box_ys<<" ye: "<<box_ye<<" zs: "<<box_zs<<" ze: "<<box_ze<<endl;
    
}