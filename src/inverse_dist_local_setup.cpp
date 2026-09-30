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

#include "inverse_dist_local.h"
#include "dive.h"
#include "lexer.h"
#include <algorithm>
#include <cmath>

void inverse_dist_local::setup(lexer *p, dive *a, double *Fx, double *Fy, double *Fz, double *XC, double *YC, int kx, int ky)
{
    int ic,jc;

    // Grid of bins
    Nx = kx + 2*dd+1;
    Ny = ky + 2*dd+1;

    const size_t nbin = size_t(Nx)*size_t(Ny);

    // bin of every point (-1: outside)
    std::vector<int> bin(p->Np,-1);
    binstart.assign(nbin+1,0);

    for(int n=0;n<p->Np;++n)
    {
        ic = p->poscgen_i(Fx[n],XC,kx);
        jc = p->poscgen_j(Fy[n],YC,ky);

        ICFLAG
        {
            bin[n] = (ic+dd)*Ny + (jc+dd);
            ++binstart[bin[n]+1];
        }
    }

    for(size_t b=0;b<nbin;++b)
    binstart[b+1] += binstart[b];

    // points sorted by bin, stable
    const int npt = binstart[nbin];
    bx.resize(npt);
    by.resize(npt);
    bz.resize(npt);

    std::vector<int> pos(binstart.begin(),binstart.end()-1);

    for(int n=0;n<p->Np;++n)
    if(bin[n]>=0)
    {
        const int q = pos[bin[n]]++;
        bx[q] = Fx[n];
        by[q] = Fy[n];
        bz[q] = Fz[n];
    }

    // summed-area table of point counts
    sat.assign(size_t(Nx+1)*(Ny+1),0);

    for(int r=0;r<Nx;++r)
    for(int s=0;s<Ny;++s)
    sat[size_t(r+1)*(Ny+1)+s+1] = (binstart[size_t(r)*Ny+s+1]-binstart[size_t(r)*Ny+s])
                                + sat[size_t(r)*(Ny+1)+s+1] + sat[size_t(r+1)*(Ny+1)+s] - sat[size_t(r)*(Ny+1)+s];

    dij = p->G17;

    cout<<"IDW local "<<" Nx: "<<Nx<<" Ny: "<<Ny<<" dij: "<<dij<<endl;
}
