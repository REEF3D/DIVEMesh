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
    
    
}









