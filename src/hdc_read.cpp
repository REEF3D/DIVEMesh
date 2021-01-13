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
#include"dive.h"
#include<iostream>
#include<fstream>
#include<sys/stat.h>
#include<sys/types.h>

void hdc::read(lexer *p, dive *a)
{
    ifstream result;
    

    // result
    for(q=0; q<numprocs; ++q)
    {
    // Open File
	filename_in(p,a,n,q); 
	
	result.open(name, ios::binary);
	
    
    // read eta and bed
    for(i=0;i<NLx[q];++i)
    for(j=0;j<NLy[q];++j)
    {
    result.read((char*)&ffn, sizeof (float)); 
    eta[i+orig_i[q]][j+orig_j[q]] = ffn;
    }
    
    for(i=0;i<NLx[q];++i)
    for(j=0;j<NLy[q];++j)
    for(k=0;k<NLz[q];++k)
    {
    result.read((char*)&ffn, sizeof (float)); 
    U[i+orig_i[q]][j+orig_j[q]][k+orig_k[q]] = ffn;
    }
    
    for(i=0;i<NLx[q];++i)
    for(j=0;j<NLy[q];++j)
    for(k=0;k<NLz[q];++k)
    {
    result.read((char*)&ffn, sizeof (float)); 
    V[i+orig_i[q]][j+orig_j[q]][k+orig_k[q]] = ffn;
    }
    
    for(i=0;i<NLx[q];++i)
    for(j=0;j<NLy[q];++j)
    for(k=0;k<NLz[q];++k)
    {
    result.read((char*)&ffn, sizeof (float)); 
    W[i+orig_i[q]][j+orig_j[q]][k+orig_k[q]] = ffn;
    }
    
    
    result.close();
    }
}

