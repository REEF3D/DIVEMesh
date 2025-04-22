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
    void topo_preproc();
    void gridspacing();
    void createspace();
    void tri_space();
    void domain_extend();
    
    void gridspacing_fsf();
    
    double cellBasedSpacing(const double&, const double&, const double&, const double&, const double&, const double&, const double&);
    void cellBasedSpacing(const double&, const double&, const double&, const double&, const double&, const double&, const double&, int&);
    
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
    int poscgen_i(double,double*,int);
    int poscgen_j(double,double*,int);
    int ihalf(int,int);
    
	// ----------------------
	int ID;
    double xmax,ymax,zmax;
    double xmin,ymin,zmin;
    double dx;
    
    int Np;

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
    int C21,C22,C23;
	
	int D10,D13,D14,D15,D19;
    int D20,D23;
    int D100;
	
    double *D10_x, *D10_y, *D10_z, *D10_dataset;
    double D11_x, D11_y, D11_z;
    double D12_x, D12_y, D12_z;
	double D16,D17,D18,D24;

    int G9,G10,G13,G14;
    double *G10_x, *G10_y, *G10_z;
    double G11_x, G11_y, G11_z;
    double G12_x, G12_y, G12_z;
	double G13_phi;
	double G14_x, G14_y;
    int G15,G17,G19;
    int G20,G23,G24,G25,G26,G27;
    double G24_h,G24_dz;
    double G25_h,G25_fz;
    double G26_zh,G27_zh;
    double G21_x, G21_y, G21_z;
    double G22_x, G22_y, G22_z;
    int G31,G37,G38,G41;
    int G36_select,G37_select,G38_select,G39;
	double G32,G35,G36;
    int G51,G53_flag;
    double G52,G53;
    
    int H10;
    double H21,H22,H23;
    double H31,H32;
    int H33,H34;

    int M10,M11,M12,M13;
	int M20;
    int M30,M30_x,M30_y,M30_z;
    int *M31,*M32,*M33;
	double M41, M45;
	
	int P10;
    

    // solid
	int S1,S2,S3,S5,S6,S7,S9,S9_1,S10,S11,S12,S18;
	double S4,S8;
    double S18_1,S19;
	
	double S5_x,S5_y,S5_z,S5_phi,S5_theta,S5_psi;
	double S3_xs,S3_xe,S3_ys,S3_ye,S3_zs,S3_ze;
	double S7_dx,S7_dy,S7_dz;
    double *S10_xs,*S10_xe,*S10_ys,*S10_ye,*S10_zs,*S10_ze;
	double *S11_xs,*S11_ys,*S11_zs,*S11_L,*S11_G;
    double *S12_xs,*S12_xe,*S12_ys,*S12_ye,*S12_zs,*S12_ze,*S12_b,*S12_h;
	int *S11_ni,*S11_nj,*S11_nk;
    int S15;
    int S31;
    double S31_x,S31_y,S31_z,S31_phi,S31_theta,S31_psi;
    int S32;
    double *S32_xm, *S32_zm, *S32_r;
	int S33;
    double *S33_xm, *S33_ym, *S33_r;
    int S37;
    double *S37_xm1, *S37_ym1, *S37_zm1, *S37_r1, *S37_xm2, *S37_ym2, *S37_zm2, *S37_r2;
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
    double **S81_xyz;
    int S82;
    double **S82_xyz;
    int S83;
    double **S83_xyz;
    int S84;
    double **S84_xyz;
    int S90,S91;
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
    int S301;
    double S305,S306,S307_fh,S307_bh,S308_x,S308_y,S308_z,S309_x,S309_y,S309_z;
    int S310;
    double *S310_l;
    int S320;
    double *S320_r,*S320_phi;
    int S330;
    double *S330_r,*S330_phi;
    int S340;
    double *S340_teta,*S340_L,*S340_N,*S340_ds;
    
    
    // topo
    int T1,T2,T3,T5,T6,T7,T9,T9_1,T10,T11,T18;
	double T4,T8;
    double T18_1,T19;
	
	double T5_x,T5_y,T5_z,T5_phi,T5_theta,T5_psi;
	double T3_xs,T3_xe,T3_ys,T3_ye,T3_zs,T3_ze;
	double T7_dx,T7_dy,T7_dz;
    double *T10_xs,*T10_xe,*T10_ys,*T10_ye,*T10_zs,*T10_ze;
	double *T11_xs,*T11_ys,*T11_zs,*T11_L,*T11_G;
	int *T11_ni,*T11_nj,*T11_nk;
    int T15;
    int T31;
    double T31_x,T31_y,T31_z,T31_phi,T31_theta,T31_psi;
    int T32;
    double *T32_xm, *T32_zm, *T32_r;
	int T33;
    double *T33_xm, *T33_ym, *T33_r;
    int T37;
    double *T37_xm1, *T37_ym1, *T37_zm1, *T37_r1, *T37_xm2, *T37_ym2, *T37_zm2, *T37_r2;
	int T41,T42,T43;
    double *T41_ym, *T41_zm, *T41_x1, *T41_x2, *T41_r1, *T41_r2;
	double *T42_xm, *T42_zm, *T42_y1, *T42_y2, *T42_r1, *T42_r2;
	double *T43_xm, *T43_ym, *T43_z1, *T43_z2, *T43_r1, *T43_r2;
    int T51;
    double *T51_xm,*T51_ym,*T51_zm,*T51_r;
    int T52;
    double *T52_xm,*T52_ym,*T52_zm,*T52_a,*T52_b,*T52_c;
    int T53;
    double *T53_xm,*T53_ym,*T53_zm,*T53_a,*T53_b,*T53_c,*T53_h;
    int T54;
    double *T54_xm,*T54_ym,*T54_zm,*T54_a,*T54_b,*T54_c,*T54_h,*T54_phi,*T54_theta,*T54_psi;
	int T61,T62,T63;
    double *T61_xs,*T61_xe,*T61_ys,*T61_ye,*T61_zs,*T61_ze;
    double *T62_xs,*T62_xe,*T62_ys,*T62_ye,*T62_zs,*T62_ze;
    double *T63_xs,*T63_xe,*T63_ys,*T63_ye,*T63_zs,*T63_ze;
    int T81;
    double **T81_xyz;
    int T82;
    double **T82_xyz;
    int T83;
    double **T83_xyz;
    int T84;
    double **T84_xyz;
	int T121;
	double *T121_x,*T121_y,*T121_z,*T121_b,*T121_Pd,*T121_H0;
	double T122;
	double *T122_K, *T122_n, *T122_xc, *T122_yc;
	double T123;
	double *T123_R1, *T123_R2;
	int T131;
	double *T131_xm, *T131_zm, *T131_y1, *T131_y2, *T131_r1, *T131_r2;
	int T141;
	double *T141_xs,*T141_xe,*T141_ys,*T141_ye,*T141_zs,*T141_ze,*T141_r;
    int T201;
    double *T201_x,*T201_ys,*T201_ye,*T201_zs,*T201_ze;
    int T202;
    double *T202_y,*T202_xs,*T202_xe,*T202_zs,*T202_ze;
    int T203;
    double *T203_z,*T203_xs,*T203_xe,*T203_ys,*T203_ye;
    
    int T300,T300_ds;
    int *T300_ord;
    int T301;
    double T305,T306,T307_fh,T307_bh,T308_x,T308_y,T308_z,T309_x,T309_y,T309_z;
    int T310;
    double *T310_l;
    int T320;
    double *T320_r,*T320_phi;
    int T330;
    double *T330_r,*T330_phi;
    int T340;
    double *T340_teta,*T340_L,*T340_N,*T340_ds;
    
    // VRANS porous structures
	int V1,V5,V6,V7,V9,V9_1,V10,V11,V18;
	double V4,V8;
    double V18_1,V19;
	
	double V5_x,V5_y,V5_z,V5_phi,V5_theta,V5_psi;
	double V3_xs,V3_xe,V3_ys,V3_ye,V3_zs,V3_ze;
	double V7_dx,V7_dy,V7_dz;
    double *V10_xs,*V10_xe,*V10_ys,*V10_ye,*V10_zs,*V10_ze;
	double *V11_xs,*V11_ys,*V11_zs,*V11_L,*V11_G;
	int *V11_ni,*V11_nj,*V11_nk;
    int V15;
    int V31;
    double V31_x,V31_y,V31_z,V31_phi,V31_theta,V31_psi;
    int V32;
    double *V32_xm, *V32_zm, *V32_r;
	int V33;
    double *V33_xm, *V33_ym, *V33_r;
    int V37;
    double *V37_xm1, *V37_ym1, *V37_zm1, *V37_r1, *V37_xm2, *V37_ym2, *V37_zm2, *V37_r2;
	int V41,V42,V43;
    double *V41_ym, *V41_zm, *V41_x1, *V41_x2, *V41_r1, *V41_r2;
	double *V42_xm, *V42_zm, *V42_y1, *V42_y2, *V42_r1, *V42_r2;
	double *V43_xm, *V43_ym, *V43_z1, *V43_z2, *V43_r1, *V43_r2;
    int V51;
    double *V51_xm,*V51_ym,*V51_zm,*V51_r;
	int V61,V62,V63;
    double *V61_xs,*V61_xe,*V61_ys,*V61_ye,*V61_zs,*V61_ze;
    double *V62_xs,*V62_xe,*V62_ys,*V62_ye,*V62_zs,*V62_ze;
    double *V63_xs,*V63_xe,*V63_ys,*V63_ye,*V63_zs,*V63_ze;
    int V81;
    double **V81_xyz;
    int V82;
    double **V82_xyz;
    int V83;
    double **V83_xyz;
    int V84;
    double **V84_xyz;
	int V131;
	double *V131_xm, *V131_zm, *V131_y1, *V131_y2, *V131_r1, *V131_r2;
	
	
	double xs_stl,xe_stl,ys_stl,ye_stl,zs_stl,ze_stl;
	
	int solidprint,topoprint,porousprint;

    double xstart,xend,ystart,yend,zstart,zend;
    double xstep,zstep;
    int knox,knoy,knoz;
    int numlinsurf;
	int solid_count, topo_count;
    double xm,ym,radius;

    int *i0,*j0,*k0,*i1,*j1,*k1;
	
	double **tri_x,**tri_y,**tri_z;
	double *trivec_x,*trivec_y,*trivec_z;
	int trinum,tricount;
    int trinum_stl,trinum_solid,trinum_topo;
    
    
    double *XN,*YN,*ZN;
    double *XP,*YP,*ZP;
    double *DX,*DY,*DZ;
    double *DXP,*DYP,*DZP;
    double DXM,DXYM;
    double DR,DS,DT;
    
    double *SN,*RN,*TN;
    double *SP,*RP,*TP;
    

private:

    void ini_default();
    
    int ii,jj,kk;
};

#endif
