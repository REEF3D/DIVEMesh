/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2022 Hans Bihs

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
	B130=0;         // int print grid vtk
    
	C11=21;          // C12
    C12=21;          // C12
    C13=21;          // C12
    C14=21;          // C12
    C15=21;          // C12
    C16=21;          // C12
    
    C21=0;          // Periodic BC in x-dir
    C22=0;          // Periodic BC in y-dir
    C23=0;          // Periodic BC in z-dir
	
	D10=0;            // int dataset off/on
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
    D100=0;        // int FNPF state file merge

    G9=1;            // int geodat either topo or solid
    G10=0;           // int geodata off/on
    G11_x=0.0;       // double dx
    G11_y=0.0;       // double dy
    G11_z=0.0;       // double dz
    G12_x=1.0;       // double x factor
    G12_y=1.0;       // double y factor
    G12_z=1.0;       // double z factor
	G13=0;			  // int turn geo coordinates
	G13_phi=0.0;     // doubel turn angle geo coordinates
	G14=0;			  // int read origin for turn angle
	G14_x=0.0;       // double x origin for turn angle
    G14_y=0.0;       // double y origin for turn angle
    G15=2;           // int interpolation scheme
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
    G26=0;          // int remove all points below a threshold zh
    G27=0;          // int remove all points above a threshold zh
    G31=0;          // int number of smoothing iterations
    G32=0.5;        // double smoothing factor
	G35=16.0;		// double inverse distance factor
    G36=1.0;        // doulble duplicate points factor times DXM
    G36_select=0;
    G37_select=0;
    G37=1e8;        // int maximum number of geaodat after duplicate removal
    G38=1;          // int skip horizontal cells for geodat interpolation algorithm
    G38_select=0;
    G39=1;          // int remove out of bounds geodat points
    G41=0;          // print SWAN bottom file
    G51=0;          // int turn on holefill
    G52=0.0;         // double base topo level for local IDW
    G53_flag=0;     // int turn on manual search radius
    G53=0.0;         // double manual search radius
    
    H10=0;          // int turn on hydrodynamic coupling procedures
    H21=0.0;        // double deltax
    H22=0.0;        // double deltay
    H23=0.0;        // double deltaz
    H31=-1.0e20;    // double starttime
    H32= 1.0e20;    // double endtime
    H33=-2147483647;      // int start iter
    H34= 2147483647;      // int end iter
	
	M10=1;          // int number of grids
	M11=1;          // int decompose in x-dir
	M12=1;          // int decompose in y-dir
	M13=0;          // int decompose in z-dir
	M20=1;          // int decompossition method
    M30=0;          // int manual partition distribution
    M31=0;          // int manual partition x-dir
    M32=0;          // int manual partition y-dir
    M33=0;          // int manual partition z-dir
	M41=0.1;		// double variance percentage parameter
    M45=5.0;       // double xvar factor

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
    S18 = 1;        // int invert solid
    S19 = 0.1;       // double factor solid resolution
    S31 = 0;			// int jacket rotation
    S31_x=S31_y=S31_z=S31_phi=S31_theta=S31_psi=0.0;
    S32 = 0;       // int solid cylinder_y 
	S33 = 0;		// int solid cylinder_z 
    S37 = 0;		// int solid jacketmember_horz
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
    S300 = 0;       // int turn fluvial box
    S301 = 1;       // int fluvial box type
    S300_ds = 0;    // int fluvial box ds num
    S305 = 0.5;     // double factor times dx for calculating ds
    S306 = 1.0;     // double width fluival channel
    S307_fh = 0.5;     // double flowheight fluvial box
    S307_bh = 0.2;     // double bed height fluvial box
    S308_x = 0.0;   // double deltax fluvial box
    S308_y = 0.0;   // double deltay fluvial box
    S308_z = 0.0;   // double deltaz fluvial box
    S309_x = 0.0;   // double extra margin x
    S309_y = 0.2;   // double extra margin y
    S309_z = 0.0;   // double extra margin z
    S310 = 0;       // int straight
    S320 = 0;       // int left bend
    S330 = 0;       // int right bend
    S340 = 0;       // int meander
    
    T1 = 0;			// int read TTL file
	T2 = 0;			// int auto margins
	T3 = 0;			// int set auto margins
	T4 = 1.0;		// double scaling factor for stl model
	T5 = 0;			// int solid rotation
	T5_x=T5_y=T5_z=T5_phi=T5_theta=T5_psi=0.0;
	T6 = 0;			// int print transformed TTL 
	T7 = 0;			// move origin of TTL:
	T8 = 0.0;		// double turn angle in horizontal xy-plane
	T9 = 1;			// int invert TTL model
	T10 = 0;		// int solid box
	T11 = 0;		// int solid box array
    T15 = 0;        // int rotate solids with geodat
    T18 = 1;        // int invert solid
    T19 = 0.1;       // double factor solid resolution
    T31 = 0;			// int jacket rotation
    T31_x=T31_y=T31_z=T31_phi=T31_theta=T31_psi=0.0;
    T32 = 0;       // int solid cylinder_y 
	T33 = 0;		// int solid cylinder_z 
    T37 = 0;		// int solid jacketmember_horz
	T41 = 0;		// int solid cone_x
	T42 = 0;		// int solid cone_y
	T43 = 0;		// int solid cone_z
    T51 = 0;        // int solid sphere    
    T52 = 0;        // int solid ellipsoid
    T53 = 0;        // int solid semi-ellipsoid
    T54 = 0;        // int solid semi-ellipsoid with rotation
	T61 = 0;		// int solid wedge_x
	T62 = 0;		// int solid wedge_y
	T63 = 0;		// int solid wedge_z
    T81 = 0;		// int solid tetrahedon
    T82 = 0;		// int solid pyramid
    T83 = 0;		// int solid wedge
    T84 = 0;		// int solid hexahedon
	T121 = 0; 		// int solid ogee weir
	T122 = 0; 		// int solid ogee weir, K and n
	T123 = 0; 		// int solid ogee weir, R1 and R2
	T131 = 0;		// int half cone weir in y-dir
    T141 = 0;       // int arch
    T201 = 0;       // int x-plate
    T202 = 0;       // int y-plate
    T203 = 0;       // int z-plate
    T300 = 0;       // int turn fluvial box
    T301 = 1;       // int fluvial box type
    T300_ds = 0;    // int fluvial box ds num
    T305 = 0.5;     // double factor times dx for calculating ds
    T306 = 1.0;     // double width fluival channel
    T307_fh = 0.5;     // double flowheight fluvial box
    T307_bh = 0.2;     // double bed height fluvial box
    T308_x = 0.0;   // double deltax fluvial box
    T308_y = 0.0;   // double deltay fluvial box
    T308_z = 0.0;   // double deltaz fluvial box
    T309_x = 0.0;   // double extra margin x
    T309_y = 0.2;   // double extra margin y
    T309_z = 0.0;   // double extra margin z
    T310 = 0;       // int straight
    T320 = 0;       // int left bend
    T330 = 0;       // int right bend
    T340 = 0;       // int meander
    
	solidprint=0;
    topoprint=0;

    xstep=0.0;      // step, x location
    zstep=0.0;      // step, step height

    xstart=0.0;     // pier, x start
    xend=0.0;       // pier, x end
    ystart=0.0;     // pier, y start
    yend=0.0;       // pier, y end
    zstart=0.0;     // pier, z start
    zend=0.0;       // pier, z end
    numlinsurf=10;  // number of linear surfaces
	

    P10=1;          // ascii/binary print format

    trinum=0;
    trinum_stl=0;
    trinum_solid=0;
    trinum_topo=0;
}


