/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2018 Hans Bihs

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

#include"lexer.h"

void lexer::ini_default()
{


    xmax=0.0;       // xlength
    ymax=0.0;       // ylength
    zmax=0.0;       // zlength
    dx=0.0;     // deltax

    B1=0.0;         // double deltax
    B2=0;           // int cell size
    B2_knox=0;
    B2_knoy=0;
    B2_knoz=0;
	B5=1;			// int turn on true 2D
    B101=0;         // int grid spacing xdir
    B102=0;         // int grid spacing ydir
    B103=0;         // int grid spacing zdir
    B111=1.0;       // double factor grid spacing
    B112=1.0;       // double factor grid spacing
    B113=1.0;       // double factor grid spacing
    B114=0;         // int stretch position given xdir
    B115=0;         // int stretch position given ydir
    B116=0;         // int stretch position given zdir
	
	C11=21;          // C12
    C12=21;          // C12
    C13=21;          // C12
    C14=21;          // C12
    C15=21;          // C12
    C16=21;          // C12
	
	D10=0;            // int data off/on
    D11_x=0.0;       // double dx
    D11_y=0.0;       // double dy
    D11_z=0.0;       // double dz
    D12_x=1.0;       // double x factor
    D12_y=1.0;       // double y factor
    D12_z=1.0;       // double z factor
	D13=1; 			// int read ith line from gmdata
	D14=1;			// int interpolation scheme
	D15=0;			// int number of smoothing iterations
	D16=0.5;		// double factor for smoothing
	D17=16.0;		// double factor for ivd
	D18=0.3;		// double kringing range factor
    D19=0;              // int read letter in front of 3D coordinates
	D23=0;			// int reverse sign of vertical coordinate in geo.dat file
	D24=-10.0;

    F3_zs=0.0;         // double z-start
    F3_ze=0.0;         // double z-end
    F11=0;
    F12=0;
    F13=0;
    F21=0;
    F22=0;
    F23=0;
    F31=0;
    F32=0;
    F33=0;
    F41=0;
    F42=0;
    F43=0;

    G10=0;            // int geodata off/on
    G11_x=0.0;       // double dx
    G11_y=0.0;       // double dy
    G11_z=0.0;       // double dz
    G12_x=1.0;       // double x factor
    G12_y=1.0;       // double y factor
    G12_z=1.0;       // double z factor
	G13=0;			  // int turn geo coordinates
	G13_phi=0.0;     // doubel turn angle geo coordinates
	G14=0;			  // int read origin for turn angle
	G14_x=1.0;       // double x origin for turn angle
    G14_y=1.0;       // double y origin for turn angle
    G15=2;           // int interpolation scheme
    G16=0.0;         // double base topo level for local IDW
    G17=2;          // int dij limit
    G19=0;              // int read letter in front of 3D coordinates
    G20=0;              // int auto box
    G21_x=0.0;       // double dxmin
    G21_y=0.0;       // double dymin
    G21_z=0.0;       // double dzmin
    G22_x=0.0;       // double dxmax
    G22_y=0.0;       // double dymax
    G22_z=0.0;       // double dzmax
	G23=0;			// int reverse sign of vertical coordinate in geo.dat file
    G24=0;          // int raise dry side by a dz
    G25=0;          // int increase dry side by multiplication factor
    G31=0;          // int number of smoothing iterations
    G32=0.5;        // double smoothing factor
	G35=16.0;		// double inverse distance factor
    G41=0;          // print SWAN bottom file
	
	M10=1;          // int number of grids
	M11=1;          // int decompose in x-dir
	M12=1;          // int decompose in y-dir
	M13=0;          // int decompose in z-dir
	M20=1;          // int decompossition method
	M31=0.1;		// double variance percentage parameter
	
	O10 = 0;
	O32 = 0;
	O33 = 0;
	O43 = 0;
	O61 = 0;
	O62 = 0;
	O63 = 0;
	O64 = 0;
	O65 = 0;
	O66 = 0;
	
	S1 = 0;			// int read STL file
	S2 = 0;			// int auto margins
	S3 = 0;			// int set auto margins
	S4 = 1.0;		// double scaling factor for stl model
	S5 = 0;			// int solid rotation
	S5_x=S5_y=S5_z=S5_phi=S5_theta=S5_psi=0.0;
	S6 = 0;			// int print transformed STL 
	S7 = 0;			// move origin of STL:
	S8 = 0.0;		// double turn angle in horizontal xy-plane
	S9 = 1;			// int invert STL model
	S10 = 0;		// int solid box
	S11 = 0;		// int solid box array
    S15 = 0;        // int rotate solids with geodat
    S19 = 0.1;       // double factor solid resolution
    S31 = 0;			// int jacket rotation
    S31_x=S31_y=S31_z=S31_phi=S31_theta=S31_psi=0.0;
    S32 = 0;       // int solid cylinder_y 
	S33 = 0;		// int solid cylinder_z 
    S34 = 0;		// int solid jacketmember_x 
    S35 = 0;		// int solid jacketmember_y 
    S36 = 0;		// int solid jacketmember_z 
    S37 = 0;		// int solid jacketmember_horz
    S38 = 0;		// int solid jacketmember_vert 
    S39 = 0;		// int solid jacketmember_norm 
	S41 = 0;		// int solid cone_x
	S42 = 0;		// int solid cone_y
	S43 = 0;		// int solid cone_z
    S51 = 0;        // int solid sphere    
    S52 = 0;        // int solid ellipsoid
    S53 = 0;        // int solid semi-ellipsoid
    S54 = 0;        // int solid semi-ellipsoid with rotation
	S61 = 0;		// int solid wedge_x
	S62 = 0;		// int solid wedge_y
	S63 = 0;		// int solid wedge_z
    S81 = 0;		// int solid tetrahedon
    S82 = 0;		// int solid pyramid
    S83 = 0;		// int solid wedge
    S84 = 0;		// int solid hexahedon
	S121 = 0; 		// int solid ogee weir
	S122 = 0; 		// int solid ogee weir, K and n
	S123 = 0; 		// int solid ogee weir, R1 and R2
	S131 = 0;		// int half cone weir in y-dir
    S141 = 0;       // int arch
    S201 = 0;       // int x-plate
    S202 = 0;       // int y-plate
    S203 = 0;       // int z-plate

	solidprint=0;

    xstep=0.0;      // step, x location
    zstep=0.0;      // step, step height

    xstart=0.0;     // pier, x start
    xend=0.0;       // pier, x end
    ystart=0.0;     // pier, y start
    yend=0.0;       // pier, y end
    zstart=0.0;     // pier, z start
    zend=0.0;       // pier, z end
    numlinsurf=10;  // number of linear surfaces
	
	bl_count=0;
	obj_count=0;

    P10=1;          // ascii/binary print format


}


