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

#include"print_binary.h"

void print_binary::print_debug(lexer* p, dive* a)
{

    char name[20];
    sprintf(name,"DIVE.MESH_debug.txt");
	ofstream result;
	result.open(name);

    result<<"partition: "<<a->mx<<" "<<a->my<<" "<<a->mz<<endl;

    result<<endl<<"--------------------------------------------------"<<endl;

    NLOOP
    {
    result<<aa<<" "<<bb<<" "<<cc<<" : "<<a->xnode[aa-1]<<" "<<a->ynode[bb-1]<<" "<<a->znode[cc-1];
    result<<" \t "<<a->xnode[aa]<<" "<<a->ynode[bb]<<" "<<a->znode[cc]<<endl;
    }

    result.close();
}

