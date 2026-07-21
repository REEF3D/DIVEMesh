/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2026 Hans Bihs

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

auto out_single = [](char* name, int size, const char* model, int num, int rank)
{
    snprintf(name,size,"./REEF3D_%s_HDC_Input/REEF3D-HDC-Input-%08i-%06i.r3d",model,num,rank+1);
};

auto out_continuous = [](char* name, int size, const char* model, int rank)
{
    snprintf(name,size,"./REEF3D_%s_HDC_Input/REEF3D-HDC-Input-%06i.r3d",model,rank+1);
};

auto out_header = [](char* name, int size, const char* model, int rank)
{
    snprintf(name,size,"./REEF3D_%s_HDC_Input/REEF3D-HDC-Input-Header-%06i.r3d",model,rank+1);
};

void hdc::filename_out_single(lexer *p, int num, int rank)
{
    if(p->H10==44)
    {
        out_single(name,sizeof(name),"FNPF",num,rank);
    }
    else
    {
        out_single(name,sizeof(name),"CFD",num,rank);
    }
}

void hdc::filename_out_continuous(lexer *p, int rank)
{
    if(p->H10==44)
    {
        out_continuous(name,sizeof(name),"FNPF",rank);
    }
    else
    {
        out_continuous(name,sizeof(name),"CFD",rank);
    }
}

void hdc::filename_out_header(lexer *p, int rank)
{
    if(p->H10==44)
    {
        out_header(name,sizeof(name),"FNPF",rank);
    }
    else
    {
        out_header(name,sizeof(name),"CFD",rank);
    }
}
