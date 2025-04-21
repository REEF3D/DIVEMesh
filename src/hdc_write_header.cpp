/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2025 Hans Bihs

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

void hdc::write_header(lexer *p, dive *a)
{
    cout<<"HDC write header "<<endl;
    
    ofstream header;
    
    // write header
    count=0;
    for(aa=0;aa<a->mx;++aa)
    for(bb=0;bb<a->my;++bb)
    {
        filename_out_header(p,a,count);
        header.open(name, ios::binary);
        
        // file_version
        iin=file_version;
        header.write((char*)&iin, sizeof (int));
        
        // file_type
        iin=file_type;
        header.write((char*)&iin, sizeof (int));
        
        // jdir
        iin=jdir;
        header.write((char*)&iin, sizeof (int));
        
        // origin_ij
        iin=is[aa];
        header.write((char*)&iin, sizeof (int));
        
        iin=js[bb];
        header.write((char*)&iin, sizeof (int));
        
        // origin_xy
        ffn=xs[aa];
        header.write((char*)&ffn, sizeof (float));
        
        ffn=ys[bb];
        header.write((char*)&ffn, sizeof (float));
        
        // Nx,Ny,Nz
        iin=ie[aa]-is[aa];
        header.write((char*)&iin, sizeof (int));
        
        iin=je[bb]-js[bb];
        header.write((char*)&iin, sizeof (int));
        
        iin=NGz;
        header.write((char*)&iin, sizeof (int));
        

        // write coordinates
        for(i=is[aa]; i<ie[aa]; ++i)
        {
        ffn=float(X[i]);
        header.write((char*)&ffn, sizeof (float));
        }
            
        for(j=js[bb]; j<je[bb]; ++j)
        {
        ffn=float(Y[j]);
        header.write((char*)&ffn, sizeof (float));
        }
        
        for(k=0; k<NGz; ++k)
        {
        ffn=float(Z[k]);
        header.write((char*)&ffn, sizeof (float));
        }
        
        
        // write bed
        for(i=is[aa]; i<ie[aa]; ++i)
        for(j=js[bb]; j<je[bb]; ++j)
        {
        ffn=float(bed[i][j]);
        header.write((char*)&ffn, sizeof (float));
        }  
        
        
        // numer of iterations
        int qn=0;
        for(n=0;n<numiter;++n)
        if(simtime[n]>=p->H31 && simtime[n]<p->H32)
        if(n>=p->H33 && n<p->H34)
        ++qn;

        iin=qn;
        header.write((char*)&iin, sizeof (int));
        
        // delta iterations
        qn=0;
        for(n=0;n<numiter;++n)
        if(simtime[n]>=p->H31 && simtime[n]<p->H32)
        if(n>=p->H33)
        {
        qn=n;
        break;
        }
        
        
        iin=qn;
        header.write((char*)&iin, sizeof (int));
        
        // simtime
        for(n=0;n<numiter;++n)
        if(simtime[n]>=p->H31 && simtime[n]<p->H32)
        if(n>=p->H33 && n<p->H34)
        {
        ddn=simtime[n];
        header.write((char*)&ddn, sizeof (double));
        }
        ++count;
        
    header.close();
    }
    
}
    