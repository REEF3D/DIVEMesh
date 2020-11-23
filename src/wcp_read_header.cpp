/*--------------------------------------------------------------------
REEF3D
Copyright 2008-2020 Hans Bihs

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
    
    cout<<"WCP numprocs:"<<numprocs<<endl;
    
    

    for(q=0; q<numprocs; ++q)
    {
        // filename
        filename_in_header(p,a,q);
        
        // read header
        header.open(name, ios::binary);
        
 
        // read header section
        
        // orig_ijk
        header.read((char*)&iin, sizeof (int));
        orig_i[q]=iin;
        
        header.read((char*)&iin, sizeof (int));
        orig_j[q]=iin;
        
        header.read((char*)&iin, sizeof (int));
        orig_k[q]=iin;
        
        // orig_xyz
        header.read((char*)&ffn, sizeof (float)); 
        orig_x[q] = ffn;
        
        header.read((char*)&ffn, sizeof (float)); 
        orig_y[q] = ffn;
        
        header.read((char*)&ffn, sizeof (float)); 
        orig_z[q] = ffn;
        

        
        // NLx[q],NLy[q],NLz[q]
        header.read((char*)&iin, sizeof (int));
        NLx[q]=iin;
        
        header.read((char*)&iin, sizeof (int));
        NLy[q]=iin;
        
        header.read((char*)&iin, sizeof (int));
        NLz[q]=iin;
        
        
        // nbx
        header.read((char*)&iin, sizeof (int));
        nb1[q]=iin;
        
        header.read((char*)&iin, sizeof (int));
        nb2[q]=iin;

        header.read((char*)&iin, sizeof (int));
        nb3[q]=iin;
        
        header.read((char*)&iin, sizeof (int));
        nb4[q]=iin;
        
        /*
        cout<<"WCP read coords: "<<q<<endl;
        
        cout<<"WCP NGx: "<<NGx<<endl;
        cout<<"WCP NGy: "<<NGy<<endl;
        cout<<"WCP NGz: "<<NGz<<endl;
        
        cout<<"WCP NLx: "<<NLx[q]<<endl;
        cout<<"WCP NLy: "<<NLy[q]<<endl;
        cout<<"WCP NLz: "<<NLz[q]<<endl;
        
        cout<<"WCP orig_i: "<<orig_i[q]<<endl;
        cout<<"WCP orig_j: "<<orig_j[q]<<endl;
        cout<<"WCP orig_k: "<<orig_k[q]<<endl;
        
        cout<<"WCP orig_x: "<<orig_x[q]<<endl;
        cout<<"WCP orig_y: "<<orig_y[q]<<endl;
        cout<<"WCP orig_z: "<<orig_z[q]<<endl;*/
        
        
          // read coordinates
        for(i=0;i<NLx[q];++i)
        {
        header.read((char*)&ffn, sizeof (float)); 
        X[i+orig_i[q]] = double(ffn)-p->H21;
        }
        
        for(j=0;j<NLy[q];++j)
        {
        header.read((char*)&ffn, sizeof (float)); 
        Y[j+orig_j[q]] = double(ffn)-p->H22;
        }
        
        for(k=0;k<NLz[q];++k)
        {
        header.read((char*)&ffn, sizeof (float)); 
        Z[k+orig_k[q]] = double(ffn)-p->H23;
        }
        
        
        for(i=0;i<NLx[q];++i)
        for(j=0;j<NLy[q];++j)
        {
        header.read((char*)&ffn, sizeof (float)); 
        bed[i+orig_i[q]][j+orig_j[q]] = ffn;
        }
        
        
        header.close();
    }

}
