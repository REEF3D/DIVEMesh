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

#ifndef PRINT_VTU_H_
#define PRINT_VTU_H_

#include"printer.h"
#include"increment.h"

class print_vtu : public printer, public increment
{
public:
    print_vtu(lexer*);
    virtual ~print_vtu() = default;
    void start(lexer*,dive*) override;
private:
    double ipol(dive*,field&);
};

#endif
