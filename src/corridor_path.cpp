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
#include"lexer.h"
#include<cmath>
#include<queue>
#include<fstream>
#include<iostream>
#include<cstdlib>
#include<algorithm>

// the wet runs where the river leaves the raster: inflow on a side with C 1x = 1 or 6, outflow on a
// side with C 1x = 2, 7 or 8 (C 11 x-min, C 14 x-max, C 13 y-min, C 12 y-max); without those the two
// longest runs.  start/end: the cell of the run farthest from the banks.
void corridor::side_runs(const vector<char> &m, int &start, int &end, lexer *p) const
{
    struct run { int side, len, best; double dmax; };
    vector<run> runs;

    vector<char> notm(m.size());
    for(size_t q=0; q<m.size(); ++q) notm[q]=!m[q];
    vector<double> d;
    dist_to(notm,d);

    const int ctype[4]={p->C11,p->C14,p->C13,p->C12};

    for(int side=0; side<4; ++side)
    {
        const int n = (side<2) ? ny : nx;
        run r={side,0,-1,-1.0};

        for(int k=0; k<=n; ++k)
        {
            int q=-1;
            if(k<n)
            q = (side==0) ? id(0,k) : (side==1) ? id(nx-1,k) : (side==2) ? id(k,0) : id(k,ny-1);

            if(q>=0 && m[q])
            {
                ++r.len;
                if(d[q]>r.dmax)
                {
                    r.dmax=d[q];
                    r.best=q;
                }
            }
            else if(r.len>0)
            {
                runs.push_back(r);
                r={side,0,-1,-1.0};
            }
        }
    }

    auto longest=[&](auto pred)
    {
        int b=-1;
        for(int k=0; k<int(runs.size()); ++k)
        if(pred(runs[k]) && (b<0 || runs[k].len>runs[b].len))
        b=k;
        return b;
    };

    int bi=longest([&](const run &r){int c=ctype[r.side]; return c==1 || c==6;});
    int bo=longest([&](const run &r){int c=ctype[r.side]; return c==2 || c==7 || c==8;});

    if(bi<0 || bo<0)
    {
        bi=longest([](const run&){return true;});
        bo=longest([&](const run &r){return &r!=&runs[bi];});
        cout<<"corridor grid: no wet inflow/outflow sides from C 11-14, using the two longest wet edge runs"<<endl;
    }

    if(bi<0 || bo<0)
    {
        cout<<"!!! corridor grid: the area below R 2 does not reach the domain edge twice !!!"<<endl;
        exit(1);
    }

    start=runs[bi].best;
    end=runs[bo].best;
}

// centreline: least-cost path along the medial ridge of the wet area below R 2
void corridor::centreline(lexer *p)
{
    vector<double> px,py;

    if(p->R7==1)
    {
        if(!read_centreline(p))
        exit(1);

        // a user line is only resampled and lightly smoothed
        px=cx; py=cy;
        stations(px,py,2.0*h);
        return;
    }

    const int N=nx*ny;
    vector<char> m(N);
    for(int q=0; q<N; ++q)
    m[q] = (bed[q]<p->R2 && !solid[q]);

    main_component(m,4);

    // close gaps of a few cells (bridges, narrow shallows)
    {
        vector<char> c=m;
        dilate4(c,3);
        vector<char> nc(N);
        for(int q=0; q<N; ++q) nc[q]=!c[q];
        dilate4(nc,3);
        for(int q=0; q<N; ++q)
        m[q] = (m[q] || !nc[q]) && !solid[q];
    }

    vector<char> notm(N);
    for(int q=0; q<N; ++q) notm[q]=!m[q];
    vector<double> dt;
    dist_to(notm,dt);
    for(double &v : dt) v/=h;            // in cells

    int s0,s1;
    side_runs(m,s0,s1,p);

    // Dijkstra on the wet cells, 8 neighbours, cost = length / (distance to the bank + 0.5)^2
    vector<double> dist(N,1.0e300);
    vector<int> pred(N,-1);
    typedef std::pair<double,int> item;
    std::priority_queue<item,vector<item>,std::greater<item>> pq;
    dist[s0]=0.0;
    pq.push(item(0.0,s0));

    while(!pq.empty())
    {
        const item it=pq.top();
        pq.pop();
        const int q=it.second;
        if(it.first>dist[q])
        continue;
        if(q==s1)
        break;

        const int qi=q%nx, qj=q/nx;
        for(int dj=-1; dj<=1; ++dj)
        for(int di=-1; di<=1; ++di)
        {
            if(di==0 && dj==0)
            continue;
            const int ii=qi+di, jj=qj+dj;
            if(ii<0 || ii>=nx || jj<0 || jj>=ny)
            continue;
            const int r=id(ii,jj);
            if(!m[r])
            continue;
            const double L=(di!=0 && dj!=0) ? std::sqrt(2.0) : 1.0;
            const double w=0.5*(dt[q]+dt[r])+0.5;
            const double nd=dist[q]+L/(w*w);
            if(nd<dist[r])
            {
                dist[r]=nd;
                pred[r]=q;
                pq.push(item(nd,r));
            }
        }
    }

    if(pred[s1]<0)
    {
        cout<<"!!! corridor grid: no wet connection between inflow and outflow below R 2 !!!"<<endl;
        exit(1);
    }

    vector<int> path;
    for(int q=s1; q>=0; q=pred[q])
    {
        path.push_back(q);
        if(q==s0)
        break;
    }
    std::reverse(path.begin(),path.end());

    for(int q : path)
    {
        px.push_back(x0+(q%nx)*h);
        py.push_back(y0+(q/nx)*h);
    }

    stations(px,py,p->R8);
}

// centreline from corridor-centreline.dat: x y per line, from the inflow to the outflow
bool corridor::read_centreline(lexer *p)
{
    std::ifstream in("corridor-centreline.dat");
    if(!in)
    {
        cout<<"!!! corridor grid: R 7 1 needs corridor-centreline.dat (x y per line) !!!"<<endl;
        return false;
    }

    cx.clear(); cy.clear();
    double x,y;
    while(in>>x>>y)
    {
        cx.push_back(x);
        cy.push_back(y);
    }

    if(cx.size()<2)
    {
        cout<<"!!! corridor grid: corridor-centreline.dat holds fewer than 2 points !!!"<<endl;
        return false;
    }

    cout<<"corridor grid: centreline from corridor-centreline.dat, "<<cx.size()<<" points"<<endl;
    return true;
}

// stations every h/2 along the polyline, Gaussian-smoothed over sigma (m), unit normals to the left
void corridor::stations(vector<double> &px, vector<double> &py, double sigma)
{
    auto resample=[&](vector<double> &x, vector<double> &y, double ds)
    {
        vector<double> s(x.size(),0.0);
        for(size_t k=1; k<x.size(); ++k)
        s[k]=s[k-1]+std::hypot(x[k]-x[k-1],y[k]-y[k-1]);

        const int n=std::max(2,int(s.back()/ds)+1);
        vector<double> X(n),Y(n);
        size_t k=0;
        for(int q=0; q<n; ++q)
        {
            const double t=s.back()*q/(n-1);
            while(k+1<s.size()-1 && s[k+1]<t) ++k;
            const double a=(s[k+1]>s[k]) ? (t-s[k])/(s[k+1]-s[k]) : 0.0;
            X[q]=x[k]+a*(x[k+1]-x[k]);
            Y[q]=y[k]+a*(y[k+1]-y[k]);
        }
        x=X; y=Y;
    };

    const double ds=0.5*h;
    resample(px,py,ds);

    // Gaussian smoothing along the line, ends held at the nearest value
    const double sg=std::max(sigma/ds,1.0e-6);
    const int r=int(std::ceil(3.0*sg));
    const int n=int(px.size());
    vector<double> sx(n),sy(n);
    for(int q=0; q<n; ++q)
    {
        double wx=0.0, wy=0.0, ws=0.0;
        for(int k=-r; k<=r; ++k)
        {
            const int c=std::min(std::max(q+k,0),n-1);
            const double w=std::exp(-0.5*k*k/(sg*sg));
            wx+=w*px[c]; wy+=w*py[c]; ws+=w;
        }
        sx[q]=wx/ws; sy[q]=wy/ws;
    }
    resample(sx,sy,ds);

    const int m=int(sx.size());
    cx=sx; cy=sy;
    cnx.assign(m,0.0); cny.assign(m,0.0); cs.assign(m,0.0);

    for(int q=0; q<m; ++q)
    {
        const int a=std::max(q-1,0), b=std::min(q+1,m-1);
        const double tx=cx[b]-cx[a], ty=cy[b]-cy[a], tl=std::hypot(tx,ty);
        cnx[q]=-ty/tl;
        cny[q]= tx/tl;
        if(q>0)
        cs[q]=cs[q-1]+std::hypot(cx[q]-cx[q-1],cy[q]-cy[q-1]);
    }

    cout<<"corridor grid: centreline "<<cs.back()<<" m, "<<m<<" stations"<<endl;
}
