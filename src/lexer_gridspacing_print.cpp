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

#include "lexer.h"

void lexer::gridspacing_print()
{
    ofstream gridPrint;
    gridPrint.open("gridSpacing.vtk", ios::binary);

    gridPrint << "# vtk DataFile Version 2.0" << endl;
    gridPrint << "Grid spacing" << endl;
    gridPrint << "ASCII" << endl;
    gridPrint << "DATASET RECTILINEAR_GRID" << endl;
    gridPrint << "DIMENSIONS " <<knox+1<<" "<<knoy+1<<" "<<knoz+1<<" "<< endl;

    gridPrint << "X_COORDINATES "<<knox+1<<" "<<" float"<<endl;
    for (i = 0; i <= knox; ++i)
    {
        gridPrint<<XN[IP]<<" ";
    }
    gridPrint<<endl;

    gridPrint << "Y_COORDINATES "<<knoy+1<<" "<<" float"<<endl;
    for (j = 0; j <= knoy; ++j)
    {
        gridPrint<<YN[JP]<<" ";
    }
    gridPrint<<endl;
    
    gridPrint << "Z_COORDINATES "<<knoz+1<<" "<<" float"<<endl;
    for (k = 0; k <= knoz; ++k)
    {
        gridPrint<<ZN[KP]<<" ";
    }
    gridPrint<<endl;    

    
    // If values should be added to the file, uncomment the following lines
    /*
    int nPoints = (knox + 1)*(knoy + 1)*(knoz + 1);
    
    gridPrint<<"\nPOINT_DATA " <<nPoints<<endl;
    gridPrint<<"SCALARS XXX float 1 \nLOOKUP_TABLE default"<<endl;

    for(int n=0; n < nPoints; ++n)
    {
        gridPrint<<n<<endl;
    }
    */

    gridPrint.close();
}