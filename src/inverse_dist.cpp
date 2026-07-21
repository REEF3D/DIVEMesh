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

#include "inverse_dist.h"
#include "dive.h"
#include "lexer.h"
#include <cmath>

inverse_dist::inverse_dist(lexer *p, dive *a)
{
}

void inverse_dist::start(lexer *p, dive *a, int numpt, double *Fx, double *Fy, double *Fz, double *XC, double *YC, int kx, int ky, double **f)
{
    int counter=0;

    for(int i=0; i<kx; ++i)
    for(int j=0; j<ky; ++j)
    {
        f[i+3][j+3] = gxy(p,i,j,Fx,Fy,Fz,XC,YC);

        ++counter;

        if(counter%1000==0)
        cout<<"> processed cells: "<<counter<<endl;
    }
}

double inverse_dist::gxy(lexer *p, int i, int j, double *Fx, double *Fy, double *Fz, double *XC, double *YC)
{
    double xc = XC[IP];
    double yc = YC[JP];

    double g=0.0;
    double wsum=0.0;
double weight = 0.0;

    for(n=0; n<p->Np; ++n)
{
        weight = w(xc-Fx[n],yc-Fy[n],p->G35);
    wsum += weight;

        g += (weight*Fz[n]);
}

    g/=wsum;

    return g;
}

double inverse_dist::w(double xcF, double ycF, double G35)
{
    double dist = sqrt(xcF*xcF + ycF*ycF);

    dist = pow(1.0/(dist>1.0e-10?dist:1.0e10),G35);

    return dist;
}
