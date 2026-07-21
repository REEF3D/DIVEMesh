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
#include <fstream>

void lexer::read_control_preread()
{
    char c;
    int numint,numval;
    int count;
    numlinsurf=0;

    cout<<"read control"<<endl;

    ifstream control("control.txt", ios_base::in);

    if(!control)
    {
        cout<<"no 'control.txt' file"<<endl<<endl;
        exit(1);
    }

    count=0;
    while(!control.eof())
    {
        control>>c;

        if (c == '/')
        {
            control.ignore(1000, '\n');
        }
        else
        {
            switch(c)
            {
            case 'B': control>>numint;
                switch(numint)
                {
                case 3: control>>B3_dx>>B3_dy;
                         B3=1;
                         clear(c,numint);
                         break;
                case 4: control>>B4;
                         alpha_grid = (PI/180.0)*B4;
                         clear(c,numint);
                         break;
                case 10: ++B10;
                         clear(c,numint);
                         break;
                }
                break;

            case 'S':
            case 'O':
            control>>numint;
                switch(numint)
                {
                case 1: control>>S1;
                         clear(c,numint);
                         break;
                case 2: control>>S2;
                         clear(c,numint);
                         break;
                case 3: control>>S3_xs>>S3_xe>>S3_ys>>S3_ye>>S3_zs>>S3_ze;
                         S3=1;
                         clear(c,numint);
                         break;
                case 4: control>>S4;
                         clear(c,numint);
                         break;
                case 5: control>>S5_x>>S5_y>>S5_z>>S5_phi>>S5_theta>>S5_psi;
                         S5=1;
                         clear(c,numint);
                         break;
                case 7: control>>S7_dx>>S7_dy>>S7_dz;
                         S7=1;
                         clear(c,numint);
                         break;
                case 8: control>>S8;
                         clear(c,numint);
                         break;
                }
                break;

            case 'T':
            control>>numint;
                switch(numint)
                {
                case 1: control>>T1;
                         clear(c,numint);
                         break;
                case 2: control>>T2;
                         clear(c,numint);
                         break;
                case 3: control>>T3_xs>>T3_xe>>T3_ys>>T3_ye>>T3_zs>>T3_ze;
                         T3=1;
                         clear(c,numint);
                         break;
                case 4: control>>T4;
                         clear(c,numint);
                         break;
                case 5: control>>T5_x>>T5_y>>T5_z>>T5_phi>>T5_theta>>T5_psi;
                          T5=1;
                         clear(c,numint);
                         break;
                case 7: control>>T7_dx>>T7_dy>>T7_dz;
                         T7=1;
                         clear(c,numint);
                         break;
                case 8: control>>T8;
                         clear(c,numint);
                         break;
                }
                break;
            }
            ++count;
        }

        if(count>1e7)
        {
            cout<<endl;
            cout<<"!!! missing input parameter in control.txt !!!"<<endl<<endl;
            cout<<"!!! please check the DIVEMesh User Guide !!!"<<endl<<endl<<endl<<endl;

            exit(1);
        }
    }
    control.close();
    control.clear();

    // re-read
    Darray(B10_xs,B10);
    Darray(B10_xe,B10);
    Darray(B10_ys,B10);
    Darray(B10_ye,B10);
    Darray(B10_zs,B10);
    Darray(B10_ze,B10);

    int countB10=0;

    control.open("control.txt", ios_base::in);
    while(!control.eof())
    {
        control>>c;
        switch(c)
        {
            case 'B': control>>numint;
                switch(numint)
                {
                case 10: control>>B10_xs[countB10]>>B10_xe[countB10]>>B10_ys[countB10]>>B10_ye[countB10]>>B10_zs[countB10]>>B10_ze[countB10];
                         ++countB10;
                         clear(c,numint);
                         break;
                }
                break;

        }
    }

    control.close();
}
