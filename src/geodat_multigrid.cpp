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

#include"geodat.h"
#include"dive.h"
#include"lexer.h"

void geodat::coarsen(lexer *p, dive *a)
{
    int count;
    
    // x
    count=0;
    ILOOP
    if(i%p->G38==0)
    {
    XC[count+marge]=p->XP[IP];
    ++count;
    }
    
    kx=count;
    
    // y
    count=0;
    JLOOP
    if(j%p->G38==0)
    {
    YC[count+marge]=p->YP[JP];
    ++count;
    }
    
    ky=count;
    
    p->Darray(topof,kx+2*dd+1,ky+2*dd+1);
    
    cout<<"coarsen knox:"<<p->knox<<" kx: "<<kx<<" | knoy:"<<p->knoy<<" ky: "<<ky<<endl;

    
    // bc
    XC[marge-1] = XC[marge] - 1.0*(XC[marge+1]-XC[marge]);
    XC[marge-2] = XC[marge] - 2.0*(XC[marge+1]-XC[marge]);
    XC[marge-3] = XC[marge] - 3.0*(XC[marge+1]-XC[marge]);
    XC[marge-4] = XC[marge] - 4.0*(XC[marge+1]-XC[marge]);
    XC[marge-5] = XC[marge] - 5.0*(XC[marge+1]-XC[marge]);
    
    
    XC[marge+kx]   = XC[marge+kx-1] + 1.0*(XC[marge+kx-1]-XC[marge+kx-2]);
    XC[marge+kx+1] = XC[marge+kx-1] + 2.0*(XC[marge+kx-1]-XC[marge+kx-2]);
    XC[marge+kx+2] = XC[marge+kx-1] + 3.0*(XC[marge+kx-1]-XC[marge+kx-2]);
    XC[marge+kx+3] = XC[marge+kx-1] + 4.0*(XC[marge+kx-1]-XC[marge+kx-2]);
    XC[marge+kx+4] = XC[marge+kx-1] + 5.0*(XC[marge+kx-1]-XC[marge+kx-2]);
    
    
    YC[marge-1] = YC[marge] - 1.0*(YC[marge+1]-YC[marge]);
    YC[marge-2] = YC[marge] - 2.0*(YC[marge+1]-YC[marge]);
    YC[marge-3] = YC[marge] - 3.0*(YC[marge+1]-YC[marge]);
    YC[marge-4] = YC[marge] - 4.0*(YC[marge+1]-YC[marge]);
    YC[marge-5] = YC[marge] - 5.0*(YC[marge+1]-YC[marge]);
    
    
    YC[marge+ky]   = YC[marge+ky-1] + 1.0*(YC[marge+ky-1]-YC[marge+ky-2]);
    YC[marge+ky+1] = YC[marge+ky-1] + 2.0*(YC[marge+ky-1]-YC[marge+ky-2]);
    YC[marge+ky+2] = YC[marge+ky-1] + 3.0*(YC[marge+ky-1]-YC[marge+ky-2]);
    YC[marge+ky+3] = YC[marge+ky-1] + 4.0*(YC[marge+ky-1]-YC[marge+ky-2]);
    YC[marge+ky+4] = YC[marge+ky-1] + 5.0*(YC[marge+ky-1]-YC[marge+ky-2]);
    
}

void geodat::prolong(lexer *p, dive *a, field2d& bed)
{
    double xc,yc,val;

    cout<<"prolong "<<endl;
    
    XYLOOP
    {
    xc = p->XP[IP];
    yc = p->YP[JP];
    
    val = ccipol(p,topof,xc,yc);   

    bed(i,j) = val;    
    }
}


