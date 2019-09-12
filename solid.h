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
#include"intfield.h"

class lexer;
class dive;

using namespace std;

#ifndef SOLID_H_
#define SOLID_H_

class solid : public increment
{
public:
    solid(lexer*,dive*);
    virtual ~solid();

    virtual void start(lexer*,dive*);
	void gcb_estimate(lexer*,dive*);
	void gcb(lexer*,dive*);
	void dist(lexer*,dive*);
	void ray_cast(lexer*,dive*,int,int);
    void ray_cast_io(lexer*,dive*,int,int);
    void ray_cast_correct(lexer*,dive*,int,int);
	void ray_cast_x(lexer*,dive*,int,int);
	void ray_cast_y(lexer*,dive*,int,int);
	void ray_cast_z(lexer*,dive*,int,int);
    void ray_cast_x_gcb(lexer*,dive*,int,int);
	void ray_cast_stl(lexer*,dive*);
    void stl_preproc(lexer*,dive*,int&,int&);
    void stl_postproc(lexer*,dive*,int&,int&);
	void box(lexer*,dive*,int,int&,int&);
	void box_array(lexer*,dive*,int,int&,int&);
	void cylinder_y(lexer*,dive*,int,int&,int&);
    void cylinder_z(lexer*,dive*,int,int&,int&);
	void cone_x(lexer*,dive*,int,int&,int&);
	void cone_y(lexer*,dive*,int,int&,int&);
	void cone_z(lexer*,dive*,int,int&,int&);
	void wedge_x(lexer*,dive*,int,int&,int&);
	void wedge_y(lexer*,dive*,int,int&,int&);
	void wedge_z(lexer*,dive*,int,int&,int&);
    void hexahedron(lexer*,dive*,int,int&,int&);
    void wedge(lexer*,dive*,int,int&,int&);
    void tetrahedon(lexer*,dive*,int,int&,int&);
    void pyramid(lexer*,dive*,int,int&,int&);
	void ogee_weir(lexer*,dive*,int,int&,int&);
	void semicyl_y(lexer*,dive*,int,int&,int&);
    void arch(lexer*,dive*,int,int&,int&);
    void sphere(lexer*,dive*,int,int&,int&);
    void ellipsoid(lexer*,dive*,int,int&,int&);
    void ellipsoid_semi(lexer*,dive*,int,int&,int&);
    void ellipsoid_semi_rot(lexer*,dive*,int,int&,int&);
    void jacket_member_x(lexer*,dive*,int,int&,int&);
    void jacket_member_y(lexer*,dive*,int,int&,int&);
    void jacket_member_z(lexer*,dive*,int,int&,int&);
    void jacket_member_norm(lexer*,dive*,int,int&,int&);
    void jacket_member_vert(lexer*,dive*,int,int&,int&);
    void jacket_member_horz(lexer*,dive*,int,int&,int&);
    void plate_x(lexer*,dive*,int,int&,int&);
    void fluvial_box(lexer*,dive*,int,int&,int&);
    
	
	void rotation(double&,double&,double&,double,double,double);
	void rotate_triangle(lexer*,dive*,int,int);
    
    
    double xtrans(double,double,double,double,double,double,double,double,double);
    double ytrans(double,double,double,double,double,double,double,double,double);
    double ztrans(double,double,double,double,double,double,double,double,double);
    
    void rotation_ellipsoid(lexer*,int,double&,double&,double&);
	void rotate_triangle_ellipsoid(lexer*,dive*,int,int,int);
    
    void angle_calc(double,double,double,double&,double&,double&);

	
private:
    void sort(double*, int, int);
    
    int rayiter,ts_stl,te_stl,tricount_stl;   
    
	intfield cutl,cutr;
    int n,count;
	int tri_start,tri_end;
    double xs,ys,zs,xe,ye,ze;
	double phi,theta,psi;
	double xrot,yrot,zrot;
	double L,G;
    double ***is_R;
    int **is_num;
    int is_count;
    int maxpt;
    const double epsi;
};

#endif

