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
    
    // header
    read_header(p,a);
    
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
	
    // read header section
    // orig_xyz
    result.read((char*)&ddn, sizeof (double)); 
    orig_x = ddn;
    
    result.read((char*)&ddn, sizeof (double)); 
    orig_y = ddn;
    
    result.read((char*)&ddn, sizeof (double)); 
    orig_z = ddn;
    
    // orig_ijk
    result.read((char*)&iin, sizeof (int));
	orig_i=iin;
    
    result.read((char*)&iin, sizeof (int));
	orig_j=iin;
    
    result.read((char*)&iin, sizeof (int));
	orig_k=iin;
    
    // NLx,NLy,NLz
    result.read((char*)&iin, sizeof (int));
	NLx=iin;
    
    result.read((char*)&iin, sizeof (int));
	NLy=iin;
    
    result.read((char*)&iin, sizeof (int));
	NLz=iin;
    
    // read coordinates
    for(i=0;i<NLx;++i)
    {
    result.read((char*)&ddn, sizeof (double)); 
    X[i+orig_i] = ddn;
    }
    
    for(j=0;j<NLy;++j)
    {
    result.read((char*)&ddn, sizeof (double)); 
    Y[j+orig_j] = ddn;
    }
    
    for(k=0;k<NLz;++k)
    {
    result.read((char*)&ddn, sizeof (double)); 
    Z[k+orig_k] = ddn;
    }
    
    // read eta and bed
    for(i=0;i<NLx;++i)
    for(j=0;j<NLy;++j)
    {
    result.read((char*)&ddn, sizeof (double)); 
    eta[i+orig_i][j+orig_j] = ddn;
    }
    
    for(i=0;i<NLx;++i)
    for(j=0;j<NLy;++j)
    {
    result.read((char*)&ddn, sizeof (double)); 
    bed[i+orig_i][j+orig_j] = ddn;
    }
    
    for(i=0;i<NLx;++i)
    for(j=0;j<NLy;++j)
    for(k=0;k<NLz;++k)
    {
    result.read((char*)&ddn, sizeof (double)); 
    U[i+orig_i][j+orig_j][k+orig_k] = ddn;
    }
    
    for(i=0;i<NLx;++i)
    for(j=0;j<NLy;++j)
    for(k=0;k<NLz;++k)
    {
    result.read((char*)&ddn, sizeof (double)); 
    V[i+orig_i][j+orig_j][k+orig_k] = ddn;
    }
    
    for(i=0;i<NLx;++i)
    for(j=0;j<NLy;++j)
    for(k=0;k<NLz;++k)
    {
    result.read((char*)&ddn, sizeof (double)); 
    W[i+orig_i][j+orig_j][k+orig_k] = ddn;
    }
    
    
    result.close();
    }
}



void wcp::read_header(lexer *p, dive *a)
{
    ifstream header;
	header.open(name, ios::binary);
    
    // count numiter
    header.read((char*)&iin, sizeof (int));
    header.read((char*)&iin, sizeof (int));
    header.read((char*)&iin, sizeof (int));
    header.read((char*)&iin, sizeof (int));
    
    numiter=0;
    while(!header.eof())
	{
    header.read((char*)&iin, sizeof (int));
 
    header.read((char*)&ddn, sizeof (double));    
    ++numiter;
    }
    
    header.close();
    
    p->Darray(simtime,numiter);
    
    
    // read header
    header.open(name, ios::binary);
    
    header.read((char*)&iin, sizeof (int));
	numprocs=iin;
    
    header.read((char*)&iin, sizeof (int));
	NGx=iin;
    
    header.read((char*)&iin, sizeof (int));
	NGy=iin;
    
    header.read((char*)&iin, sizeof (int));
	NGz=iin;
    
    count=0;
    while(!header.eof())
	{
    header.read((char*)&iin, sizeof (int));
 
    header.read((char*)&ddn, sizeof (double)); 
    simtime[count] = ddn;
    ++count;
    }
}
