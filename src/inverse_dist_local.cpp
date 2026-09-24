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

inverse_dist_local::inverse_dist_local(lexer *p, dive *a)
{
}

void inverse_dist_local::start(lexer *p, dive *a, int numpt, double *Fx, double *Fy, double *Fz, double *XC, double *YC, int kx, int ky, double **f)
{
    setup(p,a,Fx,Fy,Fz,XC,YC,kx,ky);

    double smooth_length = p->G34*p->DXM;
    smooth_lengthP4 = smooth_length*smooth_length*smooth_length*smooth_length;

    int counter = 0;
    for(int i=0; i<kx; ++i)
    for(int j=0; j<ky; ++j)
    {
        f[i+3][j+3] = gxy(p,a,i,j,Fx,Fy,Fz,XC,YC,kx,ky);
        ++counter;

        if(counter%1000==0)
        cout<<"> processed cells: "<<counter<<endl;
    }
}

double inverse_dist_local::gxy(lexer *p, dive *a, int i, int j, double *Fx, double *Fy, double *Fz, double *XC, double *YC, int kx, int ky)
{
    constexpr int radius = 3;

    const double xc = XC[IP];
    const double yc = YC[JP];

    double g = 0.0;
    double wsum = 0.0;
    double zmean = 0.0;
    int cp = 0;

    double xcF, ycF, dist, w;
    int is, ie, js, je;
    int r, s, t, q;
    int count;

    do{
        is=std::max(i-dij-cp,-radius);
        ie=std::min(i+dij+cp,Nx-radius);

        js=std::max(j-dij-cp,-radius);
        je=std::min(j+dij+cp,Ny-radius);

        zmean=0.0;
        count=0;
        for(r=is; r<ie; ++r)
        {
            for(s=js; s<je; ++s)
            {
                for(t=0; t<ptnum[r+dd][s+dd]; ++t)
                {
                    q = ptid[r+dd][s+dd][t];

                    xcF = xc-Fx[q];
                    ycF = yc-Fy[q];
                    dist = sqrt(xcF*xcF + ycF*ycF + smooth_lengthP4);

                    // interpolation loop
                    w = pow(1.0/(dist>1.0e-15?dist:1.0e15),p->G35);

                    wsum += w;

                    g += w*Fz[q];

                    zmean += Fz[q];

                    ++count;
                }
            }
        }

        if(count>0)
        zmean = zmean/double(count);

        cp += 2;
    }
    while(count<std::min(p->G18,p->Np));

    if(wsum>0.0)
    g /= wsum;
    else if(wsum==0.0)
    g /= 1.0e20;

    return g;
}
