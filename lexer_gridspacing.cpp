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

void lexer::gridspacing()
{
    cout<<"grid_spacing: ";
    
    if(B2==0)
    DXM = dx;
    
    if(B2==1)
    DXM=dx = (1./3.0) * ((xmax-xmin)/double(knox) + (ymax-ymin)/double(knoy) + (zmax-zmin)/double(knoz));
    
    
    Darray(XN,knox+14);
    Darray(YN,knoy+14);
    Darray(ZN,knoz+14);
    
    Darray(XP,knox+14);
    Darray(YP,knoy+14);
    Darray(ZP,knoz+14);
    
    Darray(DX,knox+14);
    Darray(DY,knoy+14);
    Darray(DZ,knoz+14);
    
    Darray(DXP,knox+14);
    Darray(DYP,knoy+14);
    Darray(DZP,knoz+14);
    
    double ddx,ddy,ddz;
    
    ddx=ddy=ddz=dx;
    
    if(B2==1)
    {
    ddx = (xmax-xmin)/double(knox);
    ddy = (ymax-ymin)/double(knoy);
    ddz = (zmax-zmin)/double(knoz);
    }
    
    for(i=0;i<knox+1;++i)
    XN[IP] = double(i)*ddx;
    
    for(j=0;j<knoy+1;++j)
    YN[JP] = double(j)*ddy;
    
    for(k=0;k<knoz+1;++k)
    ZN[KP] = double(k)*ddz;
    
    cout<<".";
    
    
    if(B101>0 || B102>0 || B103>0)
    gridspacing_fsf();
    cout<<".";
    
    
    
    // margins
    i=0;
    XN[IM1] = XN[IP] - 1.0*(XN[IP1]-XN[IP]);
    XN[IM2] = XN[IP] - 2.0*(XN[IP1]-XN[IP]);
    XN[IM3] = XN[IP] - 3.0*(XN[IP1]-XN[IP]);
    XN[IM4] = XN[IP] - 4.0*(XN[IP1]-XN[IP]);
    XN[IM5] = XN[IP] - 5.0*(XN[IP1]-XN[IP]);
    
    j=0;
    YN[JM1] = YN[IP] - 1.0*(YN[JP1]-YN[JP]);
    YN[JM2] = YN[IP] - 2.0*(YN[JP1]-YN[JP]);
    YN[JM3] = YN[IP] - 3.0*(YN[JP1]-YN[JP]);
    YN[JM4] = YN[IP] - 4.0*(YN[JP1]-YN[JP]);
    YN[JM5] = YN[IP] - 5.0*(YN[JP1]-YN[JP]);
    
    k=0;
    ZN[KM1] = ZN[KP] - 1.0*(ZN[KP1]-ZN[KP]);
    ZN[KM2] = ZN[KP] - 2.0*(ZN[KP1]-ZN[KP]);
    ZN[KM3] = ZN[KP] - 3.0*(ZN[KP1]-ZN[KP]);
    ZN[KM4] = ZN[KP] - 4.0*(ZN[KP1]-ZN[KP]);
    ZN[KM5] = ZN[KP] - 5.0*(ZN[KP1]-ZN[KP]);
    
    i=knox;
    XN[IP1] = XN[IP] + 1.0*(XN[IP]-XN[IM1]);
    XN[IP2] = XN[IP] + 2.0*(XN[IP]-XN[IM1]);
    XN[IP3] = XN[IP] + 3.0*(XN[IP]-XN[IM1]);
    XN[IP4] = XN[IP] + 4.0*(XN[IP]-XN[IM1]);
    XN[IP5] = XN[IP] + 5.0*(XN[IP]-XN[IM1]);
    
    j=knoy;
    YN[JP1] = YN[JP] + 1.0*(YN[JP]-YN[JM1]);
    YN[JP2] = YN[JP] + 2.0*(YN[JP]-YN[JM1]);
    YN[JP3] = YN[JP] + 3.0*(YN[JP]-YN[JM1]);
    YN[JP4] = YN[JP] + 4.0*(YN[JP]-YN[JM1]);
    YN[JP5] = YN[JP] + 5.0*(YN[JP]-YN[JM1]);
    
    k=knoz;
    ZN[KP1] = ZN[KP] + 1.0*(ZN[KP]-ZN[KM1]);
    ZN[KP2] = ZN[KP] + 2.0*(ZN[KP]-ZN[KM1]);
    ZN[KP3] = ZN[KP] + 3.0*(ZN[KP]-ZN[KM1]);
    ZN[KP4] = ZN[KP] + 4.0*(ZN[KP]-ZN[KM1]);
    ZN[KP5] = ZN[KP] + 5.0*(ZN[KP]-ZN[KM1]);

    cout<<".";
    for(i=-marge;i<knox+marge;++i)
    XP[IP] = 0.5*(XN[IP]+XN[IP1]);
    
    for(j=-marge;j<knoy+marge;++j)
    YP[JP] = 0.5*(YN[JP]+YN[JP1]);
    
    for(k=-marge;k<knoz+marge;++k)
    ZP[KP] = 0.5*(ZN[KP]+ZN[KP1]);
    
    //dx
    for(i=-marge;i<knox+marge;++i)
    DX[IP] = XN[IP1]-XN[IP];
    
    for(j=-marge;j<knoy+marge;++j)
    DY[JP] = YN[JP1]-YN[JP];
    
    for(k=-marge;k<knoz+marge;++k)
    DZ[KP] = ZN[KP1]-ZN[KP];

    cout<<".";
    // dxP
    for(i=-marge;i<knox+marge-1;++i)
    DXP[IP] = 0.5*(XN[IP2]+XN[IP1]) - 0.5*(XN[IP1]+XN[IP]);
    
    for(j=-marge;j<knoy+marge-1;++j)
    DYP[JP] = 0.5*(YN[JP2]+YN[JP1]) - 0.5*(YN[JP1]+YN[JP]);
    
    for(k=-marge;k<knoz+marge-1;++k)
    DZP[KP] = 0.5*(ZN[KP2]+ZN[KP1]) - 0.5*(ZN[KP1]+ZN[KP]);
    
    
    if (B130 == 1)
    {
        gridspacing_print();
    }
    
    
    cout<<" finished"<<endl;
}