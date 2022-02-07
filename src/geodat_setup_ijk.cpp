/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2022 Hans Bihs

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

void geodat::setup_ijk(lexer *p, dive *a, double *Fx, double *Fy, double *Fz, double *XC, double *YC, int kx, int ky)
{            
    // Grid
    Nx = kx + 2*dd+1;
    Ny = ky + 2*dd+1;

    p->Iarray(ptnum,Nx,Ny);
    
    for(r=0;r<Nx;++r)
    for(s=0;s<Ny;++s)
    ptnum[r][s]=0;

    for(n=0;n<p->Np;++n)
    {
    ic = p->poscgen_i(Fx[n],XC,kx);
    jc = p->poscgen_j(Fy[n],YC,ky);
    
    //ICFLAG
    ++ptnum[ic+dd][jc+dd];
    }
    
    
    p->Iarray(ptid,Nx,Ny, ptnum);
    
    for(r=0;r<Nx;++r)
    for(s=0;s<Ny;++s)
    for(t=0;t<ptnum[r][s];++t)
    ptid[r][s][t]=-1;
    
    for(r=0;r<Nx;++r)
    for(s=0;s<Ny;++s)
    ptnum[r][s]=0;
    
    
    for(n=0;n<p->Np;++n)
    {
        ic = p->poscgen_i(Fx[n],XC,kx);
        jc = p->poscgen_j(Fy[n],YC,ky);

        //ICFLAG
        {
        ptid[ic+dd][jc+dd][ptnum[ic+dd][jc+dd]]=n;
        ++ptnum[ic+dd][jc+dd];
        }
    }
    
}

void geodat::setup_ijk_delete(lexer *p, dive *a, int kx, int ky)
{
    
    Nx = kx + 2*dd+1;
    Ny = ky + 2*dd+1;

    
    p->del_Iarray(ptid,Nx,Ny, ptnum);
    p->del_Iarray(ptnum,Nx,Ny);
    
}


