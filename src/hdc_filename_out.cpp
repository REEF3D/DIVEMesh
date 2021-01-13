/*--------------------------------------------------------------------
REEF3D
Copyright 2008-2021 Hans Bihs

This file is part of REEF3D.

REEF3D is free software; you can redistribute it and/or modify it
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

#include"hdc.h"
#include"lexer.h"

void hdc::filename_out(lexer *p, dive *a,int num, int rank)
{
    
	if(rank<9)
	{
		if(num<10)
		sprintf(name,"./REEF3D_WCP_Input/REEF3D-WCP-Input-0000000%d-0000%d.r3d",num,rank+1);

		if(num<100&&num>9)
		sprintf(name,"./REEF3D_WCP_Input/REEF3D-WCP-Input-000000%d-0000%d.r3d",num,rank+1);

		if(num<1000&&num>99)
		sprintf(name,"./REEF3D_WCP_Input/REEF3D-WCP-Input-00000%d-0000%d.r3d",num,rank+1);

		if(num<10000&&num>999)
		sprintf(name,"./REEF3D_WCP_Input/REEF3D-WCP-Input-0000%d-0000%d.r3d",num,rank+1);

		if(num<100000&&num>9999)
		sprintf(name,"./REEF3D_WCP_Input/REEF3D-WCP-Input-000%d-0000%d.r3d",num,rank+1);

		if(num<1000000&&num>99999)
		sprintf(name,"./REEF3D_WCP_Input/REEF3D-WCP-Input-00%d-0000%d.r3d",num,rank+1);
        
        if(num<10000000&&num>999999)
		sprintf(name,"./REEF3D_WCP_Input/REEF3D-WCP-Input-0%d-0000%d.r3d",num,rank+1);
        
        if(num>9999999)
		sprintf(name,"./REEF3D_WCP_Input/REEF3D-WCP-Input-%d-0000%d.r3d",num,rank+1);
	}

	if(rank<99&&rank>8)
	{
		if(num<10)
		sprintf(name,"./REEF3D_WCP_Input/REEF3D-WCP-Input-0000000%d-000%d.r3d",num,rank+1);

		if(num<100&&num>9)
		sprintf(name,"./REEF3D_WCP_Input/REEF3D-WCP-Input-000000%d-000%d.r3d",num,rank+1);

		if(num<1000&&num>99)
		sprintf(name,"./REEF3D_WCP_Input/REEF3D-WCP-Input-00000%d-000%d.r3d",num,rank+1);

		if(num<10000&&num>999)
		sprintf(name,"./REEF3D_WCP_Input/REEF3D-WCP-Input-0000%d-000%d.r3d",num,rank+1);

		if(num<100000&&num>9999)
		sprintf(name,"./REEF3D_WCP_Input/REEF3D-WCP-Input-000%d-000%d.r3d",num,rank+1);

		if(num<1000000&&num>99999)
		sprintf(name,"./REEF3D_WCP_Input/REEF3D-WCP-Input-00%d-000%d.r3d",num,rank+1);
        
        if(num<10000000&&num>999999)
		sprintf(name,"./REEF3D_WCP_Input/REEF3D-WCP-Input-0%d-000%d.r3d",num,rank+1);
        
        if(num>9999999)
		sprintf(name,"./REEF3D_WCP_Input/REEF3D-WCP-Input-%d-000%d.r3d",num,rank+1);
	}
	if(rank<999&&rank>98)
	{
		if(num<10)
		sprintf(name,"./REEF3D_WCP_Input/REEF3D-WCP-Input-0000000%d-00%d.r3d",num,rank+1);

		if(num<100&&num>9)
		sprintf(name,"./REEF3D_WCP_Input/REEF3D-WCP-Input-000000%d-00%d.r3d",num,rank+1);

		if(num<1000&&num>99)
		sprintf(name,"./REEF3D_WCP_Input/REEF3D-WCP-Input-00000%d-00%d.r3d",num,rank+1);

		if(num<10000&&num>999)
		sprintf(name,"./REEF3D_WCP_Input/REEF3D-WCP-Input-0000%d-00%d.r3d",num,rank+1);

		if(num<100000&&num>9999)
		sprintf(name,"./REEF3D_WCP_Input/REEF3D-WCP-Input-000%d-00%d.r3d",num,rank+1);

		if(num<1000000&&num>99999)
		sprintf(name,"./REEF3D_WCP_Input/REEF3D-WCP-Input-00%d-00%d.r3d",num,rank+1);
        
        if(num<10000000&&num>999999)
		sprintf(name,"./REEF3D_WCP_Input/REEF3D-WCP-Input-0%d-00%d.r3d",num,rank+1);
        
        if(num>9999999)
		sprintf(name,"./REEF3D_WCP_Input/REEF3D-WCP-Input-%d-00%d.r3d",num,rank+1);
	}

	if(rank<9999&&rank>998)
	{
		if(num<10)
		sprintf(name,"./REEF3D_WCP_Input/REEF3D-WCP-Input-0000000%d-0%d.r3d",num,rank+1);

		if(num<100&&num>9)
		sprintf(name,"./REEF3D_WCP_Input/REEF3D-WCP-Input-000000%d-0%d.r3d",num,rank+1);

		if(num<1000&&num>99)
		sprintf(name,"./REEF3D_WCP_Input/REEF3D-WCP-Input-00000%d-0%d.r3d",num,rank+1);

		if(num<10000&&num>999)
		sprintf(name,"./REEF3D_WCP_Input/REEF3D-WCP-Input-0000%d-0%d.r3d",num,rank+1);

		if(num<100000&&num>9999)
		sprintf(name,"./REEF3D_WCP_Input/REEF3D-WCP-Input-000%d-0%d.r3d",num,rank+1);

		if(num<1000000&&num>99999)
		sprintf(name,"./REEF3D_WCP_Input/REEF3D-WCP-Input-00%d-0%d.r3d",num,rank+1);
        
        if(num<10000000&&num>999999)
		sprintf(name,"./REEF3D_WCP_Input/REEF3D-WCP-Input-0%d-0%d.r3d",num,rank+1);
        
        if(num>9999999)
		sprintf(name,"./REEF3D_WCP_Input/REEF3D-WCP-Input-%d-0%d.r3d",num,rank+1);
	}

	if(rank>9998)
	{
		if(num<10)
		sprintf(name,"./REEF3D_WCP_Input/REEF3D-WCP-Input-0000000%d-%d.r3d",num,rank+1);

		if(num<100&&num>9)
		sprintf(name,"./REEF3D_WCP_Input/REEF3D-WCP-Input-000000%d-%d.r3d",num,rank+1);

		if(num<1000&&num>99)
		sprintf(name,"./REEF3D_WCP_Input/REEF3D-WCP-Input-00000%d-%d.r3d",num,rank+1);

		if(num<10000&&num>999)
		sprintf(name,"./REEF3D_WCP_Input/REEF3D-WCP-Input-0000%d-%d.r3d",num,rank+1);

		if(num<100000&&num>9999)
		sprintf(name,"./REEF3D_WCP_Input/REEF3D-WCP-Input-000%d-%d.r3d",num,rank+1);

		if(num<1000000&&num>99999)
		sprintf(name,"./REEF3D_WCP_Input/REEF3D-WCP-Input-00%d-%d.r3d",num,rank+1);
        
        if(num<10000000&&num>999999)
		sprintf(name,"./REEF3D_WCP_Input/REEF3D-WCP-Input-0%d-%d.r3d",num,rank+1);
        
        if(num>9999999)
		sprintf(name,"./REEF3D_WCP_Input/REEF3D-WCP-Input-%d-%d.r3d",num,rank+1);
	}
}

void hdc::filename_out_header(lexer *p, dive *a, int rank)
{
    
	if(rank<9)
	sprintf(name,"./REEF3D_WCP_Input/REEF3D-WCP-Input-Header-0000%d.r3d",rank+1);

	if(rank<99&&rank>8)
	sprintf(name,"./REEF3D_WCP_Input/REEF3D-WCP-Input-Header-000%d.r3d",rank+1);
    
	if(rank<999&&rank>98)
	sprintf(name,"./REEF3D_WCP_Input/REEF3D-WCP-Input-Header-00%d.r3d",rank+1);

	if(rank<9999&&rank>998)
	sprintf(name,"./REEF3D_WCP_Input/REEF3D-WCP-Input-Header-0%d.r3d",rank+1);

	if(rank>9998)
	sprintf(name,"./REEF3D_WCP_Input/REEF3D-WCP-Input-Header-%d.r3d",rank+1);
}