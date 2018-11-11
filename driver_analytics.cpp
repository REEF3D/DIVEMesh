/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2018 Hans Bihs

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

#include"driver.h"
#include"lexer.h"
#include"dive.h"

void driver::analytics(lexer *p, dive *a)
{
	// Number of Cells
	
    int count=0;

    LOOP
    if(a->flag(i,j,k)>0)
    ++count;

    cout<<"Number of Cells: "<<count<<endl;


	// Min/Max cell size and position
	
    double dx_min, dx_max, dy_min, dy_max, dz_min, dz_max;
	double i_min, i_max, j_min, j_max, k_min, k_max;
	
	dx_min = 100.0*p->DXM;
	dy_min = 100.0*p->DXM;
	dz_min = 100.0*p->DXM;
	dx_max = 0.0;
	dy_max = 0.0;
	dz_max = 0.0;
	
    for(i=-marge;i<p->knox+marge;++i)
	{
		if (p->DX[IP] < dx_min && p->DX[IP] > 1e-5)
		{
			dx_min = p->DX[IP];
			i_min = p->posc_x();
		}
		if (p->DX[IP] > dx_max) 
		{
			dx_max = p->DX[IP];
			i_max = p->posc_x();
		}
	}
    
    for(j=-marge;j<p->knoy+marge;++j)
	{
		if (p->DY[JP] < dy_min && p->DY[JP] > 1e-5) 
		{
			dy_min = p->DY[JP];
			j_min = p->posc_y();
		}
		if (p->DY[JP] > dy_max) 
		{
			dy_max = p->DY[JP];	
			j_max = p->posc_y();	
		}
	}

    for(k=-marge;k<p->knoz+marge;++k)
	{
		if (p->DZ[KP] < dz_min && p->DZ[KP] > 1e-5) 
		{
			dz_min = p->DZ[KP];
			k_min = p->posc_z();
		}
		if (p->DZ[KP] > dz_max) 
		{
			dz_max = p->DZ[KP];	
			k_max = p->posc_z();		
		}
	}
	
    cout<<"Min/Max Cell Size:"<<endl;
	cout<<"dx= "<<dx_min<<"/"<<dx_max<<" at "<<i_min<<"/"<<i_max<<endl;
	cout<<"dy= "<<dy_min<<"/"<<dy_max<<" at "<<j_min<<"/"<<j_max<<endl;
	cout<<"dz= "<<dz_min<<"/"<<dz_max<<" at "<<k_min<<"/"<<k_max<<endl;	


	// Min/Max Aspect Ratio
	
	double ratio;
	double ratiox_max, ratioy_max, ratioz_max;
	
    for(i=-marge;i<p->knox+marge-2;++i)
	{
		ratio =
			p->DX[IP1] > p->DX[IP] ? p->DX[IP1]/p->DX[IP] : p->DX[IP]/p->DX[IP1];

		if (ratio > ratiox_max) 
		{
			ratiox_max = ratio;
			i_max = p->posc_x();
		}
	}
    
    for(j=-marge;j<p->knoy+marge-2;++j)
	{
		ratio =
			p->DY[JP1] > p->DY[JP] ? p->DY[JP1]/p->DY[JP] : p->DY[JP]/p->DY[JP1];

		if (ratio > ratioy_max) 
		{
			ratioy_max = ratio;
			j_max = p->posc_y();
		}
	}

    for(k=-marge;k<p->knoz+marge-2;++k)
	{
		ratio =
			p->DZ[KP1] > p->DZ[KP] ? p->DZ[KP1]/p->DZ[KP] : p->DZ[KP]/p->DZ[KP1];

		if (ratio > ratioz_max) 
		{
			ratioz_max = ratio;
			i_max = p->posc_z();
		}
	}

    cout<<"Max Aspect Ratio:"<<endl;
	cout<<"x "<<ratiox_max<<" at "<<i_max<<endl;
	cout<<"y "<<ratioy_max<<" at "<<j_max<<endl;
	cout<<"z "<<ratioz_max<<" at "<<k_max<<endl;		
	
	
	cout<<endl<<endl<<"--DONE--"<<endl<<endl<<endl;	
}
