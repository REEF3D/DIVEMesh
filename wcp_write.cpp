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
    // write header
    for(q=0; q<p->M10; ++q)
    {
        ofstream header;
        
        filename_header(p,a,q);
        header.open(name, ios::binary);
        
        iin=numiter;
        header.write((char*)&iin, sizeof (int));
        
        for(n=0;n<numiter;++n)
        {
        ddn=simtime[n];
        header.write((char*)&ddn, sizeof (double));
        }
        
    header.close();
    }
    
    // write result
    for(n=0; n<numiter; ++n)
    for(q=0; q<p->M10; ++q)
    {
        
    }
}




