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

#include "lexer.h"


void lexer::createspace()
{
    
    xmin=+1.0e19;
    ymin=+1.0e19;
    zmin=+1.0e19;

    xmax=-1.0e19;
    ymax=-1.0e19;
    zmax=-1.0e19;

    for(qn=0;qn<B10;++qn)
    {
    xmin=MIN(xmin,B10_xs[qn]);
    ymin=MIN(ymin,B10_ys[qn]);
    zmin=MIN(zmin,B10_zs[qn]);
    xmin=MIN(xmin,B10_xe[qn]);
    ymin=MIN(ymin,B10_ye[qn]);
    zmin=MIN(zmin,B10_ze[qn]);

    xmax=MAX(xmax,B10_xs[qn]);
    ymax=MAX(ymax,B10_ys[qn]);
    zmax=MAX(zmax,B10_zs[qn]);
    xmax=MAX(xmax,B10_xe[qn]);
    ymax=MAX(ymax,B10_ye[qn]);
    zmax=MAX(zmax,B10_ze[qn]);
    }

    for(qn=0;qn<B22;++qn)
    {
    xmin=MIN(xmin,B22_xm[qn]-B22_r[qn])-dx;
    ymin=MIN(ymin,B22_ym[qn]-B22_r[qn])-dx;
    zmin=MIN(zmin,B22_zm[qn]-B22_r[qn])-dx;

    xmax=MAX(xmax,B22_xm[qn]+B22_r[qn])+dx;
    ymax=MAX(ymax,B22_ym[qn]+B22_r[qn])+dx;
    zmax=MAX(zmax,B22_zm[qn]+B22_r[qn])+dx;
    }

    for(qn=0;qn<B31;++qn)
    {
    xmin=MIN(xmin,B31_xs[qn]);
    xmin=MIN(xmin,B31_xe[qn]);
    ymin=MIN(ymin,B31_ym[qn]-B31_r[qn])-dx;
    zmin=MIN(zmin,B31_zm[qn]-B31_r[qn])-dx;

    xmax=MAX(xmax,B31_xs[qn]);
    xmax=MAX(xmax,B31_xe[qn]);
    ymax=MAX(ymax,B31_ym[qn]+B31_r[qn])+dx;
    zmax=MAX(zmax,B31_zm[qn]+B31_r[qn])+dx;
    }

    for(qn=0;qn<B32;++qn)
    {
    xmin=MIN(xmin,B32_xm[qn]-B32_r[qn])-dx;
    ymin=MIN(ymin,B32_ys[qn]);
    ymin=MIN(ymin,B32_ye[qn]);
    zmin=MIN(zmin,B32_zm[qn]-B32_r[qn])-dx;

    xmax=MAX(xmax,B32_xm[qn]+B32_r[qn])+dx;
    ymax=MAX(ymax,B32_ys[qn]);
    ymax=MAX(ymax,B32_ye[qn]);
    zmax=MAX(zmax,B32_zm[qn]+B32_r[qn])+dx;
    }

    for(qn=0;qn<B33;++qn)
    {
    xmin=MIN(xmin,B33_xm[qn]-B33_r[qn])-dx;
    ymin=MIN(ymin,B33_ym[qn]-B33_r[qn])-dx;
    zmin=MIN(zmin,B33_zs[qn]);
    zmin=MIN(zmin,B33_ze[qn]);

    xmax=MAX(xmax,B33_xm[qn]+B33_r[qn])+dx;
    ymax=MAX(ymax,B33_ym[qn]+B33_r[qn])+dx;
    zmax=MAX(zmax,B33_zs[qn]);
    zmax=MAX(zmax,B33_ze[qn]);
    }

    for(qn=0;qn<F11;++qn)
    {
    xmin=MIN(xmin,F11_xs[qn]);
    ymin=MIN(ymin,F11_ys[qn]);
    zmin=MIN(zmin,F3_zs);
    xmin=MIN(xmin,F11_xe[qn]);
    ymin=MIN(ymin,F11_ye[qn]);
    zmin=MIN(zmin,F3_ze);

    xmax=MAX(xmax,F11_xs[qn]);
    ymax=MAX(ymax,F11_ys[qn]);
    zmax=MAX(zmax,F3_zs);
    xmax=MAX(xmax,F11_xe[qn]);
    ymax=MAX(ymax,F11_ye[qn]);
    zmax=MAX(zmax,F3_ze);
    }

    for(qn=0;qn<F21;++qn)
    {
    xmin=MIN(xmin,F21_xs[qn]);
    ymin=MIN(ymin,F21_ys[qn]);
    zmin=MIN(zmin,F3_zs);
    xmin=MIN(xmin,F21_xe[qn]);
    ymin=MIN(ymin,F21_ye[qn]);
    zmin=MIN(zmin,F3_ze);

    xmax=MAX(xmax,F21_xs[qn]);
    ymax=MAX(ymax,F21_ys[qn]);
    zmax=MAX(zmax,F3_zs);
    xmax=MAX(xmax,F21_xe[qn]);
    ymax=MAX(ymax,F21_ye[qn]);
    zmax=MAX(zmax,F3_ze);
    }
    
    if(S1==1 && S2==1)
    {
    xmin=xs_stl;
    ymin=ys_stl;
    zmin=zs_stl;
    xmax=xe_stl;
    ymax=ye_stl;
    zmax=ze_stl;
	}
    
    
    if(B2==0)
    {
    knox = conv((xmax-xmin)/dx);
	knoy = conv((ymax-ymin)/dx);
	knoz = conv((zmax-zmin)/dx);
    }
    
    if(B2==1)
    {
    knox = B2_knox;
    knoy = B2_knoy;
    knoz = B2_knoz;
    }
    
    if(B101==8)
    knox = B121_N1 + B121_N2 + B121_N3;
    
    if(B102==8)
    knoy = B122_N1 + B122_N2 + B122_N3;
    
    if(B103==8)
    knoz = B123_N1 + B123_N2 + B123_N3;
    
    if(B101==9)
    knox = B124_N1 + B124_N2 + B124_N3;
    
    if(B102==9)
    knoy = B125_N1 + B125_N2 + B125_N3;
    
    if(B103==9)
    knoz = B126_N1 + B126_N2 + B126_N3;
    
    
    if(B2==0)
    DXM = dx;
    
    if(B2==1)
    DXM=dx = (1./3.0) * ((xmax-xmin)/double(knox) + (ymax-ymin)/double(knoy) + (zmax-zmin)/double(knoz));
    
    cout<<"DXM: "<<DXM<<endl;

	x1=0;
	y1=0;
	z1=0;

    cout<<"xma:"<<xma<<" yma: "<<yma<<" zma: "<<zma<<endl;
    cout<<"xmin:"<<xmin<<" ymin: "<<ymin<<" zmin: "<<zmin<<endl;
    cout<<"xmax:"<<xmax<<" ymax: "<<ymax<<" zmax: "<<zmax<<endl;
    cout<<"knox:"<<knox<<" knoy: "<<knoy<<" knoz: "<<knoz<<endl;
	cout<<"base_cellnum3D: "<<knox*knoy*knoz<<endl;
    cout<<"base_cellnum2D: "<<knox*knoy<<endl;
    cout<<"x1:"<<x1<<" y1: "<<y1<<" z1: "<<z1<<endl;
	
	cout<<"field: "<<(knox+2*xma)*(knoy+2*yma)*(knoz+2*zma)<<endl;
    cout<<"slice: "<<(knox+2*xma)*(knoy+2*yma)<<endl<<endl;

}

