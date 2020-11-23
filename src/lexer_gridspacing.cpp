/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2020 Hans Bihs

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
    DXM = DXYM = DR=DS=DT = dx;
    
    if(knoy==1)
    {
    if(B2==1)
    DXM=dx = (1./2.0) * ((xmax-xmin)/double(knox)+ (zmax-zmin)/double(knoz));
    
    if(B2==1)
    DXYM = (xmax-xmin)/double(knox);
    }
    
    if(knoy>1)
    {
    if(B2==1)
    DXM=dx = (1./3.0) * ((xmax-xmin)/double(knox) + (ymax-ymin)/double(knoy) + (zmax-zmin)/double(knoz));
    
    if(B2==1)
    DXYM = (1./2.0) * ((xmax-xmin)/double(knox) + (ymax-ymin)/double(knoy));
    }
    
    
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
    
    Darray(RN,knox+14);
    Darray(SN,knoy+14);
    Darray(TN,knoz+14);
    
    Darray(RP,knox+14);
    Darray(SP,knoy+14);
    Darray(TP,knoz+14);
    
    double ddx,ddy,ddz;
    
    ddx=ddy=ddz=dx;
    

    ddx = DR = (xmax-xmin)/double(knox);
    ddy = DS = (ymax-ymin)/double(knoy);
    ddz = DT = (zmax-zmin)/double(knoz);
    
    cout<<"DR: "<<DR<<" DS: "<<DS<<" DT: "<<DT<<endl;

    
    for(i=0;i<knox+1;++i)
    XN[IP] = RN[IP] = double(i)*ddx + xmin;
    
    for(j=0;j<knoy+1;++j)
    YN[JP] = SN[JP] = double(j)*ddy + ymin;
    
    for(k=0;k<knoz+1;++k)
    ZN[KP] = TN[KP] = double(k)*ddz + zmin;
    
    cout<<".";
    
    // GRIDSPACING_FSF
    if(B101>0 || B102>0 || B103>0)
    gridspacing_fsf();
    cout<<".";
    
    
    
    // margins XYZ
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
    
    // margins RST
    i=0;
    RN[IM1] = RN[IP] - 1.0*(RN[IP1]-RN[IP]);
    RN[IM2] = RN[IP] - 2.0*(RN[IP1]-RN[IP]);
    RN[IM3] = RN[IP] - 3.0*(RN[IP1]-RN[IP]);
    RN[IM4] = RN[IP] - 4.0*(RN[IP1]-RN[IP]);
    RN[IM5] = RN[IP] - 5.0*(RN[IP1]-RN[IP]);
    
    j=0;
    SN[JM1] = SN[IP] - 1.0*(SN[JP1]-SN[JP]);
    SN[JM2] = SN[IP] - 2.0*(SN[JP1]-SN[JP]);
    SN[JM3] = SN[IP] - 3.0*(SN[JP1]-SN[JP]);
    SN[JM4] = SN[IP] - 4.0*(SN[JP1]-SN[JP]);
    SN[JM5] = SN[IP] - 5.0*(SN[JP1]-SN[JP]);
    
    k=0;
    TN[KM1] = TN[KP] - 1.0*(TN[KP1]-TN[KP]);
    TN[KM2] = TN[KP] - 2.0*(TN[KP1]-TN[KP]);
    TN[KM3] = TN[KP] - 3.0*(TN[KP1]-TN[KP]);
    TN[KM4] = TN[KP] - 4.0*(TN[KP1]-TN[KP]);
    TN[KM5] = TN[KP] - 5.0*(TN[KP1]-TN[KP]);
    
    i=knox;
    RN[IP1] = RN[IP] + 1.0*(RN[IP]-RN[IM1]);
    RN[IP2] = RN[IP] + 2.0*(RN[IP]-RN[IM1]);
    RN[IP3] = RN[IP] + 3.0*(RN[IP]-RN[IM1]);
    RN[IP4] = RN[IP] + 4.0*(RN[IP]-RN[IM1]);
    RN[IP5] = RN[IP] + 5.0*(RN[IP]-RN[IM1]);
    
    j=knoy;
    SN[JP1] = SN[JP] + 1.0*(SN[JP]-SN[JM1]);
    SN[JP2] = SN[JP] + 2.0*(SN[JP]-SN[JM1]);
    SN[JP3] = SN[JP] + 3.0*(SN[JP]-SN[JM1]);
    SN[JP4] = SN[JP] + 4.0*(SN[JP]-SN[JM1]);
    SN[JP5] = SN[JP] + 5.0*(SN[JP]-SN[JM1]);
    
    k=knoz;
    TN[KP1] = TN[KP] + 1.0*(TN[KP]-TN[KM1]);
    TN[KP2] = TN[KP] + 2.0*(TN[KP]-TN[KM1]);
    TN[KP3] = TN[KP] + 3.0*(TN[KP]-TN[KM1]);
    TN[KP4] = TN[KP] + 4.0*(TN[KP]-TN[KM1]);
    TN[KP5] = TN[KP] + 5.0*(TN[KP]-TN[KM1]);

    cout<<".";
    
    // XYZ
    for(i=-marge;i<knox+marge;++i)
    XP[IP] = 0.5*(XN[IP]+XN[IP1]);
    
    for(j=-marge;j<knoy+marge;++j)
    YP[JP] = 0.5*(YN[JP]+YN[JP1]);
    
    for(k=-marge;k<knoz+marge;++k)
    ZP[KP] = 0.5*(ZN[KP]+ZN[KP1]);
    
    // RST
    for(i=-marge;i<knox+marge;++i)
    RP[IP] = 0.5*(RN[IP]+RN[IP1]);
    
    for(j=-marge;j<knoy+marge;++j)
    SP[JP] = 0.5*(SN[JP]+SN[JP1]);
    
    for(k=-marge;k<knoz+marge;++k)
    TP[KP] = 0.5*(TN[KP]+TN[KP1]);
    
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