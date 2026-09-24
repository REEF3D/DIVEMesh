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

#include"lexer.h"
#include<iomanip>
#include<cmath>

void lexer::createspace()
{
    if(B2==0)
    {
        knox = std::round((xmax-xmin)/dx);
        knoy = std::round((ymax-ymin)/dx);
        knoz = std::round((zmax-zmin)/dx);
    }
    else if(B2==1)
    {
        knox = B2_knox;
        knoy = B2_knoy;
        knoz = B2_knoz;
    }

    if(B101==8)
    {
        knox = B121_N1 + B121_N2 + B121_N3;
    }
    else if(B101==9)
    {
        knox = B124_N1 + B124_N2 + B124_N3;
    }
    else if(B101==10)
    {
        char name[100];
        int count;
        double val,val0;

        sprintf(name,"x-spacing.dat");

        // open file------------
        ifstream file(name, ios_base::in);

        if(!file)
        {
            cout<<endl<<("no 'x-spacing.dat' file found")<<endl<<endl;
        }

        val=0.0;
        val0=0.0;
        count=0;
        while(!file.eof())
        {
            val0=val;
            file>>val;
            ++count;
        }

        file.close();

        knox=count-1;

        if(val0==val)
        knox--;
    }
    else if (B101 == 11)
    {
        knox = cellBasedSpacing(xmin, xmax, B127_pf, B127_df, B127_dx_min, B127_dx_max, B127_r);
    }

    if(B102==8)
    {
        knoy = B122_N1 + B122_N2 + B122_N3;
    }
    else if(B102==9)
    {
        knoy = B125_N1 + B125_N2 + B125_N3;
    }
    else if(B102==10)
    {
        char name[100];
        int count;
        double val,val0;

        sprintf(name,"y-spacing.dat");

        // open file------------
        ifstream file(name, ios_base::in);

        if(!file)
        {
            cout<<endl<<("no 'y-spacing.dat' file found")<<endl<<endl;
        }

        val=0.0;
        val0=0.0;
        count=0;
        while(!file.eof())
        {
            val0=val;
            file>>val;
            ++count;
        }

        file.close();

        knoy=count-1;

        if(val0==val)
        knoy--;
    }
    else if (B102 == 11)
    {
        knoy = cellBasedSpacing(ymin, ymax, B128_pf, B128_df, B128_dx_min, B128_dx_max, B128_r);
    }

    if(B103==8)
    {
        knoz = B123_N1 + B123_N2 + B123_N3;
    }
    else if(B103==9)
    {
        knoz = B126_N1 + B126_N2 + B126_N3;
    }
    else if(B103==10)
    {
        char name[100];
        int count;
        double val,val0;


        sprintf(name,"z-spacing.dat");

        // open file------------
        ifstream file(name, ios_base::in);

        if(!file)
        {
            cout<<endl<<("no 'z-spacing.dat' file found")<<endl<<endl;
        }

        val=0.0;
        val0=0.0;
        count=0;
        while(!file.eof())
        {
        val0=val;
        file>>val;
        ++count;
        }

        file.close();

        knoz=count-1;

        if(val0==val)
        knoz--;
    }
    else if (B103 == 11)
    {
        knoz = cellBasedSpacing(zmin, zmax, B129_pf, B129_df, B129_dx_min, B129_dx_max, B129_r);
    }


    if(B2==0)
    {
        DXM = dx;
    }
    else if(B2==1)
    {
        DXM = dx = (1./3.0) * ((xmax-xmin)/double(knox) + (ymax-ymin)/double(knoy) + (zmax-zmin)/double(knoz));
    }

    cout<<"DXM: "<<DXM<<endl;

    cout<<"xma: "<<xma<<" yma: "<<yma<<" zma: "<<zma<<endl;
    cout<<"xmin: "<<xmin<<" ymin: "<<ymin<<" zmin: "<<zmin<<endl;
    cout<<"xmax: "<<xmax<<" ymax: "<<ymax<<" zmax: "<<zmax<<endl;
    cout<<"knox: "<<knox<<" knoy: "<<knoy<<" knoz: "<<knoz<<endl;
    cout<<"base_cellnum3D: "<<knox*knoy*knoz<<endl;
    cout<<"base_cellnum2D: "<<knox*knoy<<endl;

    cout<<"field: "<<(knox+2*xma)*(knoy+2*yma)*(knoz+2*zma)<<endl;
    cout<<"slice: "<<(knox+2*xma)*(knoy+2*yma)<<endl<<endl;
}

void lexer::tri_space()
{
    trinum = trinum_stl+trinum_solid+trinum_topo;

    // create arrays
    Darray(tri_x,trinum,3);
    Darray(tri_y,trinum,3);
    Darray(tri_z,trinum,3);

    Darray(trivec_x,trinum);
    Darray(trivec_y,trinum);
    Darray(trivec_z,trinum);

    cout<<"TRINUM: "<<trinum<<endl;
}
