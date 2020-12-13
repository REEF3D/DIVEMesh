/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2020 Hans Bihs

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

#include<iostream>
#include"lexer.h"
#include"field.h"
#include"intfield.h"
#include"increment.h"
#include"field2d.h"
#include"intfield2d.h"

using namespace std;
 
#ifndef DIVE_H_
#define DIVE_H_

class dive : public increment, public resize_class
{
 public:

    dive(lexer*);
    virtual ~dive();
    void initialize();

    intfield flag;         // water/soC12/empty  +  which bc
	intfield solid;
    field solid_dist;
    intfield cellside;     // cellside
    intfield subgrid;      // for all water cells: number of subgrid
    intfield numfac;       // number of points per facet
    intfield confac;       // connects facet index to ijk
    intfield xdir,ydir,zdir;
	intfield onnode;
    field2d topo,data,bedlevel;
    intfield2d flagslice,subslice;

    int knox,knoy,knoz;
    int maxknox;
    int incount,utcount,fsfcount,bedcount,surfcount,surfcount_solid,surfnum_solid;
    int facetcount,ccpointcount;
    int **surf,**surf_solid;
    int *in,*ut,*fsf,*bed,*wall;                                // surface counter
    int *subknox,*subknoy,*subknoz;
	int i_dir,j_dir,k_dir;

	//domain decomp
	int *mpx,*mpy,*mpz;                                         // possible subgrids in each directions
    int mx,my,mz;                                               // final subgrids in each direction

	double *xorig,*yorig,*zorig;                                // origin in [m] for each subgrid
    int *xnode,*ynode,*znode;                                   // origin of subgrids in ijk in large grid

    int para1count,para2count,para3count,para4count,para5count,para6count;
    int paraslice1count,paraslice2count,paraslice3count,paraslice4count;
    int paracoslice1count,paracoslice2count,paracoslice3count,paracoslice4count;
    int paraco1count,paraco2count,paraco3count,paraco4count,paraco5count,paraco6count;
    int **para1sf,**para2sf,**para3sf,**para4sf,**para5sf,**para6sf;
    int **paraslice1sf,**paraslice2sf,**paraslice3sf,**paraslice4sf;
	int **para1void,**para2void,**para3void,**para4void,**para5void,**para6void;
    int **para1co,**para2co,**para3co,**para4co,**para5co,**para6co;
    int **paracoslice1sf,**paracoslice2sf,**paracoslice3sf,**paracoslice4sf;
    int *para1,*para2,*para3,*para4,*para5,*para6;              // para surface counter
    int *paraco1,*paraco2,*paraco3,*paraco4,*paraco5,*paraco6;
    int *paraslice1,*paraslice2,*paraslice3,*paraslice4;              // paraslice surface counter
    int *paracoslice1,*paracoslice2,*paracoslice3,*paracoslice4; 
    int *nbpara1,*nbpara2,*nbpara3,*nbpara4,*nbpara5,*nbpara6;  // neigbours for each subgrid

    int*** sgfield;
    
    int **periodicX,*periodicXall;

    //ibm
    int **facet,**dirfac;
    double **ccpoint;
    int *ccmem;
    double ***ccloc;
    int *ccptnum, *facetnum, *ccstatenum;
    int *ccstate;
    int maxsurf;
    int **surfdir;
    double **gcn;
    double *gcd;
	int *mpi_index, *mpi_edges, mpi_edgenum;
	int *solid_gcb,*geodat_gcb;
	
	//polygon objects
	int vertice_num, polygon_num,vnum;
	int **polygon,*numvert,*polygon_offset,polygon_sum;
	double **vertice;
	
	
	// MG
	int ***paramg1,***paramg2,***paramg3,***paramg4,***paramg5,***paramg6;
	int *paramg1_count,*paramg2_count,*paramg3_count,*paramg4_count,*paramg5_count,*paramg6_count;
	int **paramgsub1,**paramgsub2,**paramgsub3,**paramgsub4,**paramgsub5,**paramgsub6;
	int maxcoarse,maxlevels;
	int *mgx,*mgy,*mgz;
	int **submgx,**submgy,**submgz;
	int **xoff,**yoff,**zoff;
	int *magx,*magy,*magz;
	int **submg;

};


#endif
