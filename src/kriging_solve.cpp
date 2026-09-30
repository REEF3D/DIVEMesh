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
#include <cmath>
#include <utility>

// in-place LU decomposition with partial pivoting, row-major N x N
void kriging::decomp(vector<double> &G, vector<int> &piv, int N)
{
    for(int r=0; r<N; ++r)
    {
        if(r%1000==0)
        cout<<"decomp: "<<r<<endl;

        // pivot search
        int pr = r;
        double vmax = fabs(G[(size_t)r*N+r]);

        for(int nn=r+1; nn<N; ++nn)
        {
            const double v = fabs(G[(size_t)nn*N+r]);

            if(v>vmax)
            {
                vmax = v;
                pr = nn;
            }
        }

        piv[r] = pr;

        if(pr!=r)
        {
            double *Ga = &G[(size_t)r*N];
            double *Gb = &G[(size_t)pr*N];

            for(int qq=0; qq<N; ++qq)
            std::swap(Ga[qq],Gb[qq]);
        }

        const double *Gr = &G[(size_t)r*N];
        const double aii = 1.0/(fabs(Gr[r])>1.0e-19?Gr[r]:1.0e-19);

        // update trailing submatrix
        #pragma omp parallel for schedule(static)
        for(int nn=r+1; nn<N; ++nn)
        {
            double *Gn = &G[(size_t)nn*N];

            const double l = Gn[r]*aii;
            Gn[r] = l;

            if(l!=0.0)
            for(int qq=r+1; qq<N; ++qq)
            Gn[qq] -= l*Gr[qq];
        }
    }
}

// solve LU * x = P*b, b is overwritten with x
void kriging::solve(const vector<double> &G, const vector<int> &piv, vector<double> &b, int N)
{
    for(int r=0; r<N; ++r)
    if(piv[r]!=r)
    std::swap(b[r],b[piv[r]]);

    // forward substitution
    for(int qq=0; qq<N; ++qq)
    {
        const double *Gq = &G[(size_t)qq*N];
        double sum = b[qq];

        for(int nn=0; nn<qq; ++nn)
        sum -= Gq[nn]*b[nn];

        b[qq] = sum;
    }

    // backward substitution
    for(int qq=N-1; qq>=0; --qq)
    {
        const double *Gq = &G[(size_t)qq*N];
        double sum = b[qq];

        for(int nn=qq+1; nn<N; ++nn)
        sum -= Gq[nn]*b[nn];

        b[qq] = sum/(fabs(Gq[qq])>1.0e-19?Gq[qq]:1.0e-19);
    }
}

// small dense system A*x = b with partial pivoting, row-major m x m, A and b are overwritten, b holds x
void kriging::solve_small(double *A, double *b, int m)
{
    for(int r=0; r<m; ++r)
    {
        int pr = r;
        double vmax = fabs(A[r*m+r]);

        for(int nn=r+1; nn<m; ++nn)
        if(fabs(A[nn*m+r])>vmax)
        {
            vmax = fabs(A[nn*m+r]);
            pr = nn;
        }

        if(pr!=r)
        {
            for(int qq=0; qq<m; ++qq)
            std::swap(A[r*m+qq],A[pr*m+qq]);

            std::swap(b[r],b[pr]);
        }

        const double aii = 1.0/(fabs(A[r*m+r])>1.0e-19?A[r*m+r]:1.0e-19);

        for(int nn=r+1; nn<m; ++nn)
        {
            const double l = A[nn*m+r]*aii;

            if(l!=0.0)
            {
                for(int qq=r+1; qq<m; ++qq)
                A[nn*m+qq] -= l*A[r*m+qq];

                b[nn] -= l*b[r];
            }
        }
    }

    for(int qq=m-1; qq>=0; --qq)
    {
        double sum = b[qq];

        for(int nn=qq+1; nn<m; ++nn)
        sum -= A[qq*m+nn]*b[nn];

        b[qq] = sum/(fabs(A[qq*m+qq])>1.0e-19?A[qq*m+qq]:1.0e-19);
    }
}
