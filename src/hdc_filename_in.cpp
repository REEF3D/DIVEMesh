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

#include"hdc.h"
#include"lexer.h"

void hdc::filename_single_in(lexer *p, dive *a,int num, int rank)
{
    if(p->H10==2)
    filename_sflow_single_in(p,a,num,rank); 
    
    if(p->H10==4)
    filename_fnpf_single_in(p,a,num,rank);  
}

void hdc::filename_continuous_in(lexer *p, dive *a, int rank)
{
    if(p->H10==2)
    filename_sflow_continuous_in(p,a,rank); 
    
    if(p->H10==4)
    filename_fnpf_continuous_in(p,a,rank); 
}

void hdc::filename_in_header(lexer *p, dive *a,int rank)
{
    if(p->H10==2)
    filename_sflow_in_header(p,a,rank); 
    
    if(p->H10==4)
    filename_fnpf_in_header(p,a,rank);
}

void hdc::filename_sflow_single_in(lexer *p, dive *a,int num, int rank)
{
    
	if(rank<9)
	{
		if(num<10)
		sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D_SFLOW-State-0000000%i-0000%i.r3d",num,rank+1);

		if(num<100&&num>9)
		sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D_SFLOW-State-000000%i-0000%i.r3d",num,rank+1);

		if(num<1000&&num>99)
		sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D_SFLOW-State-00000%i-0000%i.r3d",num,rank+1);

		if(num<10000&&num>999)
		sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D_SFLOW-State-0000%i-0000%i.r3d",num,rank+1);

		if(num<100000&&num>9999)
		sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D_SFLOW-State-000%i-0000%i.r3d",num,rank+1);

		if(num<1000000&&num>99999)
		sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D_SFLOW-State-00%i-0000%i.r3d",num,rank+1);
        
        if(num<10000000&&num>999999)
		sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D_SFLOW-State-0%i-0000%i.r3d",num,rank+1);
        
        if(num>9999999)
		sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D_SFLOW-State-%i-0000%i.r3d",num,rank+1);
	}

	if(rank<99&&rank>8)
	{
		if(num<10)
		sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D_SFLOW-State-0000000%i-000%i.r3d",num,rank+1);

		if(num<100&&num>9)
		sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D_SFLOW-State-000000%i-000%i.r3d",num,rank+1);

		if(num<1000&&num>99)
		sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D_SFLOW-State-00000%i-000%i.r3d",num,rank+1);

		if(num<10000&&num>999)
		sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D_SFLOW-State-0000%i-000%i.r3d",num,rank+1);

		if(num<100000&&num>9999)
		sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D_SFLOW-State-000%i-000%i.r3d",num,rank+1);

		if(num<1000000&&num>99999)
		sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D_SFLOW-State-00%i-000%i.r3d",num,rank+1);
        
        if(num<10000000&&num>999999)
		sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D_SFLOW-State-0%i-000%i.r3d",num,rank+1);
        
        if(num>9999999)
		sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D_SFLOW-State-%i-000%i.r3d",num,rank+1);
	}
	if(rank<999&&rank>98)
	{
		if(num<10)
		sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D_SFLOW-State-0000000%i-00%i.r3d",num,rank+1);

		if(num<100&&num>9)
		sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D_SFLOW-State-000000%i-00%i.r3d",num,rank+1);

		if(num<1000&&num>99)
		sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D_SFLOW-State-00000%i-00%i.r3d",num,rank+1);

		if(num<10000&&num>999)
		sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D_SFLOW-State-0000%i-00%i.r3d",num,rank+1);

		if(num<100000&&num>9999)
		sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D_SFLOW-State-000%i-00%i.r3d",num,rank+1);

		if(num<1000000&&num>99999)
		sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D_SFLOW-State-00%i-00%i.r3d",num,rank+1);
        
        if(num<10000000&&num>999999)
		sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D_SFLOW-State-0%i-00%i.r3d",num,rank+1);
        
        if(num>9999999)
		sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D_SFLOW-State-%i-00%i.r3d",num,rank+1);
	}

	if(rank<9999&&rank>998)
	{
		if(num<10)
		sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D_SFLOW-State-0000000%i-0%i.r3d",num,rank+1);

		if(num<100&&num>9)
		sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D_SFLOW-State-000000%i-0%i.r3d",num,rank+1);

		if(num<1000&&num>99)
		sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D_SFLOW-State-00000%i-0%i.r3d",num,rank+1);

		if(num<10000&&num>999)
		sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D_SFLOW-State-0000%i-0%i.r3d",num,rank+1);

		if(num<100000&&num>9999)
		sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D_SFLOW-State-000%i-0%i.r3d",num,rank+1);

		if(num<1000000&&num>99999)
		sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D_SFLOW-State-00%i-0%i.r3d",num,rank+1);
        
        if(num<10000000&&num>999999)
		sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D_SFLOW-State-0%i-0%i.r3d",num,rank+1);
        
        if(num>9999999)
		sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D_SFLOW-State-%i-0%i.r3d",num,rank+1);
	}

	if(rank>9998)
	{
		if(num<10)
		sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D_SFLOW-State-0000000%i-%i.r3d",num,rank+1);

		if(num<100&&num>9)
		sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D_SFLOW-State-000000%i-%i.r3d",num,rank+1);

		if(num<1000&&num>99)
		sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D_SFLOW-State-00000%i-%i.r3d",num,rank+1);

		if(num<10000&&num>999)
		sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D_SFLOW-State-0000%i-%i.r3d",num,rank+1);

		if(num<100000&&num>9999)
		sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D_SFLOW-State-000%i-%i.r3d",num,rank+1);

		if(num<1000000&&num>99999)
		sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D_SFLOW-State-00%i-%i.r3d",num,rank+1);
        
        if(num<10000000&&num>999999)
		sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D_SFLOW-State-0%i-%i.r3d",num,rank+1);
        
        if(num>9999999)
		sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D_SFLOW-State-%i-%i.r3d",num,rank+1);
	}
}

void hdc::filename_sflow_continuous_in(lexer *p, dive *a, int rank)
{
	if(rank<9)
    sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D_SFLOW-State-0000%i.r3d",rank+1);

	if(rank<99&&rank>8)
    sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D_SFLOW-State-000%i.r3d",rank+1);
    
	if(rank<999&&rank>98)
    sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D_SFLOW-State-00%i.r3d",rank+1);

	if(rank<9999&&rank>998)
    sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D_SFLOW-State-%i.r3d",rank+1);

	if(rank>9998)
    sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D_SFLOW-State-%i.r3d",rank+1);
}

void hdc::filename_sflow_in_header(lexer *p, dive *a,int rank)
{
    if(rank<9)
	sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D-SFLOW-State-Header-0000%i.r3d",rank+1);

	if(rank<99&&rank>8)
	sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D-SFLOW-State-Header-000%i.r3d",rank+1);
    
	if(rank<999&&rank>98)
	sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D-SFLOW-State-Header-00%i.r3d",rank+1);

	if(rank<9999&&rank>998)
	sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D-SFLOW-State-Header-0%i.r3d",rank+1);

	if(rank>9998)
	sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D-SFLOW-State-Header-%i.r3d",rank+1);
}

// -----------------------------------------

void hdc::filename_fnpf_single_in(lexer *p, dive *a,int num, int rank)
{
    
	if(rank<9)
	{
		if(num<10)
		sprintf(name,"./REEF3D_FNPF_STATE/REEF3D_FNPF-State-0000000%i-0000%i.r3d",num,rank+1);

		if(num<100&&num>9)
		sprintf(name,"./REEF3D_FNPF_STATE/REEF3D_FNPF-State-000000%i-0000%i.r3d",num,rank+1);

		if(num<1000&&num>99)
		sprintf(name,"./REEF3D_FNPF_STATE/REEF3D_FNPF-State-00000%i-0000%i.r3d",num,rank+1);

		if(num<10000&&num>999)
		sprintf(name,"./REEF3D_FNPF_STATE/REEF3D_FNPF-State-0000%i-0000%i.r3d",num,rank+1);

		if(num<100000&&num>9999)
		sprintf(name,"./REEF3D_FNPF_STATE/REEF3D_FNPF-State-000%i-0000%i.r3d",num,rank+1);

		if(num<1000000&&num>99999)
		sprintf(name,"./REEF3D_FNPF_STATE/REEF3D_FNPF-State-00%i-0000%i.r3d",num,rank+1);
        
        if(num<10000000&&num>999999)
		sprintf(name,"./REEF3D_FNPF_STATE/REEF3D_FNPF-State-0%i-0000%i.r3d",num,rank+1);
        
        if(num>9999999)
		sprintf(name,"./REEF3D_FNPF_STATE/REEF3D_FNPF-State-%i-0000%i.r3d",num,rank+1);
	}

	if(rank<99&&rank>8)
	{
		if(num<10)
		sprintf(name,"./REEF3D_FNPF_STATE/REEF3D_FNPF-State-0000000%i-000%i.r3d",num,rank+1);

		if(num<100&&num>9)
		sprintf(name,"./REEF3D_FNPF_STATE/REEF3D_FNPF-State-000000%i-000%i.r3d",num,rank+1);

		if(num<1000&&num>99)
		sprintf(name,"./REEF3D_FNPF_STATE/REEF3D_FNPF-State-00000%i-000%i.r3d",num,rank+1);

		if(num<10000&&num>999)
		sprintf(name,"./REEF3D_FNPF_STATE/REEF3D_FNPF-State-0000%i-000%i.r3d",num,rank+1);

		if(num<100000&&num>9999)
		sprintf(name,"./REEF3D_FNPF_STATE/REEF3D_FNPF-State-000%i-000%i.r3d",num,rank+1);

		if(num<1000000&&num>99999)
		sprintf(name,"./REEF3D_FNPF_STATE/REEF3D_FNPF-State-00%i-000%i.r3d",num,rank+1);
        
        if(num<10000000&&num>999999)
		sprintf(name,"./REEF3D_FNPF_STATE/REEF3D_FNPF-State-0%i-000%i.r3d",num,rank+1);
        
        if(num>9999999)
		sprintf(name,"./REEF3D_FNPF_STATE/REEF3D_FNPF-State-%i-000%i.r3d",num,rank+1);
	}
	if(rank<999&&rank>98)
	{
		if(num<10)
		sprintf(name,"./REEF3D_FNPF_STATE/REEF3D_FNPF-State-0000000%i-00%i.r3d",num,rank+1);

		if(num<100&&num>9)
		sprintf(name,"./REEF3D_FNPF_STATE/REEF3D_FNPF-State-000000%i-00%i.r3d",num,rank+1);

		if(num<1000&&num>99)
		sprintf(name,"./REEF3D_FNPF_STATE/REEF3D_FNPF-State-00000%i-00%i.r3d",num,rank+1);

		if(num<10000&&num>999)
		sprintf(name,"./REEF3D_FNPF_STATE/REEF3D_FNPF-State-0000%i-00%i.r3d",num,rank+1);

		if(num<100000&&num>9999)
		sprintf(name,"./REEF3D_FNPF_STATE/REEF3D_FNPF-State-000%i-00%i.r3d",num,rank+1);

		if(num<1000000&&num>99999)
		sprintf(name,"./REEF3D_FNPF_STATE/REEF3D_FNPF-State-00%i-00%i.r3d",num,rank+1);
        
        if(num<10000000&&num>999999)
		sprintf(name,"./REEF3D_FNPF_STATE/REEF3D_FNPF-State-0%i-00%i.r3d",num,rank+1);
        
        if(num>9999999)
		sprintf(name,"./REEF3D_FNPF_STATE/REEF3D_FNPF-State-%i-00%i.r3d",num,rank+1);
	}

	if(rank<9999&&rank>998)
	{
		if(num<10)
		sprintf(name,"./REEF3D_FNPF_STATE/REEF3D_FNPF-State-0000000%i-0%i.r3d",num,rank+1);

		if(num<100&&num>9)
		sprintf(name,"./REEF3D_FNPF_STATE/REEF3D_FNPF-State-000000%i-0%i.r3d",num,rank+1);

		if(num<1000&&num>99)
		sprintf(name,"./REEF3D_FNPF_STATE/REEF3D_FNPF-State-00000%i-0%i.r3d",num,rank+1);

		if(num<10000&&num>999)
		sprintf(name,"./REEF3D_FNPF_STATE/REEF3D_FNPF-State-0000%i-0%i.r3d",num,rank+1);

		if(num<100000&&num>9999)
		sprintf(name,"./REEF3D_FNPF_STATE/REEF3D_FNPF-State-000%i-0%i.r3d",num,rank+1);

		if(num<1000000&&num>99999)
		sprintf(name,"./REEF3D_FNPF_STATE/REEF3D_FNPF-State-00%i-0%i.r3d",num,rank+1);
        
        if(num<10000000&&num>999999)
		sprintf(name,"./REEF3D_FNPF_STATE/REEF3D_FNPF-State-0%i-0%i.r3d",num,rank+1);
        
        if(num>9999999)
		sprintf(name,"./REEF3D_FNPF_STATE/REEF3D_FNPF-State-%i-0%i.r3d",num,rank+1);
	}

	if(rank>9998)
	{
		if(num<10)
		sprintf(name,"./REEF3D_FNPF_STATE/REEF3D_FNPF-State-0000000%i-%i.r3d",num,rank+1);

		if(num<100&&num>9)
		sprintf(name,"./REEF3D_FNPF_STATE/REEF3D_FNPF-State-000000%i-%i.r3d",num,rank+1);

		if(num<1000&&num>99)
		sprintf(name,"./REEF3D_FNPF_STATE/REEF3D_FNPF-State-00000%i-%i.r3d",num,rank+1);

		if(num<10000&&num>999)
		sprintf(name,"./REEF3D_FNPF_STATE/REEF3D_FNPF-State-0000%i-%i.r3d",num,rank+1);

		if(num<100000&&num>9999)
		sprintf(name,"./REEF3D_FNPF_STATE/REEF3D_FNPF-State-000%i-%i.r3d",num,rank+1);

		if(num<1000000&&num>99999)
		sprintf(name,"./REEF3D_FNPF_STATE/REEF3D_FNPF-State-00%i-%i.r3d",num,rank+1);
        
        if(num<10000000&&num>999999)
		sprintf(name,"./REEF3D_FNPF_STATE/REEF3D_FNPF-State-0%i-%i.r3d",num,rank+1);
        
        if(num>9999999)
		sprintf(name,"./REEF3D_FNPF_STATE/REEF3D_FNPF-State-%i-%i.r3d",num,rank+1);
	}
}

void hdc::filename_fnpf_continuous_in(lexer *p, dive *a, int rank)
{
	if(rank<9)
    sprintf(name,"./REEF3D_FNPF_STATE/REEF3D_FNPF-State-0000%i.r3d",rank+1);

	if(rank<99&&rank>8)
    sprintf(name,"./REEF3D_FNPF_STATE/REEF3D_FNPF-State-000%i.r3d",rank+1);
    
	if(rank<999&&rank>98)
    sprintf(name,"./REEF3D_FNPF_STATE/REEF3D_FNPF-State-00%i.r3d",rank+1);

	if(rank<9999&&rank>998)
    sprintf(name,"./REEF3D_FNPF_STATE/REEF3D_FNPF-State-%i.r3d",rank+1);

	if(rank>9998)
    sprintf(name,"./REEF3D_FNPF_STATE/REEF3D_FNPF-State-%i.r3d",rank+1);
}

void hdc::filename_fnpf_in_header(lexer *p, dive *a,int rank)
{
    if(rank<9)
	sprintf(name,"./REEF3D_FNPF_STATE/REEF3D-FNPF-State-Header-0000%i.r3d",rank+1);

	if(rank<99&&rank>8)
	sprintf(name,"./REEF3D_FNPF_STATE/REEF3D-FNPF-State-Header-000%i.r3d",rank+1);
    
	if(rank<999&&rank>98)
	sprintf(name,"./REEF3D_FNPF_STATE/REEF3D-FNPF-State-Header-00%i.r3d",rank+1);

	if(rank<9999&&rank>998)
	sprintf(name,"./REEF3D_FNPF_STATE/REEF3D-FNPF-State-Header-0%i.r3d",rank+1);

	if(rank>9998)
	sprintf(name,"./REEF3D_FNPF_STATE/REEF3D-FNPF-State-Header-%i.r3d",rank+1);
}