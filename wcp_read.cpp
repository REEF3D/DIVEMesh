/*--------------------------------------------------------------------
REEF3D
Copyright 2008-2019 Hans Bihs

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

#include"wcp.h"
#include"lexer.h"
#include"dive.h"
#include<iostream>
#include<fstream>
#include<sys/stat.h>
#include<sys/types.h>

void wcp::read(lexer *p, dive *a)
{
    ifstream result;
    
    
    // allocate arrays
    p->Darray(X,NGx);
    p->Darray(Y,NGy);
    p->Darray(Z,NGz);
    p->Darray(eta,NGx,NGy);
    p->Darray(bed,NGx,NGy);
    p->Darray(U,NGx,NGy,NGz);
    p->Darray(V,NGx,NGy,NGz);
    p->Darray(W,NGx,NGy,NGz);
    
    // result
    for(n=0; n<numiter; ++n)
    for(q=0; q<numprocs; ++q)
    {
    // Open File
	filename_in(p,a,n,q); 
	
	result.open(name, ios::binary);
	
    
    // read eta and bed
    for(i=0;i<NLx[q];++i)
    for(j=0;j<NLy[q];++j)
    {
    result.read((char*)&ddn, sizeof (double)); 
    eta[i+orig_i[q]][j+orig_j[q]] = ddn;
    }
    
    for(i=0;i<NLx[q];++i)
    for(j=0;j<NLy[q];++j)
    for(k=0;k<NLz[q];++k)
    {
    result.read((char*)&ddn, sizeof (double)); 
    U[i+orig_i[q]][j+orig_j[q]][k+orig_k[q]] = ddn;
    }
    
    for(i=0;i<NLx[q];++i)
    for(j=0;j<NLy[q];++j)
    for(k=0;k<NLz[q];++k)
    {
    result.read((char*)&ddn, sizeof (double)); 
    V[i+orig_i[q]][j+orig_j[q]][k+orig_k[q]] = ddn;
    }
    
    for(i=0;i<NLx[q];++i)
    for(j=0;j<NLy[q];++j)
    for(k=0;k<NLz[q];++k)
    {
    result.read((char*)&ddn, sizeof (double)); 
    W[i+orig_i[q]][j+orig_j[q]][k+orig_k[q]] = ddn;
    }
    
    
    result.close();
    }
}

