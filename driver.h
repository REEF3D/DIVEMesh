/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2020 Hans Bihs

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
#include<fstream>
#include"driver_declarations.h"
#include"increment.h"

#ifndef DRIVER_H_
#define DRIVER_H_

using namespace std;

class driver : public increment
{
public:

    driver();
    virtual ~driver();
    void mainloop();
	void logic(lexer*);
	void analytics(lexer*,dive*);
	
	int conlev(int);

	lexer *p;
	dive *a;
	box_bl *pbox_bl;
    printer *pprint;
    surface *psurf;
    decomp *pdd;
    initialize *pini;
    bc *pbc;
    freecoor *pfree;
    objects *pobj;
    box *pbox;
    baselayer *pbase;
    geodat *pgeo;
	data *pdata;
	objects_geometry *objgeo;
	print_objects *objprint;
	solid *psolid;
    slice *pslice;
    bedlevel *pbed;
    wcp *pwcp;

	//driver ();

	double **input;
	double *header;
	int **boundary;
	int **surf_in;
	int **surf_out;
	int **surf_fsf;
	int **surf_wall;
	int **surf_bed;
	
	int **flagmg;
	int l,h;
	int cellnum;
	
	ofstream mgout;
};


#endif
