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
#include<span>
#include<algorithm>

#ifdef _OPENMP
#include <omp.h>
#endif

using namespace std;

namespace
{
    // indices 0..num-1 grouped by a key 1..nsub; each group keeps ascending order
    struct index_lists
    {
        std::vector<int> start, idx;

        template<class Key>
        void build(int nsub, int num, Key key)
        {
            start.assign(nsub+2,0);

            for(int q=0;q<num;++q)
            {
                const int n=key(q);
                if(n>=1 && n<=nsub)
                ++start[n+1];
            }

            for(int n=1;n<nsub+2;++n)
            start[n]+=start[n-1];

            idx.resize(start[nsub+1]);
            std::vector<int> pos(start.begin(),start.end());

            for(int q=0;q<num;++q)
            {
                const int n=key(q);
                if(n>=1 && n<=nsub)
                idx[pos[n]++]=q;
            }
        }

        std::span<const int> list(int n) const { return {idx.data()+start[n], idx.data()+start[n+1]}; }
        size_t size(int n) const { return size_t(start[n+1]-start[n]); }
    };

    struct subdomain_lists
    {
        index_lists surf, slice;
        index_lists para[6], paraco[6];
        index_lists paraslice[4], paracoslice[4];
    };
}

print_grid::print_grid(lexer* p)
{
    mkdir("./DIVEMesh_Grid",0777);
}

void print_grid::start(lexer* p,dive* a)
{
    if(p->G41==1 && p->G10>0)
        print_bottom(p,a);

    cout<<"printing ";

    int write_errors=0;

    // entries of every surface list, sorted by subdomain (stable, keeps the original order)
    const int nsub = a->mx*a->my*a->mz;
    subdomain_lists bk;
    bk.surf.build(nsub,a->surfcount,[&](int q){return a->subgrid(a->surf[q][0],a->surf[q][1],a->surf[q][2]);});

    int **parasf[6] = {a->para1sf,a->para2sf,a->para3sf,a->para4sf,a->para5sf,a->para6sf};
    int **paraco[6] = {a->para1co,a->para2co,a->para3co,a->para4co,a->para5co,a->para6co};
    const int paracount[6] = {a->para1count,a->para2count,a->para3count,a->para4count,a->para5count,a->para6count};
    const int paracocount[6] = {a->paraco1count,a->paraco2count,a->paraco3count,a->paraco4count,a->paraco5count,a->paraco6count};

    for(int d=0;d<6;++d)
    {
        int **sf=parasf[d], **co=paraco[d];
        bk.para[d].build(nsub,paracount[d],[&](int q){return a->subgrid(sf[q][0],sf[q][1],sf[q][2]);});
        bk.paraco[d].build(nsub,paracocount[d],[&](int q){return co[q][3];});
    }

    int **paraslicesf[4] = {a->paraslice1sf,a->paraslice2sf,a->paraslice3sf,a->paraslice4sf};
    int **paracoslicesf[4] = {a->paracoslice1sf,a->paracoslice2sf,a->paracoslice3sf,a->paracoslice4sf};
    const int paraslicecount[4] = {a->paraslice1count,a->paraslice2count,a->paraslice3count,a->paraslice4count};
    const int paracoslicecount[4] = {a->paracoslice1count,a->paracoslice2count,a->paracoslice3count,a->paracoslice4count};

    for(int d=0;d<4;++d)
    {
        int **sf=paraslicesf[d], **co=paracoslicesf[d];
        bk.paraslice[d].build(nsub,paraslicecount[d],[&](int q){return a->subslice(sf[q][0],sf[q][1]);});
        bk.paracoslice[d].build(nsub,paracoslicecount[d],[&](int q){return co[q][2];});
    }

    // x-y cells (index i*knoy+j) by the subdomain of their bottom cell k=0
    bk.slice.build(nsub,a->knox*a->knoy,[&](int c){return a->subgrid(c/a->knoy,c%a->knoy,0);});

    #pragma omp parallel for collapse(3) schedule(dynamic)
    for(int aa=1;aa<=a->mx;++aa)
    for(int bb=1;bb<=a->my;++bb)
    for(int cc=1;cc<=a->mz;++cc)
    {
        int i = 0;
        int j = 0;
        int k = 0;
        int n = 0;
        const int count = ((aa-1)*a->my + (bb-1))*a->mz + cc;

        const size_t cells = size_t(a->xnode[aa]-a->xnode[aa-1])*size_t(a->ynode[bb]-a->ynode[bb-1])*size_t(a->znode[cc]-a->znode[cc-1]);
        const size_t nodes = size_t(a->xnode[aa]-a->xnode[aa-1] + a->ynode[bb]-a->ynode[bb-1] + a->znode[cc]-a->znode[cc-1] + 6*marge+3);

        size_t size = 32*sizeof(double) + 96*sizeof(int)
                    + cells*(sizeof(int) + 2*sizeof(double))
                    + nodes*sizeof(double)
                    + bk.surf.size(count)*5*sizeof(int)
                    + size_t(bk.slice.size(count))*(sizeof(int) + 4*sizeof(double));

        for(int d=0;d<6;++d)
        size += (bk.para[d].size(count)*3 + bk.paraco[d].size(count)*6)*sizeof(int);

        for(int d=0;d<4;++d)
        size += (bk.paraslice[d].size(count)*2 + bk.paracoslice[d].size(count)*3)*sizeof(int);

        std::vector<char> buffer(size);
        size_t m=0;

        auto put = [&](const void *val, size_t bytes)
        {
            if(m+bytes>buffer.size())
            buffer.resize(std::max(2*buffer.size(),m+bytes));

            std::memcpy(&buffer[m],val,bytes);
            m+=bytes;
        };
        auto put_int = [&](int val) { put(&val,sizeof(int)); };
        auto put_double = [&](double val) { put(&val,sizeof(double)); };

        //HEADER
        put_int(p->M10);


        put_int(a->subknox[count]);
        put_int(a->subknoy[count]);
        put_int(a->subknoz[count]);


        put_double(p->DXM);

        put_double(p->DR);
        put_double(p->DS);
        put_double(p->DT);


        put_double(a->xorig[aa-1]);
        put_double(a->yorig[bb-1]);
        put_double(a->zorig[cc-1]);
        put_double(a->xorig[aa]);
        put_double(a->yorig[bb]);
        put_double(a->zorig[cc]);


        put_double(p->xmin);
        put_double(p->ymin);
        put_double(p->zmin);
        put_double(p->xmax);
        put_double(p->ymax);
        put_double(p->zmax);


        put_int(a->knox);
        put_int(a->knoy);
        put_int(a->knoz);


        put_int(a->xnode[aa-1]);
        put_int(a->ynode[bb-1]);
        put_int(a->znode[cc-1]);


        put_int(a->wall[count]);

        put_int(a->para1[count]);
        put_int(a->para2[count]);
        put_int(a->para3[count]);
        put_int(a->para4[count]);
        put_int(a->para5[count]);
        put_int(a->para6[count]);

        put_int(a->paraco1[count]);
        put_int(a->paraco2[count]);
        put_int(a->paraco3[count]);
        put_int(a->paraco4[count]);
        put_int(a->paraco5[count]);
        put_int(a->paraco6[count]);

        put_int(a->paraslice1[count]);
        put_int(a->paraslice2[count]);
        put_int(a->paraslice3[count]);
        put_int(a->paraslice4[count]);

        put_int(a->paracoslice1[count]);
        put_int(a->paracoslice2[count]);
        put_int(a->paracoslice3[count]);
        put_int(a->paracoslice4[count]);


        put_int(a->nbpara1[count]);
        put_int(a->nbpara2[count]);
        put_int(a->nbpara3[count]);
        put_int(a->nbpara4[count]);
        put_int(a->nbpara5[count]);
        put_int(a->nbpara6[count]);


        put_int(a->mx);
        put_int(a->my);
        put_int(a->mz);

        put_int(aa-1); // dead
        put_int(bb-1); // dead
        put_int(cc-1); // dead

        put_int(p->C11);
        put_int(p->C12);
        put_int(p->C13);
        put_int(p->C14);
        put_int(p->C15);
        put_int(p->C16);

        put_int(p->C21);
        put_int(p->C22);
        put_int(p->C23);

        put_int(a->periodicX[count][0]);
        put_int(a->periodicX[count][1]);
        put_int(a->periodicX[count][2]);
        put_int(a->periodicX[count][3]);
        put_int(a->periodicX[count][4]);
        put_int(a->periodicX[count][5]);

        put_int(a->i_dir);
        put_int(a->j_dir);
        put_int(a->k_dir);

        put_int(p->D10);


        put_int(p->solidprint);    // write solid
        put_int(p->topoprint); //write topo
        put_int(a->solid_gcb[count-1]);
        put_int(a->topo_gcb[count-1]);

        put_int(a->solid_gcbextra[count-1]);
        put_int(a->topo_gcbextra[count-1]);
        put_int(a->tot_gcbextra[count-1]);


        put_int(p->porousprint);    // write porous // dead
        put_int(p->B6); // CMS on/off
        put_int(0); // dead
        put_int(0); // dead
        put_int(0); // dead

        put_double(p->global_orig_x);
        put_double(p->global_orig_y);
        put_double(p->alpha_grid);

        put_double(0.0); // dead
        put_double(0.0); // dead
        put_double(0.0); // dead

        // ---------------------------------------------------------------------------------------------------------------------
        // FLAG

        SUBLOOP
        {
            put_int(a->flag(i,j,k));
        }

        // ---------------------------------------------------------------------------------------------------------------------
        // Nodes XYZ
        SNODEILOOP
        {
            put_double(p->XN[IP]);
        }

        SNODEJLOOP
        {
            put_double(p->YN[JP]);
        }

        SNODEKLOOP
        {
            put_double(p->ZN[KP]);
        }

        // ---------------------------------------------------------------------------------------------------------------------
        // solid_dist

        if(p->solidprint==1)
        SUBLOOP
        {
            put_double(a->solid_dist(i,j,k));
        }

        // topo_dist

        if(p->topoprint==1)
        SUBLOOP
        {
            put_double(a->topo_dist(i,j,k));
        }

        // ---------------------------------------------------------------------------------------------------------------------
        //SURFACES

        for(const int q : bk.surf.list(count))
        {
            i=a->surf[q][0];
            j=a->surf[q][1];
            k=a->surf[q][2];
            n=a->subgrid(i,j,k);

            if(n==count)
            {
                put_int(i-a->xnode[aa-1]);
                put_int(j-a->ynode[bb-1]);
                put_int(k-a->znode[cc-1]);
                put_int(a->surf[q][3]); // side
                put_int(a->surf[q][4]); // group
            }
        }

        // --------------------------------------------------------------------------------------------------------------
        // Parasurface

        for(const int q : bk.para[0].list(count))
        {
            i=a->para1sf[q][0];
            j=a->para1sf[q][1];
            k=a->para1sf[q][2];
            n=a->subgrid(i,j,k);

            if(n==count)
            {
                put_int(i-a->xnode[aa-1]);

                put_int(j-a->ynode[bb-1]);

                put_int(k-a->znode[cc-1]);
            }
        }

        for(const int q : bk.para[1].list(count))
        {
            i=a->para2sf[q][0];
            j=a->para2sf[q][1];
            k=a->para2sf[q][2];
            n=a->subgrid(i,j,k);

            if(n==count)
            {
                put_int(i-a->xnode[aa-1]);

                put_int(j-a->ynode[bb-1]);

                put_int(k-a->znode[cc-1]);
            }
        }

        for(const int q : bk.para[2].list(count))
        {
            i=a->para3sf[q][0];
            j=a->para3sf[q][1];
            k=a->para3sf[q][2];
            n=a->subgrid(i,j,k);

            if(n==count)
            {
                put_int(i-a->xnode[aa-1]);

                put_int(j-a->ynode[bb-1]);

                put_int(k-a->znode[cc-1]);
            }
        }

        for(const int q : bk.para[3].list(count))
        {
            i=a->para4sf[q][0];
            j=a->para4sf[q][1];
            k=a->para4sf[q][2];
            n=a->subgrid(i,j,k);

            if(n==count)
            {
                put_int(i-a->xnode[aa-1]);

                put_int(j-a->ynode[bb-1]);

                put_int(k-a->znode[cc-1]);
            }
        }

        for(const int q : bk.para[4].list(count))
        {
            i=a->para5sf[q][0];
            j=a->para5sf[q][1];
            k=a->para5sf[q][2];
            n=a->subgrid(i,j,k);

            if(n==count)
            {
                put_int(i-a->xnode[aa-1]);

                put_int(j-a->ynode[bb-1]);

                put_int(k-a->znode[cc-1]);
            }
        }

        for(const int q : bk.para[5].list(count))
        {
            i=a->para6sf[q][0];
            j=a->para6sf[q][1];
            k=a->para6sf[q][2];
            n=a->subgrid(i,j,k);

            if(n==count)
            {
                put_int(i-a->xnode[aa-1]);

                put_int(j-a->ynode[bb-1]);

                put_int(k-a->znode[cc-1]);
            }
        }

        // -----------------------------------------------------------------------------
        // Para Corners

        for(const int q : bk.paraco[0].list(count))
        {
            i=a->para1co[q][0];
            j=a->para1co[q][1];
            k=a->para1co[q][2];
            n=a->para1co[q][3];

            if(n==count)
            {
                put_int(i-a->xnode[aa-1]);

                put_int(j-a->ynode[bb-1]);

                put_int(k-a->znode[cc-1]);

                put_int(a->para1co[q][4]); // dead

                put_int(a->para1co[q][5]); // dead

                put_int(a->para1co[q][6]); // dead
            }
        }

        for(const int q : bk.paraco[1].list(count))
        {
            i=a->para2co[q][0];
            j=a->para2co[q][1];
            k=a->para2co[q][2];
            n=a->para2co[q][3];

            if(n==count)
            {
                put_int(i-a->xnode[aa-1]);

                put_int(j-a->ynode[bb-1]);

                put_int(k-a->znode[cc-1]);

                put_int(a->para2co[q][4]); // dead

                put_int(a->para2co[q][5]); // dead

                put_int(a->para2co[q][6]); // dead
            }
        }

        for(const int q : bk.paraco[2].list(count))
        {
            i=a->para3co[q][0];
            j=a->para3co[q][1];
            k=a->para3co[q][2];
            n=a->para3co[q][3];

            if(n==count)
            {
                put_int(i-a->xnode[aa-1]);

                put_int(j-a->ynode[bb-1]);

                put_int(k-a->znode[cc-1]);

                put_int(a->para3co[q][4]); // dead

                put_int(a->para3co[q][5]); // dead

                put_int(a->para3co[q][6]); // dead
            }
        }

        for(const int q : bk.paraco[3].list(count))
        {
            i=a->para4co[q][0];
            j=a->para4co[q][1];
            k=a->para4co[q][2];
            n=a->para4co[q][3];

            if(n==count)
            {
                put_int(i-a->xnode[aa-1]);

                put_int(j-a->ynode[bb-1]);

                put_int(k-a->znode[cc-1]);

                put_int(a->para4co[q][4]); // dead

                put_int(a->para4co[q][5]); // dead

                put_int(a->para4co[q][6]); // dead
            }
        }

        for(const int q : bk.paraco[4].list(count))
        {
            i=a->para5co[q][0];
            j=a->para5co[q][1];
            k=a->para5co[q][2];
            n=a->para5co[q][3];

            if(n==count)
            {
                put_int(i-a->xnode[aa-1]);

                put_int(j-a->ynode[bb-1]);

                put_int(k-a->znode[cc-1]);

                put_int(a->para5co[q][4]); // dead

                put_int(a->para5co[q][5]); // dead

                put_int(a->para5co[q][6]); // dead
            }
        }

        for(const int q : bk.paraco[5].list(count))
        {
            i=a->para6co[q][0];
            j=a->para6co[q][1];
            k=a->para6co[q][2];
            n=a->para6co[q][3];

            if(n==count)
            {
                put_int(i-a->xnode[aa-1]);

                put_int(j-a->ynode[bb-1]);

                put_int(k-a->znode[cc-1]);

                put_int(a->para6co[q][4]); // dead

                put_int(a->para6co[q][5]); // dead

                put_int(a->para6co[q][6]); // dead
            }
        }

        // --------------------------------------------------------------------------------------------------------------
        //Slice

        k=0;
        for(const int c : bk.slice.list(count))
        {
            i = c/a->knoy;
            j = c%a->knoy;

            put_int(a->flagslice(i,j));
        }

        // --------------------------------------------------------------------------------------------------------------
        // Paraslicesurface

        for(const int q : bk.paraslice[0].list(count))
        {
            i=a->paraslice1sf[q][0];
            j=a->paraslice1sf[q][1];
            n=a->subslice(i,j);

            if(n==count)
            {
                put_int(i-a->xnode[aa-1]);
                put_int(j-a->ynode[bb-1]);
            }
        }

        for(const int q : bk.paraslice[1].list(count))
        {
            i=a->paraslice2sf[q][0];
            j=a->paraslice2sf[q][1];
            n=a->subslice(i,j);

            if(n==count)
            {
                put_int(i-a->xnode[aa-1]);
                put_int(j-a->ynode[bb-1]);
            }
        }

        for(const int q : bk.paraslice[2].list(count))
        {
            i=a->paraslice3sf[q][0];
            j=a->paraslice3sf[q][1];
            n=a->subslice(i,j);

            if(n==count)
            {
                put_int(i-a->xnode[aa-1]);
                put_int(j-a->ynode[bb-1]);
            }
        }

        for(const int q : bk.paraslice[3].list(count))
        {
            i=a->paraslice4sf[q][0];
            j=a->paraslice4sf[q][1];
            n=a->subslice(i,j);

            if(n==count)
            {
                put_int(i-a->xnode[aa-1]);
                put_int(j-a->ynode[bb-1]);
            }
        }


        // --------------------------------------------------------------------------------------------------------------
        // Paracoslicesurface

        for(const int q : bk.paracoslice[0].list(count))
        {
            i=a->paracoslice1sf[q][0];
            j=a->paracoslice1sf[q][1];
            n=a->paracoslice1sf[q][2];

            if(n==count)
            {
                put_int(i-a->xnode[aa-1]);
                put_int(j-a->ynode[bb-1]);
                put_int(a->paracoslice1sf[q][3]); // dead
            }
        }

        for(const int q : bk.paracoslice[1].list(count))
        {
            i=a->paracoslice2sf[q][0];
            j=a->paracoslice2sf[q][1];
            n=a->paracoslice2sf[q][2];

            if(n==count)
            {
                put_int(i-a->xnode[aa-1]);
                put_int(j-a->ynode[bb-1]);
                put_int(a->paracoslice2sf[q][3]); // dead
            }
        }

        for(const int q : bk.paracoslice[2].list(count))
        {
            i=a->paracoslice3sf[q][0];
            j=a->paracoslice3sf[q][1];
            n=a->paracoslice3sf[q][2];

            if(n==count)
            {
                put_int(i-a->xnode[aa-1]);
                put_int(j-a->ynode[bb-1]);
                put_int(a->paracoslice3sf[q][3]); // dead
            }
        }

        for(const int q : bk.paracoslice[3].list(count))
        {
            i=a->paracoslice4sf[q][0];
            j=a->paracoslice4sf[q][1];
            n=a->paracoslice4sf[q][2];

            if(n==count)
            {
                put_int(i-a->xnode[aa-1]);
                put_int(j-a->ynode[bb-1]);
                put_int(a->paracoslice4sf[q][3]); // dead
            }
        }


        // ---------------------------------------------------------------------------------------------------------------------
        //Bedlevels
        // *********************
        for(const int c : bk.slice.list(count))
        {
            i = c/a->knoy;
            j = c%a->knoy;

            put_double(a->bedlevel(i,j));
        }

        //GEODAT
        // *********************
        if(p->solidprint>0)
        for(const int c : bk.slice.list(count))
        {
            i = c/a->knoy;
            j = c%a->knoy;

            put_double(a->solidbed(i,j));
        }

        if(p->topoprint>0)
        for(const int c : bk.slice.list(count))
        {
            i = c/a->knoy;
            j = c%a->knoy;

            put_double(a->topobed(i,j));
        }

        //DATA INTERPOLATION
        // *********************
        k=0;
        if(p->D10>0)
        for(const int c : bk.slice.list(count))
        {
            i = c/a->knoy;
            j = c%a->knoy;

            put_double(a->dataset(i,j));
        }

        buffer.resize(m);

        char name[100];
        const int padding = 6;
        snprintf(name,sizeof(name),"DIVEMesh_Grid/grid-%0*i.dat",padding,count);

        FILE* file = fopen(name, "wb");
        bool ok = (file!=nullptr);
        if(ok)
        {
            setvbuf(file, nullptr, _IOFBF, 131072);
            ok = (fwrite(buffer.data(), buffer.size(), 1, file)==1);
            ok = (fclose(file)==0) && ok;
        }

        if(!ok)
        {
            #pragma omp critical
            {
                cout<<endl<<"!!! could not write "<<name<<" !!!"<<endl;
                ++write_errors;
            }
        }

        #pragma omp critical
        {
            cout<<".";
        }
    }

    if(write_errors>0)
    {
        cout<<endl<<"!!! "<<write_errors<<" grid file(s) could not be written !!!"<<endl<<endl;
        exit(1);
    }

    cout<<"\nprinting complete\n"
        <<"__________________________________________\n"<<endl;
}
