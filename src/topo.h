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

#include"geometry.h"
#include"intfield.h"

class lexer;
class dive;

using namespace std;

#ifndef TOPO_H_
#define TOPO_H_

class topo : public geometry
{
public:
    topo(lexer*,dive*);
    virtual ~topo();

    virtual void start(lexer*,dive*);
	void gcb_estimate(lexer*,dive*);

    // fluvial box
    void fluvial_box(lexer*,dive*,int,int&,int&);
    void fluvial_box_fill_segments(lexer*,dive*,int,int&,int&);
    void fluvial_box_v1(lexer*,dive*,int,int&,int&);
    void fluvial_box_v2(lexer*,dive*,int,int&,int&);
    
private:
    double xs,ys,zs,xe,ye,ze;
	double L,G;
    double ***is_R;
    int **is_num;
    int is_count;
    int maxpt;

    
    // fluvial box
    void fluvial_box_move(lexer*,dive*);
    void fluvial_box_extend(lexer*,dive*);
    
    int countS310;
    int countS320;
    int countS330;
    int countS340;
    int countds;
    int numds;
    int ds_count;
    double dangle,length;
    double *xl,*yl,*xr,*yr;
    double x0; // add origin afterwards
    double y0; // add origin
    double phi0;
    double deltax,deltay;
    int lastds;
    int fluvial_outflow_side;
    double box_xs,box_xe,box_ys,box_ye,box_zs,box_ze;
    
    double nx,ny,norm,xc,yc,x1,y1,teta,ds,m,s;
};

#endif

