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

#include "gaussian.h"
#include "dive.h"
#include "lexer.h"
#include <algorithm>
#include <cmath>
#include <limits>

void gaussian::setup(lexer *p, dive *a, double *Fx, double *Fy, double *Fz, double *XC, double *YC, int kx, int ky)
{
    double xmin = +std::numeric_limits<double>::max();
    double ymin = +std::numeric_limits<double>::max();
    double zmin = +std::numeric_limits<double>::max();

    double xmax = -std::numeric_limits<double>::max();
    double ymax = -std::numeric_limits<double>::max();
    double zmax = -std::numeric_limits<double>::max();

    for(n=0;n<p->Np;++n)
    {
        xmax=std::max(xmax,Fx[n]);
        xmin=std::min(xmin,Fx[n]);
        ymax=std::max(ymax,Fy[n]);
        ymin=std::min(ymin,Fy[n]);
        zmax=std::max(zmax,Fz[n]);
        zmin=std::min(zmin,Fz[n]);
    }

    // Grid
    Nx = kx + 2*dd+1;
    Ny = ky + 2*dd+1;

    p->Iarray(ptnum,Nx,Ny);

    int n,r,s,t;
    int ic,jc;

    for(n=0;n<p->Np;++n)
    {
        ic = p->poscgen_i(Fx[n],XC,kx);
        jc = p->poscgen_j(Fy[n],YC,ky);

        ICFLAG
        ++ptnum[ic+dd][jc+dd];
    }

    p->Iarray(ptid,Nx,Ny, ptnum);

    for(r=0;r<Nx;++r)
    for(s=0;s<Ny;++s)
    ptnum[r][s]=0;

    for(r=0;r<Nx;++r)
    for(s=0;s<Ny;++s)
    for(t=0;t<ptnum[r][s];++t)
    ptid[r][s][t]=-1;

    for(n=0;n<p->Np;++n)
    {
        ic = p->poscgen_i(Fx[n],XC,kx);
        jc = p->poscgen_j(Fy[n],YC,ky);

        ICFLAG
        {
            ptid[ic+dd][jc+dd][ptnum[ic+dd][jc+dd]]=n;
            ++ptnum[ic+dd][jc+dd];
        }
    }

    // Radius
    const double dx = p->xmax-p->xmin;
    const double dy = p->ymax-p->ymin;
    const double Dmax = sqrt(dx*dx+dy*dy);
    const double R = 0.25*Dmax*sqrt(p->G18/p->Np);

    dij = std::max(int(R/(p->DXM)),p->G17);

    dij=p->G17;

    cout<<"IDW local "<<" Nx: "<<Nx<<" Ny: "<<Ny<<" R: "<<R<<" dij: "<<dij<<endl;
}
