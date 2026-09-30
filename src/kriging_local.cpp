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

#include "kriging.h"
#include "lexer.h"
#include <algorithm>
#include <cmath>
#include <limits>

// Local ordinary kriging: for each grid cell, the nnb nearest geodat points form a small
// (nnb+1)x(nnb+1) kriging system. Neighbour search uses a uniform bucket grid.
// Neighbouring cells often share the same neighbour set; the solved dual weights are then reused.
void kriging::start_local(lexer* p, int N, double *X, double *Y, double *F, double *XC, double *YC, int kx, int ky, double **f)
{
    const int K = std::max(1,std::min(nnb,N));

    cout<<"kriging local  Np: "<<N<<"  neighbours: "<<K<<endl;

    // bucket grid, roughly 2 points per bucket
    double xmin = X[0], xmax = X[0], ymin = Y[0], ymax = Y[0];

    for(int nn=1; nn<N; ++nn)
    {
        xmin = std::min(xmin,X[nn]);
        xmax = std::max(xmax,X[nn]);
        ymin = std::min(ymin,Y[nn]);
        ymax = std::max(ymax,Y[nn]);
    }

    const double Lx = xmax-xmin;
    const double Ly = ymax-ymin;

    double h = sqrt(Lx*Ly*2.0/double(N));
    h = std::max(h, 2.0*std::max(Lx,Ly)/double(N));
    h = std::max(h, 1.0e-12);

    const int nbx = std::min(int(Lx/h)+1, 4*N+1);
    const int nby = std::min(int(Ly/h)+1, 4*N+1);

    vector<int> bstart((size_t)nbx*nby+1,0);
    vector<int> bpts(N);
    vector<int> bid(N);

    for(int nn=0; nn<N; ++nn)
    {
        const int bi = std::min(std::max(int((X[nn]-xmin)/h),0),nbx-1);
        const int bj = std::min(std::max(int((Y[nn]-ymin)/h),0),nby-1);

        bid[nn] = bi*nby + bj;
        ++bstart[bid[nn]+1];
    }

    for(size_t b=0; b<(size_t)nbx*nby; ++b)
    bstart[b+1] += bstart[b];

    {
        vector<int> fill(bstart.begin(),bstart.end()-1);

        for(int nn=0; nn<N; ++nn)
        bpts[fill[bid[nn]]++] = nn;
    }

    cout<<"bucket grid: "<<nbx<<" x "<<nby<<endl;
    cout<<"mainloop kriging"<<endl<<endl;

    long long numsolve = 0;

    #pragma omp parallel reduction(+:numsolve)
    {
        const int M = K+1;

        vector<int> nid(K), sid(K), lastsid(K,-1);
        vector<double> nd2(K);
        vector<double> A((size_t)M*M), w(M), lastw(M,0.0);
        int lastcnt = -1;

        #pragma omp for collapse(2) schedule(static)
        for(int ii=0; ii<kx; ++ii)
        for(int jj=0; jj<ky; ++jj)
        {
            const double xc = XC[ii+marge];
            const double yc = YC[jj+marge];

            // k nearest neighbour search, ring by ring around the query bucket
            const int bi = std::min(std::max(int(floor((xc-xmin)/h)),0),nbx-1);
            const int bj = std::min(std::max(int(floor((yc-ymin)/h)),0),nby-1);

            int cnt = 0;

            for(int r=0; ; ++r)
            {
                for(int ib=bi-r; ib<=bi+r; ++ib)
                {
                    if(ib<0 || ib>=nbx)
                    continue;

                    const bool edge = (ib==bi-r || ib==bi+r);
                    const int jstep = (edge || r==0) ? 1 : 2*r;

                    for(int jb=bj-r; jb<=bj+r; jb+=jstep)
                    {
                        if(jb<0 || jb>=nby)
                        continue;

                        const int b = ib*nby + jb;

                        for(int t=bstart[b]; t<bstart[b+1]; ++t)
                        {
                            const int q = bpts[t];
                            const double dx = xc-X[q];
                            const double dy = yc-Y[q];
                            const double d2 = dx*dx + dy*dy;

                            int pos;

                            if(cnt<K)
                            pos = cnt++;
                            else if(d2<nd2[K-1])
                            pos = K-1;
                            else
                            continue;

                            while(pos>0 && nd2[pos-1]>d2)
                            {
                                nd2[pos] = nd2[pos-1];
                                nid[pos] = nid[pos-1];
                                --pos;
                            }

                            nd2[pos] = d2;
                            nid[pos] = q;
                        }
                    }
                }

                // lower bound for the distance to any bucket outside the searched box
                double dmin = std::numeric_limits<double>::max();

                if(bi-r>0)
                dmin = std::min(dmin, xc-(xmin+(bi-r)*h));

                if(bi+r<nbx-1)
                dmin = std::min(dmin, xmin+(bi+r+1)*h-xc);

                if(bj-r>0)
                dmin = std::min(dmin, yc-(ymin+(bj-r)*h));

                if(bj+r<nby-1)
                dmin = std::min(dmin, ymin+(bj+r+1)*h-yc);

                if(dmin==std::numeric_limits<double>::max())
                break;

                dmin = std::max(dmin,0.0);

                if(cnt==K && dmin*dmin>=nd2[K-1])
                break;
            }

            for(int nn=0; nn<cnt; ++nn)
            sid[nn] = nid[nn];

            std::sort(sid.begin(),sid.begin()+cnt);

            const int m = cnt+1;

            // solve only if the neighbour set changed
            if(cnt!=lastcnt || !std::equal(sid.begin(),sid.begin()+cnt,lastsid.begin()))
            {
                for(int nn=0; nn<cnt; ++nn)
                {
                    double *An = &A[(size_t)nn*m];

                    for(int qq=0; qq<cnt; ++qq)
                    {
                        const double dx = X[sid[nn]]-X[sid[qq]];
                        const double dy = Y[sid[nn]]-Y[sid[qq]];

                        An[qq] = semivariogram(sqrt(dx*dx + dy*dy));
                    }

                    An[cnt] = 1.0;
                    lastw[nn] = F[sid[nn]];
                }

                for(int qq=0; qq<cnt; ++qq)
                A[(size_t)cnt*m+qq] = 1.0;

                A[(size_t)cnt*m+cnt] = 0.0;
                lastw[cnt] = 0.0;

                solve_small(A.data(),lastw.data(),m);

                for(int nn=0; nn<cnt; ++nn)
                lastsid[nn] = sid[nn];

                lastcnt = cnt;
                ++numsolve;
            }

            double val = lastw[cnt];

            for(int nn=0; nn<cnt; ++nn)
            {
                const double dx = xc-X[sid[nn]];
                const double dy = yc-Y[sid[nn]];

                val += lastw[nn]*semivariogram(sqrt(dx*dx + dy*dy));
            }

            f[ii+3][jj+3] = val;
        }
    }

    cout<<"> processed cells: "<<kx*ky<<"   kriging systems solved: "<<numsolve<<endl;
}
