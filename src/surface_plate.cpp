/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2024 Hans Bihs

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
#include"surface.h"
#include"lexer.h"
#include"dive.h"

void surface::mem_alloc_plate(lexer* p, dive* a)
{
    int js,je,ks,ke;

    for(qn=0;qn<p->S201;++qn)
    {

        js = p->posc_j(p->S201_ys[qn]);
        je = p->posc_j(p->S201_ye[qn]);

        ks = p->posc_k(p->S201_zs[qn]);
        ke = p->posc_k(p->S201_ze[qn]);

        for(j=js;j<=je;++j)
        for(k=ks;k<=ke;++k)
        ++surfnum;

        for(j=js;j<=je;++j)
        for(k=ks;k<=ke;++k)
        ++surfnum;
    }
}

void surface::makesurf_plate(lexer* p, dive* a)
{

    double locx;
    int loci;
    int js,je,ks,ke;

    for(qn=0;qn<p->S201;++qn)
    {
        //left
        ILOOP
        if(p->XP[IP]<p->S201_x[qn] && p->XP[IP1]>=p->S201_x[qn])
        {
        js = p->posc_j(p->S201_ys[qn]);
        je = p->posc_j(p->S201_ye[qn]);

        ks = p->posc_k(p->S201_zs[qn]);
        ke = p->posc_k(p->S201_ze[qn]);

        for(j=js;j<=je;++j)
        for(k=ks;k<=ke;++k)
        {
        a->surf[a->surfcount][0]=i;
        a->surf[a->surfcount][1]=j;
        a->surf[a->surfcount][2]=k;
        a->surf[a->surfcount][3]=4;
        a->surf[a->surfcount][4]=21;
        a->surfcount++;
        }

        for(j=js;j<=je;++j)
        for(k=ks;k<=ke;++k)
        {
        a->surf[a->surfcount][0]=i+1;
        a->surf[a->surfcount][1]=j;
        a->surf[a->surfcount][2]=k;
        a->surf[a->surfcount][3]=1;
        a->surf[a->surfcount][4]=21;
        a->surfcount++;
        }

        }



    }


}
