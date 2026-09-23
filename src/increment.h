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

#ifndef INCREMENT_H_
#define INCREMENT_H_

#include "iterators.h"
#include "looping.h"

#include <iostream>
#include <math.h>

inline constexpr double PI = 3.14159265359;

using namespace std;

struct increment
{
protected:
    increment() = default;
    ~increment() = default;

public:
    static inline int i = 0, j = 0, k = 0;
    static inline int aa = 0, bb = 0, cc = 0;
    static inline int n = 0, q = 0, qn = 0;

    static constexpr int xma = 3, yma = 3, zma = 3;
    static constexpr int marge = 5;
};
#endif
