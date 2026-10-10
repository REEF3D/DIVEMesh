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

#include"corridor.h"
#include<cmath>
#include<limits>
#include<algorithm>

// connected components of the true cells (conn 4 or 8), labels 1..n, 0 elsewhere
int corridor::label(const vector<char> &m, vector<int> &lab, int conn) const
{
    lab.assign(m.size(),0);
    vector<int> stack;
    int n=0;

    for(int q=0; q<nx*ny; ++q)
    if(m[q] && lab[q]==0)
    {
        ++n;
        lab[q]=n;
        stack.push_back(q);

        while(!stack.empty())
        {
            const int p=stack.back();
            stack.pop_back();
            const int pi=p%nx, pj=p/nx;

            for(int dj=-1; dj<=1; ++dj)
            for(int di=-1; di<=1; ++di)
            {
                if(di==0 && dj==0)
                continue;
                if(conn==4 && di!=0 && dj!=0)
                continue;

                const int ii=pi+di, jj=pj+dj;
                if(ii<0 || ii>=nx || jj<0 || jj>=ny)
                continue;

                const int r=id(ii,jj);
                if(m[r] && lab[r]==0)
                {
                    lab[r]=n;
                    stack.push_back(r);
                }
            }
        }
    }

    return n;
}

// keep the largest connected component
void corridor::main_component(vector<char> &m, int conn) const
{
    vector<int> lab;
    const int n=label(m,lab,conn);

    if(n==0)
    return;

    vector<long> size(n+1,0);
    for(int q=0; q<nx*ny; ++q)
    ++size[lab[q]];

    size[0]=0;
    const int big=int(std::max_element(size.begin(),size.end())-size.begin());

    for(int q=0; q<nx*ny; ++q)
    m[q] = (lab[q]==big);
}

// false regions that do not touch the raster edge become true (islands, enclosed dry areas)
void corridor::fill_holes(vector<char> &m) const
{
    vector<char> c(m.size());
    for(int q=0; q<nx*ny; ++q)
    c[q]=!m[q];

    vector<int> lab;
    const int n=label(c,lab,4);

    vector<char> edge(n+1,0);
    for(int i=0; i<nx; ++i)
    {
        edge[lab[id(i,0)]]=1;
        edge[lab[id(i,ny-1)]]=1;
    }
    for(int j=0; j<ny; ++j)
    {
        edge[lab[id(0,j)]]=1;
        edge[lab[id(nx-1,j)]]=1;
    }

    for(int q=0; q<nx*ny; ++q)
    if(c[q] && !edge[lab[q]])
    m[q]=1;
}

// exact Euclidean distance (m) from every cell to the nearest true cell (Felzenszwalb & Huttenlocher)
void corridor::dist_to(const vector<char> &m, vector<double> &d) const
{
    const double INF=1.0e20;
    d.assign(m.size(),INF);

    for(int q=0; q<nx*ny; ++q)
    if(m[q])
    d[q]=0.0;

    auto pass=[&](int n, auto get, auto set)
    {
        vector<double> f(n), out(n), z(n+1);
        vector<int> v(n);

        f.assign(n,0.0);
        for(int q=0; q<n; ++q)
        f[q]=get(q);

        int k=0;
        v[0]=0;
        z[0]=-INF;
        z[1]=INF;

        for(int q=1; q<n; ++q)
        {
            double s=((f[q]+double(q)*q)-(f[v[k]]+double(v[k])*v[k]))/(2.0*q-2.0*v[k]);
            while(s<=z[k])          // z[0] = -INF ends the loop at k = 0
            {
                --k;
                s=((f[q]+double(q)*q)-(f[v[k]]+double(v[k])*v[k]))/(2.0*q-2.0*v[k]);
            }
            ++k;
            v[k]=q;
            z[k]=s;
            z[k+1]=INF;
        }

        k=0;
        for(int q=0; q<n; ++q)
        {
            while(z[k+1]<q)
            ++k;
            out[q]=double(q-v[k])*(q-v[k])+f[v[k]];
        }

        for(int q=0; q<n; ++q)
        set(q,out[q]);
    };

    for(int j=0; j<ny; ++j)
    pass(nx,[&](int q){return d[id(q,j)];},[&](int q,double val){d[id(q,j)]=val;});

    for(int i=0; i<nx; ++i)
    pass(ny,[&](int q){return d[id(i,q)];},[&](int q,double val){d[id(i,q)]=val;});

    for(int q=0; q<nx*ny; ++q)
    d[q]=std::sqrt(d[q])*h;
}

// separable Gaussian, sigma in m, nearest-value edges
void corridor::blur(vector<double> &f, double sigma) const
{
    const double s=sigma/h;
    const int r=std::max(1,int(std::ceil(3.0*s)));
    vector<double> w(2*r+1);
    double sum=0.0;

    for(int k=-r; k<=r; ++k)
    {
        w[k+r]=std::exp(-0.5*k*k/(s*s));
        sum+=w[k+r];
    }
    for(double &v : w)
    v/=sum;

    vector<double> g(f.size());

    for(int j=0; j<ny; ++j)
    for(int i=0; i<nx; ++i)
    {
        double v=0.0;
        for(int k=-r; k<=r; ++k)
        v+=w[k+r]*f[id(std::min(std::max(i+k,0),nx-1),j)];
        g[id(i,j)]=v;
    }

    for(int j=0; j<ny; ++j)
    for(int i=0; i<nx; ++i)
    {
        double v=0.0;
        for(int k=-r; k<=r; ++k)
        v+=w[k+r]*g[id(i,std::min(std::max(j+k,0),ny-1))];
        f[id(i,j)]=v;
    }
}

// it iterations of a 4-neighbour dilation
void corridor::dilate4(vector<char> &m, int it) const
{
    for(int n=0; n<it; ++n)
    {
        vector<char> o=m;

        for(int j=0; j<ny; ++j)
        for(int i=0; i<nx; ++i)
        if(!o[id(i,j)])
        if((i>0 && o[id(i-1,j)]) || (i<nx-1 && o[id(i+1,j)]) || (j>0 && o[id(i,j-1)]) || (j<ny-1 && o[id(i,j+1)]))
        m[id(i,j)]=1;
    }
}

// bilinear interpolation between cell centres, clamped at the raster edge
double corridor::bilin(const vector<double> &f, double x, double y) const
{
    double fx=(x-x0)/h, fy=(y-y0)/h;
    fx=std::min(std::max(fx,0.0),double(nx-1)-1.0e-9);
    fy=std::min(std::max(fy,0.0),double(ny-1)-1.0e-9);

    const int i=int(fx), j=int(fy);
    const double a=fx-i, b=fy-j;

    return (1.0-a)*(1.0-b)*f[id(i,j)] + a*(1.0-b)*f[id(i+1,j)] + (1.0-a)*b*f[id(i,j+1)] + a*b*f[id(i+1,j+1)];
}

int corridor::cell(double x, double y) const
{
    const int i=int(std::floor((x-x0)/h+0.5)), j=int(std::floor((y-y0)/h+0.5));

    if(i<0 || i>=nx || j<0 || j>=ny)
    return -1;

    return id(i,j);
}
