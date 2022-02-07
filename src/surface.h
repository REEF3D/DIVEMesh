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

#include<iostream>
#include"increment.h"

class lexer;
class dive;
class field;

using namespace std;

#ifndef SURFACE_H_
#define SURFACE_H_

class surface : public increment
{
public:

    surface();
    virtual ~surface();
    void start(lexer*,dive*);

    void makesurf(lexer*,dive*);
    void makedist(lexer*,dive*);
    void direction(lexer*,dive*);
	void mem_alloc(lexer*,dive*);
    void make_solidsurf(lexer*,dive*);
    void makesurfsolid(lexer*,dive*);
    
    
    void mem_alloc_plate(lexer*,dive*);
    void makesurf_plate(lexer*,dive*);


private:

    
    int surfnum;
};

#endif
