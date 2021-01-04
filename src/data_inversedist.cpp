/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2021 Hans Bihs

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

#include"data.h"
#include"dive.h"
#include"lexer.h"

double data::inverse_dist_2D(lexer *p, dive *a)
{	
    xc = p->XP[IP];
    yc = p->YP[JP];

    g=0.0;
    wsum=0.0;

    for(n=0; n<p->D10; ++n)
    wsum += inverse_dist_w(p);

    for(n=0; n<p->D10; ++n)
    g += (inverse_dist_w(p)*p->D10_data[n]);
	
	g/=wsum;
	

    return g;
}


double data::inverse_dist_w(lexer *p)
{
    dist = sqrt(pow(xc-p->D10_x[n],2.0) + pow(yc-p->D10_y[n],2.0));
	
	if(dist>p->D24 && p->D24>-1.0)
	dist=0.0;
		
    dist = pow(1.0/(dist>1.0e-10?dist:1.0e10),p->D17);
	
    return dist;
}






