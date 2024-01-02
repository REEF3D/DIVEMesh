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
#include"dive.h"
#include<iostream>
#include<sys/stat.h>
#include<sys/types.h>

void hdc::read_fnpf(lexer *p, dive *a)
{
    // result
    for(q=0; q<numprocs; ++q)
    if(flag_all[q]==1)
    {
        // Open Single File
        if(file_type==1)
        {
        filename_single_in(p,a,n,q); 
        result[q].open(name, ios::binary);
        }
    
    // header section
        result[q].read((char*)&iin, sizeof (int));
        result[q].read((char*)&iin, sizeof (int));
        result[q].read((char*)&iin, sizeof (int));

        result[q].read((char*)&ddn, sizeof (double)); 
        result[q].read((char*)&ddn, sizeof (double)); 
        result[q].read((char*)&ddn, sizeof (double)); 
        result[q].read((char*)&ddn, sizeof (double)); 
        result[q].read((char*)&ddn, sizeof (double)); 
        result[q].read((char*)&ddn, sizeof (double)); 
	
    // read eta and bed
    for(i=0;i<NLx[q];++i)
    for(j=0;j<NLy[q];++j)
    {
    result[q].read((char*)&ffn, sizeof (float)); 
    eta[i+orig_i[q]][j+orig_j[q]] = ffn;
    }
    
    for(i=0;i<NLx[q];++i)
    for(j=0;j<NLy[q];++j)
    {
    result[q].read((char*)&ffn, sizeof (float)); 
    Fifsf[i+orig_i[q]][j+orig_j[q]] = ffn;
    }
    
    for(i=0;i<NLx[q];++i)
    for(j=0;j<NLy[q];++j)
    for(k=0;k<NLz[q];++k)
    {
    result[q].read((char*)&ffn, sizeof (float)); 
    U[i+orig_i[q]][j+orig_j[q]][k+orig_k[q]] = ffn;
    }
    
    for(i=0;i<NLx[q];++i)
    for(j=0;j<NLy[q];++j)
    for(k=0;k<NLz[q];++k)
    {
    result[q].read((char*)&ffn, sizeof (float)); 
    V[i+orig_i[q]][j+orig_j[q]][k+orig_k[q]] = ffn;
    }
    
    for(i=0;i<NLx[q];++i)
    for(j=0;j<NLy[q];++j)
    for(k=0;k<NLz[q];++k)
    {
    result[q].read((char*)&ffn, sizeof (float)); 
    W[i+orig_i[q]][j+orig_j[q]][k+orig_k[q]] = ffn;
    }
    }
    
    if(file_type==1)
    for(q=0; q<numprocs; ++q)
    result[q].close();
}

