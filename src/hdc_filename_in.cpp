/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2024 Hans Bihs

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
    
    if(p->H10==5)
    filename_nhflow_single_in(p,a,num,rank);  
}

void hdc::filename_continuous_in(lexer *p, dive *a, int rank)
{
    if(p->H10==2)
    filename_sflow_continuous_in(p,a,rank); 
    
    if(p->H10==4)
    filename_fnpf_continuous_in(p,a,rank);

    if(p->H10==5)
    filename_nhflow_continuous_in(p,a,rank); 
}

void hdc::filename_in_header(lexer *p, dive *a,int rank)
{
    if(p->H10==2)
    filename_sflow_in_header(p,a,rank); 
    
    if(p->H10==4)
    filename_fnpf_in_header(p,a,rank);
    
    if(p->H10==5)
    filename_nhflow_in_header(p,a,rank);
}

// -----------------------------------------

void hdc::filename_sflow_single_in(lexer *p, dive *a,int num, int rank)
{
	sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D_SFLOW-State-%08i-%06i.r3d",num,rank+1);
}

void hdc::filename_sflow_continuous_in(lexer *p, dive *a, int rank)
{
	sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D_SFLOW-State-%06i.r3d",rank+1);
}

void hdc::filename_sflow_in_header(lexer *p, dive *a,int rank)
{
    sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D-SFLOW-State-Header-%06i.r3d",rank+1);
}

// -----------------------------------------

void hdc::filename_fnpf_single_in(lexer *p, dive *a,int num, int rank)
{
	sprintf(name,"./REEF3D_FNPF_STATE/REEF3D_FNPF-State-%08i-%06i.r3d",num,rank+1);
}

void hdc::filename_fnpf_continuous_in(lexer *p, dive *a, int rank)
{
	sprintf(name,"./REEF3D_FNPF_STATE/REEF3D_FNPF-State-%06i.r3d",rank+1);
}

void hdc::filename_fnpf_in_header(lexer *p, dive *a,int rank)
{
    sprintf(name,"./REEF3D_FNPF_STATE/REEF3D-FNPF-State-Header-%06i.r3d",rank+1);
}

// -----------------------------------------

void hdc::filename_nhflow_single_in(lexer *p, dive *a,int num, int rank)
{
	sprintf(name,"./REEF3D_NHFLOW_STATE/REEF3D_NHFLOW-State-%08i-%06i.r3d",num,rank+1);
}

void hdc::filename_nhflow_continuous_in(lexer *p, dive *a, int rank)
{
	sprintf(name,"./REEF3D_NHFLOW_STATE/REEF3D_NHFLOW-State-%06i.r3d",rank+1);
}

void hdc::filename_nhflow_in_header(lexer *p, dive *a,int rank)
{
    sprintf(name,"./REEF3D_NHFLOW_STATE/REEF3D-NHFLOW-State-Header-%06i.r3d",rank+1);
}