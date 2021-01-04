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


void solid::ray_cast(lexer* p, dive* a, int ts, int te)
{
    if(rayiter==0)
    {
	ray_cast_io_x(p,a,tri_start,tri_end);	
    ray_cast_io_ycorr(p,a,tri_start,tri_end);
    ray_cast_io_zcorr(p,a,tri_start,tri_end);	
    }
    
    if(rayiter==1)
    {
	ray_cast_x(p,a,tri_start,tri_end);
	ray_cast_y(p,a,tri_start,tri_end);
	ray_cast_z(p,a,tri_start,tri_end);
    }
}
