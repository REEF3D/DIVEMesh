/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2018 Hans Bihs

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
--------------------------------------------------------------------*/

#include"print_binary.h"
#include"lexer.h"
#include"dive.h"
#include<iostream>
#include<fstream>
#include<sys/stat.h>
#include<sys/types.h>
#include <iomanip>

print_binary::print_binary(lexer* p)
{
}

print_binary::~print_binary()
{
}

void print_binary::start(lexer* p,dive* a)
{
    int iin;
    double ddn;
    
    if(p->G41==1 && p->G10>0)
    print_bottom(p,a);
	int l;
	
	cout<<"printing ";
	char name[100];
	
	count=0;
    

NLOOP
{
    ++count;

	if(count<10&&count>0)
	sprintf(name,"grid-00000%d.dat",count);

	if(count<100&&count>9)
	sprintf(name,"grid-0000%d.dat",count);

	if(count<1000&&count>99)
	sprintf(name,"grid-000%d.dat",count);

	if(count<10000&&count>999)
	sprintf(name,"grid-00%d.dat",count);

	if(count<100000&&count>9999)
	sprintf(name,"grid-0%d.dat",count);

	if(count>99999)
	sprintf(name,"grid-%d.dat",count);

	ofstream result;
	result.open(name, ios::binary);
    
    

	//HEADER
    iin = p->M10;
    result.write((char*)&iin, sizeof (int));
    
    
    iin = a->subknox[count];
    result.write((char*)&iin, sizeof (int));
    iin = a->subknoy[count];
    result.write((char*)&iin, sizeof (int));
    iin = a->subknoz[count];
    result.write((char*)&iin, sizeof (int));
    
    
    ddn = p->DXM;
    result.write((char*)&ddn, sizeof (double));
    
    
    ddn = a->xorig[aa-1];
    result.write((char*)&ddn, sizeof (double));
    ddn = a->yorig[bb-1];
    result.write((char*)&ddn, sizeof (double));
    ddn = a->zorig[cc-1];
    result.write((char*)&ddn, sizeof (double));
    ddn = a->xorig[aa];
    result.write((char*)&ddn, sizeof (double));
    ddn = a->yorig[bb];
    result.write((char*)&ddn, sizeof (double));
    ddn = a->zorig[cc];
    result.write((char*)&ddn, sizeof (double));


    ddn = p->xmin;
    result.write((char*)&ddn, sizeof (double));
    ddn = p->ymin;
    result.write((char*)&ddn, sizeof (double));
    ddn = p->zmin;
    result.write((char*)&ddn, sizeof (double));
    ddn = p->xmax;
    result.write((char*)&ddn, sizeof (double));
    ddn = p->ymax;
    result.write((char*)&ddn, sizeof (double));
    ddn = p->zmax;
    result.write((char*)&ddn, sizeof (double));

    
    iin = a->knox;
    result.write((char*)&iin, sizeof (int));
    iin = a->knoy;
    result.write((char*)&iin, sizeof (int));
    iin = a->knoz;
    result.write((char*)&iin, sizeof (int));
    
    
    iin = a->xnode[aa-1];
    result.write((char*)&iin, sizeof (int));
    iin = a->ynode[bb-1];
    result.write((char*)&iin, sizeof (int));
    iin = a->znode[cc-1];
    result.write((char*)&iin, sizeof (int));
    
    
    iin = a->wall[count];
    result.write((char*)&iin, sizeof (int));
    iin = a->ccptnum[count];
    result.write((char*)&iin, sizeof (int));
    iin = a->facetnum[count];
    result.write((char*)&iin, sizeof (int));


    iin = a->para1[count];
    result.write((char*)&iin, sizeof (int));
    iin = a->para2[count];
    result.write((char*)&iin, sizeof (int));
    iin = a->para3[count];
    result.write((char*)&iin, sizeof (int));
    iin = a->para4[count];
    result.write((char*)&iin, sizeof (int));
    iin = a->para5[count];
    result.write((char*)&iin, sizeof (int));
    iin = a->para6[count];
    result.write((char*)&iin, sizeof (int));
    
    iin = a->paravoid1[count];
    result.write((char*)&iin, sizeof (int));
    iin = a->paravoid2[count];
    result.write((char*)&iin, sizeof (int));
    iin = a->paravoid3[count];
    result.write((char*)&iin, sizeof (int));
    iin = a->paravoid4[count];
    result.write((char*)&iin, sizeof (int));
    iin = a->paravoid5[count];
    result.write((char*)&iin, sizeof (int));
    iin = a->paravoid6[count];
    result.write((char*)&iin, sizeof (int));
    
    iin = a->paraco1[count];
    result.write((char*)&iin, sizeof (int));
    iin = a->paraco2[count];
    result.write((char*)&iin, sizeof (int));
    iin = a->paraco3[count];
    result.write((char*)&iin, sizeof (int));
    iin = a->paraco4[count];
    result.write((char*)&iin, sizeof (int));
    iin = a->paraco5[count];
    result.write((char*)&iin, sizeof (int));
    iin = a->paraco6[count];
    result.write((char*)&iin, sizeof (int));
    
    iin = a->paraslice1[count];
    result.write((char*)&iin, sizeof (int));
    iin = a->paraslice2[count];
    result.write((char*)&iin, sizeof (int));
    iin = a->paraslice3[count];
    result.write((char*)&iin, sizeof (int));
    iin = a->paraslice4[count];
    result.write((char*)&iin, sizeof (int));
    
    iin = a->paracoslice1[count];
    result.write((char*)&iin, sizeof (int));
    iin = a->paracoslice2[count];
    result.write((char*)&iin, sizeof (int));
    iin = a->paracoslice3[count];
    result.write((char*)&iin, sizeof (int));
    iin = a->paracoslice4[count];
    result.write((char*)&iin, sizeof (int));
    
    
    iin = a->nbpara1[count];
    result.write((char*)&iin, sizeof (int));
    iin = a->nbpara2[count];
    result.write((char*)&iin, sizeof (int));
    iin = a->nbpara3[count];
    result.write((char*)&iin, sizeof (int));
    iin = a->nbpara4[count];
    result.write((char*)&iin, sizeof (int));
    iin = a->nbpara5[count];
    result.write((char*)&iin, sizeof (int));
    iin = a->nbpara6[count];
    result.write((char*)&iin, sizeof (int));
    
    
    iin = a->mx;
    result.write((char*)&iin, sizeof (int));
    iin = a->my;
    result.write((char*)&iin, sizeof (int));
    iin = a->mz;
    result.write((char*)&iin, sizeof (int));
    
    iin = aa-1;
    result.write((char*)&iin, sizeof (int));
    iin = bb-1;
    result.write((char*)&iin, sizeof (int));
    iin = cc-1;
    result.write((char*)&iin, sizeof (int));
    
    iin = p->C11;
    result.write((char*)&iin, sizeof (int));
    iin = p->C12;
    result.write((char*)&iin, sizeof (int));
    iin = p->C13;
    result.write((char*)&iin, sizeof (int));
    iin = p->C14;
    result.write((char*)&iin, sizeof (int));
    iin = p->C15;
    result.write((char*)&iin, sizeof (int));
    iin = p->C16;
    result.write((char*)&iin, sizeof (int));
	

    iin = p->G10;
    result.write((char*)&iin, sizeof (int));
    iin = p->D10;
    result.write((char*)&iin, sizeof (int));  
    iin = p->solidprint;
    result.write((char*)&iin, sizeof (int));  
    iin = a->solid_gcb[count-1];
    result.write((char*)&iin, sizeof (int));  
    iin = a->i_dir;
    result.write((char*)&iin, sizeof (int));  
    iin = a->j_dir;
    result.write((char*)&iin, sizeof (int));  
    iin = a->k_dir;
    result.write((char*)&iin, sizeof (int));  
    iin = a->geodat_gcb[count-1];
    result.write((char*)&iin, sizeof (int));  
    

    
// ---------------------------------------------------------------------------------------------------------------------
// FLAG

    SUBLOOP
    {
    iin = a->flag(i,j,k);
    result.write((char*)&iin, sizeof (int));  
    }
    
// ---------------------------------------------------------------------------------------------------------------------
// Nodes
    SNODEILOOP
    {
    ddn = p->XN[IP]+p->xmin;
    result.write((char*)&ddn, sizeof (double));
    }
    
    SNODEJLOOP
    {
    ddn = p->YN[JP]+p->ymin;
    result.write((char*)&ddn, sizeof (double));
    }
    
    SNODEKLOOP
    {
    ddn = p->ZN[KP]+p->zmin;
    result.write((char*)&ddn, sizeof (double));
    }

// ---------------------------------------------------------------------------------------------------------------------
// solid_dist
	
    if(p->solidprint==1)
    SUBLOOP
    {
    ddn = a->solid_dist(i,j,k);
    result.write((char*)&ddn, sizeof (double));
    }

// ---------------------------------------------------------------------------------------------------------------------
//CCSTATE:
// *********************

    LOOP
    if(a->subgrid(i,j,k)==count && a->numfac(i,j,k)>0)
    {
    q=a->confac(i,j,k);
    iin = a->ccstate[q];
    result.write((char*)&iin, sizeof (int));  
    }

// ---------------------------------------------------------------------------------------------------------------------
//SURFACES

    for(q=0;q<a->surfcount;q++)
    {
    i=a->surf[q][0];
    j=a->surf[q][1];
    k=a->surf[q][2];
    n=a->subgrid(i,j,k);
    
        if(n==count)
        {
        iin = i-a->xnode[aa-1];
        result.write((char*)&iin, sizeof (int)); 
        iin = j-a->ynode[bb-1];
        result.write((char*)&iin, sizeof (int)); 
        iin = k-a->znode[cc-1];
        result.write((char*)&iin, sizeof (int)); 
        iin = a->surf[q][3];
        result.write((char*)&iin, sizeof (int)); 
        iin = a->surf[q][4];
        result.write((char*)&iin, sizeof (int)); 
        }
    }

// ------------
// GCD
    for(q=0;q<a->surfcount;q++)
    {
    i=a->surf[q][0];
    j=a->surf[q][1];
    k=a->surf[q][2];
    n=a->subgrid(i,j,k);
    
        if(n==count)
        {
        ddn = a->gcd[q];
        result.write((char*)&ddn, sizeof (double));
        }
    }
    
// --------------------------------------------------------------------------------------------------------------
// CC POINTS
    for(q=0;q<a->ccptnum[count];q++)
    {
    ddn = a->ccloc[count][q][0]+p->xmin;
    result.write((char*)&ddn, sizeof (double));
    ddn = a->ccloc[count][q][1]+p->ymin;
    result.write((char*)&ddn, sizeof (double));
    ddn = a->ccloc[count][q][2]+p->zmin;
    result.write((char*)&ddn, sizeof (double));
    }

// --------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------
// CC FACETS

    LOOP
    if(a->subgrid(i,j,k)==count && a->numfac(i,j,k)>0)
    {
    q=a->confac(i,j,k);
    iin = i-a->xnode[aa-1];
    result.write((char*)&iin, sizeof (int));  
    iin = j-a->ynode[bb-1];
    result.write((char*)&iin, sizeof (int));  
    iin = k-a->znode[cc-1];
    result.write((char*)&iin, sizeof (int));  
    
    iin = a->surfdir[q][0];
    result.write((char*)&iin, sizeof (int));  
    iin = a->surfdir[q][1];
    result.write((char*)&iin, sizeof (int));  
    iin = a->surfdir[q][2];
    result.write((char*)&iin, sizeof (int)); 
    
    ddn = a->gcn[q][0];
    result.write((char*)&ddn, sizeof (double));
    ddn = a->gcn[q][1];
    result.write((char*)&ddn, sizeof (double));
    ddn = a->gcn[q][2];
    result.write((char*)&ddn, sizeof (double));
    
    iin = a->numfac(i,j,k);
    result.write((char*)&iin, sizeof (int));  

        for(qq=0;qq<a->numfac(i,j,k);qq++)
        {
        iin = a->facet[q][qq];
        result.write((char*)&iin, sizeof (int));  
        }
    }

// --------------------------------------------------------------------------------------------------------------
// Parasurface

    for(q=0;q<a->para1count;q++)
    {
    i=a->para1sf[q][0];
    j=a->para1sf[q][1];
    k=a->para1sf[q][2];
    n=a->subgrid(i,j,k);

        if(n==count)
        {
        iin = i-a->xnode[aa-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = j-a->ynode[bb-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = k-a->znode[cc-1];
        result.write((char*)&iin, sizeof (int)); 
        }
    }

    for(q=0;q<a->para2count;q++)
    {
    i=a->para2sf[q][0];
    j=a->para2sf[q][1];
    k=a->para2sf[q][2];
    n=a->subgrid(i,j,k);
        
        if(n==count)
        {
        iin = i-a->xnode[aa-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = j-a->ynode[bb-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = k-a->znode[cc-1];
        result.write((char*)&iin, sizeof (int)); 
        }
    }

    for(q=0;q<a->para3count;q++)
    {
    i=a->para3sf[q][0];
    j=a->para3sf[q][1];
    k=a->para3sf[q][2];
    n=a->subgrid(i,j,k);
        
        if(n==count)
        {
        iin = i-a->xnode[aa-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = j-a->ynode[bb-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = k-a->znode[cc-1];
        result.write((char*)&iin, sizeof (int)); 
        }
    }

    for(q=0;q<a->para4count;q++)
    {
    i=a->para4sf[q][0];
    j=a->para4sf[q][1];
    k=a->para4sf[q][2];
    n=a->subgrid(i,j,k);
        
        if(n==count)
        {
        iin = i-a->xnode[aa-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = j-a->ynode[bb-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = k-a->znode[cc-1];
        result.write((char*)&iin, sizeof (int)); 
        }    
    }

    for(q=0;q<a->para5count;q++)
    {
    i=a->para5sf[q][0];
    j=a->para5sf[q][1];
    k=a->para5sf[q][2];
    n=a->subgrid(i,j,k);
    
        if(n==count)
        {
        iin = i-a->xnode[aa-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = j-a->ynode[bb-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = k-a->znode[cc-1];
        result.write((char*)&iin, sizeof (int)); 
        }
    }

    for(q=0;q<a->para6count;q++)
    {
    i=a->para6sf[q][0];
    j=a->para6sf[q][1];
    k=a->para6sf[q][2];
    n=a->subgrid(i,j,k);
    
        if(n==count)
        {
        iin = i-a->xnode[aa-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = j-a->ynode[bb-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = k-a->znode[cc-1];
        result.write((char*)&iin, sizeof (int)); 
        }
    }

// -----------------------------------------------------------------------------
// ParaVOIDsurface
	
    for(q=0;q<a->paravoid1count;q++)
    {
    i=a->para1void[q][0];
    j=a->para1void[q][1];
    k=a->para1void[q][2];
    n=a->subgrid(i,j,k);

        if(n==count)
        {
        iin = i-a->xnode[aa-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = j-a->ynode[bb-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = k-a->znode[cc-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = a->para1void[q][3];
        result.write((char*)&iin, sizeof (int)); 
        }
    }

    for(q=0;q<a->paravoid2count;q++)
    {
    i=a->para2void[q][0];
    j=a->para2void[q][1];
    k=a->para2void[q][2];
    n=a->subgrid(i,j,k);
        
        if(n==count)
        {
        iin = i-a->xnode[aa-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = j-a->ynode[bb-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = k-a->znode[cc-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = a->para2void[q][3];
        result.write((char*)&iin, sizeof (int)); 
        }
    }

    for(q=0;q<a->paravoid3count;q++)
    {
    i=a->para3void[q][0];
    j=a->para3void[q][1];
    k=a->para3void[q][2];
    n=a->subgrid(i,j,k);
        
        if(n==count)
        {
        iin = i-a->xnode[aa-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = j-a->ynode[bb-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = k-a->znode[cc-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = a->para3void[q][3];
        result.write((char*)&iin, sizeof (int)); 
        }
    }

    for(q=0;q<a->paravoid4count;q++)
    {
    i=a->para4void[q][0];
    j=a->para4void[q][1];
    k=a->para4void[q][2];
    n=a->subgrid(i,j,k);
    
        if(n==count)
        {
        iin = i-a->xnode[aa-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = j-a->ynode[bb-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = k-a->znode[cc-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = a->para4void[q][3];
        result.write((char*)&iin, sizeof (int)); 
        }
    }

    for(q=0;q<a->paravoid5count;q++)
    {
    i=a->para5void[q][0];
    j=a->para5void[q][1];
    k=a->para5void[q][2];
    n=a->subgrid(i,j,k);
    
        if(n==count)
        {
        iin = i-a->xnode[aa-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = j-a->ynode[bb-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = k-a->znode[cc-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = a->para5void[q][3];
        result.write((char*)&iin, sizeof (int)); 
        }
    }

    for(q=0;q<a->paravoid6count;q++)
    {
    i=a->para6void[q][0];
    j=a->para6void[q][1];
    k=a->para6void[q][2];
    n=a->subgrid(i,j,k);
        
        if(n==count)
        {
        iin = i-a->xnode[aa-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = j-a->ynode[bb-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = k-a->znode[cc-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = a->para6void[q][3];
        result.write((char*)&iin, sizeof (int)); 
        }
    }

// -----------------------------------------------------------------------------
    // Para Corners
    for(q=0;q<a->paraco1count;q++)
    {
    i=a->para1co[q][0];
    j=a->para1co[q][1];
    k=a->para1co[q][2];
    n=a->para1co[q][3];

        if(n==count)
        {
        iin = i-a->xnode[aa-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = j-a->ynode[bb-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = k-a->znode[cc-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = a->para1co[q][4];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = a->para1co[q][5];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = a->para1co[q][6];
        result.write((char*)&iin, sizeof (int)); 
        }
    }

    for(q=0;q<a->paraco2count;q++)
    {
    i=a->para2co[q][0];
    j=a->para2co[q][1];
    k=a->para2co[q][2];
    n=a->para2co[q][3];
        
        if(n==count)
        {
        iin = i-a->xnode[aa-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = j-a->ynode[bb-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = k-a->znode[cc-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = a->para2co[q][4];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = a->para2co[q][5];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = a->para2co[q][6];
        result.write((char*)&iin, sizeof (int)); 
        }
    }
	
    for(q=0;q<a->paraco3count;q++)
    {
    i=a->para3co[q][0];
    j=a->para3co[q][1];
    k=a->para3co[q][2];
    n=a->para3co[q][3];
        
        if(n==count)
        {
        iin = i-a->xnode[aa-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = j-a->ynode[bb-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = k-a->znode[cc-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = a->para3co[q][4];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = a->para3co[q][5];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = a->para3co[q][6];
        result.write((char*)&iin, sizeof (int)); 
        }
    }

    for(q=0;q<a->paraco4count;q++)
    {
    i=a->para4co[q][0];
    j=a->para4co[q][1];
    k=a->para4co[q][2];
    n=a->para4co[q][3];
        
        if(n==count)
        {
        iin = i-a->xnode[aa-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = j-a->ynode[bb-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = k-a->znode[cc-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = a->para4co[q][4];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = a->para4co[q][5];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = a->para4co[q][6];
        result.write((char*)&iin, sizeof (int)); 
        }
    }

    for(q=0;q<a->paraco5count;q++)
    {
    i=a->para5co[q][0];
    j=a->para5co[q][1];
    k=a->para5co[q][2];
    n=a->para5co[q][3];
        
        if(n==count)
        {
        iin = i-a->xnode[aa-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = j-a->ynode[bb-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = k-a->znode[cc-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = a->para5co[q][4];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = a->para5co[q][5];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = a->para5co[q][6];
        result.write((char*)&iin, sizeof (int)); 
        }
    }

    for(q=0;q<a->paraco6count;q++)
    {
    i=a->para6co[q][0];
    j=a->para6co[q][1];
    k=a->para6co[q][2];
    n=a->para6co[q][3];

        if(n==count)
        {
        iin = i-a->xnode[aa-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = j-a->ynode[bb-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = k-a->znode[cc-1];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = a->para6co[q][4];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = a->para6co[q][5];
        result.write((char*)&iin, sizeof (int)); 
        
        iin = a->para6co[q][6];
        result.write((char*)&iin, sizeof (int)); 
        }
    }
	
// --------------------------------------------------------------------------------------------------------------
//Slice

    k=z1;
    XYLOOP
    if(a->subgrid(i,j,k)==count)
    {
    iin = a->flagslice(i,j);
    result.write((char*)&iin, sizeof (int)); 
    }
    
// --------------------------------------------------------------------------------------------------------------
// Paraslicesurface

    for(q=0;q<a->paraslice1count;q++)
    {
    i=a->paraslice1sf[q][0];
    j=a->paraslice1sf[q][1];
    n=a->subslice(i,j);
    
        if(n==count)
        {
        iin = i-a->xnode[aa-1];
        result.write((char*)&iin, sizeof (int));
        iin = j-a->ynode[bb-1];
        result.write((char*)&iin, sizeof (int)); 
        }
    }

    for(q=0;q<a->paraslice2count;q++)
    {
    i=a->paraslice2sf[q][0];
    j=a->paraslice2sf[q][1];
    n=a->subslice(i,j);
        
        if(n==count)
        {
        iin = i-a->xnode[aa-1];
        result.write((char*)&iin, sizeof (int));
        iin = j-a->ynode[bb-1];
        result.write((char*)&iin, sizeof (int)); 
        }
    }

    for(q=0;q<a->paraslice3count;q++)
    {
    i=a->paraslice3sf[q][0];
    j=a->paraslice3sf[q][1];
    n=a->subslice(i,j);
        
        if(n==count)
        {
        iin = i-a->xnode[aa-1];
        result.write((char*)&iin, sizeof (int));
        iin = j-a->ynode[bb-1];
        result.write((char*)&iin, sizeof (int)); 
        }
    }

    for(q=0;q<a->paraslice4count;q++)
    {
    i=a->paraslice4sf[q][0];
    j=a->paraslice4sf[q][1];
    n=a->subslice(i,j);
        
        if(n==count)
        {
        iin = i-a->xnode[aa-1];
        result.write((char*)&iin, sizeof (int));
        iin = j-a->ynode[bb-1];
        result.write((char*)&iin, sizeof (int)); 
        }
    }


// --------------------------------------------------------------------------------------------------------------
// Paracoslicesurface

    for(q=0;q<a->paracoslice1count;q++)
    {
    i=a->paracoslice1sf[q][0];
    j=a->paracoslice1sf[q][1];
    n=a->paracoslice1sf[q][2];

        if(n==count)
        {
        iin = i-a->xnode[aa-1];
        result.write((char*)&iin, sizeof (int));
        iin = j-a->ynode[bb-1];
        result.write((char*)&iin, sizeof (int)); 
        iin = a->paracoslice1sf[q][3];
        result.write((char*)&iin, sizeof (int)); 
        }
    }

    for(q=0;q<a->paracoslice2count;q++)
    {
    i=a->paracoslice2sf[q][0];
    j=a->paracoslice2sf[q][1];
    n=a->paracoslice2sf[q][2];
        
        if(n==count)
        {
        iin = i-a->xnode[aa-1];
        result.write((char*)&iin, sizeof (int));
        iin = j-a->ynode[bb-1];
        result.write((char*)&iin, sizeof (int)); 
        iin = a->paracoslice2sf[q][3];
        result.write((char*)&iin, sizeof (int)); 
        }
    }

    for(q=0;q<a->paracoslice3count;q++)
    {
    i=a->paracoslice3sf[q][0];
    j=a->paracoslice3sf[q][1];
    n=a->paracoslice3sf[q][2];
        
        if(n==count)
        {
        iin = i-a->xnode[aa-1];
        result.write((char*)&iin, sizeof (int));
        iin = j-a->ynode[bb-1];
        result.write((char*)&iin, sizeof (int)); 
        iin = a->paracoslice3sf[q][3];
        result.write((char*)&iin, sizeof (int)); 
        }
    }

    for(q=0;q<a->paracoslice4count;q++)
    {
    i=a->paracoslice4sf[q][0];
    j=a->paracoslice4sf[q][1];
    n=a->paracoslice4sf[q][2];
    
        if(n==count)
        {
        iin = i-a->xnode[aa-1];
        result.write((char*)&iin, sizeof (int));
        iin = j-a->ynode[bb-1];
        result.write((char*)&iin, sizeof (int)); 
        iin = a->paracoslice4sf[q][3];
        result.write((char*)&iin, sizeof (int)); 
        }
    }


// ---------------------------------------------------------------------------------------------------------------------
//GEODAT
// *********************
    k=z1;
	if(p->G10>0)
    XYLOOP
    if(a->subgrid(i,j,k)==count)
    {
    ddn = a->topo(i,j);
    result.write((char*)&ddn, sizeof (double)); 
    }
	
//DATA INTERPOLATION
// *********************
    k=z1;
	if(p->D10>0)
    XYLOOP
    if(a->subgrid(i,j,k)==count)
    {
    ddn = a->data(i,j);
    result.write((char*)&ddn, sizeof (double)); 
    }
    
//Bedlevels
// *********************
    k=z1;
    XYLOOP
    if(a->subgrid(i,j,k)==count)
    if(a->subgrid(i,j,k)==count)
    {
    ddn = a->bedlevel(i,j);
    result.write((char*)&ddn, sizeof (double)); 
    }
    
result.close();

cout<<".";

}

cout<<endl;

}



















