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

#include"hdc.h"
#include"lexer.h"

void hdc::filename_single_out(lexer *p, dive *a,int num, int rank)
{

    sprintf(name,"./REEF3D_CFD_HDC_Input/REEF3D-HDC-Input-%08i-%06i.r3d",num,rank+1);
}

void hdc::filename_continuous_out(lexer *p, dive *a, int rank)
{
	sprintf(name,"./REEF3D_CFD_HDC_Input/REEF3D-HDC-Input-%06i.r3d",rank+1);
}

void hdc::filename_out_header(lexer *p, dive *a, int rank)
{
	sprintf(name,"./REEF3D_CFD_HDC_Input/REEF3D-HDC-Input-Header-%06i.r3d",rank+1);
}


