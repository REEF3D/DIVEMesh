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

#include"increment.h"

class lexer;
class dive;

using namespace std;

#ifndef WCP_H_
#define WCP_H_

class wcp : public increment
{
public:
    wcp(lexer*,dive*);
    virtual ~wcp();

    virtual void start(lexer*,dive*);
    
	void read(lexer*, dive*);
    void read_header(lexer*, dive*);
    void read_result(lexer*, dive*);
    
    void merge(lexer*,dive*);
    void decompa(lexer*,dive*);
	void write(lexer*,dive*);

private:
	
	double g,wsum,dist;
    double xc,yc;
};

#endif


