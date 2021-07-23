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
Author: Hans Bihs
--------------------------------------------------------------------*/
#include "dive.h"

dive::dive(lexer* p) : flag(p),solid(p),solid_dist(p),
                   topo(p),topo_dist(p),
                   cellside(p),subgrid(p),
                   numfac(p), confac(p),
                   xdir(p),ydir(p),zdir(p),onnode(p),
                   topobed(p),solidbed(p),data(p),
                   bedlevel(p),
                   flagslice(p),subslice(p)
{

	p->Iarray(mpx,p->M10*p->M10*p->M10);
	p->Iarray(mpy,p->M10*p->M10*p->M10);
	p->Iarray(mpz,p->M10*p->M10*p->M10);
	
	p->Darray(xorig,p->M10+10);
	p->Darray(yorig,p->M10+10);
	p->Darray(zorig,p->M10+10);
	
	p->Iarray(xnode,p->M10+10);
	p->Iarray(ynode,p->M10+10);
	p->Iarray(znode,p->M10+10);


 knox=p->knox;
 knoy=p->knoy;
 knoz=p->knoz;

 maxknox=0;
 maxknox=MAX(maxknox,p->knox);
 maxknox=MAX(maxknox,p->knoy);
 maxknox=MAX(maxknox,p->knoz);
	
	p->Iarray(subknox,p->M10+1);
	p->Iarray(subknoy,p->M10+1);
	p->Iarray(subknoz,p->M10+1);

incount=0;
utcount=0;
fsfcount=0;
surfcount=0;
surfcount_solid=0;
bedcount=0;

para1count=0;
para2count=0;
para3count=0;
para4count=0;
para5count=0;
para6count=0;

facetcount=0;
ccpointcount=0;


	Iarray(mpi_index,p->M10+1);
	Iarray(mpi_edges,(p->M10+1)*6);


	Iarray(in,p->M10+1);
	Iarray(ut,p->M10+1);
	Iarray(fsf,p->M10+1);
	Iarray(wall,p->M10+1);
	Iarray(bed,p->M10+1);

	Iarray(para1,p->M10+1);
	Iarray(para2,p->M10+1);
	Iarray(para3,p->M10+1);
	Iarray(para4,p->M10+1);
	Iarray(para5,p->M10+1);
	Iarray(para6,p->M10+1);
	Iarray(paraco1,p->M10+1);
	Iarray(paraco2,p->M10+1);
	Iarray(paraco3,p->M10+1);
	Iarray(paraco4,p->M10+1);
	Iarray(paraco5,p->M10+1);
	Iarray(paraco6,p->M10+1);
    
    Iarray(paraslice1,p->M10+1);
	Iarray(paraslice2,p->M10+1);
	Iarray(paraslice3,p->M10+1);
	Iarray(paraslice4,p->M10+1);
    
    Iarray(paracoslice1,p->M10+1);
	Iarray(paracoslice2,p->M10+1);
	Iarray(paracoslice3,p->M10+1);
	Iarray(paracoslice4,p->M10+1);
    
	Iarray(nbpara1,p->M10+1);
	Iarray(nbpara2,p->M10+1);
	Iarray(nbpara3,p->M10+1);
	Iarray(nbpara4,p->M10+1);
	Iarray(nbpara5,p->M10+1);
	Iarray(nbpara6,p->M10+1);


    for(n=0;n<p->M10+1;n++)
    {
        in[n]=0;
        ut[n]=0;
        fsf[n]=0;
        wall[n]=0;
        bed[n]=0;

        para1[n]=0;
        para2[n]=0;
        para3[n]=0;
        para4[n]=0;
        para5[n]=0;
        para6[n]=0;

        paraco1[n]=0;
        paraco2[n]=0;
        paraco3[n]=0;
        paraco4[n]=0;
        paraco5[n]=0;
        paraco6[n]=0;

        nbpara1[n]=-1;
        nbpara2[n]=-1;
        nbpara3[n]=-1;
        nbpara4[n]=-1;
        nbpara5[n]=-1;
        nbpara6[n]=-1;
    }

//ibm
    maxsurf =int((knox*knoy + knox*knoz + knoy*knoz)); // just in time? pre count in cce3d
	
	//cout<<"MAXSURF: "<<maxsurf<<endl;

	
    Iarray(facet,maxsurf,6);
    Darray(ccpoint,maxsurf,3);
    Iarray(ccptnum,p->M10+1);
    Iarray(facetnum,p->M10+1);
    Iarray(ccstate,maxsurf);
    Iarray(ccstatenum,p->M10+1);
    Iarray(ccmem,maxsurf);
    
	
	i_dir=j_dir=k_dir=0;
	
	if(p->knox>1 || p->B5!=1)
	i_dir=1;
	
	if(p->knoy>1 || p->B5!=1)
	j_dir=1;
	
	if(p->knoz>1 || p->B5!=1)
	k_dir=1;
//object print

	
	int polyval=1e6;
	
	Iarray(polygon,polyval,5);
	Iarray(numvert,5*polyval);
	Iarray(polygon_offset,5*polyval);
	Darray(vertice,5*polyval,3);
	
	
	Iarray(solid_gcb,p->M10+1);    
    Iarray(topo_gcb,p->M10+1);


cout<<'.'<<endl;


}

dive::~dive()
{

}



