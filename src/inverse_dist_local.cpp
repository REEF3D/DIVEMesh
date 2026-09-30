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
#include <sstream>

#ifdef _OPENMP
#include <omp.h>
#endif

inverse_dist_local::inverse_dist_local(lexer *p, dive *a)
{
}

void inverse_dist_local::start(lexer *p, dive *a, int numpt, double *Fx, double *Fy, double *Fz, double *XC, double *YC, int kx, int ky, double **f)
{
    setup(p,a,Fx,Fy,Fz,XC,YC,kx,ky);

    int progress_output_interval = 1000;
    if(p->knox*p->knoy*p->knoz>1000000)
    progress_output_interval = 100000;

    double smooth_length = p->G34*p->DXM;
    smooth_lengthP4 = smooth_length*smooth_length*smooth_length*smooth_length;

    int counter = 0;
    #pragma omp parallel for collapse(2) schedule(dynamic)
    for(int i=0; i<kx; ++i)
    for(int j=0; j<ky; ++j)
    {
        f[i+3][j+3] = gxy(p,i,j,XC,YC);

        int done;
        #pragma omp atomic capture
        done = ++counter;

        if(done%progress_output_interval==0)
        {
            std::stringstream ss;
            ss<<"> processed cells: "<<done<<endl;
            cout<<ss.str();
        }
    }
}

double inverse_dist_local::gxy(lexer *p, int i, int j, double *XC, double *YC)
{
    constexpr int radius = 3;

    const double xc = XC[IP];
    const double yc = YC[JP];
    const double G35 = p->G35;
    const long long target = std::min(p->G18,p->Np);

    // Find the window the search ends with: it starts at +-dij bins and grows
    // by 2 bins per side until it holds at least G18 points or covers the grid.
    // The point count of a window comes from the summed-area table.
    int is, ie, js, je;
    int cp = 0;

    while(true)
    {
        is = std::max(i-dij-cp,-radius);
        ie = std::min(i+dij+cp,Nx-radius-1);

        js = std::max(j-dij-cp,-radius);
        je = std::min(j+dij+cp,Ny-radius-1);

        const bool fullwindow = (is==-radius && ie==Nx-radius-1 && js==-radius && je==Ny-radius-1);

        if(window_count(is+dd,ie+dd,js+dd,je+dd)>=target || fullwindow)
        break;

        cp += 2;
    }

    // weighted sum over that window, in the original order (bins r, s, points t)
    double g = 0.0;
    double wsum = 0.0;

    for(int r=is; r<=ie; ++r)
    {
        const int *start = &binstart[size_t(r+dd)*Ny + (js+dd)];
        const int q0 = start[0];
        const int q1 = start[je-js+1];

        for(int q=q0; q<q1; ++q)
        {
            const double xcF = xc-bx[q];
            const double ycF = yc-by[q];
            const double dist = sqrt(xcF*xcF + ycF*ycF + smooth_lengthP4);

            const double w = pow(1.0/(dist>1.0e-15?dist:1.0e15),G35);

            wsum += w;
            g += w*bz[q];
        }
    }

    if(wsum>0.0)
    g /= wsum;
    else if(wsum==0.0)
    g /= 1.0e20;

    return g;
}
