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

#include "kriging.h"
#include "dive.h"
#include "lexer.h"
#include <algorithm>
#include <cmath>
#include <limits>

void kriging::ini(lexer *p, dive *a, int numpt, double *X, double *Y, double *F)
{
    double xmin = +std::numeric_limits<double>::max();
    double ymin = +std::numeric_limits<double>::max();
    double xmax = -std::numeric_limits<double>::max();
    double ymax = -std::numeric_limits<double>::max();
    double mean = 0.0;

    for(n=0; n<numpt; ++n)
    {
        xmin = std::min(xmin,X[n]);
        xmax = std::max(xmax,X[n]);

        ymin = std::min(ymin,Y[n]);
        ymax = std::max(ymax,Y[n]);

        mean += F[n];
    }

    const double dx = xmax-xmin;
    const double dy = ymax-ymin;
    range = p->D18*sqrt(dx*dx + dy*dy);

    mean/=double(numpt);

    variance=0.0;
    for(n=0; n<numpt; ++n)
    variance += (F[n] - mean)*(F[n] - mean);

    variance/=double(numpt);

    cout<<"Np: "<<numpt<<"  mean: "<<mean<<"  variance: "<<variance<<"  range: "<<range<<endl;
}
