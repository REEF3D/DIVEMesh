/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2023 Hans Bihs

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
#include<fstream>
#include<sys/stat.h>
#include<sys/types.h>

void hdc::write_sflow(lexer *p, dive *a)
{    
    // write result
    count=0;
    for(aa=0;aa<a->mx;++aa)
    for(bb=0;bb<a->my;++bb)
    {   
        // Open single file
        if(file_type==1)
        {
        filename_single_out(p,a,n,count);
        wfile[count].open(name, ios::binary);
        }
        
        // write iter
        iin = n;
        wfile[count].write((char*)&iin, sizeof (iin));
        
        //ijk loop
        // ->write
        for(i=is[aa]; i<ie[aa]; ++i)
        for(j=js[bb]; j<je[bb]; ++j)
        {
        ffn=eta[i][j];
        wfile[count].write((char*)&ffn, sizeof (float));
        }
        
        for(i=is[aa]; i<ie[aa]; ++i)
        for(j=js[bb]; j<je[bb]; ++j)
        {
        ffn=U[i][j][0];
        wfile[count].write((char*)&ffn, sizeof (float));
        } 
        
        for(i=is[aa]; i<ie[aa]; ++i)
        for(j=js[bb]; j<je[bb]; ++j)
        {
        ffn=V[i][j][0];
        wfile[count].write((char*)&ffn, sizeof (float));
        } 
        
        for(i=is[aa]; i<ie[aa]; ++i)
        for(j=js[bb]; j<je[bb]; ++j)
        {
        ffn=W[i][j][0];
        wfile[count].write((char*)&ffn, sizeof (float));
        } 
        ++count;
    }
    
    // file close
    if(file_type==1)
    for(q=0;q<p->M10;++q)
    wfile[q].close();
}




