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

#include"lexer.h"
#include <fstream>

void lexer::read_control()
{
	char c;
	int numint,numval;
    int count;
	numlinsurf=0;

    B10=0;
    B22=0;
    B31=0;
    B33=0;
	S10=0;
	
	cout<<"read control"<<endl;

	ifstream control("control.txt", ios_base::in);

	if(!control)
	{
		cout<<"no 'control.txt' file"<<endl<<endl;
		//exit(0);
	}
    
    count=0;
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
                case 127: control>>B127_dx_min>>B127_dx_max>>B127_pf>>B127_df>>B127_r;
                        B127=1;
						 clear(c,numint);
						 break;
                case 128: control>>B128_dx_min>>B128_dx_max>>B128_pf>>B128_df>>B128_r;
                        B128=1;
						 clear(c,numint);
						 break;   
                case 129: control>>B129_dx_min>>B129_dx_max>>B129_pf>>B129_df>>B129_r;
                        B129=1;
						 clear(c,numint);
						 break;  
				case 130: control>>B130;
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
                case 21: control>>C21;
                         clear(c,numint);
						 break;
                case 22: control>>C22;
                         clear(c,numint);
						 break;
                case 23: control>>C23;
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
               case 100: control>>D100;
                         clear(c,numint);
						 break;
				}
				break;

        case 'G': control>>numint;
				switch(numint)
				{
                case  9: control>>G9;
                         clear(c,numint);
						 break;
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
                case 26: control>>G26_zh;
                        G26=1;
                         clear(c,numint);
						 break;
                case 27: control>>G27_zh;
                        G27=1;
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
                case 36: control>>G36;
                        G36_select=1;
                         clear(c,numint);
						 break;
                case 37: control>>G37;
                        if(G37>0)
                        G37_select=1;
                        
                        if(G37<0)
                        G37_select=-1;
                         clear(c,numint);
						 break;
                case 38: control>>G38;
                        G38_select=1;
                         clear(c,numint);
						 break;
                case 39: control>>G39;
                         clear(c,numint);
						 break;
                case 41: control>>G41;
                         clear(c,numint);
						 break;
                case 51: control>>G51;
                         clear(c,numint);
						 break;
                case 52: control>>G52;
                         clear(c,numint);
						 break;
                case 53: control>>G53;
                        G53_flag=1;
                         clear(c,numint);
						 break;
				}
				break;
                
        case 'H': control>>numint;
				switch(numint)
				{
                case 10: control>>H10;
                         clear(c,numint);
						 break;
                case 21: control>>H21;
                         clear(c,numint);
						 break;
                case 22: control>>H22;
                         clear(c,numint);
						 break;
                case 23: control>>H23;
                         clear(c,numint);
						 break;
                case 31: control>>H31;
                         clear(c,numint);
						 break;
                case 32: control>>H32;
                         clear(c,numint);
						 break;
                case 33: control>>H33;
                         clear(c,numint);
						 break;
                case 34: control>>H34;
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
                case 30: control>>M30_x>>M30_y>>M30_z;
						 clear(c,numint);
						 break;
				case 41: control>>M41;
						 clear(c,numint);
						 break;
               case 45: control>>M45;
						 clear(c,numint);
						 break;
				}
				break;
				
		case 'S': 
        case 'O': 
        control>>numint;
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
                case 12: ++S12;
						 clear(c,numint);
						 break;
               case 15: control>>S15;
						 clear(c,numint);
						 break;
               case 18: control>>S18;
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
               case 37: ++S37;
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
               case 90: control>>S90;
						 clear(c,numint);
						 break;
               case 91: control>>S91;
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
                case 301: control>>S301;
						 clear(c,numint);
						 break;
                case 305: control>>S305;
						 clear(c,numint);
						 break;
                case 306: control>>S306;
						 clear(c,numint);
						 break;
                case 307: control>>S307_fh>>S307_bh;
						 clear(c,numint);
						 break;
                case 308: control>>S308_x>>S308_y;
						 clear(c,numint);
						 break;
                case 309: control>>S309_x>>S309_y>>S309_z;
						 clear(c,numint);
						 break;
                case 310: ++S310;
						 clear(c,numint);
                        ++S300;
						 break;
                case 320: ++S320;
						 clear(c,numint);
                        ++S300;
						 break;
                case 330: ++S330;
						 clear(c,numint);
                        ++S300;
						 break;
                case 340: ++S340;
						 clear(c,numint);
                        ++S300;
						 break;
				}
				break;
                
        case 'T': 
        control>>numint;
				switch(numint)
				{
				case 1: control>>T1;
						 clear(c,numint);
						 break;
				case 2: control>>T2;
						 clear(c,numint);
						 break;
				case 3: control>>T3_xs>>T3_xe>>T3_ys>>T3_ye>>T3_zs>>T3_ze;
						T3=1;
						 clear(c,numint);
						 break;
				case 4: control>>T4;
						 clear(c,numint);
						 break;
				case 5: control>>T5_x>>T5_y>>T5_z>>T5_phi>>T5_theta>>T5_psi;
                          T5=1;
						 clear(c,numint);
						 break;
				case 6: control>>T6;
						 clear(c,numint);
						 break;
				case 7: control>>T7_dx>>T7_dy>>T7_dz;
						T7=1;
						 clear(c,numint);
						 break;
				case 8: control>>T8;
						 clear(c,numint);
						 break;
				case 9: control>>T9;
						 clear(c,numint);
						 break;
				case 10: ++T10;
						 clear(c,numint);
						 break;
				case 11: ++T11;
						 clear(c,numint);
						 break;
               case 15: control>>T15;
						 clear(c,numint);
						 break;
               case 18: control>>T18;
						 clear(c,numint);
						 break;
               case 19: control>>T19;
						 clear(c,numint);
						 break;
               case 31: control>>T31_x>>T31_y>>T31_z>>T31_phi>>T31_theta>>T31_psi;
                          T31=1;
						 clear(c,numint);
						 break;
				case 32: ++T32;
						 clear(c,numint);
						 break;
               case 33: ++T33;
						 clear(c,numint);
						 break;
               case 37: ++T37;
						 clear(c,numint);
						 break;
				case 41: ++T41;
						 clear(c,numint);
						 break;
				case 42: ++T42;
						 clear(c,numint);
						 break;
				case 43: ++T43;
						 clear(c,numint);
						 break;
                case 51: ++T51;
						 clear(c,numint);
						 break;
                case 52: ++T52;
						 clear(c,numint);
						 break;
                case 53: ++T53;
						 clear(c,numint);
						 break;
               case 54: ++T54;
						 clear(c,numint);
						 break;
				case 61: ++T61;
						 clear(c,numint);
						 break;
				case 62: ++T62;
						 clear(c,numint);
						 break;
				case 63: ++T63;
						 clear(c,numint);
						 break;
               case 81: ++T81;
						 clear(c,numint);
						 break;
               case 82: ++T82;
						 clear(c,numint);
						 break;
               case 83: ++T83;
						 clear(c,numint);
						 break;
               case 84: ++T84;
						 clear(c,numint);
						 break;
				case 121: ++T121;
						 clear(c,numint);
						 break;
				case 122: ++T122;
						 clear(c,numint);
						 break;
				case 123: ++T123;
						 clear(c,numint);
						 break;
				case 131: ++T131;
						 clear(c,numint);
						 break;
                case 141: ++T141;
						 clear(c,numint);
						 break;
                case 201: ++T201;
						 clear(c,numint);
						 break;
                case 202: ++T202;
						 clear(c,numint);
						 break;
                case 203: ++T203;
						 clear(c,numint);
						 break;
                case 301: control>>T301;
						 clear(c,numint);
						 break;
                case 305: control>>T305;
						 clear(c,numint);
						 break;
                case 306: control>>T306;
						 clear(c,numint);
						 break;
                case 307: control>>T307_fh>>T307_bh;
						 clear(c,numint);
						 break;
                case 308: control>>T308_x>>T308_y;
						 clear(c,numint);
						 break;
                case 309: control>>T309_x>>T309_y>>T309_z;
						 clear(c,numint);
						 break;
                case 310: ++T310;
						 clear(c,numint);
                        ++T300;
						 break;
                case 320: ++T320;
						 clear(c,numint);
                        ++T300;
						 break;
                case 330: ++T330;
						 clear(c,numint);
                        ++T300;
						 break;
                case 340: ++T340;
						 clear(c,numint);
                        ++T300;
						 break;
				}
				break;
                

        case 'V': 
        control>>numint;
				switch(numint)
				{
				case 1:  ++V1;
						 clear(c,numint);
						 break;
				case 4: control>>V4;
						 clear(c,numint);
						 break;
				case 5: control>>V5_x>>V5_y>>V5_z>>V5_phi>>V5_theta>>V5_psi;
                          V5=1;
						 clear(c,numint);
						 break;
				case 6: control>>V6;
						 clear(c,numint);
						 break;
				case 7: control>>V7_dx>>V7_dy>>V7_dz;
						V7=1;
						 clear(c,numint);
						 break;
				case 8: control>>V8;
						 clear(c,numint);
						 break;
				case 9: control>>V9;
						 clear(c,numint);
						 break;
				case 10: ++V10;
						 clear(c,numint);
						 break;
				case 11: ++V11;
						 clear(c,numint);
						 break;
               case 15: control>>V15;
						 clear(c,numint);
						 break;
               case 18: control>>V18;
						 clear(c,numint);
						 break;
               case 19: control>>V19;
						 clear(c,numint);
						 break;
               case 31: control>>V31_x>>V31_y>>V31_z>>V31_phi>>V31_theta>>V31_psi;
                          V31=1;
						 clear(c,numint);
						 break;
				case 32: ++V32;
						 clear(c,numint);
						 break;
               case 33: ++V33;
						 clear(c,numint);
						 break;
               case 37: ++V37;
						 clear(c,numint);
						 break;
				case 41: ++V41;
						 clear(c,numint);
						 break;
				case 42: ++V42;
						 clear(c,numint);
						 break;
				case 43: ++V43;
						 clear(c,numint);
						 break;
                case 51: ++V51;
						 clear(c,numint);
						 break;
				case 61: ++V61;
						 clear(c,numint);
						 break;
				case 62: ++V62;
						 clear(c,numint);
						 break;
				case 63: ++V63;
						 clear(c,numint);
						 break;
               case 81: ++V81;
						 clear(c,numint);
						 break;
               case 82: ++V82;
						 clear(c,numint);
						 break;
               case 83: ++V83;
						 clear(c,numint);
						 break;
               case 84: ++V84;
						 clear(c,numint);
						 break;
				case 131: ++V131;
						 clear(c,numint);
						 break;
				}
				break;


		}
        ++count;
	}
        if(count>1e7)
        {
        cout<<endl;
        cout<<"!!! missing input parameter in control.txt !!!"<<endl<<endl;
        cout<<"!!! please check the DIVEMesh User Guide !!!"<<endl<<endl<<endl<<endl;
        
        exit(0);
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
    
    Iarray(M31,M30_x);
    Iarray(M32,M30_y);
    Iarray(M33,M30_z);
	
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
    
    Darray(S12_xs,S12);
    Darray(S12_ys,S12);
    Darray(S12_zs,S12);
    Darray(S12_xe,S12);
    Darray(S12_ye,S12);
    Darray(S12_ze,S12);
    Darray(S12_b,S12);
    Darray(S12_h,S12);
	
    S32_xm = new double[S32];
	S32_zm = new double[S32];
	S32_r  = new double[S32];
    
	S33_xm = new double[S33];
	S33_ym = new double[S33];
	S33_r  = new double[S33];
    
    S37_xm1 = new double[S37];
	S37_ym1 = new double[S37];
    S37_zm1 = new double[S37];
    S37_r1 = new double[S37];
	S37_xm2 = new double[S37];
	S37_ym2 = new double[S37];
    S37_zm2 = new double[S37];
    S37_r2 = new double[S37];
	
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
    
    Darray(S81_xyz,S81,12);
    
    Darray(S82_xyz,S82,15);
    
    Darray(S83_xyz,S83,18);
    
    Darray(S84_xyz,S84,24);
	
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
    
    Iarray(S300_ord,S300);
    
    Darray(S310_l,S310);
    
    Darray(S320_r,S320);
    Darray(S320_phi,S320);
    
    Darray(S330_r,S330);
    Darray(S330_phi,S330);
    
    Darray(S340_teta,S340);
    Darray(S340_L,S340);
    Darray(S340_N,S340);
    Darray(S340_ds,S340);
    
    
    T10_xs = new double[T10];
	T10_xe = new double[T10];
	T10_ys = new double[T10];
	T10_ye = new double[T10];
	T10_zs = new double[T10];
	T10_ze = new double[T10];
	
	T11_xs = new double[T11];
	T11_ys = new double[T11];
	T11_zs = new double[T11];
	T11_L = new double[T11];
	T11_G = new double[T11];
	T11_ni = new int[T11];
	T11_nj = new int[T11];
	T11_nk = new int[T11];
	
    T32_xm = new double[T32];
	T32_zm = new double[T32];
	T32_r  = new double[T32];
    
	T33_xm = new double[T33];
	T33_ym = new double[T33];
	T33_r  = new double[T33];
    
    T37_xm1 = new double[T37];
	T37_ym1 = new double[T37];
    T37_zm1 = new double[T37];
    T37_r1 = new double[T37];
	T37_xm2 = new double[T37];
	T37_ym2 = new double[T37];
    T37_zm2 = new double[T37];
    T37_r2 = new double[T37];
	
	T41_ym = new double[T41];
	T41_zm = new double[T41];
	T41_x1 = new double[T41];
	T41_x2 = new double[T41];
	T41_r1 = new double[T41];
	T41_r2 = new double[T41];
	
	T42_xm = new double[T42];
	T42_zm = new double[T42];
	T42_y1 = new double[T42];
	T42_y2 = new double[T42];
	T42_r1 = new double[T42];
	T42_r2 = new double[T42];
	
	T43_xm = new double[T43];
	T43_ym = new double[T43];
	T43_z1 = new double[T43];
	T43_z2 = new double[T43];
	T43_r1 = new double[T43];
	T43_r2 = new double[T43];
    
    Darray(T51_xm,T51);
    Darray(T51_ym,T51);
    Darray(T51_zm,T51);
    Darray(T51_r,T51);
    
    Darray(T52_xm,T52);
    Darray(T52_ym,T52);
    Darray(T52_zm,T52);
    Darray(T52_a,T52);
    Darray(T52_b,T52);
    Darray(T52_c,T52);
    
    Darray(T53_xm,T53);
    Darray(T53_ym,T53);
    Darray(T53_zm,T53);
    Darray(T53_a,T53);
    Darray(T53_b,T53);
    Darray(T53_c,T53);
    Darray(T53_h,T53);
    
    Darray(T54_xm,T54);
    Darray(T54_ym,T54);
    Darray(T54_zm,T54);
    Darray(T54_a,T54);
    Darray(T54_b,T54);
    Darray(T54_c,T54);
    Darray(T54_h,T54);
    Darray(T54_phi,T54);
    Darray(T54_theta,T54);
    Darray(T54_psi,T54);
    
	
	T61_xs = new double[T61];
	T61_xe = new double[T61];
	T61_ys = new double[T61];
	T61_ye = new double[T61];
	T61_zs = new double[T61];
	T61_ze = new double[T61];
	
	T62_xs = new double[T62];
	T62_xe = new double[T62];
	T62_ys = new double[T62];
	T62_ye = new double[T62];
	T62_zs = new double[T62];
	T62_ze = new double[T62];
	
	T63_xs = new double[T63];
	T63_xe = new double[T63];
	T63_ys = new double[T63];
	T63_ye = new double[T63];
	T63_zs = new double[T63];
	T63_ze = new double[T63];
    
    Darray(T81_xyz,T81,12);
    
    Darray(T82_xyz,T82,15);
    
    Darray(T83_xyz,T83,18);
    
    Darray(T84_xyz,T84,24);
	
	T131_xm = new double[T131];
	T131_zm = new double[T131];
	T131_y1 = new double[T131];
	T131_y2 = new double[T131];
	T131_r1 = new double[T131];
	T131_r2 = new double[T131];
    
    T141_xs = new double[T141];
	T141_xe = new double[T141];
	T141_ys = new double[T141];
	T141_ye = new double[T141];
	T141_zs = new double[T141];
	T141_ze = new double[T141];
    T141_r = new double[T141];
    
    T201_x  = new double[T201];
	T201_ys = new double[T201];
	T201_ye = new double[T201];
	T201_zs = new double[T201];
	T201_ze = new double[T201];
    
    T202_y  = new double[T202];
	T202_xs = new double[T202];
	T202_xe = new double[T202];
	T202_zs = new double[T202];
	T202_ze = new double[T202];
    
    T203_z  = new double[T203];
	T203_xs = new double[T203];
	T203_xe = new double[T203];
	T203_ys = new double[T203];
	T203_ye = new double[T203];
	
	Darray(T121_x,T121);
	Darray(T121_y,T121);
	Darray(T121_z,T121);
	Darray(T121_b,T121);
	Darray(T121_Pd,T121);
	Darray(T121_H0,T121);
	
	Darray(T122_K,T121);
	Darray(T122_n,T121);
	Darray(T122_xc,T121);
	Darray(T122_yc,T121);
	
	Darray(T123_R1,T121);
	Darray(T123_R2,T121);
    
    Iarray(T300_ord,T300);
    
    Darray(T310_l,T310);
    
    Darray(T320_r,T320);
    Darray(T320_phi,T320);
    
    Darray(T330_r,T330);
    Darray(T330_phi,T330);
    
    Darray(T340_teta,T340);
    Darray(T340_L,T340);
    Darray(T340_N,T340);
    Darray(T340_ds,T340);

    int countB10=0;
    int countB22=0;
    int countB31=0;
    int countB32=0;
    int countB33=0;
	int countS10=0;
	int countS11=0;
    int countS12=0;
	int countS32=0;
    int countS33=0;
    int countS37=0;
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
    int countS300=0;
    int countG310=0;
    int countG320=0;
    int countG330=0;
    int countG340=0;
    int countT10=0;
	int countT11=0;
	int countT32=0;
    int countT33=0;
    int countT37=0;
	int countT41=0;
	int countT42=0;
	int countT43=0;
    int countT51=0;
    int countT52=0;
    int countT53=0;
    int countT54=0;
	int countT61=0;
	int countT62=0;
	int countT63=0;
    int countT81=0;
    int countT82=0;
    int countT83=0;
    int countT84=0;
	int countT121=0;
	int countT122=0;
	int countT123=0;
	int countT131=0;
    int countT141=0;
    int countT201=0;
    int countT202=0;
    int countT203=0;
    int countT300=0;
    int countT310=0;
    int countT320=0;
    int countT330=0;
    int countT340=0;
	
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
                
                
                case 'M': control>>numint;
				switch(numint)
				{
                case 31: 
                    for(int qn=0;qn<M30_x-1;++qn)
                    control>>M31[qn];
						 clear(c,numint);
						 break;
                case 32: 
                    for(int qn=0;qn<M30_y-1;++qn)
                    control>>M32[qn];
						 clear(c,numint);
						 break;
                case 33: 
                    for(int qn=0;qn<M30_z-1;++qn)
                    control>>M33[qn];
						 clear(c,numint);
						 break;
   
				}
				break;
				
			case 'S': 
           case 'O': 
            control>>numint;
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
                case 12: control>>S12_xs[countS12]>>S12_ys[countS12]>>S12_zs[countS12]>>S12_xe[countS12]>>S12_ye[countS12]>>S12_ze[countS12]>>S12_b[countS12]>>S12_h[countS12];
                        ++countS12;
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
               case 37: control>>S37_xm1[countS37]>>S37_ym1[countS37]>>S37_zm1[countS37]>>S37_r1[countS37]>>S37_xm2[countS37]>>S37_ym2[countS37]>>S37_zm2[countS37]>>S37_r2[countS37];
                        ++countS37;
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
               case 81: for(int qn=0;qn<12;++qn)
                        control>>S81_xyz[countS81][qn];
                        ++countS81;
						 clear(c,numint);
						 break;
               case 82: for(int qn=0;qn<15;++qn)
                        control>>S82_xyz[countS82][qn];
                        ++countS82;
						 clear(c,numint);
						 break;
               case 83: for(int qn=0;qn<18;++qn)
                        control>>S83_xyz[countS83][qn];
                        ++countS83;
						 clear(c,numint);
						 break;
               case 84: for(int qn=0;qn<24;++qn)
                        control>>S84_xyz[countS84][qn];
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
                case 310: control>>S310_l[countG310];
                        ++countG310;
                        S300_ord[countS300]=1;
                        ++countS300;
                        clear(c,numint);
                        break;
                case 320: control>>S320_r[countG320]>>S320_phi[countG320];
                        ++countG320;
                        S300_ord[countS300]=2;
                        ++countS300;
                        clear(c,numint);
                        break;
                case 330: control>>S330_r[countG330]>>S330_phi[countG330];
                        ++countG330;
                        S300_ord[countS300]=3;
                        ++countS300;
                        clear(c,numint);
                        break;
                case 340: control>>S340_teta[countG340]>>S340_L[countG340]>>S340_N[countG340]>>S340_ds[countG340];
                        ++countG340;
                        S300_ord[countS300]=4;
                        ++countS300;
                        clear(c,numint);
                        break;
                
				}
				break;
                
            case 'T': 
            control>>numint;
				switch(numint)
				{
                case 10: control>>T10_xs[countT10]>>T10_xe[countT10]>>T10_ys[countT10]>>T10_ye[countT10]>>T10_zs[countT10]>>T10_ze[countT10];
                        ++countT10;
						 clear(c,numint);
						 break;
				case 11: control>>T11_xs[countT11]>>T11_ys[countT11]>>T11_zs[countT11]>>T11_L[countT11]>>T11_G[countT11]>>T11_ni[countT11]>>T11_nj[countT11]>>T11_nk[countT11];
                        ++countT11;
						 clear(c,numint);
						 break;
				case 32: control>>T32_xm[countT32]>>T32_zm[countT32]>>T32_r[countT32];
                        ++countT32;
						 clear(c,numint);
						 break;
               case 33: control>>T33_xm[countT33]>>T33_ym[countT33]>>T33_r[countT33];
                        ++countT33;
						 clear(c,numint);
						 break;
               case 37: control>>T37_xm1[countT37]>>T37_ym1[countT37]>>T37_zm1[countT37]>>T37_r1[countT37]>>T37_xm2[countT37]>>T37_ym2[countT37]>>T37_zm2[countT37]>>T37_r2[countT37];
                        ++countT37;
						 clear(c,numint);
						 break;
				case 41: control>>T41_ym[countT41]>>T41_zm[countT41]>>T41_x1[countT41]>>T41_x2[countT41]>>T41_r1[countT41]>>T41_r2[countT41];
                        ++countT41;
						 clear(c,numint);
						 break;
				case 42: control>>T42_xm[countT42]>>T42_zm[countT42]>>T42_y1[countT42]>>T42_y2[countT42]>>T42_r1[countT42]>>T42_r2[countT42];
                        ++countT42;
						 clear(c,numint);
						 break;
				case 43: control>>T43_xm[countT43]>>T43_ym[countT43]>>T43_z1[countT43]>>T43_z2[countT43]>>T43_r1[countT43]>>T43_r2[countT43];
                        ++countT43;
						 clear(c,numint);
						 break;
                case 51: control>>T51_xm[countT51]>>T51_ym[countT51]>>T51_zm[countT51]>>T51_r[countT51];
                        ++countT51;
						 clear(c,numint);
						 break;
                case 52: control>>T52_xm[countT52]>>T52_ym[countT52]>>T52_zm[countT52]>>T52_a[countT52]>>T52_b[countT52]>>T52_c[countT52];
                        ++countT52;
						 clear(c,numint);
						 break;
                case 53: control>>T53_xm[countT53]>>T53_ym[countT53]>>T53_zm[countT53]>>T53_a[countT53]>>T53_b[countT53]>>T53_c[countT53]>>T53_h[countT53];
                        ++countT53;
						 clear(c,numint);
						 break;
               case 54: control>>T54_xm[countT54]>>T54_ym[countT54]>>T54_zm[countT54]>>T54_a[countT54]>>T54_b[countT54]>>T54_c[countT54]>>T54_h[countT54]>>T54_phi[countT54]>>T54_theta[countT54]>>T54_psi[countT54];
                        ++countT54;
						 clear(c,numint);
						 break;
				case 61: control>>T61_xs[countT61]>>T61_xe[countT61]>>T61_ys[countT61]>>T61_ye[countT61]>>T61_zs[countT61]>>T61_ze[countT61];
                        ++countT61;
						 clear(c,numint);
						 break;
				case 62: control>>T62_xs[countT62]>>T62_xe[countT62]>>T62_ys[countT62]>>T62_ye[countT62]>>T62_zs[countT62]>>T62_ze[countT62];
                        ++countT62;
						 clear(c,numint);
						 break;
				case 63: control>>T63_xs[countT63]>>T63_xe[countT63]>>T63_ys[countT63]>>T63_ye[countT63]>>T63_zs[countT63]>>T63_ze[countT63];
                        ++countT63;
						 clear(c,numint);
						 break;
               case 81: for(int qn=0;qn<12;++qn)
                        control>>T81_xyz[countT81][qn];
                        ++countT81;
						 clear(c,numint);
						 break;
               case 82: for(int qn=0;qn<15;++qn)
                        control>>T82_xyz[countT82][qn];
                        ++countT82;
						 clear(c,numint);
						 break;
               case 83: for(int qn=0;qn<18;++qn)
                        control>>T83_xyz[countT83][qn];
                        ++countT83;
						 clear(c,numint);
						 break;
               case 84: for(int qn=0;qn<24;++qn)
                        control>>T84_xyz[countT84][qn];
                        ++countT84;
						 clear(c,numint);
						 break;
				case 121: control>>T121_x[countT121]>>T121_y[countT121]>>T121_z[countT121]>>T121_b[countT121]>>T121_Pd[countT121]>>T121_H0[countT121];
                        ++countT121;
						 clear(c,numint);
						 break;
				case 122: control>>T122_K[countT122]>>T122_n[countT122]>>T122_xc[countT122]>>T122_yc[countT122];
                        ++countT122;
						 clear(c,numint);
						 break;
				case 123: control>>T123_R1[countT123]>>T123_R2[countT123];
                        ++countT123;
						 clear(c,numint);
						 break;
				case 131: control>>T131_xm[countT131]>>T131_zm[countT131]>>T131_y1[countT131]>>T131_y2[countT131]>>T131_r1[countT131]>>T131_r2[countT131];
                        ++countT131;
						 clear(c,numint);
						 break;
               case 141: control>>T141_xs[countT141]>>T141_xe[countT141]>>T141_ys[countT141]>>T141_ye[countT141]>>T141_zs[countT141]>>T141_ze[countT141]>>T141_r[countT141];
                        ++countT141;
						 clear(c,numint);
						 break;
                case 201: control>>T201_x[countT201]>>T201_ys[countT201]>>T201_ye[countT201]>>T201_zs[countT201]>>T201_ze[countT201];
                        ++countT201;
						 clear(c,numint);
						 break;
                case 202: control>>T202_y[countT202]>>T202_xs[countT202]>>T202_xe[countT202]>>T202_zs[countT202]>>T202_ze[countT202];
                        ++countT202;
						 clear(c,numint);
						 break;
                case 203: control>>T203_z[countT203]>>T203_xs[countT203]>>T203_xe[countT203]>>T203_ys[countT203]>>T203_ye[countT203];
                        ++countT203;
						 clear(c,numint);
						 break;
                case 310: control>>T310_l[countT310];
                        ++countT310;
                        T300_ord[countT300]=1;
                        ++countT300;
                        clear(c,numint);
                        break;
                case 320: control>>T320_r[countT320]>>T320_phi[countT320];
                        ++countT320;
                        T300_ord[countT300]=2;
                        ++countT300;
                        clear(c,numint);
                        break;
                case 330: control>>T330_r[countT330]>>T330_phi[countT330];
                        ++countT330;
                        T300_ord[countT300]=3;
                        ++countT300;
                        clear(c,numint);
                        break;
                case 340: control>>T340_teta[countT340]>>T340_L[countT340]>>T340_N[countT340]>>T340_ds[countT340];
                        ++countT340;
                        T300_ord[countT300]=4;
                        ++countT300;
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
