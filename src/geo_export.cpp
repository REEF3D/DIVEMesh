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

#include"geo_export.h"
#include"gridfile_v2.h"
#include"lexer.h"
#include<cstdio>
#include<iostream>
#include<unordered_map>
#include<cstring>
#include<cstdint>

geo_export::geo_export() : kw(0), idx(0)
{
}

void geo_export::meta(int keyword, int index, std::initializer_list<double> p)
{
    kw = keyword;
    idx = index;
    par.assign(p.begin(),p.end());
}

void geo_export::add(lexer *p, int role, int ts, int te, int raymode)
{
    object ob;

    ob.role = role;
    ob.keyword = kw;
    ob.index = idx;
    ob.raymode = raymode;
    ob.invert = 0;
    ob.ts = (long long)(tri.size()/9);
    ob.nt = (long long)(te>ts ? te-ts : 0);
    ob.param = par;

    tri.reserve(tri.size() + 9*size_t(ob.nt));

    for(int n=ts; n<te; ++n)
    for(int q=0; q<3; ++q)
    {
        tri.push_back(p->tri_x[n][q]);
        tri.push_back(p->tri_y[n][q]);
        tri.push_back(p->tri_z[n][q]);
    }

    obj.push_back(ob);
}

void geo_export::invert_last(int role)
{
    for(int n=int(obj.size())-1; n>=0; --n)
    if(obj[n].role==role)
    {
        obj[n].invert = 1;
        return;
    }
}

int geo_export::count(int role) const
{
    int num=0;

    for(const object &ob : obj)
    if(ob.role==role)
    ++num;

    return num;
}

bool geo_export::write(lexer *p, const char *name, int solidread, int toporead, int geodat) const
{
    gridv2::writer w;
    size_t pos;

    w.start(gridv2::magic_geom);

    // header
    pos = w.begin("GHDR");

    w.put_int(6);
    w.put_int(solidread);           // REEF3D builds the solid field
    w.put_int(toporead);            // REEF3D builds the topo field
    w.put_int(geodat);              // geodat bed in GEOB: 0 none, else the role it belongs to (1 solid, 2 topo)
    w.put_int(int(obj.size()));
    w.put_int(count(role_solid));
    w.put_int(count(role_topo));

    w.put_int(1);
    w.put_double(p->DXM);           // DIVEMesh mean cell size, reference for ray offsets and clipping

    w.end(pos);

    // objects
    pos = w.begin("OBJS");

    w.put_int(int(obj.size()));

    for(const object &ob : obj)
    {
        w.put_int(ob.role);
        w.put_int(ob.keyword);
        w.put_int(ob.index);
        w.put_int(ob.raymode);
        w.put_int(ob.invert);
        w.put_i64(ob.ts);
        w.put_i64(ob.nt);
        w.put_int(int(ob.param.size()));

        for(double v : ob.param)
        w.put_double(v);
    }

    w.end(pos);

    // triangles as an indexed mesh: unique vertices (exact coordinates) and vertex indices
    {
        struct key
        {
            uint64_t a,b,c;
            bool operator==(const key &o) const { return a==o.a && b==o.b && c==o.c; }
        };

        struct hash
        {
            size_t operator()(const key &k) const
            {
                uint64_t h = k.a*0x9E3779B97F4A7C15ull;
                h ^= k.b + 0x9E3779B97F4A7C15ull + (h<<6) + (h>>2);
                h ^= k.c + 0x9E3779B97F4A7C15ull + (h<<6) + (h>>2);
                return size_t(h);
            }
        };

        const size_t nt = tri.size()/9;

        std::unordered_map<key,int,hash> index;
        std::vector<double> vert;
        std::vector<int> tidx(3*nt);

        index.reserve(2*nt+1);

        for(size_t q=0; q<3*nt; ++q)
        {
            key k;
            std::memcpy(&k.a,&tri[3*q],sizeof(double));
            std::memcpy(&k.b,&tri[3*q+1],sizeof(double));
            std::memcpy(&k.c,&tri[3*q+2],sizeof(double));

            auto it = index.find(k);

            if(it==index.end())
            {
                const int id = int(vert.size()/3);
                index.emplace(k,id);
                vert.push_back(tri[3*q]);
                vert.push_back(tri[3*q+1]);
                vert.push_back(tri[3*q+2]);
                tidx[q] = id;
            }
            else
            tidx[q] = it->second;
        }

        pos = w.begin("VERT");

        w.put_i64((long long)(vert.size()/3));

        if(!vert.empty())
        w.put(vert.data(),vert.size()*sizeof(double));

        w.end(pos);

        pos = w.begin("TIDX");

        w.put_table((long long)nt,3,[&](long long r, int c){return tidx[3*size_t(r)+c];});

        w.end(pos);
    }

    // river corridor grid
    if(curv.ni>0)
    {
        pos = w.begin("CURV");

        w.put_int(3);
        w.put_int(1);                   // layout version of the section
        w.put_int(curv.ni);
        w.put_int(curv.nj);

        w.put_int(int(curv.par.size()));
        for(double v : curv.par)
        w.put_double(v);

        const size_t nn = size_t(curv.ni+1)*size_t(curv.nj+1);
        w.put(curv.x.data(),nn*sizeof(double));
        w.put(curv.y.data(),nn*sizeof(double));
        w.put(curv.zb.data(),nn*sizeof(double));

        w.end(pos);
    }

    w.finish();

    FILE* file = fopen(name, "wb");
    bool ok = (file!=nullptr);

    if(ok)
    {
        ok = (fwrite(w.buf.data(), w.buf.size(), 1, file)==1);
        ok = (fclose(file)==0) && ok;
    }

    if(ok)
    std::cout<<"geometry: "<<obj.size()<<" objects, "<<tri.size()/9<<" triangles"<<std::endl;

    return ok;
}
