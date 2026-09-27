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
#include <sstream>

#ifdef _OPENMP
#include <omp.h>
#endif

gaussian::gaussian(lexer *p, dive *a)
{
    const double sigma = 5.0*p->DXM;

    cutoff = 3.0*sigma;

    sigmaP2M2 = 2.0*sigma*sigma;
}

void gaussian::start(lexer *p, dive *a, int numpt, double *Fx, double *Fy, double *Fz, double *XC, double *YC, int kx, int ky, double **f)
{
    setup(p,a,Fx,Fy,Fz,XC,YC,kx,ky);

    int counter=0;

    const int progress_output_interval = 1000;
    #pragma omp parallel for collapse(2) schedule(dynamic)
    for(int i=0; i<kx; ++i)
    for(int j=0; j<ky; ++j)
    {
        f[i+3][j+3] = gxy(p,i,j,Fx,Fy,Fz,XC,YC);
        ++counter;

        if(counter%progress_output_interval==0)
        {
            std::stringstream ss;
            ss<<"> processed cells: "<<counter<<endl;
            cout<<ss.str();
        }
    }
}

double gaussian::gxy(lexer *p, int i, int j, double *Fx, double *Fy, double *Fz, double *XC, double *YC)
{
    constexpr int radius = 3;

    const double xc = XC[IP];
    const double yc = YC[JP];

    double g = 0.0;
    double wsum = 0.0;
    double zmean = 0.0;
    int cp = 0;

    double w;
    double rx, ry, r2;
    int is,ie,js,je;
    int r,s,t,q;
    int count;

    do{
        is = std::max(i-dij-cp,-radius);
        ie = std::min(i+dij+cp,Nx-radius);

        js = std::max(j-dij-cp,-radius);
        je = std::min(j+dij+cp,Ny-radius);

        zmean=0.0;
        count=0;
        for(r=is;r<ie;++r)
        {
            for(s=js;s<je;++s)
            {
                for(t=0;t<ptnum[r+dd][s+dd];++t)
                {
                    q = ptid[r+dd][s+dd][t];

                    rx = xc-Fx[q];
                    ry = yc-Fy[q];
                    r2 = rx*rx + ry*ry;

                    //if(r2<cutoff)
                    //{
                        w = exp(-r2 / sigmaP2M2);

                        wsum += w;

                        g += w*Fz[q];

                        ++count;
                        zmean+=Fz[q];
                    //}
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
