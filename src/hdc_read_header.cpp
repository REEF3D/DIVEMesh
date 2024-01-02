/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2024 Hans Bihs

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

void hdc::read_header(lexer *p, dive *a)
{
    ifstream header;
    
    for(q=0; q<numprocs; ++q)
    if(flag_all[q]==1)
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
        header.read((char*)&ddn, sizeof (double)); 
        orig_x[q] = ddn;
        
        header.read((char*)&ddn, sizeof (double)); 
        orig_y[q] = ddn;
        
        header.read((char*)&ddn, sizeof (double)); 
        orig_z[q] = ddn;
        

        
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
        cout<<q<<" HDC NGx: "<<NGx<<endl;
        cout<<q<<" HDC NGy: "<<NGy<<endl;
        cout<<q<<" HDC NGz: "<<NGz<<endl;
        
        cout<<q<<" HDC NLx: "<<NLx[q]<<endl;
        cout<<q<<" HDC NLy: "<<NLy[q]<<endl;
        cout<<q<<" HDC NLz: "<<NLz[q]<<endl;
        
        cout<<q<<" HDC orig_i: "<<orig_i[q]<<endl;
        cout<<q<<" HDC orig_j: "<<orig_j[q]<<endl;
        cout<<q<<" HDC orig_k: "<<orig_k[q]<<endl;
        
        cout<<q<<" HDC orig_x: "<<orig_x[q]<<endl;
        cout<<q<<" HDC orig_y: "<<orig_y[q]<<endl;
        cout<<q<<" HDC orig_z: "<<orig_z[q]<<endl<<endl;
        */
        
          // read coordinates
        for(i=0;i<NLx[q];++i)
        {
        header.read((char*)&ddn, sizeof (double)); 
        X[i+orig_i[q]] = ddn-p->H21;
        }
        
        for(j=0;j<NLy[q];++j)
        {
        header.read((char*)&ddn, sizeof (double)); 
        Y[j+orig_j[q]] = ddn-p->H22;
        }
        
        for(k=0;k<NLz[q];++k)
        {
        header.read((char*)&ddn, sizeof (double)); 
        Z[k+orig_k[q]] = ddn-p->H23;
        }
        
        
        for(i=0;i<NLx[q];++i)
        for(j=0;j<NLy[q];++j)
        {
        header.read((char*)&ddn, sizeof (double)); 
        bed[i+orig_i[q]][j+orig_j[q]] = ddn;
        }
        
        
        header.close();
    }

}
