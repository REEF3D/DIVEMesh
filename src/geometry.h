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

#include"increment.h"
#include"intfield.h"

class lexer;
class dive;
class field;
class field2d;

using namespace std;

#ifndef GEOMETRY_H_
#define GEOMETRY_H_

class geometry : public increment
{
public:
    geometry(lexer*,dive*);
    virtual ~geometry();
    virtual void start(lexer*,dive*);
    
    // entities
	void box(lexer*,dive*,int,int&,int&,double,double,double,double,double,double);
	void box_array(lexer*,dive*,intfield&,field&,field2d&,int,int&,int&, double, double, double, double, double, int, int, int);
    void beam(lexer*,dive*,int,int&,int&,double,double,double,double,double,double,double,double);
	void cylinder_y(lexer*,dive*,int,int&,int&,double,double,double,double,double,double);
    void cylinder_z(lexer*,dive*,int,int&,int&,double,double,double,double,double,double);
	void cone_x(lexer*,dive*,int,int&,int&,double,double,double,double,double,double);
	void cone_y(lexer*,dive*,int,int&,int&,double,double,double,double,double,double);
	void cone_z(lexer*,dive*,int,int&,int&,double,double,double,double,double,double);
	void wedge_x(lexer*,dive*,int,int&,int&,double,double,double,double,double,double);
	void wedge_y(lexer*,dive*,int,int&,int&,double,double,double,double,double,double);
	void wedge_z(lexer*,dive*,int,int&,int&,double,double,double,double,double,double);
    void hexahedron(lexer*,dive*,int,int&,int&,double**);
    void wedge(lexer*,dive*,int,int&,int&,double**);
    void tetrahedon(lexer*,dive*,int,int&,int&,double**);
    void pyramid(lexer*,dive*,int,int&,int&,double**);
	void ogee_weir(lexer*,dive*,int,int&,int&,double,double,double,double,double,double,double,double,double,double,double,double);
	void semicyl_y(lexer*,dive*,int,int&,int&,double,double,double,double,double,double);
    void arch(lexer*,dive*,int,int&,int&,double,double,double,double,double,double,double);
    void sphere(lexer*,dive*,int,int&,int&,double,double,double,double);
    void ellipsoid(lexer*,dive*,int,int&,int&,double,double,double,double,double,double);
    void ellipsoid_semi(lexer*,dive*,int,int&,int&,double,double,double,double,double,double,double);
    void ellipsoid_semi_rot(lexer*,dive*,int,int&,int&,double,double,double,double,double,double,double);
    void jacket_member_norm(lexer*,dive*,int,int&,int&,double,double,double,double,double,double,double,double);
    void plate_x(lexer*,dive*,int,int&,int&,double,double,double,double,double);
    
    //STL
    void ray_cast(lexer*,dive*,int,int,intfield&,field&,field2d&);
    void ray_cast_io_x(lexer*,dive*,int,int,intfield&,field&);
    void ray_cast_io_ycorr(lexer*,dive*,int,int,intfield&,field&);
    void ray_cast_io_zcorr(lexer*,dive*,int,int,intfield&,field&);
	void ray_cast_x(lexer*,dive*,int,int,intfield&,field&);
	void ray_cast_y(lexer*,dive*,int,int,intfield&,field&);
	void ray_cast_z(lexer*,dive*,int,int,intfield&,field&,field2d&);
    void ray_cast_x_gcb(lexer*,dive*,int,int,intfield&,field&);
    void stl_preproc(lexer*,dive*,int&,int&);
    void stl_postproc(lexer*,dive*,int&,int&,intfield&,field&,int);
    
    // fluvial box
    void fluvial_box_fill_segments(lexer*,dive*,int,int&,int&);
    void fluvial_box_v1(lexer*,dive*,int,int&,int&);
    void fluvial_box_v2(lexer*,dive*,int,int&,int&);
    void fluvial_box_move(lexer*,dive*);
    void fluvial_box_extend(lexer*,dive*);
	
	void rotation(double&,double&,double&,double,double,double);
	void rotate_triangle(lexer*,dive*,int,int);
    
    
    double xtrans(double,double,double,double,double,double,double,double,double);
    double ytrans(double,double,double,double,double,double,double,double,double);
    double ztrans(double,double,double,double,double,double,double,double,double);
    
    void rotation_ellipsoid(lexer*,int,double&,double&,double&,double,double,double);
	void rotate_triangle_ellipsoid(lexer*,dive*,int,int,int,double,double,double);
    
    void angle_calc(double,double,double,double&,double&,double&);
    
    // common variables
    int rayiter,ts_stl,te_stl,tricount_stl; 
	double phi,theta,psi;
	double xrot,yrot,zrot;
    int n,count;
	int tri_start,tri_end;
    
    //fluvial box variables
    int G300,G300_ds;
    int *G300_ord;
    int G301;
    double G305,G306,G307_fh,G307_bh,G308_x,G308_y,G308_z,G309_x,G309_y,G309_z;
    int G310;
    double *G310_l;
    int G320;
    double *G320_r,*G320_phi;
    int G330;
    double *G330_r,*G330_phi;
    int G340;
    double *G340_teta,*G340_L,*G340_N,*G340_ds;
    
    double *xl,*yl,*xr,*yr;
    int countds;
    int numds;
    int ds_count;
    
private:
    void sort(double*, int, int);
    
	intfield cutl,cutr;
    
    double xs,ys,zs,xe,ye,ze;
	
	double L,G;
    double ***is_R;
    int **is_num;
    int is_count;
    int maxpt;
    const double epsi;
    
    // fluvial box
    int countG310;
    int countG320;
    int countG330;
    int countG340;
    
    double dangle,length;
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

