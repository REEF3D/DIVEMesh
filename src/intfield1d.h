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

#ifndef INTFIELD1D_H_
#define INTFIELD1D_H_

#include"increment.h"
#include<vector>

class lexer;

class intfield1d : public increment
{
public:
    intfield1d(lexer*);
    intfield1d(const intfield1d&) = delete;
    intfield1d& operator=(const intfield1d&) = delete;

    inline int& operator()(int ii)
    {
        return feld[(size_t)(ii+xma)];
    };

private:
    // contiguous storage, index (i,j,k) -> ((i+xma)*nj + j+yma)*nk + k+zma
    std::vector<int> feld;
};

#endif
