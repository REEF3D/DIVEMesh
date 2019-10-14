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

void wcp::write(lexer *p, dive *a)
{
    ofstream header;
    ofstream wfile;
    
    // write header
    for(q=0; q<p->M10; ++q)
    {
        
        
        filename_header(p,a,q);
        header.open(name, ios::binary);
        
        // numer of iterations
        iin=numiter;
        header.write((char*)&iin, sizeof (int));
        
        
        // origin_xyz
        
        // Nx,Ny,Nz
        
        for(n=0;n<numiter;++n)
        {
        ddn=simtime[n];
        header.write((char*)&ddn, sizeof (double));
        }
        
    header.close();
    }
    
    count=0;
    // write result
    for(n=0; n<numiter; ++n)
    NLOOP
    {
        ++count;
        // filename
        // file open
        
        
        
        filename_out(p,a,n,count);
        wfile.open(name, ios::binary);
        
        //ijk loop
        // ->write
        for(i=is[aa]; i<ie[aa]; ++i)
        {
        ffn=float(X[i]);
        wfile.write((char*)&ffn, sizeof (float));
        }
            
        for(j=js[bb]; j=je[bb]; ++j)
        {
        ffn=float(X[i]);
        wfile.write((char*)&ffn, sizeof (float));
        }
        
        for(k=0; k<NGz; ++k)
            
            
        for(i=is[aa]; i<ie[aa]; ++i)
        for(j=js[bb]; j=je[bb]; ++j)
        for(k=0; k<NGz; ++k)
        {
        
            
            
            
            
            
            
        }
        
        
        // file close
    }
}




