/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2022 Hans Bihs

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
#include"lexer.h"

void lexer::read_geodat()
{
	int countG10=0;

// read geodat
	if(G10>0)
	{
        cout<<"open geo.dat and count entries"<<endl;
        double val;
        char cval;
        ifstream geo("geo.dat", ios_base::in);

        while(!geo.eof())
        {
        if(G19==0)
        geo>>val>>val>>val;

        if(G19==1)
        geo>>cval>>val>>val>>val;

        ++countG10;
        }
        G10=countG10-1;
        cout<<"> geodat entries: "<<G10<<endl;
        geo.close();

        G10_x = new double[countG10];
        G10_y = new double[countG10];
        G10_z = new double[countG10];

        
        cout<<"read geo.dat"<<endl;
        
        geo.open("geo.dat", ios_base::in);

        countG10=0;
        while(!geo.eof()&&countG10<G10)
        {
        if(G19==0)
        geo>>G10_x[countG10]>>G10_y[countG10]>>G10_z[countG10];

        if(G19==1)
        geo>>cval>>G10_x[countG10]>>G10_y[countG10]>>G10_z[countG10];
        ++countG10;
        }

        geo.close();
		
		if(G13>0)
		{   
            xmin=+1.0e19;
            ymin=+1.0e19;
            zmin=+1.0e19;

            xmax=-1.0e19;
            ymax=-1.0e19;
            zmax=-1.0e19;

            for(n=0;n<G10;++n)
            {
            xmax=MAX(xmax,G12_x*G10_x[n]);
            xmin=MIN(xmin,G12_x*G10_x[n]);
            ymax=MAX(ymax,G12_y*G10_y[n]);
            ymin=MIN(ymin,G12_y*G10_y[n]);
            zmax=MAX(zmax,G12_z*G10_z[n]);
            zmin=MIN(zmin,G12_z*G10_z[n]);
            }
            
            if(G14==0)
            {
            G14_x = xmin + 0.5*(xmax-xmin);
            G14_y = ymin + 0.5*(ymax-ymin);
            }
            
			// rotate geodat points
			G13_phi	 = G13_phi*PI/180.0;
			
			double xval,yval;
			for(n=0;n<G10;++n)
			{
			xval = G14_x + (G10_x[n]-G14_x)*cos(G13_phi) - (G10_y[n]-G14_y)*sin(G13_phi);
			yval = G14_y + (G10_x[n]-G14_x)*sin(G13_phi) + (G10_y[n]-G14_y)*cos(G13_phi);

			G10_x[n] = xval;
			G10_y[n] = yval;
			}
		}
        

        if(G20>0)
        {
            xmin=+1.0e19;
            ymin=+1.0e19;
            zmin=+1.0e19;

            xmax=-1.0e19;
            ymax=-1.0e19;
            zmax=-1.0e19;

            for(n=0;n<G10;++n)
            {
            xmax=MAX(xmax,G12_x*G10_x[n]);
            xmin=MIN(xmin,G12_x*G10_x[n]);
            ymax=MAX(ymax,G12_y*G10_y[n]);
            ymin=MIN(ymin,G12_y*G10_y[n]);
            zmax=MAX(zmax,G12_z*G10_z[n]);
            zmin=MIN(zmin,G12_z*G10_z[n]);
            }

            if(B10==0)
            {
            B10=1;
            B10_xs = new double[B10];
            B10_xe = new double[B10];

            B10_ys= new double[B10];
            B10_ye= new double[B10];

            B10_zs = new double[B10];
            B10_ze = new double[B10];
            }

            B10_xs[0] = xmin-G21_x;
            B10_xe[0] = xmax+G22_x;

            B10_ys[0]= ymin-G21_y;
            B10_ye[0]= ymax+G22_y;

            B10_zs[0] = zmin-G21_z;
            B10_ze[0] = zmax+G22_z;

            B10=1;


            if(G20==2)
            {
                for(n=0;n<G10;++n)
                {
                G10_x[n]-=xmin;
                G10_y[n]-=ymin;
                G10_z[n]-=zmin;
                }

                B10_xs[0] -= xmin;
                B10_xe[0] -= xmin;

                B10_ys[0] -= ymin;
                B10_ye[0] -= ymin;

                B10_zs[0] -= zmin;
                B10_ze[0] -= zmin;
            }
        }
	}
}