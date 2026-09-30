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

#ifndef FIELD_H_
#define FIELD_H_

#include"increment.h"
#include<vector>

class lexer;

class field : public increment
{
public:
    field(lexer*);
    field(const field&) = delete;
    field& operator=(const field&) = delete;

    inline double& operator()(int ii, int jj, int kk)
    {
        return feld[((size_t)(ii+xma)*nj + (size_t)(jj+yma))*nk + (size_t)(kk+zma)];
    };

private:
    // contiguous storage, index (i,j,k) -> ((i+xma)*nj + j+yma)*nk + k+zma
    size_t nj, nk;
    std::vector<double> feld;
};

#endif
