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

#include"multiblock.h"
#include"lexer.h"
#include<fstream>
#include<iostream>
#include<sstream>
#include<cmath>
#include<map>
#include<algorithm>
#include<sys/stat.h>

multiblock::multiblock() : W(8), hm(1.0), tol(1.0e-9)
{
}

namespace
{
// node (K,L) of face f at position k along it
inline void face_node(int f, int k, int ni, int nj, int &K, int &L)
{
    if(f==0) { K=0;  L=k; }
    if(f==1) { K=ni; L=k; }
    if(f==2) { K=k;  L=0; }
    if(f==3) { K=k;  L=nj; }
}
inline int face_len(int f, int ni, int nj) { return (f<2) ? nj : ni; }   // cells along the face
}

bool multiblock::start(lexer *p)
{
    W = std::max(p->R21,1);

    ifstream in("blocks.dat");
    int nb=0;
    if(!(in>>nb) || nb<1)
    {
        cout<<"!!! R 20 1: blocks.dat missing or without the number of blocks !!!"<<endl;
        return false;
    }

    b.assign(nb,block());
    double hmin = 1.0e20;
    for(int q=0; q<nb; ++q)
    {
        block &B = b[q];
        if(!(in>>B.ni>>B.nj) || B.ni<1 || B.nj<1)
        {
            cout<<"!!! R 20 1: blocks.dat, block "<<q<<": no \"ni nj\" !!!"<<endl;
            return false;
        }
        const size_t nn = size_t(B.ni+1)*size_t(B.nj+1);
        B.x.resize(nn); B.y.resize(nn); B.zb.resize(nn);
        for(size_t k=0; k<nn; ++k)
        if(!(in>>B.x[k]>>B.y[k]>>B.zb[k]))
        {
            cout<<"!!! R 20 1: blocks.dat ends in block "<<q<<" at node "<<k<<" !!!"<<endl;
            return false;
        }

        // shortest cell edge (tolerance of the node matching)
        for(int L=0; L<=B.nj; ++L)
        for(int K=0; K<=B.ni; ++K)
        {
            const size_t a = K + size_t(B.ni+1)*L;
            if(K<B.ni) hmin = std::min(hmin, hypot(B.x[a+1]-B.x[a], B.y[a+1]-B.y[a]));
            if(L<B.nj) hmin = std::min(hmin, hypot(B.x[a+B.ni+1]-B.x[a], B.y[a+B.ni+1]-B.y[a]));
        }
    }
    tol = 1.0e-6*hmin;

    // mean spacing of block 0: the DIVEMesh box of the run
    {
        const block &B = b[0];
        double s=0.0; long n=0;
        for(int L=0; L<=B.nj; ++L)
        for(int K=0; K<B.ni; ++K)
        {
            const size_t a = K + size_t(B.ni+1)*L;
            s += hypot(B.x[a+1]-B.x[a], B.y[a+1]-B.y[a]); ++n;
        }
        for(int L=0; L<B.nj; ++L)
        for(int K=0; K<=B.ni; ++K)
        {
            const size_t a = K + size_t(B.ni+1)*L;
            s += hypot(B.x[a+B.ni+1]-B.x[a], B.y[a+B.ni+1]-B.y[a]); ++n;
        }
        hm = (n>0) ? s/double(n) : 1.0;
    }

    find_interfaces(p);

    // block 0: the interfaces of a face (one or several neighbour blocks) over the whole face, a ring of
    // W cells there
    bool ok = true;
    for(int f=0; f<4; ++f)
    {
        const int n = face_len(f,b[0].ni,b[0].nj);
        vector<int> cov(n,0);
        int nseg = 0;
        for(const seg &S : b[0].segs)
        if(S.face==f)
        {
            for(int k=S.lo; k<=S.hi; ++k)
            ++cov[k];
            ++nseg;
        }
        if(nseg==0)
        continue;
        int lo=-1, hi=-1;
        for(int k=0; k<n; ++k)
        if(cov[k]!=1)
        {
            if(lo<0) lo=k;
            hi=k;
        }
        if(lo>=0)
        {
            ostringstream o;
            o<<"block 0, face "<<f<<": cells "<<lo<<".."<<hi<<" without an interface (or with several); the interfaces of "
             <<"block 0 (the grid of the run) have to cover whole faces";
            msg.push_back(o.str());
            ok = false;
        }
        b[0].ring[f] = W;
    }

    // the neighbours reach W cells beyond every face (ring, ghost cells of the other blocks)
    for(int q=0; q<nb; ++q)
    for(const seg &S : b[q].segs)
    {
        const block &N = b[S.nbr];
        const int depth = (S.nface<2) ? N.ni : N.nj;
        if(depth<W)
        {
            ostringstream o;
            o<<"block "<<S.nbr<<" is "<<depth<<" cells deep behind its face "<<S.nface<<" (interface with block "<<q
             <<"), less than the ring R 21 = "<<W;
            msg.push_back(o.str());
            if(q==0)
            ok = false;
        }
    }

    box_nodes();
    log(p);

    for(const string &m : msg)
    cout<<(ok ? "multi-block grid: " : "!!! multi-block grid: ")<<m<<(ok ? "" : " !!!")<<endl;

    if(!ok)
    return false;

    int ns=0;
    for(const block &B : b)
    ns += int(B.segs.size());

    cout<<endl<<"multi-block grid (R 20 1): "<<nb<<" blocks, "<<ns<<" interface segments; block 0 with its ring "
        <<box_ni()<<" x "<<box_nj()<<" cells, spacing "<<hm<<" m"<<endl<<endl;

    return true;
}

// segments: runs of coincident face nodes of two blocks (also two faces of one block)
void multiblock::find_interfaces(lexer *p)
{
    const int nb = int(b.size());

    auto key = [&](double x, double y)
    {
        const double s = 4.0*tol;
        return make_pair((long long)floor(x/s), (long long)floor(y/s));
    };

    for(int A=0; A<nb; ++A)
    for(int fA=0; fA<4; ++fA)
    {
        const block &BA = b[A];
        const int nA = face_len(fA,BA.ni,BA.nj);

        for(int Bq=0; Bq<nb; ++Bq)
        for(int fB=0; fB<4; ++fB)
        {
            if(Bq==A && fB==fA)
            continue;

            const block &BB = b[Bq];
            const int nB = face_len(fB,BB.ni,BB.nj);

            // nodes of face fB by position (with the neighbouring buckets for the tolerance)
            map<pair<long long,long long>,vector<int>> M;
            for(int k=0; k<=nB; ++k)
            {
                int K,L;
                face_node(fB,k,BB.ni,BB.nj,K,L);
                const size_t a = K + size_t(BB.ni+1)*L;
                M[key(BB.x[a],BB.y[a])].push_back(k);
            }

            vector<int> match(nA+1,-1);
            for(int k=0; k<=nA; ++k)
            {
                int K,L;
                face_node(fA,k,BA.ni,BA.nj,K,L);
                const size_t a = K + size_t(BA.ni+1)*L;
                const pair<long long,long long> c = key(BA.x[a],BA.y[a]);
                for(long long dx=-1; dx<=1 && match[k]<0; ++dx)
                for(long long dy=-1; dy<=1 && match[k]<0; ++dy)
                {
                    auto it = M.find(make_pair(c.first+dx,c.second+dy));
                    if(it==M.end())
                    continue;
                    for(int kb : it->second)
                    {
                        int KB,LB;
                        face_node(fB,kb,BB.ni,BB.nj,KB,LB);
                        const size_t bb = KB + size_t(BB.ni+1)*LB;
                        if(fabs(BB.x[bb]-BA.x[a])<=tol && fabs(BB.y[bb]-BA.y[a])<=tol)
                        {
                            match[k] = kb;
                            break;
                        }
                    }
                }
            }

            // runs of at least two nodes with a constant step along face fB
            int k=0;
            while(k<nA)
            {
                if(match[k]<0 || match[k+1]<0 || abs(match[k+1]-match[k])!=1)
                {
                    ++k;
                    continue;
                }
                const int d = match[k+1]-match[k];
                int k1 = k+1;
                while(k1<nA && match[k1+1]>=0 && match[k1+1]-match[k1]==d)
                ++k1;

                seg S;
                S.face = fA;
                S.lo = k;
                S.hi = k1-1;
                S.nbr = Bq;
                S.nface = fB;

                // node transform: tangential of A -> d * tangential of B, outward normal of A ->
                // inward normal of B
                const int tA = (fA<2) ? 1 : 0, nAx = 1-tA, sA = (fA%2==0) ? -1 : 1;
                const int tB = (fB<2) ? 1 : 0, nBx = 1-tB, sB = (fB%2==0) ? -1 : 1;
                S.perm[tB] = tA;  S.sign[tB] = d;
                S.perm[nBx] = nAx; S.sign[nBx] = -sA*sB;

                int KA,LA,KB,LB;
                face_node(fA,k,BA.ni,BA.nj,KA,LA);
                face_node(fB,match[k],BB.ni,BB.nj,KB,LB);
                const int NA[2] = {KA,LA}, NB[2] = {KB,LB};
                for(int c=0; c<2; ++c)
                {
                    S.t[c] = NB[c] - S.sign[c]*NA[S.perm[c]];
                    S.off[c] = S.t[c] - (S.sign[c]<0 ? 1 : 0);
                }

                b[A].segs.push_back(S);
                k = k1;
            }
        }
    }
}

// node (K,L) of block blk, beyond its faces through the interfaces (corners: two hops)
bool multiblock::node_of(int blk, int K, int L, int depth, double &x, double &y, double &z) const
{
    const block &B = b[blk];

    if(K>=0 && K<=B.ni && L>=0 && L<=B.nj)
    {
        const size_t a = K + size_t(B.ni+1)*L;
        x = B.x[a]; y = B.y[a]; z = B.zb[a];
        return true;
    }

    if(depth>=3)
    return false;

    // the faces crossed, i first
    int fc[2], nf=0;
    if(K<0) fc[nf++]=0;
    if(K>B.ni) fc[nf++]=1;
    if(L<0) fc[nf++]=2;
    if(L>B.nj) fc[nf++]=3;

    for(int q=0; q<nf; ++q)
    {
        const int f = fc[q];
        // position along the face, clamped (a corner continues the end segment)
        const int k = (f<2) ? std::min(std::max(L,0),B.nj) : std::min(std::max(K,0),B.ni);
        for(const seg &S : B.segs)
        {
            if(S.face!=f || k<S.lo || k>S.hi+1)
            continue;
            const int N[2] = {K,L};
            const int K2 = S.sign[0]*N[S.perm[0]] + S.t[0];
            const int L2 = S.sign[1]*N[S.perm[1]] + S.t[1];
            if(node_of(S.nbr,K2,L2,depth+1,x,y,z))
            return true;
        }
    }
    return false;
}

// nodes of block 0 with its ring; nodes no interface reaches (corners at walls) by parallelograms
void multiblock::box_nodes()
{
    const block &B = b[0];
    const int NI = box_ni(), NJ = box_nj();
    const size_t nn = size_t(NI+1)*size_t(NJ+1);
    X0.assign(nn,0.0); Y0.assign(nn,0.0); Z0.assign(nn,0.0);
    vector<char> set(nn,0);

    for(int Ln=0; Ln<=NJ; ++Ln)
    for(int Kn=0; Kn<=NI; ++Kn)
    {
        const size_t a = Kn + size_t(NI+1)*Ln;
        double x,y,z;
        if(node_of(0,Kn-B.ring[0],Ln-B.ring[2],0,x,y,z))
        {
            X0[a]=x; Y0[a]=y; Z0[a]=z;
            set[a]=1;
        }
    }

    // the rest, from the box of block 0 outwards
    int missing = 0;
    for(int pass=0; pass<NI+NJ+2; ++pass)
    {
        bool changed=false;
        for(int Ln=0; Ln<=NJ; ++Ln)
        for(int Kn=0; Kn<=NI; ++Kn)
        {
            const size_t a = Kn + size_t(NI+1)*Ln;
            if(set[a])
            continue;
            for(int di=-1; di<=1 && !set[a]; di+=2)
            for(int dj=-1; dj<=1 && !set[a]; dj+=2)
            {
                const int K1=Kn+di, L1=Ln+dj;
                if(K1<0 || K1>NI || L1<0 || L1>NJ)
                continue;
                const size_t ai = K1 + size_t(NI+1)*Ln, aj = Kn + size_t(NI+1)*L1, ad = K1 + size_t(NI+1)*L1;
                if(set[ai] && set[aj] && set[ad])
                {
                    X0[a] = X0[ai]+X0[aj]-X0[ad];
                    Y0[a] = Y0[ai]+Y0[aj]-Y0[ad];
                    Z0[a] = Z0[ad];
                    set[a] = 2;
                    changed = true;
                }
            }
        }
        if(!changed)
        break;
    }
    for(char s : set)
    if(s==0) ++missing;
    if(missing>0)
    {
        ostringstream o;
        o<<missing<<" ring nodes of block 0 not reached (left at the origin)";
        msg.push_back(o.str());
    }
}

void multiblock::log(lexer *p) const
{
    mkdir("./DIVEMesh_Log",0777);
    ofstream out("./DIVEMesh_Log/multiblock.log");
    out<<"multi-block grid (R 20 1), ring R 21 = "<<W<<", node tolerance "<<tol<<" m"<<endl;
    out<<"transform of a segment: neighbour cell i' = sign0*c[perm0]+off0, j' = sign1*c[perm1]+off1, c = (i,j)"<<endl<<endl;
    for(size_t q=0; q<b.size(); ++q)
    {
        const block &B = b[q];
        out<<"block "<<q<<": "<<B.ni<<" x "<<B.nj<<" cells";
        if(q==0)
        out<<", ring -i "<<B.ring[0]<<" +i "<<B.ring[1]<<" -j "<<B.ring[2]<<" +j "<<B.ring[3];
        out<<endl;
        for(const seg &S : B.segs)
        out<<"  face "<<S.face<<" cells "<<S.lo<<".."<<S.hi<<" -> block "<<S.nbr<<" face "<<S.nface
           <<"  perm "<<S.perm[0]<<" "<<S.perm[1]<<"  sign "<<S.sign[0]<<" "<<S.sign[1]<<"  off "<<S.off[0]<<" "<<S.off[1]<<endl;
    }
    for(const string &m : msg)
    out<<"note: "<<m<<endl;

    // the blocks for ParaView
    mkdir("./DIVEMesh_Paraview",0777);
    for(size_t q=0; q<b.size(); ++q)
    {
        const block &B = b[q];
        ostringstream fn;
        fn<<"./DIVEMesh_Paraview/multiblock-"<<q<<".vtk";
        ofstream v(fn.str().c_str());
        v<<"# vtk DataFile Version 3.0\nmulti-block grid, block "<<q<<"\nASCII\nDATASET STRUCTURED_GRID\n";
        v<<"DIMENSIONS "<<B.ni+1<<" "<<B.nj+1<<" 1\nPOINTS "<<B.x.size()<<" double\n";
        v.precision(12);
        for(size_t a=0; a<B.x.size(); ++a)
        v<<B.x[a]<<" "<<B.y[a]<<" "<<B.zb[a]<<"\n";
        v<<"POINT_DATA "<<B.x.size()<<"\nSCALARS bed double 1\nLOOKUP_TABLE default\n";
        for(size_t a=0; a<B.x.size(); ++a)
        v<<B.zb[a]<<"\n";
    }
}
