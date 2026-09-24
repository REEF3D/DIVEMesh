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

#include"dataset.h"
#include"lexer.h"
#include <cmath>

double dataset::inverse_dist_2D(lexer *p)
{
    const double xc = p->XP[IP];
    const double yc = p->YP[JP];

    double g = 0.0;
    double wsum = 0.0;

    double weight;

    for(n=0; n<p->D10; ++n)
    {
        weight = inverse_dist_w(xc-p->D10_x[n], yc-p->D10_y[n], p->D24, p->D17);
        wsum += weight;

        g += weight*p->D10_dataset[n];
    }

    g/=wsum;

    return g;
}

inline double dataset::inverse_dist_w(double dx, double dy, double D24, double D17)
{
    double dist = sqrt(dx*dx + dy*dy);

    if(dist>D24 && D24>-1.0)
    dist=0.0;

    dist = pow(1.0/(dist>1.0e-10?dist:1.0e10),D17);

    return dist;
}
