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

#ifndef INVERSE_DIST_LOCAL_H_
#define INVERSE_DIST_LOCAL_H_

#include "interpolation.h"
#include "increment.h"
#include <vector>

class lexer;
class dive;

using namespace std;

class inverse_dist_local final : public interpolation, public increment
{
public:
    inverse_dist_local(lexer*,dive*);
    virtual ~inverse_dist_local() = default;

    void start(lexer*,dive*,int,double*,double*,double*,double*,double*,int,int,double**) override final;

private:
    double gxy(lexer*,int,int,double*,double*);
    void setup(lexer*,dive*,double*,double*,double*,double*,double*,int,int);

    // number of points in bins [r0..r1] x [s0..s1] (bin indices incl. dd offset)
    inline long long window_count(int r0, int r1, int s0, int s1) const
    {
        return sat[size_t(r1+1)*(Ny+1)+s1+1] - sat[size_t(r0)*(Ny+1)+s1+1]
             - sat[size_t(r1+1)*(Ny+1)+s0] + sat[size_t(r0)*(Ny+1)+s0];
    }

    int Nx,Ny;
    int dij;
    double smooth_lengthP4;

    // points sorted by bin (bin = (ic+dd)*Ny + jc+dd), original order kept inside a bin
    std::vector<int> binstart;
    std::vector<double> bx,by,bz;
    // summed-area table of points per bin, (Nx+1) x (Ny+1)
    std::vector<long long> sat;

    static constexpr int dd = 3;
};

#endif
