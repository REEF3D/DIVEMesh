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

#include"bedlevel.h"
#include"dive.h"
#include"lexer.h"


bedlevel::bedlevel(lexer *p, dive *a)
{

}

bedlevel::~bedlevel()
{
}

void bedlevel::start(lexer* p, dive* a)
{
    cout<<"bedlevel"<<endl;
    
    /*
    XYLOOP
    a->bedlevel(i,j)=p->zmin;
    
    // geodat
    LOOP
	{
    if(a->flag(i,j,k)>0.0 && a->flag(i,j,k-1)<0.0)
    a->bedlevel(i,j) = MAX(a->bedlevel(i,j),p->posc_z()-0.5*p->DZ[KP]);
    
    if(a->solid_dist(i,j,k)>0.0 && a->solid_dist(i,j,k-1)<0.0)
    a->bedlevel(i,j) = MAX(a->bedlevel(i,j),a->solid_dist(i,j,k));
	}*/
	
    
    

    //XYLOOP
    //a->bedlevel(i,j) = MAX(a->bedlevel(i,j),p->zmin);
    
    
    
    
    //XYLOOP
    //cout<<a->bedlevel(i,j)<<endl;
	
    // check for lowest bedlevel
    
    
    
    // finish with solid, use solid(i,j,k)
    
    //if(solid_dist(i,j,k)>0 && solid_dist(i,j,k-1)<0)
    // check for lowest bedlevel
    
}


