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
#include"dive.h"
#include"lexer.h"

void geometry::ray_cast(lexer* p, dive* a, int ts, int te, intfield &flag, field &dist, field2d &bedlevel) 
{
    if(rayiter==0)
    {
	ray_cast_io_x(p,a,tri_start,tri_end,flag,dist);
    ray_cast_io_ycorr(p,a,tri_start,tri_end,flag,dist);
    ray_cast_io_zcorr(p,a,tri_start,tri_end,flag,dist);
    }

    if(rayiter==1)
    {
	ray_cast_x(p,a,tri_start,tri_end,flag,dist);
	ray_cast_y(p,a,tri_start,tri_end,flag,dist);
	ray_cast_z(p,a,tri_start,tri_end,flag,dist,bedlevel);
    }
}
