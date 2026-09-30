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

#ifndef KRIGING_H_
#define KRIGING_H_

#include "interpolation.h"
#include "increment.h"
#include <vector>

class lexer;
class dive;

using namespace std;

// Ordinary kriging with a spherical semivariogram.
// G 15 3: global kriging, all geodat points in one system
// G 15 4: local kriging, the G 16 nearest geodat points for each grid cell

class kriging final : public interpolation, public increment
{
public:
    kriging(lexer*,dive*,int,double*,double*,double*);
    virtual ~kriging();

    void start(lexer*,dive*,int,double*,double*,double*,double*,double*,int,int,double**) override final;

private:
    void ini(lexer*,dive*,int,double*,double*,double*);

    void start_global(lexer*,int,double*,double*,double*,double*,double*,int,int,double**);
    void start_local(lexer*,int,double*,double*,double*,double*,double*,int,int,double**);

    void decomp(vector<double>&, vector<int>&, int);
    void solve(const vector<double>&, const vector<int>&, vector<double>&, int);
    static void solve_small(double*, double*, int);

    // spherical semivariogram: variance*(1.5*h/range - 0.5*(h/range)^3)
    inline double semivariogram(double dist) const
    {
        if(dist<range)
            return dist*(c1 - c3*dist*dist);
        else
            return variance;
    }

    double variance, range;
    double c1, c3;

    bool local;
    int nnb;
};

#endif
