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
#include"gridfile_v2.h"
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
        index_lists surf;
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

    const int_table *parasf[6] = {&a->para1sf,&a->para2sf,&a->para3sf,&a->para4sf,&a->para5sf,&a->para6sf};
    const int_table *paraco[6] = {&a->para1co,&a->para2co,&a->para3co,&a->para4co,&a->para5co,&a->para6co};
    const int paracount[6] = {a->para1count,a->para2count,a->para3count,a->para4count,a->para5count,a->para6count};
    const int paracocount[6] = {a->paraco1count,a->paraco2count,a->paraco3count,a->paraco4count,a->paraco5count,a->paraco6count};

    for(int d=0;d<6;++d)
    {
        const int_table &sf=*parasf[d], &co=*paraco[d];
        bk.para[d].build(nsub,paracount[d],[&](int q){return a->subgrid(sf[q][0],sf[q][1],sf[q][2]);});
        bk.paraco[d].build(nsub,paracocount[d],[&](int q){return co[q][3];});
    }

    const int_table *paraslicesf[4] = {&a->paraslice1sf,&a->paraslice2sf,&a->paraslice3sf,&a->paraslice4sf};
    const int_table *paracoslicesf[4] = {&a->paracoslice1sf,&a->paracoslice2sf,&a->paracoslice3sf,&a->paracoslice4sf};
    const int paraslicecount[4] = {a->paraslice1count,a->paraslice2count,a->paraslice3count,a->paraslice4count};
    const int paracoslicecount[4] = {a->paracoslice1count,a->paracoslice2count,a->paracoslice3count,a->paracoslice4count};

    for(int d=0;d<4;++d)
    {
        const int_table &sf=*paraslicesf[d], &co=*paracoslicesf[d];
        bk.paraslice[d].build(nsub,paraslicecount[d],[&](int q){return a->subslice(sf[q][0],sf[q][1]);});
        bk.paracoslice[d].build(nsub,paracoslicecount[d],[&](int q){return co[q][2];});
    }


    // ---------------------------------------------------------------------------------------------------------------------
    // GEOMETRY: S/T entities for REEF3D, one file for all ranks

    {
        const int geodat = (p->G10>0) ? ((p->G9==2) ? geo_export::role_solid : geo_export::role_topo) : 0;

        if(!a->gex.write(p,"DIVEMesh_Grid/grid-geometry.dat",p->solidprint,p->topoprint,geodat))
        {
            cout<<endl<<"!!! could not write DIVEMesh_Grid/grid-geometry.dat !!!"<<endl;
            ++write_errors;
        }
    }

    #pragma omp parallel for collapse(3) schedule(dynamic)
    for(int aa=1;aa<=a->mx;++aa)
    for(int bb=1;bb<=a->my;++bb)
    for(int cc=1;cc<=a->mz;++cc)
    {
        int i = 0;
        int j = 0;
        int k = 0;
        const int count = ((aa-1)*a->my + (bb-1))*a->mz + cc;

        const int i0 = a->xnode[aa-1], i1 = a->xnode[aa];
        const int j0 = a->ynode[bb-1], j1 = a->ynode[bb];
        const int k0 = a->znode[cc-1], k1 = a->znode[cc];
        const int ni = i1-i0, nj = j1-j0, nk = k1-k0;

        gridv2::writer w;
        size_t pos;

        w.buf.reserve(size_t(ni+nj+nk+6*marge+3)*sizeof(double) + size_t(ni)*size_t(nj)*4*sizeof(double) + 65536);

        w.start(gridv2::magic_grid);

        // -------------------------------------------------------------------------------------------------------------
        // HEAD
        pos = w.begin("HEAD");

        const int nint = 62;
        w.put_int(nint);

        w.put_int(p->M10);

        w.put_int(a->subknox[count]);
        w.put_int(a->subknoy[count]);
        w.put_int(a->subknoz[count]);

        w.put_int(a->knox);
        w.put_int(a->knoy);
        w.put_int(a->knoz);

        w.put_int(i0);
        w.put_int(j0);
        w.put_int(k0);

        w.put_int(int(bk.surf.size(count)));     // boundary surfaces incl. plates (wall[] counts no plate surfaces)

        w.put_int(a->para1[count]);
        w.put_int(a->para2[count]);
        w.put_int(a->para3[count]);
        w.put_int(a->para4[count]);
        w.put_int(a->para5[count]);
        w.put_int(a->para6[count]);

        w.put_int(a->paraco1[count]);
        w.put_int(a->paraco2[count]);
        w.put_int(a->paraco3[count]);
        w.put_int(a->paraco4[count]);
        w.put_int(a->paraco5[count]);
        w.put_int(a->paraco6[count]);

        w.put_int(a->paraslice1[count]);
        w.put_int(a->paraslice2[count]);
        w.put_int(a->paraslice3[count]);
        w.put_int(a->paraslice4[count]);

        w.put_int(a->paracoslice1[count]);
        w.put_int(a->paracoslice2[count]);
        w.put_int(a->paracoslice3[count]);
        w.put_int(a->paracoslice4[count]);

        w.put_int(a->nbpara1[count]);
        w.put_int(a->nbpara2[count]);
        w.put_int(a->nbpara3[count]);
        w.put_int(a->nbpara4[count]);
        w.put_int(a->nbpara5[count]);
        w.put_int(a->nbpara6[count]);

        w.put_int(a->mx);
        w.put_int(a->my);
        w.put_int(a->mz);

        w.put_int(p->C11);
        w.put_int(p->C12);
        w.put_int(p->C13);
        w.put_int(p->C14);
        w.put_int(p->C15);
        w.put_int(p->C16);

        w.put_int(p->C21);
        w.put_int(p->C22);
        w.put_int(p->C23);

        w.put_int(a->periodicX[count][0]);
        w.put_int(a->periodicX[count][1]);
        w.put_int(a->periodicX[count][2]);
        w.put_int(a->periodicX[count][3]);
        w.put_int(a->periodicX[count][4]);
        w.put_int(a->periodicX[count][5]);

        w.put_int(a->i_dir);
        w.put_int(a->j_dir);
        w.put_int(a->k_dir);

        w.put_int(p->D10);
        w.put_int(p->B6);           // CMS
        w.put_int(marge);           // node margin of the NODE section
        w.put_int(count);           // rank+1

        const int ndbl = 22;
        w.put_int(ndbl);

        w.put_double(p->DXM);

        w.put_double(p->DR);
        w.put_double(p->DS);
        w.put_double(p->DT);

        w.put_double(a->xorig[aa-1]);
        w.put_double(a->yorig[bb-1]);
        w.put_double(a->zorig[cc-1]);
        w.put_double(a->xorig[aa]);
        w.put_double(a->yorig[bb]);
        w.put_double(a->zorig[cc]);

        w.put_double(p->xmin);
        w.put_double(p->ymin);
        w.put_double(p->zmin);
        w.put_double(p->xmax);
        w.put_double(p->ymax);
        w.put_double(p->zmax);

        w.put_double(p->global_orig_x);
        w.put_double(p->global_orig_y);
        w.put_double(p->alpha_grid);

        w.put_double(0.0);          // reserved
        w.put_double(0.0);          // reserved
        w.put_double(0.0);          // reserved

        w.end(pos);

        // -------------------------------------------------------------------------------------------------------------
        // FLAG
        pos = w.begin("FLAG");

        w.put_rle(size_t(ni)*size_t(nj)*size_t(nk),[&](size_t q)
        {
            const int ii = int(q/(size_t(nj)*size_t(nk)));
            const int jj = int((q/size_t(nk))%size_t(nj));
            const int kk = int(q%size_t(nk));
            return a->flag(i0+ii,j0+jj,k0+kk);
        });

        w.end(pos);

        // -------------------------------------------------------------------------------------------------------------
        // NODE
        pos = w.begin("NODE");

        SNODEILOOP
        w.put_double(p->XN[IP]);

        SNODEJLOOP
        w.put_double(p->YN[JP]);

        SNODEKLOOP
        w.put_double(p->ZN[KP]);

        w.end(pos);

        // -------------------------------------------------------------------------------------------------------------
        // SURF: all boundary surfaces of the subdomain, including the plate surfaces
        pos = w.begin("SURF");

        {
            const auto lst = bk.surf.list(count);

            w.put_table((long long)lst.size(),5,[&](long long r, int c){return a->surf[lst[r]][c] - (c==0 ? i0 : (c==1 ? j0 : (c==2 ? k0 : 0)));});
        }

        w.end(pos);

        // -------------------------------------------------------------------------------------------------------------
        // PARA
        pos = w.begin("PARA");

        for(int d=0;d<6;++d)
        {
            const int_table &sf=*parasf[d];
            const auto lst = bk.para[d].list(count);

            w.put_table((long long)lst.size(),3,[&](long long r, int c){return sf[lst[r]][c] - (c==0 ? i0 : (c==1 ? j0 : k0));});
        }

        w.end(pos);

        // PACO
        pos = w.begin("PACO");

        for(int d=0;d<6;++d)
        {
            const int_table &co=*paraco[d];
            const auto lst = bk.paraco[d].list(count);

            w.put_table((long long)lst.size(),3,[&](long long r, int c){return co[lst[r]][c] - (c==0 ? i0 : (c==1 ? j0 : k0));});
        }

        w.end(pos);

        // -------------------------------------------------------------------------------------------------------------
        // SLFL: the columns of the subdomain (every subdomain, also above the bottom layer)
        pos = w.begin("SLFL");

        w.put_rle(size_t(ni)*size_t(nj),[&](size_t q)
        {
            return a->flagslice(i0+int(q/size_t(nj)),j0+int(q%size_t(nj)));
        });

        w.end(pos);

        // SLPA
        pos = w.begin("SLPA");

        for(int d=0;d<4;++d)
        {
            const int_table &sf=*paraslicesf[d];
            const auto lst = bk.paraslice[d].list(count);

            w.put_table((long long)lst.size(),2,[&](long long r, int c){return sf[lst[r]][c] - (c==0 ? i0 : j0);});
        }

        w.end(pos);

        // SLPC
        pos = w.begin("SLPC");

        for(int d=0;d<4;++d)
        {
            const int_table &co=*paracoslicesf[d];
            const auto lst = bk.paracoslice[d].list(count);

            w.put_table((long long)lst.size(),2,[&](long long r, int c){return co[lst[r]][c] - (c==0 ? i0 : j0);});
        }

        w.end(pos);

        // -------------------------------------------------------------------------------------------------------------
        // GEOB: geodat bed level
        if(p->G10>0)
        {
            pos = w.begin("GEOB");

            for(i=i0;i<i1;++i)
            for(j=j0;j<j1;++j)
            w.put_double(a->geobed(i,j));

            w.end(pos);
        }

        // DATA: interpolated data
        if(p->D10>0)
        {
            pos = w.begin("DATA");

            for(i=i0;i<i1;++i)
            for(j=j0;j<j1;++j)
            w.put_double(a->dataset(i,j));

            w.end(pos);
        }

        w.finish();

        char name[100];
        const int padding = 6;
        snprintf(name,sizeof(name),"DIVEMesh_Grid/grid-%0*i.dat",padding,count);

        FILE* file = fopen(name, "wb");
        bool ok = (file!=nullptr);
        if(ok)
        {
            setvbuf(file, nullptr, _IOFBF, 131072);
            ok = (fwrite(w.buf.data(), w.buf.size(), 1, file)==1);
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
