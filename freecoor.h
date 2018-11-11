/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2018 Hans Bihs

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
--------------------------------------------------------------------*/

#include"increment.h"

class lexer;
class dive;
class entity;
class cce;
class flag_indicate;
class surfdir_indicate;

using namespace std;

#ifndef FREECOOR_H_
#define FREECOOR_H_

class freecoor : public increment
{
public:
    freecoor(lexer*,dive*);
    virtual ~freecoor();

    virtual void start(lexer*,dive*);

private:
    void presort_entities(lexer*,int**,int);
    void sort_entities(lexer*,int**,int);

    int n;
	int num_ent_l, num_ent_r;
    entity **pel, **per;
	entity **pent_l, **pent_r;
    cce *pcce;
    flag_indicate *pflag;
    surfdir_indicate *psurf;

    int **left_ent, **right_ent;

};

#endif

