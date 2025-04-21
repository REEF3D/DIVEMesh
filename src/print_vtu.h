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

#include<iostream>
#include<fstream>

#include"printer.h"
#include"increment.h"

using namespace std;

#ifndef PRINT_VTU_H_
#define PRINT_VTU_H_

using namespace std;

class print_vtu : public printer, public increment
{

public:
	print_vtu(lexer*);
	virtual ~print_vtu();
	virtual void start(lexer*,dive*);

private:
    double ipol(dive*,field&);
    char name[200],pname[200],epsvar[200];
    int n,iin,offset[200];
    float ffn;
    
    double v1,v2,v3,v4,v5,v6,v7,v8;
    double value;
};

#endif

