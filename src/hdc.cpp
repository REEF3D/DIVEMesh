/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2026 Hans Bihs

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
#include"dive.h"
#include"lexer.h"
#include<sys/stat.h>
#include<sys/types.h>

hdc::hdc(lexer *p, dive *a) 
{
    // Create Folder
    if(p->H10!=44)
	mkdir("./REEF3D_CFD_HDC_Input",0777);
    
    if(p->H10==44)
    mkdir("./REEF3D_FNPF_HDC_Input",0777);
}

hdc::~hdc()
{
}

void hdc::start(lexer* p, dive* a)
{
    cout<<endl<<"Hydrodynamic Coupling (HDC) procedure "<<endl<<endl;

    // headers & decomp
    read_mainheader(p,a);
    allocate(p,a);
    read_header(p,a);
    decomp(p,a);
    write_header(p,a);
    
    // open contiuous file pointer
    if(file_conti==2)
    {
        for(q=0; q<numprocs; ++q)
        {
        filename_continuous_in(p,a,q); 
        result[q].open(name, ios::binary);
        }
        
        for(q=0; q<p->M10; ++q)
        {
        filename_continuous_out(p,a,q); 
        wfile[q].open(name, ios::binary);
        }
    }

    cout<<"HDC read/write "<<endl;
    
// read/write result files
    // single files
    if(file_conti==1)
    for(n=0; n<numiter; ++n)
    if(simtime[n]>=p->H31 && simtime[n]<p->H32)
    if(n>=p->H33 && n<p->H34)
    {
        read(p,a);
        write(p,a);
    
    cout<<"HDC I/O iter: "<<n<<"   simtime: "<<simtime[n]<<endl;
    }
    
    // continuous files
    if(file_conti==2)
    for(n=0; n<numiter; ++n)
    {
        read(p,a);
        
        if(simtime[n]>=p->H31 && simtime[n]<p->H32)
        if(n>=p->H33 && n<p->H34)
        {
            write(p,a);
        
        cout<<"HDC I/O iter: "<<n<<"   simtime: "<<simtime[n]<<endl;
        }
    }
    
    // cell check
    cout<<endl;
    
    count=0;
    for(aa=0;aa<a->mx;++aa)
    for(bb=0;bb<a->my;++bb)
    {
    cout<<count<<" Nx: "<<ie[aa]-is[aa]<<" Ny: "<<je[bb]-js[bb]<<endl;
    ++count;
    }

    
    // close continuous file pointer
    if(file_conti==2)
    {
        for(q=0; q<numprocs; ++q)
        {
        result[q].close();
        wfile[q].close();
        }
    }
    
    delete [] result;
    delete [] wfile;
    
    
    /*
    testfile[0].open("testfile.dat");
    
    for(i=0;i<100;++i)
    {
    ffn = float(i);
    testfile[0].write((char*)&ffn, sizeof(float));
    }
    
    testfile[0].close();*/
    
}

void hdc::read(lexer *p, dive *a)
{  
    if(p->H10==2)
    read_sflow(p,a);
    
    if(p->H10==4 || p->H10==44)
    read_fnpf(p,a);
    
    if(p->H10==5)
    read_nhflow(p,a);
}

void hdc::write(lexer *p, dive *a)
{  
    if(p->H10==2)
    write_sflow(p,a);
    
    if(p->H10==4 || p->H10==44)
    write_fnpf(p,a); 

    if(p->H10==5)
    write_nhflow(p,a);   
}

