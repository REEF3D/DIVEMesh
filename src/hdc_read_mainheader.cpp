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

void hdc::read_mainheader(lexer *p, dive *a)
{
    ifstream mainhead;
    int ii1,ii2;
    double val;
    
    if(p->H10==2)
    sprintf(name,"./REEF3D_SFLOW_STATE/REEF3D-SFLOW_State_Mainheader.r3d");
    
    if(p->H10==4)
    sprintf(name,"./REEF3D_FNPF_STATE/REEF3D-FNPF_State_Mainheader.r3d");
    
    if(p->H10==5)
    sprintf(name,"./REEF3D_NHFLOW_STATE/REEF3D-NHFLOW_State_Mainheader.r3d");
    
	mainhead.open(name, ios::binary);
    
    // count numiter
    mainhead.read((char*)&iin, sizeof (int));
	numprocs=iin;
    
    mainhead.read((char*)&iin, sizeof (int));
	jdir=iin;
    
    mainhead.read((char*)&iin, sizeof (int));
	NGx=iin;
    
    mainhead.read((char*)&iin, sizeof (int));
	NGy=iin;
    
    mainhead.read((char*)&iin, sizeof (int));
	NGz=iin;
    
    mainhead.read((char*)&iin, sizeof (int));
	file_version=iin;
    
    mainhead.read((char*)&iin, sizeof (int));
	file_type=iin;
    
    mainhead.read((char*)&ddn, sizeof (double));
	SWL=ddn;
    
    mainhead.read((char*)&ddn, sizeof (double));
	val=ddn;
    
    mainhead.read((char*)&ddn, sizeof (double));
	val=ddn;
    
    
    // read flag
    p->Iarray(flag_all,numprocs);
    
    for(int qn=0;qn<numprocs;++qn)
    {    
    mainhead.read((char*)&iin, sizeof (int));
    
	flag_all[qn]=iin;
    }
    
    
    // read timesteps
    numiter=0;
    while(!mainhead.eof())
	{
    ii1=ii2;
    
    mainhead.read((char*)&iin, sizeof (int));
    ii2=iin;
 
    mainhead.read((char*)&ddn, sizeof (double));  
    
    ++numiter;
    }
    
    
    if(ii1==ii2)
    --numiter;
    
    mainhead.close();
    
    cout<<"HDC numiter: "<<numiter<<endl;
    
    
    // allocate simtime
    p->Darray(simtime,numiter+1);
    
// ------------
    
    // re-read mainhead
    mainhead.open(name, ios::binary);
    
    mainhead.read((char*)&iin, sizeof (int));
	numprocs=iin;
    
    mainhead.read((char*)&iin, sizeof (int));
	jdir=iin;
    
    mainhead.read((char*)&iin, sizeof (int));
	NGx=iin;
    
    mainhead.read((char*)&iin, sizeof (int));
	NGy=iin;
    
    mainhead.read((char*)&iin, sizeof (int));
	NGz=iin;
    
    mainhead.read((char*)&iin, sizeof (int));
	file_version=iin;
    
    mainhead.read((char*)&iin, sizeof (int));
	file_type=iin;
    
    mainhead.read((char*)&ddn, sizeof (double));
	SWL=ddn;
    
    mainhead.read((char*)&ddn, sizeof (double));
	val=ddn;
    
    mainhead.read((char*)&ddn, sizeof (double));
	val=ddn;
    
    cout<<"HDC numprocs: "<<numprocs<<endl;
    cout<<"HDC NGx: "<<NGx<<endl;
    cout<<"HDC NGy: "<<NGy<<endl;
    cout<<"HDC NGz: "<<NGz<<endl;
    cout<<"HDC jdir: "<<jdir<<endl;
    cout<<"HDC file_version: "<<file_version<<endl;
    cout<<"HDC file_type: "<<file_type<<endl<<endl;

    // read flag    
    for(qn=0;qn<numprocs;++qn)
    {
    mainhead.read((char*)&iin, sizeof (int));
	flag_all[qn]=iin;
    }
    
    count=0;
    while(!mainhead.eof())
	{
    mainhead.read((char*)&iin, sizeof (int));
 
    mainhead.read((char*)&ddn, sizeof (double)); 
    simtime[count] = ddn;
    
    cout<<"simtime: "<<simtime[count]<<endl;
    
    ++count;
    }
    
    mainhead.close();
}
