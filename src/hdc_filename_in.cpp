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

auto in_single = [] (char *name, int size, const char *model, int num, int rank)
{
    snprintf(name,size,"./REEF3D_%s_STATE/REEF3D-%s-State-%08i-%06i.r3d",model,model,num,rank+1);
};

auto in_continuous = [] (char *name, int size, const char *model, int rank)
{
    snprintf(name,size,"./REEF3D_%s_STATE/REEF3D-%s-State-%06i.r3d",model,model,rank+1);
};

auto in_header = [] (char *name, int size, const char *model, int rank)
{
    snprintf(name,size,"./REEF3D_%s_STATE/REEF3D-%s-State-Header-%06i.r3d",model,model,rank+1);
};

void hdc::filename_in_single(lexer *p, int num, int rank)
{
    if(p->H10==2)
    {
        in_single(name, sizeof(name), "SFLOW", num, rank);
    }
    else if(p->H10==4 || p->H10==44)
    {
        in_single(name, sizeof(name), "FNPF", num, rank);
    }
    else if(p->H10==5)
    {
        in_single(name, sizeof(name), "NHFLOW", num, rank);
    }
}

void hdc::filename_in_continuous(lexer *p, int rank)
{
    if(p->H10==2)
    {
        in_continuous(name, sizeof(name), "SFLOW", rank);
    }
    else if(p->H10==4 || p->H10==44)
    {
        in_continuous(name,sizeof(name), "FNPF", rank);
    }
    else if(p->H10==5)
    {
        in_continuous(name, sizeof(name), "NHFLOW", rank);
    }
}

void hdc::filename_in_header(lexer *p, int rank)
{
    if(p->H10==2)
    {
        in_header(name, sizeof(name), "SFLOW", rank);
    }
    else if(p->H10==4 || p->H10==44)
    {
        in_header(name, sizeof(name), "FNPF", rank);
    }
    else if(p->H10==5)
    {
        in_header(name, sizeof(name), "NHFLOW", rank);
    }
}
