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

#include"print_grid.h"
#include"lexer.h"
#include"dive.h"
#include<iostream>
#include<fstream>
#include<sys/stat.h>
#include<sys/types.h>
#include<iomanip>
#include<vector>
#include<cstring>

#ifdef _OPENMP
#include <omp.h>
#endif

using namespace std;

print_grid::print_grid(lexer* p)
{
    mkdir("./DIVEMesh_Grid",0777);
}

void print_grid::start(lexer* p,dive* a)
{    
    if(p->G41==1 && p->G10>0)
        print_bottom(p,a);
	
	cout<<"printing ";
	
	#pragma omp parallel for collapse(3) schedule(dynamic)
    for(int aa=1;aa<=a->mx;++aa)
    for(int bb=1;bb<=a->my;++bb)
    for(int cc=1;cc<=a->mz;++cc)
    {
        int i = 0;
        int j = 0;
        int k = 0;
        int n = 0;
        int q = 0;
        int iin = 0;
        double ddn = 0.0;
        const int count = ((aa-1)*a->my + (bb-1))*a->mz + cc;

        std::vector<char> buffer;
        size_t size = 16*sizeof(double)+74*sizeof(int)
                    +((a->xnode[aa]-a->xnode[aa-1])*(a->ynode[bb]-a->ynode[bb-1])*(a->znode[cc]-a->znode[cc-1]))*sizeof(int)
                    +(a->xnode[aa]+marge-(a->xnode[aa-1]-marge))*sizeof(double)*2
                    +(a->ynode[bb]+marge-(a->ynode[bb-1]-marge))*sizeof(double)*2
                    +(a->znode[cc]+marge-(a->znode[cc-1]-marge))*sizeof(double)*2
                    +((a->xnode[aa]-a->xnode[aa-1])*(a->ynode[bb]-a->ynode[bb-1])*(a->znode[cc]-a->znode[cc-1]))*2*sizeof(double)
                    +a->surfcount*5*sizeof(int)
                    +a->para1count*3*sizeof(int)
                    +a->para2count*3*sizeof(int)
                    +a->para3count*3*sizeof(int)
                    +a->para4count*3*sizeof(int)
                    +a->para5count*3*sizeof(int)
                    +a->para6count*3*sizeof(int)
                    +a->paraco1count*6*sizeof(int)
                    +a->paraco2count*6*sizeof(int)
                    +a->paraco3count*6*sizeof(int)
                    +a->paraco4count*6*sizeof(int)
                    +a->paraco5count*6*sizeof(int)
                    +a->paraco6count*6*sizeof(int)
                    +a->knox*a->knoy*sizeof(int)
                    +a->paraslice1count*2*sizeof(int)
                    +a->paraslice2count*2*sizeof(int)
                    +a->paraslice3count*2*sizeof(int)
                    +a->paraslice4count*2*sizeof(int)
                    +a->paracoslice1count*3*sizeof(int)
                    +a->paracoslice2count*3*sizeof(int)
                    +a->paracoslice3count*3*sizeof(int)
                    +a->paracoslice4count*3*sizeof(int)
                    +a->knox*a->knoy*4*sizeof(double);
        buffer.resize(size);
        size_t m=0;

        //HEADER
        iin = p->M10;
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        
        
        iin = a->subknox[count];
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        iin = a->subknoy[count];
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        iin = a->subknoz[count];
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        
        
        ddn = p->DXM;
        std::memcpy(&buffer[m],&ddn,sizeof(double));
        m+=sizeof(double);
        
        ddn = p->DR;
        std::memcpy(&buffer[m],&ddn,sizeof(double));
        m+=sizeof(double);
        ddn = p->DS;
        std::memcpy(&buffer[m],&ddn,sizeof(double));
        m+=sizeof(double);
        ddn = p->DT;
        std::memcpy(&buffer[m],&ddn,sizeof(double));
        m+=sizeof(double);
        
        
        ddn = a->xorig[aa-1];
        std::memcpy(&buffer[m],&ddn,sizeof(double));
        m+=sizeof(double);
        ddn = a->yorig[bb-1];
        std::memcpy(&buffer[m],&ddn,sizeof(double));
        m+=sizeof(double);
        ddn = a->zorig[cc-1];
        std::memcpy(&buffer[m],&ddn,sizeof(double));
        m+=sizeof(double);
        ddn = a->xorig[aa];
        std::memcpy(&buffer[m],&ddn,sizeof(double));
        m+=sizeof(double);
        ddn = a->yorig[bb];
        std::memcpy(&buffer[m],&ddn,sizeof(double));
        m+=sizeof(double);
        ddn = a->zorig[cc];
        std::memcpy(&buffer[m],&ddn,sizeof(double));
        m+=sizeof(double);


        ddn = p->xmin;
        std::memcpy(&buffer[m],&ddn,sizeof(double));
        m+=sizeof(double);
        ddn = p->ymin;
        std::memcpy(&buffer[m],&ddn,sizeof(double));
        m+=sizeof(double);
        ddn = p->zmin;
        std::memcpy(&buffer[m],&ddn,sizeof(double));
        m+=sizeof(double);
        ddn = p->xmax;
        std::memcpy(&buffer[m],&ddn,sizeof(double));
        m+=sizeof(double);
        ddn = p->ymax;
        std::memcpy(&buffer[m],&ddn,sizeof(double));
        m+=sizeof(double);
        ddn = p->zmax;
        std::memcpy(&buffer[m],&ddn,sizeof(double));
        m+=sizeof(double);

        
        iin = a->knox;
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        iin = a->knoy;
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        iin = a->knoz;
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        
        
        iin = a->xnode[aa-1];
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        iin = a->ynode[bb-1];
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        iin = a->znode[cc-1];
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        
        
        iin = a->wall[count];
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);

        iin = a->para1[count];
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        iin = a->para2[count];
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        iin = a->para3[count];
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        iin = a->para4[count];
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        iin = a->para5[count];
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        iin = a->para6[count];
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        
        iin = a->paraco1[count];
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        iin = a->paraco2[count];
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        iin = a->paraco3[count];
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        iin = a->paraco4[count];
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        iin = a->paraco5[count];
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        iin = a->paraco6[count];
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        
        iin = a->paraslice1[count];
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        iin = a->paraslice2[count];
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        iin = a->paraslice3[count];
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        iin = a->paraslice4[count];
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        
        iin = a->paracoslice1[count];
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        iin = a->paracoslice2[count];
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        iin = a->paracoslice3[count];
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        iin = a->paracoslice4[count];
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        
        
        iin = a->nbpara1[count];
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        iin = a->nbpara2[count];
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        iin = a->nbpara3[count];
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        iin = a->nbpara4[count];
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        iin = a->nbpara5[count];
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        iin = a->nbpara6[count];
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        
        
        iin = a->mx;
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        iin = a->my;
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        iin = a->mz;
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        
        iin = aa-1; // dead
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        iin = bb-1; // dead
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        iin = cc-1; // dead
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        
        iin = p->C11;
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        iin = p->C12;
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        iin = p->C13;
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        iin = p->C14;
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        iin = p->C15;
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        iin = p->C16;
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        
        iin = p->C21;
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        iin = p->C22;
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        iin = p->C23;
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        
        iin = a->periodicX[count][0];
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        iin = a->periodicX[count][1];
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        iin = a->periodicX[count][2];
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        iin = a->periodicX[count][3];
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        iin = a->periodicX[count][4];
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        iin = a->periodicX[count][5];
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        
        iin = a->i_dir;
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);  
        iin = a->j_dir;
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);  
        iin = a->k_dir;
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);  
        
        iin = p->D10;
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);  
        
        
        iin = p->solidprint;    // write solid
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);  
        iin = p->topoprint; //write topo
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        iin = a->solid_gcb[count-1];
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);    
        iin = a->topo_gcb[count-1];
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);  
        
        iin = a->solid_gcbextra[count-1];
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);  
        iin = a->topo_gcbextra[count-1];
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);  
        iin = a->tot_gcbextra[count-1];
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);  
        
        
        iin = p->porousprint;    // write porous // dead
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        iin = 0; // dead
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);  
        iin = 0; // dead
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        iin = 0; // dead
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        iin = 0; // dead
        std::memcpy(&buffer[m],&iin,sizeof(int));
        m+=sizeof(int);
        
        // ---------------------------------------------------------------------------------------------------------------------
        // FLAG

        SUBLOOP
        {
            iin = a->flag(i,j,k);
            std::memcpy(&buffer[m],&iin,sizeof(int));
            m+=sizeof(int);  
        }
        
        // ---------------------------------------------------------------------------------------------------------------------
        // Nodes XYZ
        SNODEILOOP
        {
            ddn = p->XN[IP];
            std::memcpy(&buffer[m],&ddn,sizeof(double));
            m+=sizeof(double);
        }
        
        SNODEJLOOP
        {
            ddn = p->YN[JP];
            std::memcpy(&buffer[m],&ddn,sizeof(double));
            m+=sizeof(double);
        }
        
        SNODEKLOOP
        {
            ddn = p->ZN[KP];
            std::memcpy(&buffer[m],&ddn,sizeof(double));
            m+=sizeof(double);
        }

        // ---------------------------------------------------------------------------------------------------------------------
        // Nodes RST
        SNODEILOOP
        {
            ddn = p->RN[IP];
            std::memcpy(&buffer[m],&ddn,sizeof(double));
            m+=sizeof(double);
        }
        
        SNODEJLOOP
        {
            ddn = p->SN[JP];
            std::memcpy(&buffer[m],&ddn,sizeof(double));
            m+=sizeof(double);
        }
        
        SNODEKLOOP
        {
            ddn = p->TN[KP];
            std::memcpy(&buffer[m],&ddn,sizeof(double));
            m+=sizeof(double);
        }

        // ---------------------------------------------------------------------------------------------------------------------
        // solid_dist
        
        if(p->solidprint==1)
        SUBLOOP
        {
            ddn = a->solid_dist(i,j,k);
            std::memcpy(&buffer[m],&ddn,sizeof(double));
            m+=sizeof(double);
        }
        
        // topo_dist
        
        if(p->topoprint==1)
        SUBLOOP
        {
            ddn = a->topo_dist(i,j,k);
            std::memcpy(&buffer[m],&ddn,sizeof(double));
            m+=sizeof(double);
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
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                iin = j-a->ynode[bb-1];
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                iin = k-a->znode[cc-1];
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                iin = a->surf[q][3]; // side
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                iin = a->surf[q][4]; // group
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
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
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                
                iin = j-a->ynode[bb-1];
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                
                iin = k-a->znode[cc-1];
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
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
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                
                iin = j-a->ynode[bb-1];
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                
                iin = k-a->znode[cc-1];
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
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
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                
                iin = j-a->ynode[bb-1];
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                
                iin = k-a->znode[cc-1];
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
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
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                
                iin = j-a->ynode[bb-1];
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                
                iin = k-a->znode[cc-1];
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
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
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                
                iin = j-a->ynode[bb-1];
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                
                iin = k-a->znode[cc-1];
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
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
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                
                iin = j-a->ynode[bb-1];
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                
                iin = k-a->znode[cc-1];
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
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
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                
                iin = j-a->ynode[bb-1];
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                
                iin = k-a->znode[cc-1];
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                
                iin = a->para1co[q][4]; // dead
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                
                iin = a->para1co[q][5]; // dead
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                
                iin = a->para1co[q][6]; // dead
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
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
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                
                iin = j-a->ynode[bb-1];
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                
                iin = k-a->znode[cc-1];
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                
                iin = a->para2co[q][4]; // dead
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                
                iin = a->para2co[q][5]; // dead
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                
                iin = a->para2co[q][6]; // dead
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
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
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                
                iin = j-a->ynode[bb-1];
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                
                iin = k-a->znode[cc-1];
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                
                iin = a->para3co[q][4]; // dead
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                
                iin = a->para3co[q][5]; // dead
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                
                iin = a->para3co[q][6]; // dead
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
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
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                
                iin = j-a->ynode[bb-1];
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                
                iin = k-a->znode[cc-1];
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                
                iin = a->para4co[q][4]; // dead
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                
                iin = a->para4co[q][5]; // dead
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                
                iin = a->para4co[q][6]; // dead
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
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
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                
                iin = j-a->ynode[bb-1];
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                
                iin = k-a->znode[cc-1];
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                
                iin = a->para5co[q][4]; // dead
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                
                iin = a->para5co[q][5]; // dead
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                
                iin = a->para5co[q][6]; // dead
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
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
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                
                iin = j-a->ynode[bb-1];
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                
                iin = k-a->znode[cc-1];
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                
                iin = a->para6co[q][4]; // dead
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                
                iin = a->para6co[q][5]; // dead
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                
                iin = a->para6co[q][6]; // dead
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
            }
        }
        
        // --------------------------------------------------------------------------------------------------------------
        //Slice

        k=0;
        XYLOOP
        if(a->subgrid(i,j,k)==count)
        {
            iin = a->flagslice(i,j);
            std::memcpy(&buffer[m],&iin,sizeof(int));
            m+=sizeof(int);
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
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                iin = j-a->ynode[bb-1];
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
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
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                iin = j-a->ynode[bb-1];
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
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
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                iin = j-a->ynode[bb-1];
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
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
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                iin = j-a->ynode[bb-1];
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
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
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                iin = j-a->ynode[bb-1];
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                iin = a->paracoslice1sf[q][3]; // dead
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
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
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                iin = j-a->ynode[bb-1];
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                iin = a->paracoslice2sf[q][3]; // dead
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
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
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                iin = j-a->ynode[bb-1];
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                iin = a->paracoslice3sf[q][3]; // dead
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
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
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                iin = j-a->ynode[bb-1];
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
                iin = a->paracoslice4sf[q][3]; // dead
                std::memcpy(&buffer[m],&iin,sizeof(int));
                m+=sizeof(int);
            }
        }


        // ---------------------------------------------------------------------------------------------------------------------
        //Bedlevels
        // *********************
        XYLOOP
        if(a->subgrid(i,j,k)==count)
        if(a->subgrid(i,j,k)==count)
        {
            ddn = a->bedlevel(i,j);
            std::memcpy(&buffer[m],&ddn,sizeof(double));
            m+=sizeof(double);
        }

        //GEODAT
        // *********************
        if(p->solidprint>0)
        XYLOOP
        if(a->subgrid(i,j,k)==count)
        if(a->subgrid(i,j,k)==count)
        {
            ddn = a->solidbed(i,j);
            std::memcpy(&buffer[m],&ddn,sizeof(double));
            m+=sizeof(double);
        }
        
        if(p->topoprint>0)
        XYLOOP
        if(a->subgrid(i,j,k)==count)
        if(a->subgrid(i,j,k)==count)
        {
            ddn = a->topobed(i,j);
            std::memcpy(&buffer[m],&ddn,sizeof(double));
            m+=sizeof(double);
        }
        
        //DATA INTERPOLATION
        // *********************
        k=0;
        if(p->D10>0)
        XYLOOP
        if(a->subgrid(i,j,k)==count)
        {
            ddn = a->dataset(i,j);
            std::memcpy(&buffer[m],&ddn,sizeof(double));
            m+=sizeof(double);
        }

        buffer.resize(m);

        char name[100];
        const int padding = 6;
        sprintf(name,"DIVEMesh_Grid/grid-%0*i.dat",padding,count);

        FILE* file = fopen(name, "wb");
        if(file)
        {
            setvbuf(file, nullptr, _IOFBF, 131072);
            fwrite(buffer.data(), buffer.size(), 1, file);
            fclose(file);
        }

        #pragma omp critical
        {
            cout<<".";
        }
    }

    cout<<"\nprinting complete\n"
        <<"__________________________________________\n"<<endl;
}
