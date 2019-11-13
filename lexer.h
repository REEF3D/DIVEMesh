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
#include<iostream>
#include<fstream>
#include<string>
#include"resize.h"
#include"field.h"
#include"increment.h"
#include<stdlib.h>

#ifndef LEXER_H_
#define LEXER_H_

using namespace std;

class lexer : public resize_class, public increment
{
public:

	lexer();
	virtual ~lexer();

	void read_control();
	void read_geodat();
	void read_data();
	void read_stl();
    void pre_read_stl();
	void clear(char&, int&);
	void solid_preproc();
    void gridspacing();
    void createspace();
    void domain_extend();
    
    void gridspacing_fsf();
    
    double cellBasedSpacing(const double&, const double&, const double&, const double&, const double&, const double&, const double&);
    void cellBasedSpacing(const double&, const double&, const double&, const double&, const double&, const double&, const double&, int&);
    void fitFocusPoint(double&, const double&, const double&, const double&, const int&, const double&, const double&, const double&);
    double fitStretching(const double&, const double&, const double&, const double&, const int&, const double&, double&, const double&);
    double fitMinSize(bool&, const double&, const double&, const double&, const double&, int&, const double&, double&, const double&);
    double fitMaxSize(bool&, double&, const double&, const double&, const double&, const double&, const int&, const double&, double&, const double&);
    
    void gridspacing_print();
    
    double posc_x();
    double posc_y();
    double posc_z();
    
    int posc_i(double);
    int posc_j(double);
    int posc_k(double);
    int posf_i(double);
    int posf_j(double);
    int posf_k(double);
    int ihalf(int,int);
    
	// ----------------------
	int ID;
    double xmax,ymax,zmax;
    double xmin,ymin,zmin;
    double dx;

    double B1;
    int B2;
    int B2_knox,B2_knoy,B2_knoz;
    int B5,B10;
    double *B10_xs,*B10_xe,*B10_ys,*B10_ye,*B10_zs,*B10_ze;
    int B22;
    double *B22_xm, *B22_ym, *B22_zm,  *B22_r;
    int B31;
    double *B31_xs, *B31_xe, *B31_ym, *B31_zm, *B31_r;
    int B32;
    double *B32_ys, *B32_ye, *B32_xm, *B32_zm, *B32_r;
    int B33;
    double *B33_zs, *B33_ze, *B33_xm, *B33_ym, *B33_r;
    
    int B101,B102,B103;
    double B111,B112,B113;
    int B114,B115,B116;
    double B114_x,B115_y,B116_z;
    int B121;
    double B121_x1,B121_x2;
    int B121_N1,B121_N2,B121_N3;
    int B122;
    double B122_y1,B122_y2;
    int B122_N1,B122_N2,B122_N3;
    int B123;
    double B123_z1,B123_z2;
    int B123_N1,B123_N2,B123_N3;
    int B124;
    double B124_x1,B124_f1,B124_x2,B124_f2,B124_x3,B124_f3;
    int B124_N1,B124_N2,B124_N3;
    int B125;
    double B125_y1,B125_f1,B125_y2,B125_f2,B125_y3,B125_f3;
    int B125_N1,B125_N2,B125_N3;
    int B126;
    double B126_z1,B126_f1,B126_z2,B126_f2,B126_z3,B126_f3;
    int B126_N1,B126_N2,B126_N3;
    int B127;
    double B127_dx_min, B127_dx_max, B127_pf, B127_df, B127_r;
    int B128;
    double B128_dx_min, B128_dx_max, B128_pf, B128_df, B128_r;
    int B129;
    double B129_dx_min, B129_dx_max, B129_pf, B129_df, B129_r;   
    int B130;
    
    int C11,C12,C13,C14,C15,C16;
	
	int D10,D13,D14,D15,D19;
    int D20,D23;
    int D100;
	
    double *D10_x, *D10_y, *D10_z, *D10_data;
    double D11_x, D11_y, D11_z;
    double D12_x, D12_y, D12_z;
	double D16,D17,D18,D24;
    


    double F3_zs, F3_ze;
    int F11, F12, F13;
    int F21, F22, F23;
    int F31, F32, F33;
    int F41, F42, F43;
    double *F11_xs,*F11_xe,*F11_ys,*F11_ye;
    double *F21_xs,*F21_xe,*F21_ys,*F21_ye;
	int *F31_num, *F41_num;	
	double **F31_x,**F31_y;
	double **F41_x,**F41_y;

    int G10,G13,G14;
    double *G10_x, *G10_y, *G10_z;
    double G11_x, G11_y, G11_z;
    double G12_x, G12_y, G12_z;
	double G13_phi;
	double G14_x, G14_y,G16;
    int G15,G17,G19;
    int G20,G23,G24,G25;
    double G24_h,G24_dz;
    double G25_h,G25_fz;
    double G21_x, G21_y, G21_z;
    double G22_x, G22_y, G22_z;
    int G31,G41;
	double G32,G35;
    
    int H10;
    double H21,H22,H23;
    double H31,H32;
    int H33,H34;

    int M10,M11,M12,M13;
	int M20;
	double M31, M35;
	
	int P10;

    int O10;
    double *O10_xs,*O10_xe,*O10_ys,*O10_ye,*O10_zs,*O10_ze;
    int O32;
    double *O32_xm, *O32_zm, *O32_r;
    int O33;
    double *O33_xm, *O33_ym, *O33_r;
	int O43;
    double *O43_xm, *O43_ym, *O43_z1, *O43_z2, *O43_r1, *O43_r2;
    int O61;
    double *O61_xs,*O61_xe,*O61_ys,*O61_ye,*O61_zs,*O61_ze;
    int O62;
    double *O62_xs,*O62_xe,*O62_ys,*O62_ye,*O62_zs,*O62_ze;
    int O63;
    double *O63_xs,*O63_xe,*O63_ys,*O63_ye,*O63_zs,*O63_ze;
    int O64;
    double *O64_xs,*O64_xe,*O64_ys,*O64_ye,*O64_zs,*O64_ze;
    int O65;
    double *O65_xs,*O65_xe,*O65_ys,*O65_ye,*O65_zs,*O65_ze;
    int O66;
    double *O66_xs,*O66_xe,*O66_ys,*O66_ye,*O66_zs,*O66_ze;
	
	
	int S1,S2,S3,S5,S6,S7,S9,S10,S11;
	double S4,S8,S9_1;
    double S19;
	
	double S5_x,S5_y,S5_z,S5_phi,S5_theta,S5_psi;
	double S3_xs,S3_xe,S3_ys,S3_ye,S3_zs,S3_ze;
	double S7_dx,S7_dy,S7_dz;
    double *S10_xs,*S10_xe,*S10_ys,*S10_ye,*S10_zs,*S10_ze;
	double *S11_xs,*S11_ys,*S11_zs,*S11_L,*S11_G;
	int *S11_ni,*S11_nj,*S11_nk;
    int S15;
    int S31;
    double S31_x,S31_y,S31_z,S31_phi,S31_theta,S31_psi;
    int S32;
    double *S32_xm, *S32_zm, *S32_r;
	int S33;
    double *S33_xm, *S33_ym, *S33_r;
    int S34;
    double *S34_xm1, *S34_ym1, *S34_zm1, *S34_r1, *S34_xm2, *S34_ym2, *S34_zm2, *S34_r2;
    int S35;
    double *S35_xm1, *S35_ym1, *S35_zm1, *S35_r1, *S35_xm2, *S35_ym2, *S35_zm2, *S35_r2;
    int S36;
    double *S36_xm1, *S36_ym1, *S36_zm1, *S36_r1, *S36_xm2, *S36_ym2, *S36_zm2, *S36_r2;
    int S37;
    double *S37_xm1, *S37_ym1, *S37_zm1, *S37_r1, *S37_xm2, *S37_ym2, *S37_zm2, *S37_r2;
    int S38;
    double *S38_xm1, *S38_ym1, *S38_zm1, *S38_r1, *S38_xm2, *S38_ym2, *S38_zm2, *S38_r2;
    int S39;
    double *S39_xm1, *S39_ym1, *S39_zm1, *S39_r1, *S39_xm2, *S39_ym2, *S39_zm2, *S39_r2;
	int S41,S42,S43;
    double *S41_ym, *S41_zm, *S41_x1, *S41_x2, *S41_r1, *S41_r2;
	double *S42_xm, *S42_zm, *S42_y1, *S42_y2, *S42_r1, *S42_r2;
	double *S43_xm, *S43_ym, *S43_z1, *S43_z2, *S43_r1, *S43_r2;
    int S51;
    double *S51_xm,*S51_ym,*S51_zm,*S51_r;
    int S52;
    double *S52_xm,*S52_ym,*S52_zm,*S52_a,*S52_b,*S52_c;
    int S53;
    double *S53_xm,*S53_ym,*S53_zm,*S53_a,*S53_b,*S53_c,*S53_h;
    int S54;
    double *S54_xm,*S54_ym,*S54_zm,*S54_a,*S54_b,*S54_c,*S54_h,*S54_phi,*S54_theta,*S54_psi;
	int S61,S62,S63;
    double *S61_xs,*S61_xe,*S61_ys,*S61_ye,*S61_zs,*S61_ze;
    double *S62_xs,*S62_xe,*S62_ys,*S62_ye,*S62_zs,*S62_ze;
    double *S63_xs,*S63_xe,*S63_ys,*S63_ye,*S63_zs,*S63_ze;
    int S81;
    double *S81_x1,*S81_y1,*S81_z1;
    double *S81_x2,*S81_y2,*S81_z2;
    double *S81_x3,*S81_y3,*S81_z3;
    double *S81_x4,*S81_y4,*S81_z4;
    int S82;
    double *S82_x1,*S82_y1,*S82_z1;
    double *S82_x2,*S82_y2,*S82_z2;
    double *S82_x3,*S82_y3,*S82_z3;
    double *S82_x4,*S82_y4,*S82_z4;
    double *S82_x5,*S82_y5,*S82_z5;
    int S83;
    double *S83_x1,*S83_y1,*S83_z1;
    double *S83_x2,*S83_y2,*S83_z2;
    double *S83_x3,*S83_y3,*S83_z3;
    double *S83_x4,*S83_y4,*S83_z4;
    double *S83_x5,*S83_y5,*S83_z5;
    double *S83_x6,*S83_y6,*S83_z6;
    int S84;
    double *S84_x1,*S84_y1,*S84_z1;
    double *S84_x2,*S84_y2,*S84_z2;
    double *S84_x3,*S84_y3,*S84_z3;
    double *S84_x4,*S84_y4,*S84_z4;
    double *S84_x5,*S84_y5,*S84_z5;
    double *S84_x6,*S84_y6,*S84_z6;
    double *S84_x7,*S84_y7,*S84_z7;
    double *S84_x8,*S84_y8,*S84_z8;
	int S121;
	double *S121_x,*S121_y,*S121_z,*S121_b,*S121_Pd,*S121_H0;
	double S122;
	double *S122_K, *S122_n, *S122_xc, *S122_yc;
	double S123;
	double *S123_R1, *S123_R2;
	int S131;
	double *S131_xm, *S131_zm, *S131_y1, *S131_y2, *S131_r1, *S131_r2;
	int S141;
	double *S141_xs,*S141_xe,*S141_ys,*S141_ye,*S141_zs,*S141_ze,*S141_r;
    int S201;
    double *S201_x,*S201_ys,*S201_ye,*S201_zs,*S201_ze;
    int S202;
    double *S202_y,*S202_xs,*S202_xe,*S202_zs,*S202_ze;
    int S203;
    double *S203_z,*S203_xs,*S203_xe,*S203_ys,*S203_ye;
    
    int S300,S300_ds;
    int *S300_ord;
    double S305,S306,S307_fh,S307_bh,S308_x,S308_y,S308_z,S309_x,S309_y,S309_z;
    int S310;
    double *S310_l;
    int S320;
    double *S320_r,*S320_phi;
    int S330;
    double *S330_r,*S330_phi;
    int S340;
    double *S340_teta,*S340_L,*S340_N,*S340_ds;
	
	
	double xs_stl,xe_stl,ys_stl,ye_stl,zs_stl,ze_stl;
	
	int solidprint;

    double xstart,xend,ystart,yend,zstart,zend;
    double xstep,zstep;
    int knox,knoy,knoz;
    int numlinsurf;
	int bl_count, obj_count, fc_count, solid_count;
    double xm,ym,radius;

    int *i0,*j0,*k0,*i1,*j1,*k1;
	
	double **tri_x,**tri_y,**tri_z;
	double *trivec_x,*trivec_y,*trivec_z;
	int trinum,tricount;
    
    
    double *XN,*YN,*ZN;
    double *XP,*YP,*ZP;
    double *DX,*DY,*DZ;
    double *DXP,*DYP,*DZP;
    double DXM;
    
    

private:

    void ini_default();
    
    
    
    int ii,jj,kk;
};

#endif
