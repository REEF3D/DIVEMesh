/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2023 Hans Bihs

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
#include<fstream>

#include"printer.h"
#include"increment.h"

using namespace std;

#ifndef PRINT_BINARY_H_
#define PRINT_BINARY_H_

class print_grid : public printer, public increment
{
public:
    print_grid(lexer*);
    virtual ~print_grid();

    virtual void start(lexer*,dive*);
    void print_debug(lexer*,dive*);
    
    void print_bottom(lexer*,dive*);

private:
    int count;
    int q,qq;
    int i_old,j_old;
    int bcount;
};

#endif
