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

void wcp::read(lexer *p, dive *a)
{
    ifstream result;
    
    // header
    read_header(p,a);
    
    // allocate arrays
    p->Darray(U,NGx,NGy,NGz);
    p->Darray(V,NGx,NGy,NGz);
    p->Darray(W,NGx,NGy,NGz);
    p->Darray(eta,NGx,NGy);
    
    // result
    for(n=0; n<numiter; ++n)
    for(q=0; q<numprocs; ++q)
    {
    // Open File
	filename_in(p,a,n,q); 
	
	result.open(name, ios::binary);
	
    
    
    result.close();
    }
    
    
    
    /*
    result.read((char*)&iin, sizeof (int));
	p->count=p->count_wcpstart=iin;
	
    result.read((char*)&iin, sizeof (int));
	p->printcount=iin;
	
    result.read((char*)&ddn, sizeof (double));
	p->simtime=ddn;
    
    result.read((char*)&ddn, sizeof (double));
	p->printtime=ddn;
    
    result.read((char*)&ddn, sizeof (double));
	p->sedprinttime=ddn;
    
    result.read((char*)&ddn, sizeof (double));
	p->fsfprinttime=ddn;
    
    result.read((char*)&ddn, sizeof (double));
	p->probeprinttime=ddn;
    
    result.read((char*)&ddn, sizeof (double));
	p->wcpprinttime=ddn;
    
    ULOOP
    {
    result.read((char*)&ffn, sizeof (float));
    a->u(i,j,k)=double(ffn);
    }
	
	VLOOP
    {
    result.read((char*)&ffn, sizeof (float));
    a->v(i,j,k)=double(ffn);
    }
	
	WLOOP
    {
    result.read((char*)&ffn, sizeof (float));
    a->w(i,j,k)=double(ffn);
    }
	
	LOOP
    {
    result.read((char*)&ffn, sizeof (float));
    a->press(i,j,k)=double(ffn);
    }
	
	LOOP
    {
    result.read((char*)&ffn, sizeof (float));
    a->phi(i,j,k)=double(ffn);
    }
	
	LOOP
    {
    result.read((char*)&ffn, sizeof (float));
    pturb->kinget(i,j,k,ffn);
    }
	
	LOOP
    {
    result.read((char*)&ffn, sizeof (float));
    pturb->epsget(i,j,k,ffn);
    }
	
	LOOP
    {
    result.read((char*)&ffn, sizeof (float));
    a->eddyv(i,j,k)=double(ffn);
    }
	
	ALOOP
    {
    result.read((char*)&ffn, sizeof (float));
    a->topo(i,j,k)=double(ffn);
    }
	
	SLICELOOP4
    {
    result.read((char*)&ffn, sizeof (float));
    a->bedload(i,j)=double(ffn);
    }
	
	LOOP
    {
    result.read((char*)&ffn, sizeof (float));
    a->conc(i,j,k)=double(ffn);
    }
	
	int gcval_press, gcval_phi, gcval_topo;
	
	if(p->B76==0)
    gcval_press=40;  

    if(p->B76==1)
    gcval_press=41;

    if(p->B76==2)
    gcval_press=42;

    if(p->B76==3)
    gcval_press=43;
	
	if(p->B76==4) 
    gcval_press=44;
	
	if(p->B76==5) 
    gcval_press=45;
	
	
	if(p->F50==1)
	gcval_phi=51;

	if(p->F50==2)
	gcval_phi=52;

	if(p->F50==3)
	gcval_phi=53;

	if(p->F50==4)
	gcval_phi=54;
	
	
	if(p->S50==1)
	gcval_topo=151;

	if(p->S50==2)
	gcval_topo=152;

	if(p->S50==3)
	gcval_topo=153;
	
	if(p->S50==4)
	gcval_topo=154;
	
	
	pgc->start1(p,a->u,10);
	pgc->start2(p,a->v,11);
	pgc->start3(p,a->w,12);
    pgc->start4(p,a->press,gcval_press);
	pgc->start4(p,a->phi,gcval_phi);
	pturb->gcupdate(p,a,pgc);
	pgc->start4(p,a->eddyv,24);
	pgc->start4a(p,a->topo,gcval_topo);
	pgc->start4(p,a->conc,40);
	
	result.close();*/
}



void wcp::read_header(lexer *p, dive *a)
{
    ifstream header;
	header.open(name, ios::binary);
    
    // count numiter
    header.read((char*)&iin, sizeof (int));
    header.read((char*)&iin, sizeof (int));
    header.read((char*)&iin, sizeof (int));
    header.read((char*)&iin, sizeof (int));
    
    numiter=0;
    while(!header.eof())
	{
    header.read((char*)&iin, sizeof (int));
 
    header.read((char*)&ddn, sizeof (double));    
    ++numiter;
    }
    
    header.close();
    
    p->Darray(simtime,numiter);
    
    
    // read header
    header.open(name, ios::binary);
    
    header.read((char*)&iin, sizeof (int));
	numprocs=iin;
    
    header.read((char*)&iin, sizeof (int));
	NGx=iin;
    
    header.read((char*)&iin, sizeof (int));
	NGy=iin;
    
    header.read((char*)&iin, sizeof (int));
	NGz=iin;
    
    count=0;
    while(!header.eof())
	{
    header.read((char*)&iin, sizeof (int));
 
    header.read((char*)&ddn, sizeof (double)); 
    simtime[count] = ddn;
    ++count;
    }
}