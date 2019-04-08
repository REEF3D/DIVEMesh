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

#include"lexer.h"
#include <fstream>

void lexer::read_control()
{
	char c;
	int numint;
	numlinsurf=0;

    B10=0;
    B22=0;
    B31=0;
    B33=0;
	O10=0;
	O32=0;
	O33=0;
	O43=0;
	O61=O62=O63=O64=O65=O66=0;
	F11=0;
	F21=0;
	S10=0;
	
	cout<<"read control"<<endl;

	ifstream control("control.txt", ios_base::in);

	if(!control)
	{
		cout<<"no 'control.txt' file"<<endl<<endl;
		//exit(0);
	}

	while(!control.eof())
	{
	    control>>c;

	if (c == '/') 
	{
		control.ignore(1000, '\n');
	}
	else
	{	
		switch(c)
		{
        case 'B': control>>numint;
				switch(numint)
				{
                case 1: control>>dx;
                         clear(c,numint);
						 break;
				case 2: control>>B2_knox>>B2_knoy>>B2_knoz;
                        B2=1;
                        clear(c,numint);
						 break;
               case 3: control>>B3;
                         clear(c,numint);
						 break;
               case 5: control>>B5;
                         clear(c,numint);
						 break;
				case 10: ++B10;
                         clear(c,numint);
						 break;
                case 22: ++B22;
						 clear(c,numint);
						 break;
                case 31: ++B31;
						 clear(c,numint);
						 break;
                case 32: ++B32;
						 clear(c,numint);
						 break;
                case 33: ++B33;
						 clear(c,numint);
						 break;
                case 101: control>>B101;
						 clear(c,numint);
						 break;
                case 102: control>>B102;
						 clear(c,numint);
						 break;
                case 103: control>>B103;
						 clear(c,numint);
						 break;
                case 111: control>>B111;
						 clear(c,numint);
						 break;
                case 112: control>>B112;
						 clear(c,numint);
						 break;
                case 113: control>>B113;
						 clear(c,numint);
						 break;
                case 114: control>>B114_x;
                        B114=1;
						 clear(c,numint);
						 break;
                case 115: control>>B115_y;
                        B115=1;
						 clear(c,numint);
						 break;
                case 116: control>>B116_z;
                        B116=1;
						 clear(c,numint);
						 break;
                case 121: control>>B121_N1>>B121_x1>>B121_N2>>B121_x2>>B121_N3;
                        B121=1;
						 clear(c,numint);
                        break;
                case 122: control>>B122_N1>>B122_y1>>B122_N2>>B122_y2>>B122_N3;
                        B122=1;
						 clear(c,numint);
                        break;
                case 123: control>>B123_N1>>B123_z1>>B123_N2>>B123_z2>>B123_N3;
                        B123=1;
						 clear(c,numint);
                        break;
                case 124: control>>B124_N1>>B124_x1>>B124_f1>>B124_N2>>B124_x2>>B124_f2>>B124_N3>>B124_x3>>B124_f3;
                        B124=1;
						 clear(c,numint);
						 break;
                case 125: control>>B125_N1>>B125_y1>>B125_f1>>B125_N2>>B125_y2>>B125_f2>>B125_N3>>B125_y3>>B125_f3;
                        B125=1;
						 clear(c,numint);
						 break;
                case 126: control>>B126_N1>>B126_z1>>B126_f1>>B126_N2>>B126_z2>>B126_f2>>B126_N3>>B126_z3>>B126_f3;
                        B126=1;
						 clear(c,numint);
						 break;

				}
				break;
				
		case 'D': control>>numint;
				switch(numint)
				{
                case 10: control>>D10;
                         clear(c,numint);
						 break;
                case 11: control>>D11_x>>D11_y>>D11_z;
                         clear(c,numint);
						 break;
                case 12: control>>D12_x>>D12_y>>D12_z;
                         clear(c,numint);
						 break;
				case 13: control>>D13;
                         clear(c,numint);
						 break;
				case 14: control>>D14;
                         clear(c,numint);
						 break;
				case 15: control>>D15;
                         clear(c,numint);
						 break;
				case 16: control>>D16;
                         clear(c,numint);
						 break;
				case 17: control>>D17;
                         clear(c,numint);
						 break;
				case 18: control>>D18;
                         clear(c,numint);
						 break;
                case 19: control>>D19;
                         clear(c,numint);
						 break;
                case 20: control>>D20;
                         clear(c,numint);
						 break;
				case 23: control>>D23;
                         clear(c,numint);
						 break;
				case 24: control>>D24;
                         clear(c,numint);
						 break;
				}
				break;

        case 'F': control>>numint;
				switch(numint)
				{
                case 3: control>>F3_zs>>F3_ze;
                         clear(c,numint);
						 break;
				case 11: ++F11;
                         clear(c,numint);
						 break;
                case 21: ++F21;
                         clear(c,numint);
						 break;
			    case 31: ++F31;
                         clear(c,numint);
						 break;
                case 41: ++F41;
                         clear(c,numint);
						 break;

				}
				break;

        case 'G': control>>numint;
				switch(numint)
				{
                case 10: control>>G10;
                         clear(c,numint);
						 break;
                case 11: control>>G11_x>>G11_y>>G11_z;
                         clear(c,numint);
						 break;
                case 12: control>>G12_x>>G12_y>>G12_z;
                         clear(c,numint);
						 break;
				 case 13: control>>G13_phi;
						 G13=1; 
						 clear(c,numint);
						 break;
				 case 14: control>>G14_x>>G14_y;
						  G14=1;
                         clear(c,numint);
						 break;
                case 15: control>>G15;
                         clear(c,numint);
						 break;
                case 16: control>>G16;
                         clear(c,numint);
						 break;
                case 17: control>>G17;
                         clear(c,numint);
						 break;
                case 19: control>>G19;
                         clear(c,numint);
						 break;
                case 20: control>>G20;
                         clear(c,numint);
						 break;
                case 21: control>>G21_x>>G21_y>>G21_z;
                         clear(c,numint);
						 break;
                case 22: control>>G22_x>>G22_y>>G22_z;
                         clear(c,numint);
						 break;
				 case 23: control>>G23;
                         clear(c,numint);
						 break;
                case 24: control>>G24_h>>G24_dz;
                        G24=1;
                         clear(c,numint);
						 break;
                case 25: control>>G25_h>>G25_fz;
                        G25=1;
                         clear(c,numint);
						 break;
				 case 31: control>>G31;
                         clear(c,numint);
						 break;
                case 32: control>>G32;
                         clear(c,numint);
						 break;
                case 35: control>>G35;
                         clear(c,numint);
						 break;
                case 41: control>>G41;
                         clear(c,numint);
						 break;
				}
				break;

		case 'C': control>>numint;
				switch(numint)
				{
                case 11: control>>C11;
                         clear(c,numint);
						 break;
                case 12: control>>C12;
                         clear(c,numint);
						 break;
                case 13: control>>C13;
                         clear(c,numint);
						 break;
                case 14: control>>C14;
                         clear(c,numint);
						 break;
                case 15: control>>C15;
                         clear(c,numint);
						 break;
                case 16: control>>C16;
                         clear(c,numint);
						 break;
				}
				break;

        case 'M': control>>numint;
				switch(numint)
				{
				case 10: control>>M10;
						 clear(c,numint);
						 break;
				case 11: control>>M11;
						 clear(c,numint);
						 break;
				case 12: control>>M12;
						 clear(c,numint);
						 break;
				case 13: control>>M13;
						 clear(c,numint);
						 break;
				case 20: control>>M20;
						 clear(c,numint);
						 break;
				case 31: control>>M31;
						 clear(c,numint);
						 break;
				}
				break;

        case 'O': control>>numint;
				switch(numint)
				{
				case 10: ++O10;
						 clear(c,numint);
						 break;
                case 32: ++O32;
						 clear(c,numint);
						 break;
                case 33: ++O33;
						 clear(c,numint);
						 break;
				case 43: ++O43;
						 clear(c,numint);
						 break;
                case 61: ++O61;
						 clear(c,numint);
						 break;
				case 62: ++O62;
						 clear(c,numint);
						 break;
				}
				break;
				
		case 'S': control>>numint;
				switch(numint)
				{
				case 1: control>>S1;
						 clear(c,numint);
						 break;
				case 2: control>>S2;
						 clear(c,numint);
						 break;
				case 3: control>>S3_xs>>S3_xe>>S3_ys>>S3_ye>>S3_zs>>S3_ze;
						S3=1;
						 clear(c,numint);
						 break;
				case 4: control>>S4;
						 clear(c,numint);
						 break;
				case 5: control>>S5_x>>S5_y>>S5_z>>S5_phi>>S5_theta>>S5_psi;
                          S5=1;
						 clear(c,numint);
						 break;
				case 6: control>>S6;
						 clear(c,numint);
						 break;
				case 7: control>>S7_dx>>S7_dy>>S7_dz;
						S7=1;
						 clear(c,numint);
						 break;
				case 8: control>>S8;
						 clear(c,numint);
						 break;
				case 9: control>>S9;
						 clear(c,numint);
						 break;
				case 10: ++S10;
						 clear(c,numint);
						 break;
				case 11: ++S11;
						 clear(c,numint);
						 break;
               case 15: control>>S15;
						 clear(c,numint);
						 break;
               case 19: control>>S19;
						 clear(c,numint);
						 break;
               case 31: control>>S31_x>>S31_y>>S31_z>>S31_phi>>S31_theta>>S31_psi;
                          S31=1;
						 clear(c,numint);
						 break;
				case 32: ++S32;
						 clear(c,numint);
						 break;
               case 33: ++S33;
						 clear(c,numint);
						 break;
               case 34: ++S34;
						 clear(c,numint);
						 break;
               case 35: ++S35;
						 clear(c,numint);
						 break;
               case 36: ++S36;
						 clear(c,numint);
						 break;
               case 37: ++S37;
						 clear(c,numint);
						 break;
               case 38: ++S38;
						 clear(c,numint);
						 break;
               case 39: ++S39;
						 clear(c,numint);
						 break;
				case 41: ++S41;
						 clear(c,numint);
						 break;
				case 42: ++S42;
						 clear(c,numint);
						 break;
				case 43: ++S43;
						 clear(c,numint);
						 break;
                case 51: ++S51;
						 clear(c,numint);
						 break;
                case 52: ++S52;
						 clear(c,numint);
						 break;
                case 53: ++S53;
						 clear(c,numint);
						 break;
               case 54: ++S54;
						 clear(c,numint);
						 break;
				case 61: ++S61;
						 clear(c,numint);
						 break;
				case 62: ++S62;
						 clear(c,numint);
						 break;
				case 63: ++S63;
						 clear(c,numint);
						 break;
               case 81: ++S81;
						 clear(c,numint);
						 break;
               case 82: ++S82;
						 clear(c,numint);
						 break;
               case 83: ++S83;
						 clear(c,numint);
						 break;
               case 84: ++S84;
						 clear(c,numint);
						 break;
				case 121: ++S121;
						 clear(c,numint);
						 break;
				case 122: ++S122;
						 clear(c,numint);
						 break;
				case 123: ++S123;
						 clear(c,numint);
						 break;
				case 131: ++S131;
						 clear(c,numint);
						 break;
                case 141: ++S141;
						 clear(c,numint);
						 break;
                case 201: ++S201;
						 clear(c,numint);
						 break;
                case 202: ++S202;
						 clear(c,numint);
						 break;
                case 203: ++S203;
						 clear(c,numint);
						 break;
                case 300: control>>S300;
						 clear(c,numint);
						 break;
                case 307: control>>S307;
						 clear(c,numint);
						 break;
                case 308: control>>S308_x>>S308_y;
						 clear(c,numint);
						 break;
                case 309: control>>S309;
						 clear(c,numint);
						 break;
                case 310: ++S310;
						 clear(c,numint);
						 break;
                case 320: ++S320;
						 clear(c,numint);
						 break;
                case 330: ++S330;
						 clear(c,numint);
						 break;
				}
				break;


		}
	}
	}
	control.close();
	control.clear();

	// re-read
	
	Darray(B10_xs,B10);
	Darray(B10_xe,B10);
	Darray(B10_ys,B10);
	Darray(B10_ye,B10);
	Darray(B10_zs,B10);
	Darray(B10_ze,B10);
	
	Darray(B22_xm,B22);
	Darray(B22_ym,B22);
	Darray(B22_zm,B22);
	Darray(B22_r,B22);
	
	Darray(B31_xs,B31);
	Darray(B31_xe,B31);
	Darray(B31_ym,B31);
	Darray(B31_zm,B31);
	Darray(B31_r,B31);
	
	Darray(B32_ys,B32);
	Darray(B32_ye,B32);
	Darray(B32_xm,B32);
	Darray(B32_zm,B32);
	Darray(B32_r,B32);
	
	Darray(B33_zs,B33);
	Darray(B33_ze,B33);
	Darray(B33_xm,B33);
	Darray(B33_ym,B33);
	Darray(B33_r,B33);
	
	Darray(F11_xs,F11);
	Darray(F11_xe,F11);
	Darray(F11_ys,F11);
	Darray(F11_ye,F11);
	
	Darray(F21_xs,F21);
	Darray(F21_xe,F21);
	Darray(F21_ys,F21);
	Darray(F21_ye,F21);
	
	
	if(F31>0)
	{
	F31_x= new double*[F31];
	F31_y= new double*[F31];
	}
	
	if(F41>0)
	{
	F41_x= new double*[F41];
	F41_y= new double*[F41];
	}
		
	Iarray(F31_num,F31);
	Iarray(F41_num,F41);


	Darray(O10_xs,O10);
	Darray(O10_xe,O10);
	Darray(O10_ys,O10);
	Darray(O10_ye,O10);
	Darray(O10_zs,O10);
	Darray(O10_ze,O10);

	O32_xm = new double[O32];
	O32_zm= new double[O32];
	O32_r = new double[O32];

	O33_xm = new double[O33];
	O33_ym= new double[O33];
	O33_r = new double[O33];
	
	O43_xm = new double[O43];
	O43_ym = new double[O43];
	O43_z1 = new double[O43];
	O43_z2 = new double[O43];
	O43_r1 = new double[O43];
	O43_r2 = new double[O43];

	O61_xs = new double[O61];
	O61_xe = new double[O61];

	O61_ys = new double[O61];
	O61_ye = new double[O61];

	O61_zs = new double[O61];
	O61_ze = new double[O61];

	O62_xs = new double[O62];
	O62_xe = new double[O62];

	O62_ys = new double[O62];
	O62_ye = new double[O62];

	O62_zs = new double[O62];
	O62_ze = new double[O62];

	O63_xs = new double[O63];
	O63_xe = new double[O63];

	O63_ys = new double[O63];
	O63_ye = new double[O63];

	O63_zs = new double[O63];
	O63_ze = new double[O63];

	O64_xs = new double[O64];
	O64_xe = new double[O64];

	O64_ys = new double[O64];
	O64_ye = new double[O64];

	O64_zs = new double[O64];
	O64_ze = new double[O64];

	O65_xs = new double[O65];
	O65_xe = new double[O65];

	O65_ys = new double[O65];
	O65_ye = new double[O65];

	O65_zs = new double[O65];
	O65_ze = new double[O65];

	O66_xs = new double[O66];
	O66_xe = new double[O66];

	O66_ys = new double[O66];
	O66_ye = new double[O66];

	O66_zs = new double[O66];
	O66_ze = new double[O66];
	
	
	S10_xs = new double[S10];
	S10_xe = new double[S10];
	S10_ys = new double[S10];
	S10_ye = new double[S10];
	S10_zs = new double[S10];
	S10_ze = new double[S10];
	
	S11_xs = new double[S11];
	S11_ys = new double[S11];
	S11_zs = new double[S11];
	S11_L = new double[S11];
	S11_G = new double[S11];
	S11_ni = new int[S11];
	S11_nj = new int[S11];
	S11_nk = new int[S11];
	
    S32_xm = new double[S32];
	S32_zm = new double[S32];
	S32_r  = new double[S32];
    
	S33_xm = new double[S33];
	S33_ym = new double[S33];
	S33_r  = new double[S33];
    
    S34_xm1 = new double[S34];
	S34_ym1 = new double[S34];
    S34_zm1 = new double[S34];
    S34_r1 = new double[S34];
	S34_xm2 = new double[S34];
	S34_ym2 = new double[S34];
    S34_zm2 = new double[S34];
    S34_r2 = new double[S34];
    
    S35_xm1 = new double[S35];
	S35_ym1 = new double[S35];
    S35_zm1 = new double[S35];
    S35_r1 = new double[S35];
	S35_xm2 = new double[S35];
	S35_ym2 = new double[S35];
    S35_zm2 = new double[S35];
    S35_r2 = new double[S35];
    
    S36_xm1 = new double[S36];
	S36_ym1 = new double[S36];
    S36_zm1 = new double[S36];
    S36_r1 = new double[S36];
	S36_xm2 = new double[S36];
	S36_ym2 = new double[S36];
    S36_zm2 = new double[S36];
    S36_r2 = new double[S36];
    
    S37_xm1 = new double[S37];
	S37_ym1 = new double[S37];
    S37_zm1 = new double[S37];
    S37_r1 = new double[S37];
	S37_xm2 = new double[S37];
	S37_ym2 = new double[S37];
    S37_zm2 = new double[S37];
    S37_r2 = new double[S37];
    
    S38_xm1 = new double[S38];
	S38_ym1 = new double[S38];
    S38_zm1 = new double[S38];
    S38_r1 = new double[S38];
	S38_xm2 = new double[S38];
	S38_ym2 = new double[S38];
    S38_zm2 = new double[S38];
    S38_r2 = new double[S38];
    
    S39_xm1 = new double[S39];
	S39_ym1 = new double[S39];
    S39_zm1 = new double[S39];
    S39_r1 = new double[S39];
	S39_xm2 = new double[S39];
	S39_ym2 = new double[S39];
    S39_zm2 = new double[S39];
    S39_r2 = new double[S39];
	
	S41_ym = new double[S41];
	S41_zm = new double[S41];
	S41_x1 = new double[S41];
	S41_x2 = new double[S41];
	S41_r1 = new double[S41];
	S41_r2 = new double[S41];
	
	S42_xm = new double[S42];
	S42_zm = new double[S42];
	S42_y1 = new double[S42];
	S42_y2 = new double[S42];
	S42_r1 = new double[S42];
	S42_r2 = new double[S42];
	
	S43_xm = new double[S43];
	S43_ym = new double[S43];
	S43_z1 = new double[S43];
	S43_z2 = new double[S43];
	S43_r1 = new double[S43];
	S43_r2 = new double[S43];
    
    Darray(S51_xm,S51);
    Darray(S51_ym,S51);
    Darray(S51_zm,S51);
    Darray(S51_r,S51);
    
    Darray(S52_xm,S52);
    Darray(S52_ym,S52);
    Darray(S52_zm,S52);
    Darray(S52_a,S52);
    Darray(S52_b,S52);
    Darray(S52_c,S52);
    
    Darray(S53_xm,S53);
    Darray(S53_ym,S53);
    Darray(S53_zm,S53);
    Darray(S53_a,S53);
    Darray(S53_b,S53);
    Darray(S53_c,S53);
    Darray(S53_h,S53);
    
    Darray(S54_xm,S54);
    Darray(S54_ym,S54);
    Darray(S54_zm,S54);
    Darray(S54_a,S54);
    Darray(S54_b,S54);
    Darray(S54_c,S54);
    Darray(S54_h,S54);
    Darray(S54_phi,S54);
    Darray(S54_theta,S54);
    Darray(S54_psi,S54);
    
	
	S61_xs = new double[S61];
	S61_xe = new double[S61];
	S61_ys = new double[S61];
	S61_ye = new double[S61];
	S61_zs = new double[S61];
	S61_ze = new double[S61];
	
	S62_xs = new double[S62];
	S62_xe = new double[S62];
	S62_ys = new double[S62];
	S62_ye = new double[S62];
	S62_zs = new double[S62];
	S62_ze = new double[S62];
	
	S63_xs = new double[S63];
	S63_xe = new double[S63];
	S63_ys = new double[S63];
	S63_ye = new double[S63];
	S63_zs = new double[S63];
	S63_ze = new double[S63];
    
    S81_x1 = new double[S81];
	S81_y1 = new double[S81];
	S81_z1 = new double[S81];
    S81_x2 = new double[S81];
	S81_y2 = new double[S81];
	S81_z2 = new double[S81];
    S81_x3 = new double[S81];
	S81_y3 = new double[S81];
	S81_z3 = new double[S81];
    S81_x4 = new double[S81];
	S81_y4 = new double[S81];
	S81_z4 = new double[S81];
    
    S82_x1 = new double[S82];
	S82_y1 = new double[S82];
	S82_z1 = new double[S82];
    S82_x2 = new double[S82];
	S82_y2 = new double[S82];
	S82_z2 = new double[S82];
    S82_x3 = new double[S82];
	S82_y3 = new double[S82];
	S82_z3 = new double[S82];
    S82_x4 = new double[S82];
	S82_y4 = new double[S82];
	S82_z4 = new double[S82];
    S82_x5 = new double[S82];
	S82_y5 = new double[S82];
	S82_z5 = new double[S82];
    
    S83_x1 = new double[S83];
	S83_y1 = new double[S83];
	S83_z1 = new double[S83];
    S83_x2 = new double[S83];
	S83_y2 = new double[S83];
	S83_z2 = new double[S83];
    S83_x3 = new double[S83];
	S83_y3 = new double[S83];
	S83_z3 = new double[S83];
    S83_x4 = new double[S83];
	S83_y4 = new double[S83];
	S83_z4 = new double[S83];
    S83_x5 = new double[S83];
	S83_y5 = new double[S83];
	S83_z5 = new double[S83];
    S83_x6 = new double[S83];
	S83_y6 = new double[S83];
	S83_z6 = new double[S83];
    
    S84_x1 = new double[S84];
	S84_y1 = new double[S84];
	S84_z1 = new double[S84];
    S84_x2 = new double[S84];
	S84_y2 = new double[S84];
	S84_z2 = new double[S84];
    S84_x3 = new double[S84];
	S84_y3 = new double[S84];
	S84_z3 = new double[S84];
    S84_x4 = new double[S84];
	S84_y4 = new double[S84];
	S84_z4 = new double[S84];
    S84_x5 = new double[S84];
	S84_y5 = new double[S84];
	S84_z5 = new double[S84];
    S84_x6 = new double[S84];
	S84_y6 = new double[S84];
	S84_z6 = new double[S84];
    S84_x7 = new double[S84];
	S84_y7 = new double[S84];
	S84_z7 = new double[S84];
    S84_x8 = new double[S84];
	S84_y8 = new double[S84];
	S84_z8 = new double[S84];
	
	S131_xm = new double[S131];
	S131_zm = new double[S131];
	S131_y1 = new double[S131];
	S131_y2 = new double[S131];
	S131_r1 = new double[S131];
	S131_r2 = new double[S131];
    
    S141_xs = new double[S141];
	S141_xe = new double[S141];
	S141_ys = new double[S141];
	S141_ye = new double[S141];
	S141_zs = new double[S141];
	S141_ze = new double[S141];
    S141_r = new double[S141];
    
    S201_x  = new double[S201];
	S201_ys = new double[S201];
	S201_ye = new double[S201];
	S201_zs = new double[S201];
	S201_ze = new double[S201];
    
    S202_y  = new double[S202];
	S202_xs = new double[S202];
	S202_xe = new double[S202];
	S202_zs = new double[S202];
	S202_ze = new double[S202];
    
    S203_z  = new double[S203];
	S203_xs = new double[S203];
	S203_xe = new double[S203];
	S203_ys = new double[S203];
	S203_ye = new double[S203];
	
	Darray(S121_x,S121);
	Darray(S121_y,S121);
	Darray(S121_z,S121);
	Darray(S121_b,S121);
	Darray(S121_Pd,S121);
	Darray(S121_H0,S121);
	
	Darray(S122_K,S121);
	Darray(S122_n,S121);
	Darray(S122_xc,S121);
	Darray(S122_yc,S121);
	
	Darray(S123_R1,S121);
	Darray(S123_R2,S121);

    int countB10=0;
    int countB22=0;
    int countB31=0;
    int countB32=0;
    int countB33=0;
    int countF11=0;
    int countF21=0;
	int countF31=0;
    int countF41=0;
    int countO10=0;
    int countO32=0;
    int countO33=0;
	int countO43=0;
    int countO61=0;
    int countO62=0;
    int countO63=0;
    int countO64=0;
    int countO65=0;
    int countO66=0;
	int countS10=0;
	int countS11=0;
	int countS32=0;
    int countS33=0;
    int countS34=0;
    int countS35=0;
    int countS36=0;
    int countS37=0;
    int countS38=0;
    int countS39=0;
	int countS41=0;
	int countS42=0;
	int countS43=0;
    int countS51=0;
    int countS52=0;
    int countS53=0;
    int countS54=0;
	int countS61=0;
	int countS62=0;
	int countS63=0;
    int countS81=0;
    int countS82=0;
    int countS83=0;
    int countS84=0;
	int countS121=0;
	int countS122=0;
	int countS123=0;
	int countS131=0;
    int countS141=0;
    int countS201=0;
    int countS202=0;
    int countS203=0;
	
	control.open("control.txt", ios_base::in);
	while(!control.eof())
	{
		control>>c;
		switch(c)
		{
		    case 'B': control>>numint;
				switch(numint)
				{

                case 10: control>>B10_xs[countB10]>>B10_xe[countB10]>>B10_ys[countB10]>>B10_ye[countB10]>>B10_zs[countB10]>>B10_ze[countB10];
                        ++countB10;
						 clear(c,numint);
						 break;
                case 22: control>>B22_xm[countB22]>>B22_ym[countB22]>>B22_zm[countB22]>>B22_r[countB22];
                        ++countB22;
						 clear(c,numint);
						 break;
                case 31: control>>B31_xs[countB31]>>B31_xe[countB31]>>B31_ym[countB31]>>B31_zm[countB31]>>B31_r[countB31];
                        ++countB31;
						 clear(c,numint);
						 break;
                case 32: control>>B32_ys[countB32]>>B32_ye[countB32]>>B32_xm[countB32]>>B32_zm[countB32]>>B32_r[countB32];
                        ++countB32;
						 clear(c,numint);
						 break;
                case 33: control>>B33_zs[countB33]>>B33_ze[countB33]>>B33_xm[countB33]>>B33_ym[countB33]>>B33_r[countB33];
                        ++countB33;
						 clear(c,numint);
						 break;
				}
				break;

            case 'F': control>>numint;
				switch(numint)
				{

                case 11: control>>F11_xs[countF11]>>F11_xe[countF11]>>F11_ys[countF11]>>F11_ye[countF11];
                        ++countF11;
						 clear(c,numint);
						 break;
                case 21: control>>F21_xs[countF21]>>F21_xe[countF21]>>F21_ys[countF21]>>F21_ye[countF21];
                        ++countF21;
						 clear(c,numint);
						 break;
			    case 31: control>>F31_num[countF31];
						F31_x[countF31] = new double[F31_num[countF31]];
						F31_y[countF31] = new double[F31_num[countF31]];
						for(n=0;n<F31_num[countF31];++n)
						control>>F31_x[countF31][n]>>F31_y[countF31][n];
                        ++countF31;
						 clear(c,numint);
						 break;
                case 41: control>>F41_num[countF31];
						F41_x[countF41] = new double[F41_num[countF41]];
						F41_y[countF41] = new double[F41_num[countF41]];
						for(n=0;n<F41_num[countF41];++n)
						control>>F41_x[countF41][n]>>F41_y[countF41][n];
                        ++countF41;
						 clear(c,numint);
						 break;
				}
				break;

		    case 'O': control>>numint;
				switch(numint)
				{

                case 10: control>>O10_xs[countO10]>>O10_xe[countO10]>>O10_ys[countO10]>>O10_ye[countO10]>>O10_zs[countO10]>>O10_ze[countO10];
                        ++countO10;
						 clear(c,numint);
						 break;
				case 32: control>>O32_xm[countO32]>>O32_zm[countO32]>>O32_r[countO32];
                        ++countO32;
						 clear(c,numint);
						 break;
                case 33: control>>O33_xm[countO33]>>O33_ym[countO33]>>O33_r[countO33];
                        ++countO33;
						 clear(c,numint);
						 break;
				case 43: control>>O43_xm[countO43]>>O43_ym[countO43]>>O43_z1[countO43]>>O43_z2[countO43]>>O43_r1[countO43]>>O43_r2[countO43];
                        ++countO43;
						 clear(c,numint);
						 break;
                case 61: control>>O61_xs[countO61]>>O61_xe[countO61]>>O61_ys[countO61]>>O61_ye[countO61]>>O61_zs[countO61]>>O61_ze[countO61];
                        ++countO61;
						 clear(c,numint);
						 break;
                case 62: control>>O62_xs[countO62]>>O62_xe[countO62]>>O62_ys[countO62]>>O62_ye[countO62]>>O62_zs[countO62]>>O62_ze[countO62];
                        ++countO62;
						 clear(c,numint);
						 break;
                case 63: control>>O63_xs[countO63]>>O63_xe[countO63]>>O63_ys[countO63]>>O63_ye[countO63]>>O63_zs[countO63]>>O63_ze[countO63];
                        ++countO63;
						 clear(c,numint);
						 break;
                case 64: control>>O64_xs[countO64]>>O64_xe[countO64]>>O64_ys[countO64]>>O64_ye[countO64]>>O64_zs[countO64]>>O64_ze[countO64];
                        ++countO64;
						 clear(c,numint);
						 break;
                case 65: control>>O65_xs[countO65]>>O65_xe[countO65]>>O65_ys[countO65]>>O65_ye[countO65]>>O65_zs[countO65]>>O65_ze[countO65];
                        ++countO65;
						 clear(c,numint);
						 break;
                case 66: control>>O66_xs[countO66]>>O66_xe[countO66]>>O66_ys[countO66]>>O66_ye[countO66]>>O66_zs[countO66]>>O66_ze[countO66];
                        ++countO66;
						 clear(c,numint);
						 break;
				}
				break;
				
			case 'S': control>>numint;
				switch(numint)
				{
                case 10: control>>S10_xs[countS10]>>S10_xe[countS10]>>S10_ys[countS10]>>S10_ye[countS10]>>S10_zs[countS10]>>S10_ze[countS10];
                        ++countS10;
						 clear(c,numint);
						 break;
				case 11: control>>S11_xs[countS11]>>S11_ys[countS11]>>S11_zs[countS11]>>S11_L[countS11]>>S11_G[countS11]>>S11_ni[countS11]>>S11_nj[countS11]>>S11_nk[countS11];
                        ++countS11;
						 clear(c,numint);
						 break;
				case 32: control>>S32_xm[countS32]>>S32_zm[countS32]>>S32_r[countS32];
                        ++countS32;
						 clear(c,numint);
						 break;
               case 33: control>>S33_xm[countS33]>>S33_ym[countS33]>>S33_r[countS33];
                        ++countS33;
						 clear(c,numint);
						 break;
               case 34: control>>S34_xm1[countS34]>>S34_ym1[countS34]>>S34_zm1[countS34]>>S34_r1[countS34]>>S34_xm2[countS34]>>S34_ym2[countS34]>>S34_zm2[countS34]>>S34_r2[countS34];
                        ++countS34;
						 clear(c,numint);
						 break;
               case 35: control>>S35_xm1[countS35]>>S35_ym1[countS35]>>S35_zm1[countS35]>>S35_r1[countS35]>>S35_xm2[countS35]>>S35_ym2[countS35]>>S35_zm2[countS35]>>S35_r2[countS35];
                        ++countS35;
						 clear(c,numint);
						 break;
               case 36: control>>S36_xm1[countS36]>>S36_ym1[countS36]>>S36_zm1[countS36]>>S36_r1[countS36]>>S36_xm2[countS36]>>S36_ym2[countS36]>>S36_zm2[countS36]>>S36_r2[countS36];
                        ++countS36;
						 clear(c,numint);
						 break;
               case 37: control>>S37_xm1[countS37]>>S37_ym1[countS37]>>S37_zm1[countS37]>>S37_r1[countS37]>>S37_xm2[countS37]>>S37_ym2[countS37]>>S37_zm2[countS37]>>S37_r2[countS37];
                        ++countS37;
						 clear(c,numint);
						 break;
               case 38: control>>S38_xm1[countS38]>>S38_ym1[countS38]>>S38_zm1[countS38]>>S38_r1[countS38]>>S38_xm2[countS38]>>S38_ym2[countS38]>>S38_zm2[countS38]>>S38_r2[countS38];
                        ++countS38;
						 clear(c,numint);
						 break;
               case 39: control>>S39_xm1[countS39]>>S39_ym1[countS39]>>S39_zm1[countS39]>>S39_r1[countS39]>>S39_xm2[countS39]>>S39_ym2[countS39]>>S39_zm2[countS39]>>S39_r2[countS39];
                        ++countS39;
						 clear(c,numint);
						 break;
				case 41: control>>S41_ym[countS41]>>S41_zm[countS41]>>S41_x1[countS41]>>S41_x2[countS41]>>S41_r1[countS41]>>S41_r2[countS41];
                        ++countS41;
						 clear(c,numint);
						 break;
				case 42: control>>S42_xm[countS42]>>S42_zm[countS42]>>S42_y1[countS42]>>S42_y2[countS42]>>S42_r1[countS42]>>S42_r2[countS42];
                        ++countS42;
						 clear(c,numint);
						 break;
				case 43: control>>S43_xm[countS43]>>S43_ym[countS43]>>S43_z1[countS43]>>S43_z2[countS43]>>S43_r1[countS43]>>S43_r2[countS43];
                        ++countS43;
						 clear(c,numint);
						 break;
                case 51: control>>S51_xm[countS51]>>S51_ym[countS51]>>S51_zm[countS51]>>S51_r[countS51];
                        ++countS51;
						 clear(c,numint);
						 break;
                case 52: control>>S52_xm[countS52]>>S52_ym[countS52]>>S52_zm[countS52]>>S52_a[countS52]>>S52_b[countS52]>>S52_c[countS52];
                        ++countS52;
						 clear(c,numint);
						 break;
                case 53: control>>S53_xm[countS53]>>S53_ym[countS53]>>S53_zm[countS53]>>S53_a[countS53]>>S53_b[countS53]>>S53_c[countS53]>>S53_h[countS53];
                        ++countS53;
						 clear(c,numint);
						 break;
               case 54: control>>S54_xm[countS54]>>S54_ym[countS54]>>S54_zm[countS54]>>S54_a[countS54]>>S54_b[countS54]>>S54_c[countS54]>>S54_h[countS54]>>S54_phi[countS54]>>S54_theta[countS54]>>S54_psi[countS54];
                        ++countS54;
						 clear(c,numint);
						 break;
				case 61: control>>S61_xs[countS61]>>S61_xe[countS61]>>S61_ys[countS61]>>S61_ye[countS61]>>S61_zs[countS61]>>S61_ze[countS61];
                        ++countS61;
						 clear(c,numint);
						 break;
				case 62: control>>S62_xs[countS62]>>S62_xe[countS62]>>S62_ys[countS62]>>S62_ye[countS62]>>S62_zs[countS62]>>S62_ze[countS62];
                        ++countS62;
						 clear(c,numint);
						 break;
				case 63: control>>S63_xs[countS63]>>S63_xe[countS63]>>S63_ys[countS63]>>S63_ye[countS63]>>S63_zs[countS63]>>S63_ze[countS63];
                        ++countS63;
						 clear(c,numint);
						 break;
               case 81: control>>S81_x1[countS81]>>S81_y1[countS81]>>S81_z1[countS81]>>S81_x2[countS81]>>S81_y2[countS81]>>S81_z2[countS81]>>S81_x3[countS81]>>S81_y3[countS81]>>S81_z3[countS81]
                               >>S81_x4[countS81]>>S81_y4[countS81]>>S81_z4[countS81];
                        ++countS81;
						 clear(c,numint);
						 break;
               case 82: control>>S82_x1[countS82]>>S82_y1[countS82]>>S82_z1[countS82]>>S82_x2[countS82]>>S82_y2[countS82]>>S82_z2[countS82]>>S82_x3[countS82]>>S82_y3[countS82]>>S82_z3[countS82]
                        >>S82_x4[countS82]>>S82_y4[countS82]>>S82_z4[countS82]>>S82_x5[countS82]>>S82_y5[countS82]>>S82_z5[countS82];
                        ++countS82;
						 clear(c,numint);
						 break;
               case 83: control>>S83_x1[countS83]>>S83_y1[countS83]>>S83_z1[countS83]>>S83_x2[countS83]>>S83_y2[countS83]>>S83_z2[countS83]>>S83_x3[countS83]>>S83_y3[countS83]>>S83_z3[countS83]
                        >>S83_x4[countS83]>>S83_y4[countS83]>>S83_z4[countS83]>>S83_x5[countS83]>>S83_y5[countS83]>>S83_z5[countS83]>>S83_x6[countS83]>>S83_y6[countS83]>>S83_z6[countS83];
                        ++countS83;
						 clear(c,numint);
						 break;
               case 84: control>>S84_x1[countS84]>>S84_y1[countS84]>>S84_z1[countS84]>>S84_x2[countS84]>>S84_y2[countS84]>>S84_z2[countS84]>>S84_x3[countS84]>>S84_y3[countS84]>>S84_z3[countS84]
                        >>S84_x4[countS84]>>S84_y4[countS84]>>S84_z4[countS84]>>S84_x5[countS84]>>S84_y5[countS84]>>S84_z5[countS84]>>S84_x6[countS84]>>S84_y6[countS84]>>S84_z6[countS84]
                        >>S84_x7[countS84]>>S84_y7[countS84]>>S84_z7[countS84]>>S84_x8[countS84]>>S84_y8[countS84]>>S84_z8[countS84];
                        ++countS84;
						 clear(c,numint);
						 break;
				case 121: control>>S121_x[countS121]>>S121_y[countS121]>>S121_z[countS121]>>S121_b[countS121]>>S121_Pd[countS121]>>S121_H0[countS121];
                        ++countS121;
						 clear(c,numint);
						 break;
				case 122: control>>S122_K[countS122]>>S122_n[countS122]>>S122_xc[countS122]>>S122_yc[countS122];
                        ++countS122;
						 clear(c,numint);
						 break;
				case 123: control>>S123_R1[countS123]>>S123_R2[countS123];
                        ++countS123;
						 clear(c,numint);
						 break;
				case 131: control>>S131_xm[countS131]>>S131_zm[countS131]>>S131_y1[countS131]>>S131_y2[countS131]>>S131_r1[countS131]>>S131_r2[countS131];
                        ++countS131;
						 clear(c,numint);
						 break;
               case 141: control>>S141_xs[countS141]>>S141_xe[countS141]>>S141_ys[countS141]>>S141_ye[countS141]>>S141_zs[countS141]>>S141_ze[countS141]>>S141_r[countS141];
                        ++countS141;
						 clear(c,numint);
						 break;
                case 201: control>>S201_x[countS201]>>S201_ys[countS201]>>S201_ye[countS201]>>S201_zs[countS201]>>S201_ze[countS201];
                        ++countS201;
						 clear(c,numint);
						 break;
                case 202: control>>S202_y[countS202]>>S202_xs[countS202]>>S202_xe[countS202]>>S202_zs[countS202]>>S202_ze[countS202];
                        ++countS202;
						 clear(c,numint);
						 break;
                case 203: control>>S203_z[countS203]>>S203_xs[countS203]>>S203_xe[countS203]>>S203_ys[countS203]>>S203_ye[countS203];
                        ++countS203;
						 clear(c,numint);
						 break;
				}
				break;
		}
	}

	control.close();
	
	
}

void lexer::clear(char& b, int& j)
{
	b='null';
}
