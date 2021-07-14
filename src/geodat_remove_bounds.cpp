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
#include"geodat.h"
#include"dive.h"
#include"lexer.h"

void geodat::remove_bounds(lexer *p, dive *a)
{
     // remove out of bounds points
        double xs,xe,ys,ye;
        
            i=-3;
            xs=p->XN[IP];
            
            i=p->knox+3;
            xe=p->XN[IP];
            
            
            j=-3;
            ys=p->YN[JP];
            
            j=p->knoy+3;
            ye=p->YN[JP];
            
            cout<<" xs: "<<xs<<" xe: "<<xe<<" ys: "<<ys<<" ye: "<<ye<<endl;
            
        for(n=0;n<p->Np;++n)
        {   
            
            
            if(p->G10_x[n]<xs || p->G10_x[n]>xe || p->G10_y[n]<ys || p->G10_y[n]>ye)
            {
            p->G10_x[n] = p->G10_x[p->Np-1];
            p->G10_y[n] = p->G10_y[p->Np-1];
            p->G10_z[n] = p->G10_z[p->Np-1];
            -- p->Np;
            --n;
            }       

        }
}