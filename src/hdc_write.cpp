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

void hdc::write(lexer *p, dive *a)
{
    
    // header
    
    
        
    ofstream wfile;
    
    // write result
    count=0;
    for(aa=0;aa<a->mx;++aa)
    for(bb=0;bb<a->my;++bb)
    {    
        
        // filename
        filename_out(p,a,n,count);
        
        // file open
        wfile.open(name, ios::binary);
        
        
        //ijk loop
        // ->write
        for(i=is[aa]; i<ie[aa]; ++i)
        for(j=js[bb]; j<je[bb]; ++j)
        {
        ffn=float(eta[i][j]);
        wfile.write((char*)&ffn, sizeof (float));
        }
            
        for(i=is[aa]; i<ie[aa]; ++i)
        for(j=js[bb]; j<je[bb]; ++j)
        for(k=0; k<NGz; ++k)
        {
        ffn=float(U[i][j][k]);
        wfile.write((char*)&ffn, sizeof (float));
        } 
        
        for(i=is[aa]; i<ie[aa]; ++i)
        for(j=js[bb]; j<je[bb]; ++j)
        for(k=0; k<NGz; ++k)
        {
        ffn=float(V[i][j][k]);
        wfile.write((char*)&ffn, sizeof (float));
        } 
        
        for(i=is[aa]; i<ie[aa]; ++i)
        for(j=js[bb]; j<je[bb]; ++j)
        for(k=0; k<NGz; ++k)
        {
        ffn=float(W[i][j][k]);
        wfile.write((char*)&ffn, sizeof (float));
        } 
        ++count;
        
        // file close
        wfile.close();
    }
}




