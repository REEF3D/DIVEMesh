/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2025 Hans Bihs

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

#include"increment.h"

class lexer;
class dive;

using namespace std;

#ifndef DATASET_H_
#define DATASET_H_

class dataset : public increment
{
public:
    dataset(lexer*,dive*);
    virtual ~dataset();

    virtual void start(lexer*,dive*);
	double inverse_dist_2D(lexer*, dive*);
	double inverse_dist_w(lexer*);

private:
	
	double g,wsum,dist;
    double xc,yc;
    double ddn;
    int iin;
    float ffn;
};

#endif


