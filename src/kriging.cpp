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
#include "dive.h"
#include "lexer.h"
#include <cmath>

kriging::kriging(lexer *p, dive *a, int numpt, double *X, double *Y, double *F)
{
    local = (p->G15==4);
    nnb = p->G16;
}

kriging::~kriging()
{
}

void kriging::start(lexer* p, dive* a, int numpt, double *X, double *Y, double *F, double *XC, double *YC, int kx, int ky, double **f)
{
    const int N = p->Np;

    for(int ii=0; ii<kx; ++ii)
    for(int jj=0; jj<ky; ++jj)
    f[ii+3][jj+3] = 0.0;

    if(N<1)
    {
        cout<<"kriging: no geodat points"<<endl;
        return;
    }

    ini(p,a,N,X,Y,F);

    if(local)
    start_local(p,N,X,Y,F,XC,YC,kx,ky,f);
    else
    start_global(p,N,X,Y,F,XC,YC,kx,ky,f);
}

// Global ordinary kriging in dual form:
// the kriging matrix K = [Gamma 1; 1^T 0] is symmetric, so the estimate
// f(x0) = [F;0]^T K^-1 [g(x0);1] equals sum_n w_n*g_n(x0) + mu, with K*[w;mu] = [F;0].
// One LU decomposition, then O(Np) per grid cell.
void kriging::start_global(lexer* p, int N, double *X, double *Y, double *F, double *XC, double *YC, int kx, int ky, double **f)
{
    const int M = N+1;

    cout<<"kriging global  Np: "<<N<<endl;

    vector<double> G((size_t)M*M);
    vector<int> piv(M);
    vector<double> w(M);

    for(int nn=0; nn<N; ++nn)
    w[nn] = F[nn];

    w[N] = 0.0;

    cout<<"fill Aij"<<endl;
    #pragma omp parallel for schedule(static)
    for(int nn=0; nn<N; ++nn)
    {
        double *Gn = &G[(size_t)nn*M];

        for(int qq=0; qq<N; ++qq)
        {
            const double dx = X[nn]-X[qq];
            const double dy = Y[nn]-Y[qq];

            Gn[qq] = semivariogram(sqrt(dx*dx + dy*dy));
        }

        Gn[N] = 1.0;
    }

    for(int qq=0; qq<N; ++qq)
    G[(size_t)N*M+qq] = 1.0;

    G[(size_t)N*M+N] = 0.0;

    cout<<"matrix solver"<<endl;
    decomp(G,piv,M);
    solve(G,piv,w,M);

    G.clear();
    G.shrink_to_fit();

    const double mu = w[N];

    cout<<"mainloop kriging"<<endl<<endl;

    #pragma omp parallel for collapse(2) schedule(static)
    for(int ii=0; ii<kx; ++ii)
    for(int jj=0; jj<ky; ++jj)
    {
        const double xc = XC[ii+marge];
        const double yc = YC[jj+marge];

        double val = mu;

        for(int nn=0; nn<N; ++nn)
        {
            const double dx = xc-X[nn];
            const double dy = yc-Y[nn];

            val += w[nn]*semivariogram(sqrt(dx*dx + dy*dy));
        }

        f[ii+3][jj+3] = val;
    }

    cout<<"> processed cells: "<<kx*ky<<endl;
}
