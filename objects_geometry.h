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

#include<iostream>
#include"field.h"
#include"lexer.h"
#include"resize.h"

class lexer;
class dive;

using namespace std;

#ifndef OBJECTS_GEOMETRY_H_
#define OBJECTS_GEOMETRY_H_

class objects_geometry : public increment
{
public:
    objects_geometry();
    virtual ~objects_geometry();

    virtual void start(lexer*,dive*);
	

private:
	virtual void box(lexer*,dive*,int);
	virtual void wedge(lexer*,dive*,int);
	virtual void conical(lexer*,dive*,int);
	virtual void cylinder_y(lexer*,dive*,int);
	virtual void cylinder_z(lexer*,dive*,int);
	
	int qn;

};


#endif
