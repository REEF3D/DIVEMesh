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

#ifndef TOPO_H_
#define TOPO_H_

#include"geometry.h"
#include"intfield.h"

class lexer;
class dive;

using namespace std;

class topo : public geometry
{
public:
    topo(lexer*,dive*);
    virtual ~topo();

    void start(lexer*,dive*);
    void gcb_estimate(lexer*,dive*);
};

#endif
