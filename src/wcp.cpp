/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2021 Hans Bihs

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
--------------------------------------------------------------------*/

#include"wcp.h"
#include"dive.h"
#include"lexer.h"
#include<sys/stat.h>
#include<sys/types.h>

wcp::wcp(lexer *p, dive *a) 
{
    // Create Folder
	mkdir("./REEF3D_WCP_Input",0777);
}

wcp::~wcp()
{
}

void wcp::start(lexer* p, dive* a)
{
    cout<<"WCP procedure "<<endl;

    read_mainheader(p,a);
    allocate(p,a);
    read_header(p,a);
    decomp(p,a);
    write_header(p,a);
    
    
    
    for(n=0; n<numiter; ++n)
    if(simtime[n]>=p->H31 && simtime[n]<p->H32)
    if(n>=p->H33 && n<p->H34)
    {
        read(p,a);
        write(p,a);
    
    cout<<"WCP I/O iter: "<<n<<"   simtime: "<<simtime[n]<<endl;
    }
    
    
    
}