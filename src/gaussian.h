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

#ifndef GAUSSIAN_H_
#define GAUSSIAN_H_

#include "interpolation.h"
#include "increment.h"

class lexer;
class dive;

using namespace std;

class gaussian final : public interpolation, public increment
{
public:
    gaussian(lexer*,dive*);
    virtual ~gaussian() = default;

    void start(lexer*,dive*,int,double*,double*,double*,double*,double*,int,int,double**) override final;

private:
    double gxy(lexer*,int,int,double*,double*,double*,double*,double*);
    void setup(lexer*,dive*,double*,double*,double*,double*,double*,int,int);

    double sigmaP2M2,cutoff;
    int Nx,Ny;

    int **ptnum,***ptid;

    int dij;

    static constexpr int dd = 3;
};

#endif
