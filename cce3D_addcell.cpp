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

#include"cce3D.h"
#include"dive.h"
#include"lexer.h"
#include"entity.h"

void cce3D::addcell(lexer *p, dive *a, entity *pent, int ii, int jj, int kk)
{
                 if(a->confac(ii,jj,kk)>0)
                 nn=a->confac(ii,jj,kk);

                 if(a->confac(ii,jj,kk)==0)
                 {
                 ++count;
                 a->confac(ii,jj,kk)=count;
                 nn=count;
                 }
				 
	if(count>=a->maxsurf)
	cceout<<"!!! facet: "<<count<<endl;
	
             a->facet[nn][a->numfac(ii,jj,kk)]=ptcount;
             a->numfac(ii,jj,kk)++;
             a->xdir(ii,jj,kk)=pent->xdir(ii,jj,kk);
             a->ydir(ii,jj,kk)=pent->ydir(ii,jj,kk);
             a->zdir(ii,jj,kk)=pent->zdir(ii,jj,kk);
}
