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

#include"wcp.h"
#include"lexer.h"
#include"dive.h"
#include<iostream>
#include<fstream>
#include<sys/stat.h>
#include<sys/types.h>

void wcp::write_header(lexer *p, dive *a)
{
    ofstream header;
    
    // write header
    count=0;
    for(aa=0;aa<a->mx;++aa)
    for(bb=0;bb<a->my;++bb)
    {
        cout<<"WCP write_header: "<<count<<endl;
        filename_out_header(p,a,count);
        header.open(name, ios::binary);
        
        // jdir
        iin=jdir;
        header.write((char*)&iin, sizeof (int));
        
        // origin_ij
        iin=is[aa];
        header.write((char*)&iin, sizeof (int));
        
        iin=js[aa];
        header.write((char*)&iin, sizeof (int));
        
        // origin_xy
        ffn=xs[aa];
        header.write((char*)&ffn, sizeof (float));
        
        ffn=ys[aa];
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
        //cout<<i<<" "<<X[i]<<endl;
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
        
        cout<<"WCP final iteration print: "<<qn<<" "<<p->H31<<" "<<p->H32<<" "<<p->H33<<" "<<p->H34<<endl;
            
        iin=qn;
        header.write((char*)&iin, sizeof (int));
        
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
    