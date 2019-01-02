/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2019 Hans Bihs

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

#include"printer.h"
#include"increment.h"

class lexer;
class dive;

#ifndef PRINT_OBJECTS_H_
#define PRINT_OBJECTS_H_

using namespace std;

class print_objects :  public increment
{

public:
	print_objects(lexer*,dive*);
	virtual ~print_objects();
	virtual void start(lexer*,dive*);

private:

    char name[100],pname[100],epsvar[100];
    int n,iin,offset[100];
    float ffn;
};

#endif


