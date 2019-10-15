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

void wcp::read_header(lexer *p, dive *a)
{
    ifstream header;

    // read header
    header.open(name, ios::binary);
    

    
    // read header section
    
    // orig_ijk
    header.read((char*)&iin, sizeof (int));
	orig_i=iin;
    
    header.read((char*)&iin, sizeof (int));
	orig_j=iin;
    
    header.read((char*)&iin, sizeof (int));
	orig_k=iin;
    
    // orig_xyz
    header.read((char*)&ffn, sizeof (float)); 
    orig_x = ffn;
    
    header.read((char*)&ffn, sizeof (float)); 
    orig_y = ffn;
    
    header.read((char*)&ffn, sizeof (float)); 
    orig_z = ffn;
    

    
    
    // NLx,NLy,NLz
    header.read((char*)&iin, sizeof (int));
	NLx=iin;
    
    header.read((char*)&iin, sizeof (int));
	NLy=iin;
    
    header.read((char*)&iin, sizeof (int));
	NLz=iin;
    
    
    // nbx
    header.read((char*)&iin, sizeof (int));
	nb1=iin;
    
    header.read((char*)&iin, sizeof (int));
	nb2=iin;

    header.read((char*)&iin, sizeof (int));
	nb3=iin;
    
    header.read((char*)&iin, sizeof (int));
	nb4=iin;
    
    
      // read coordinates
    for(i=0;i<NLx;++i)
    {
    header.read((char*)&ffn, sizeof (float)); 
    X[i+orig_i] = ffn;
    }
    
    for(j=0;j<NLy;++j)
    {
    header.read((char*)&ffn, sizeof (float)); 
    Y[j+orig_j] = ffn;
    }
    
    for(k=0;k<NLz;++k)
    {
    header.read((char*)&ffn, sizeof (float)); 
    Z[k+orig_k] = ffn;
    }
    
    
    for(i=0;i<NLx;++i)
    for(j=0;j<NLy;++j)
    {
    header.read((char*)&ffn, sizeof (float)); 
    bed[i+orig_i][j+orig_j] = ffn;
    }
    
    
    header.close();

}
