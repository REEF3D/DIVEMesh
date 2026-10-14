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

#include "geodat.h"
#include "dive.h"
#include "lexer.h"
#include <algorithm>
#include <cmath>
#include <vector>

// Hole check for incomplete geodat sets (G 51 1): grid columns that no geodat point covers
// get an extra point at their cell centre with the base level G 52.
//
// Every geodat point covers the disc around it with the radius
//   G 53 > 0 : G 53 times the horizontal cell size
//   G 53 = 0 : 2.6 times its own nearest-neighbour distance,
// and always the column it lies in. All lengths are horizontal and in metres, so the
// result does not depend on the vertical grid (DXM contains dz) and adapts to geodat
// sets with dense and sparse parts. A column is a hole when no disc reaches it.

namespace
{
    // number of cell centres <= x: the bin index used by setup_ijk (poscgen_i/j)
    inline int centre_bin(const double *C, int n, double x)
    {
        return int(std::upper_bound(C,C+n,x) - C);
    }
}

void geodat::holecheck(lexer *p, dive *a, double *X, double *Y, double *F)
{
    const double fac = 2.6;
    const int Np0 = p->Np;

    kx = p->knox;
    ky = p->knoy;

    const double *XPc = p->XP + marge;
    const double *YPc = p->YP + marge;
    const double *XNc = p->XN + marge;
    const double *YNc = p->YN + marge;

    // horizontal cell size, without dz
    const double dxy = 0.5*((p->xmax-p->xmin)/double(kx) + (p->ymax-p->ymin)/double(ky));
    const double Lmax = sqrt(pow(p->xmax-p->xmin,2.0) + pow(p->ymax-p->ymin,2.0));

    // bins of the points that can lie in [x0,x1] x [y0,y1]; the outer bins hold the points
    // outside the cell centres (and outside the domain with G 39 0)
    auto bin_range = [&](double x0, double x1, double y0, double y1, int &bis, int &bie, int &bjs, int &bje)
    {
        bis = centre_bin(XPc,kx,x0);
        bie = centre_bin(XPc,kx,x1);
        bjs = centre_bin(YPc,ky,y0);
        bje = centre_bin(YPc,ky,y1);

        if(bis<=0)  bis=-dd;
        if(bie>=kx) bie=kx+dd;
        if(bjs<=0)  bjs=-dd;
        if(bje>=ky) bje=ky+dd;
    };

    // squared distance to the nearest other point (coincident points do not count)
    // among the points within the box of half-width R; -1 if there is none
    auto nearest2 = [&](int self, double R) -> double
    {
        int bis,bie,bjs,bje;
        bin_range(X[self]-R,X[self]+R,Y[self]-R,Y[self]+R,bis,bie,bjs,bje);

        double d2min = -1.0;

        for(int r=bis; r<=bie; ++r)
        for(int s=bjs; s<=bje; ++s)
        for(int t=0; t<ptnum[r+dd][s+dd]; ++t)
        {
            const int q = ptid[r+dd][s+dd][t];

            if(q==self)
            continue;

            const double d2 = (X[q]-X[self])*(X[q]-X[self]) + (Y[q]-Y[self])*(Y[q]-Y[self]);

            if(d2>1.0e-12 && (d2min<0.0 || d2<d2min))
            d2min = d2;
        }

        return d2min;
    };

    // nearest-neighbour distance of every point: grow the box until a neighbour is found,
    // then search once more with the box half-width set to that distance, which is exact
    std::vector<double> nn(Np0,0.0);

    if(p->G53<=0.0)
    {
        #pragma omp parallel for schedule(dynamic,4096)
        for(int q=0; q<Np0; ++q)
        {
            double R = dxy;
            double d2 = nearest2(q,R);

            while(d2<0.0 && R<Lmax)
            {
                R *= 2.0;
                d2 = nearest2(q,R);
            }

            if(d2>0.0 && sqrt(d2)>R)
            d2 = nearest2(q,sqrt(d2));

            nn[q] = d2>0.0 ? sqrt(d2) : Lmax;
        }
    }

    // mark the covered columns
    std::vector<char> covered(size_t(kx)*size_t(ky),0);

    for(int q=0; q<Np0; ++q)
    {
        const double R = p->G53>0.0 ? p->G53*dxy : fac*nn[q];

        // the column the point lies in
        const int ic = std::min(std::max(centre_bin(XNc,kx+1,X[q])-1,0),kx-1);
        const int jc = std::min(std::max(centre_bin(YNc,ky+1,Y[q])-1,0),ky-1);

        if(X[q]>=p->xmin && X[q]<=p->xmax && Y[q]>=p->ymin && Y[q]<=p->ymax)
        covered[size_t(ic)*ky + jc] = 1;

        // the columns whose centre is inside the disc
        const int is = int(std::lower_bound(XPc,XPc+kx,X[q]-R) - XPc);
        const int ie = int(std::upper_bound(XPc,XPc+kx,X[q]+R) - XPc);
        const int js = int(std::lower_bound(YPc,YPc+ky,Y[q]-R) - YPc);
        const int je = int(std::upper_bound(YPc,YPc+ky,Y[q]+R) - YPc);

        for(int ii=is; ii<ie; ++ii)
        {
            const double dx2 = (XPc[ii]-X[q])*(XPc[ii]-X[q]);

            for(int jj=js; jj<je; ++jj)
            if(dx2 + (YPc[jj]-Y[q])*(YPc[jj]-Y[q]) <= R*R)
            covered[size_t(ii)*ky + jj] = 1;
        }
    }

    // fill the holes with points at G 52
    size_t count=0;
    for(size_t m=0; m<covered.size(); ++m)
    if(covered[m]==0)
    ++count;

    if(p->G53>0.0)
    cout<<"holecheck: cover radius "<<p->G53*dxy<<" m (G 53 "<<p->G53<<" x dxy "<<dxy<<" m)"<<endl;
    else
    {
        std::vector<double> nns(nn);
        std::nth_element(nns.begin(),nns.begin()+nns.size()/2,nns.end());
        const double nnmed = nns.empty()?0.0:nns[nns.size()/2];
        cout<<"holecheck: median point spacing "<<nnmed<<" m, cover radius "<<fac<<" x local spacing"<<endl;
    }

    const double frac = double(count)/double(covered.size());

    cout<<"holecheck: "<<count<<" of "<<covered.size()<<" columns without geodat points ("<<100.0*frac<<" %), filled with G 52 = "<<p->G52<<endl;

    if(frac>0.25)
    cout<<endl<<"!!! WARNING holecheck: "<<100.0*frac<<" % of the columns get the base level G 52 = "<<p->G52
        <<". Check that geo.dat covers the domain, the value of G 52 and G 53 !!!"<<endl<<endl;

    if(count==0)
    return;

    p->Dresize(p->G10_x,p->Np,p->Np+int(count));
    p->Dresize(p->G10_y,p->Np,p->Np+int(count));
    p->Dresize(p->G10_z,p->Np,p->Np+int(count));

    for(int ii=0; ii<kx; ++ii)
    for(int jj=0; jj<ky; ++jj)
    if(covered[size_t(ii)*ky + jj]==0)
    {
        p->G10_x[p->Np] = XPc[ii];
        p->G10_y[p->Np] = YPc[jj];
        p->G10_z[p->Np] = p->G52;

        ++p->Np;
    }
}
