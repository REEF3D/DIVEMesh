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
Author: Tobias Martin
--------------------------------------------------------------------*/

#include "lexer.h"
#include <vector>
#include <algorithm>

double lexer::cellBasedSpacing
(
const double& coord_start, 
const double& coord_end, 
const double& focus_point, 
const double& delta_focus,
const double& minDx, 
const double& maxDx, 
const double& cellRatio
)
{
    int nKnot = 0;
    
    cellBasedSpacing(coord_start, coord_end, focus_point, delta_focus, minDx, maxDx, cellRatio, nKnot);
    
    return nKnot;
}

void lexer::cellBasedSpacing
(
const double& coord_start, 
const double& coord_end, 
const double& focus_point, 
const double& delta_focus_aim,
const double& minDx, 
const double& maxDx, 
const double& cellRatio,
int& cellIndex
)
{
    double delta_focus = delta_focus_aim;
    double z_1 = coord_start;
    double z_2 = focus_point - delta_focus/2;
    double z_3 = focus_point + delta_focus/2; 
    double z_4 = coord_end; 


    // Check mesh
    double dz = minDx;
    vector<double> CN;
    CN.push_back(z_2);
    
    int index = 1;
    for (int i = 1; i < 10000; i++)
    {
        dz = cellRatio*dz;
        if (dz > maxDx)
        {
            dz = maxDx;
        }
        
        CN.push_back(CN[index - 1] - dz);
        index++;
        
        if (CN.back() < z_1)
        {
            CN.back() = z_1;
            break;
        }
    }
    reverse(CN.begin(), CN.end());

    if ((CN[2] - CN[1])/(CN[1] - CN[0]) > cellRatio)
    {  
        z_2 = focus_point - delta_focus/2 - (CN[1] - CN[0]);
    }

    delta_focus = z_3 - z_2;
    double nKnot = round(delta_focus/minDx);
    dz = delta_focus/nKnot;

    for (int i = 0; i < nKnot-1; i++)
    {
        CN.push_back(CN[index - 1] + dz);
        index++;
    }

    dz = minDx;
    CN.push_back(z_3);
    index++;

    for (int i = 1; i < 10000; i++)
    {
        dz = cellRatio*dz;
        if (dz > maxDx)
        {
            dz = maxDx;
        }

        CN.push_back(CN[index - 1] + dz);
        index++; 

        if (CN.back() > z_4)
        {
            CN.back() = z_4;
            break;
        }
    }

    int size = CN.size();

    if ((CN[size-2] - CN[size-3])/(CN[size-1] - CN[size-2]) > cellRatio)
    {
        z_3 = focus_point + delta_focus/2 + fabs(CN.back() - CN[size-2])/2.0;
    }


    // Generate mesh
    
    CN.clear();
    dz = minDx;
    CN.push_back(z_2);
    index = 1;

    for (int i = 1; i < 10000; i++)
    {
        dz = cellRatio*dz;
        if (dz > maxDx)
        {
            dz = maxDx;
        }
    
        CN.push_back(CN[index - 1] - dz);
        index++;
        
        if (CN.back() < z_1)
        {
            CN.back() = z_1;
            break;
        }
    }
    reverse(CN.begin(), CN.end());
    
    delta_focus = z_3 - z_2;
    nKnot = round(delta_focus/minDx);
    dz = delta_focus/nKnot;

    for (int i = 0; i < nKnot-1; i++)
    {
        CN.push_back(CN[index - 1] + dz);
        index++;
    }

    dz = minDx;
    CN.push_back(z_3);
    index++;

    for (int i = 1; i < 10000; i++)
    {
        dz = cellRatio*dz;
        if (dz > maxDx)
        {
            dz = maxDx;
        }
        
        CN.push_back(CN[index - 1] + dz);
        index++;
        
        if (CN.back() > z_4)
        {
            CN.back() = z_4;
            break;
        }
    }

    // Correction
    
    if ((CN[1] - CN[0]) < 1e-3)
    {
        vector<double>::iterator it_;
        it_ = CN.begin();
        CN.erase(it_);
        CN[0] = z_1;
    }

    size = CN.size();

    if (((CN[size-1]-CN[size-2]) < 1e-3) || ( (CN[size-1]-CN[size-2])/(CN[size-2]-CN[size-3]) < 0.3 ))
    {
        CN.pop_back();
        CN.back() = z_4;
    }
    else if ( (CN[size-1]-CN[size-2])/(CN[size-2]-CN[size-3]) < 0.7 )
    {
        double d = (CN.back()-CN[size-3])/2.0;
        CN.pop_back();
        CN.pop_back();
        CN.push_back(CN.back() + d);
        CN.push_back(z_4);
    }


    // Determine field size
    if (cellIndex == 0)
    {
        cellIndex = CN.size() - 1;
    }
    else
    {
        // Write field

        if (cellIndex == 1)  // x-field
        {
            for (int i = 0; i <= knox; i++)
            {
                XN[i + marge] = CN[i];
            }
        }
        else if (cellIndex == 2) // y-field
        {
            for (int i = 0; i <= knoy; i++)
            {
                YN[i + marge] = CN[i];
            }
        }
        else    // z-field
        {
            for (int i = 0; i <= knoz; i++)
            {
                ZN[i + marge] = CN[i];
            }
        }
    }
}
