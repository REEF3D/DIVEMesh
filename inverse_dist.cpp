/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2019 Hans Bihs

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
--------------------------------------------------------------------*/

#include"inverse_dist.h"
#include"dive.h"
#include"lexer.h"

inverse_dist::inverse_dist(lexer *p, dive *a) 
{
}

inverse_dist::~inverse_dist()
{
}

void inverse_dist::start(lexer *p, dive *a, int Np, double *Fx, double *Fy, double *Fz, field2d &data)
{
    
    XYLOOP
    data(i,j) = gxy(p,a,Np,Fx,Fy,Fz);
}

double inverse_dist::gxy(lexer *p, dive *a, int Np, double *Fx, double *Fy, double *Fz)
{    

    xc = p->XP[IP]+p->xmin;
    yc = p->YP[JP]+p->ymin;

    g=0.0;
    wsum=0.0;

    for(n=0; n<Np; ++n)
    wsum += w(p,Np,Fx,Fy,Fz);

    for(n=0; n<Np; ++n)
    g += (w(p,Np,Fx,Fy,Fz)*Fz[n]);
    
    

    g/=wsum;

    return g;

}


double inverse_dist::w(lexer  *p, int Np, double *Fx, double *Fy, double *Fz)
{
    dist = sqrt(pow(xc-Fx[n],2.0) + pow(yc-Fy[n],2.0));
	
	//cout<<dist<<" ";
	
    dist = pow(1.0/(dist>1.0e-10?dist:1.0e10),p->G35);

    return dist;
}






