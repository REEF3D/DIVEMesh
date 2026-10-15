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
#include"dive.h"
#include"increment.h"
#include<cmath>
#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<queue>
#include<vector>

corridor::corridor(lexer *p, dive *a) : nx(0),ny(0),x0(0.0),y0(0.0),h(1.0),ni(0),nj(0)
{
    cut_L[0]=cut_L[1]=0.0;
}

corridor::~corridor()
{
}

void corridor::start(lexer *p, dive *a)
{
    cout<<"corridor grid"<<endl;

    if(p->R3==0)
    p->R3_wl = p->R2 + 1.0;

    build_raster(p,a);
    centreline(p);
    region(p);
    solve_fields(p);
    trace_grid(p);
    smooth(p);
    quality_and_output(p,a);
}

// uniform working raster over the Cartesian grid: bed level and solid columns of the nearest cell
void corridor::build_raster(lexer *p, dive *a)
{
    const int m=increment::marge;
    const double xmin=p->XN[m], xmax=p->XN[a->knox+m];
    const double ymin=p->YN[m], ymax=p->YN[a->knoy+m];
    const double dxh=std::min((xmax-xmin)/double(a->knox),(ymax-ymin)/double(a->knoy));

    h = (p->R9>0.0) ? p->R9 : std::max(dxh,1.0);
    nx = int(std::floor((xmax-xmin)/h));
    ny = int(std::floor((ymax-ymin)/h));
    x0 = xmin + 0.5*(xmax-xmin-nx*h) + 0.5*h;
    y0 = ymin + 0.5*(ymax-ymin-ny*h) + 0.5*h;

    if(nx<8 || ny<8)
    {
        cout<<"!!! corridor grid: working raster "<<nx<<" x "<<ny<<" too small (R 9) !!!"<<endl;
        exit(1);
    }

    auto locate=[&](const double *N, int n, double v)
    {
        const double *b=N+m, *e=N+m+n+1;
        int c=int(std::upper_bound(b,e,v)-b)-1;
        return std::min(std::max(c,0),n-1);
    };

    bed.assign(nx*ny,0.0);
    solid.assign(nx*ny,0);

    for(int jj=0; jj<ny; ++jj)
    for(int ii=0; ii<nx; ++ii)
    {
        const int ci=locate(p->XN,a->knox,x0+ii*h);
        const int cj=locate(p->YN,a->knoy,y0+jj*h);
        bed[id(ii,jj)] = a->bedlevel(ci,cj);
        solid[id(ii,jj)] = (a->flagslice(ci,cj)<0) ? 1 : 0;
    }

    cout<<"corridor grid: working raster "<<nx<<" x "<<ny<<", h = "<<h<<" m"<<endl;
}

// distance from centreline station q to the corridor envelope edge along the normal (first exit)
double corridor::reach(int q, double sign) const
{
    const double dr=0.5*h;
    double r=0.0;

    for(; r<400.0; r+=dr)
    {
        const int c=cell(cx[q]+sign*r*cnx[q], cy[q]+sign*r*cny[q]);
        if(c<0 || !env[c])
        break;
    }

    return r;
}

// thalweg: least-cost path over the bed between two raster cells, cost exp((z - zmin)/2 m) per length
vector<int> corridor::thalweg(int c0, int c1) const
{
    const int N=nx*ny;
    typedef std::pair<double,int> item;

    double zmin=1.0e20;
    for(int q=0; q<N; ++q)
    if(!solid[q]) zmin=std::min(zmin,bed[q]);

    vector<double> dist(N,1.0e300);
    vector<int> pred(N,-1);
    std::priority_queue<item,vector<item>,std::greater<item>> pq;
    dist[c0]=0.0;
    pq.push(item(0.0,c0));
    while(!pq.empty())
    {
        const item it=pq.top();
        pq.pop();
        const int q=it.second;
        if(it.first>dist[q]) continue;
        if(q==c1) break;
        const int qi=q%nx, qj=q/nx;
        for(int dj=-1; dj<=1; ++dj)
        for(int di=-1; di<=1; ++di)
        {
            if(di==0 && dj==0) continue;
            const int ii=qi+di, jj=qj+dj;
            if(ii<0 || ii>=nx || jj<0 || jj>=ny) continue;
            const int r=id(ii,jj);
            if(solid[r]) continue;
            const double L=(di!=0 && dj!=0) ? std::sqrt(2.0) : 1.0;
            const double nd=dist[q]+L*std::exp(std::min((bed[r]-zmin)/2.0,600.0));
            if(nd<dist[r])
            {
                dist[r]=nd;
                pred[r]=q;
                pq.push(item(nd,r));
            }
        }
    }

    vector<int> path;
    if(pred[c1]<0 && c1!=c0)
    {
        cout<<"!!! corridor grid: R 10 finds no thalweg between the inflow and the outflow !!!"<<endl;
        exit(1);
    }
    for(int q=c1; q>=0; q=pred[q])
    {
        path.push_back(q);
        if(q==c0) break;
    }
    std::reverse(path.begin(),path.end());
    return path;
}

// lowest cell near cell c: on the raster edge the lowest cell of the run of cells below the level wl along
// that edge that holds c (the wet edge run of the centreline), elsewhere within 200 m of c
int corridor::lowest_near(int c, double wl) const
{
    const int ci=c%nx, cj=c/nx;
    const bool ei=(ci==0 || ci==nx-1), ej=(cj==0 || cj==ny-1);
    int best=c;

    if(ei || ej)
    {
        // walk along the edge in both directions
        const int n = ei ? ny : nx;
        const int k0 = ei ? cj : ci;
        auto at=[&](int k){ return ei ? id(ci,k) : id(k,cj); };
        for(int dir=-1; dir<=1; dir+=2)
        for(int k=k0; k>=0 && k<n; k+=dir)
        {
            const int q=at(k);
            if(solid[q] || (k!=k0 && bed[q]>=wl))
            break;
            if(bed[q]<bed[best])
            best=q;
        }
        return best;
    }

    const int r=int(std::ceil(200.0/h));
    for(int jj=std::max(cj-r,0); jj<=std::min(cj+r,ny-1); ++jj)
    for(int ii=std::max(ci-r,0); ii<=std::min(ci+r,nx-1); ++ii)
    {
        const int q=id(ii,jj);
        if((ii-ci)*(ii-ci)+(jj-cj)*(jj-cj)<=r*r && !solid[q] && bed[q]<bed[best])
        best=q;
    }
    return best;
}

// river bed level for R 10 (sloping rivers), a height-above-the-river reference:
//   1 thalweg  (corridor::thalweg) from the centreline (R 10 without R 7), or between the lowest cells
//              near the ends of the given centreline (R 7 1: within 200 m, or the edge cell itself)
//   2 profile  bed along the thalweg, smoothed over 200 m of its length (pools, saddles, bridges)
//   3 field    every raster cell takes the profile level of its nearest thalweg cell (Dijkstra over the
//              raster, 8 neighbours), solid cells included
void corridor::river_level(vector<double> &zr) const
{
    const int N=nx*ny, ns=int(cx.size());
    typedef std::pair<double,int> item;

    vector<int> path=tpath;
    if(path.empty())
    {
        const int a=cell(cx[0],cy[0]), b=cell(cx[ns-1],cy[ns-1]);
        if(a<0 || b<0)
        {
            cout<<"!!! corridor grid: R 10, the centreline ends lie outside the raster !!!"<<endl;
            exit(1);
        }
        path=thalweg(lowest_near(a,-1.0e20),lowest_near(b,-1.0e20));
    }

    // 2 profile, Gaussian over 200 m of the thalweg length
    const int np=int(path.size());
    vector<double> sp(np,0.0), zp(np), zs(np);
    for(int k=0; k<np; ++k)
    {
        zp[k]=bed[path[k]];
        if(k>0)
        sp[k]=sp[k-1]+h*std::hypot(double(path[k]%nx-path[k-1]%nx),double(path[k]/nx-path[k-1]/nx));
    }
    {
        const double sg=200.0;
        int lo=0, hi=0;
        for(int k=0; k<np; ++k)
        {
            while(sp[k]-sp[lo]>3.0*sg) ++lo;
            while(hi<np-1 && sp[hi+1]-sp[k]<=3.0*sg) ++hi;
            double wz=0.0, ws=0.0;
            for(int m=lo; m<=hi; ++m)
            {
                const double w=std::exp(-0.5*(sp[m]-sp[k])*(sp[m]-sp[k])/(sg*sg));
                wz+=w*zp[m]; ws+=w;
            }
            zs[k]=wz/ws;
        }
    }

    // 3 field: level of the nearest thalweg cell
    zr.assign(N,-1.0e20);
    {
        vector<double> d(N,1.0e300);
        std::priority_queue<item,vector<item>,std::greater<item>> pq;
        for(int k=0; k<np; ++k)
        {
            d[path[k]]=0.0;
            zr[path[k]]=zs[k];
            pq.push(item(0.0,path[k]));
        }
        while(!pq.empty())
        {
            const item it=pq.top();
            pq.pop();
            const int q=it.second;
            if(it.first>d[q]) continue;
            const int qi=q%nx, qj=q/nx;
            for(int dj=-1; dj<=1; ++dj)
            for(int di=-1; di<=1; ++di)
            {
                if(di==0 && dj==0) continue;
                const int ii=qi+di, jj=qj+dj;
                if(ii<0 || ii>=nx || jj<0 || jj>=ny) continue;
                const int r=id(ii,jj);
                const double nd=d[q]+((di!=0 && dj!=0) ? std::sqrt(2.0) : 1.0);
                if(nd<d[r])
                {
                    d[r]=nd;
                    zr[r]=zr[q];
                    pq.push(item(nd,r));
                }
            }
        }
    }

    cout<<"corridor grid: thalweg "<<sp.back()<<" m, river bed level "<<zs.front()<<" m at the inflow, "<<zs.back()
        <<" m at the outflow (R 10)"<<endl;
}

// corridor region: envelope of R 3 wl (or R 10: river bed level + H) + margin, islands filled, inlets removed, banks smoothed,
// cut square to the channel at the first and last station whose cross-section fits the raster
void corridor::region(lexer *p)
{
    const int N=nx*ny;
    vector<double> d;

    env.assign(N,0);

    if(p->R10==0)
    for(int q=0; q<N; ++q)
    env[q] = (bed[q]<p->R3_wl && !solid[q]);

    // R 10 H: corridor relative to the river, the bed below the river bed level of the nearest station + H
    if(p->R10==1)
    {
        vector<double> zr;
        river_level(zr);
        for(int q=0; q<N; ++q)
        env[q] = (zr[q]>-1.0e19 && bed[q]<zr[q]+p->R10_H && !solid[q]);
    }

    main_component(env,4);
    fill_holes(env);

    dist_to(env,d);
    for(int q=0; q<N; ++q)
    env[q] = (d[q]<=p->R3_m+1.0e-9) && !solid[q];

    // end stations
    const int ns=int(cx.size());
    const double xa=x0, xb=x0+(nx-1)*h, ya=y0, yb=y0+(ny-1)*h;

    auto fits=[&](int q)
    {
        const double wl=reach(q,1.0), wr=reach(q,-1.0);
        for(int k=0; k<50; ++k)
        {
            const double t=-wr+(wl+wr)*k/49.0;
            const double px=cx[q]+t*cnx[q], py=cy[q]+t*cny[q];
            if(px<xa || px>xb || py<ya || py>yb)
            return false;
        }
        return true;
    };

    int q0=0, q1=ns-1;
    while(q0<ns-1 && !fits(q0)) ++q0;
    while(q1>q0 && !fits(q1)) --q1;

    if(q1-q0<10)
    {
        cout<<"!!! corridor grid: no cross-section of the corridor fits into the domain !!!"<<endl;
        exit(1);
    }

    // open: erode and dilate by R 5, then smooth the banks
    vector<char> er(N);
    {
        vector<char> notenv(N);
        for(int q=0; q<N; ++q) notenv[q]=!env[q];
        dist_to(notenv,d);
        for(int q=0; q<N; ++q) er[q] = d[q]>p->R5;
        dist_to(er,d);
    }

    vector<double> f(N);
    {
        vector<char> op(N);
        for(int q=0; q<N; ++q) op[q] = d[q]<=p->R5;
        main_component(op,4);
        for(int q=0; q<N; ++q) f[q]=op[q];
    }
    blur(f,8.0);

    R.assign(N,0);
    for(int q=0; q<N; ++q)
    R[q] = (f[q]>0.5) && !solid[q];

    // cuts
    const int qe[2]={q0,q1};
    for(int c=0; c<2; ++c)
    {
        const int q=qe[c];
        const double tx=cny[q], ty=-cnx[q];      // as (n_y,-n_x), the sign does not matter
        cut_L[c]=std::max(reach(q,1.0),reach(q,-1.0))+80.0;
        cut_t[c].assign(N,0.0);
        cut_n[c].assign(N,0.0);

        for(int jj=0; jj<ny; ++jj)
        for(int ii=0; ii<nx; ++ii)
        {
            const double X=x0+ii*h, Y=y0+jj*h;
            const double dt=(X-cx[q])*tx+(Y-cy[q])*ty, dn=(X-cx[q])*cnx[q]+(Y-cy[q])*cny[q];
            cut_t[c][id(ii,jj)]=dt;
            cut_n[c][id(ii,jj)]=dn;
            if(std::fabs(dt)<h && std::fabs(dn)<cut_L[c])
            R[id(ii,jj)]=0;
        }
    }

    // the part between the cuts: the component that holds the middle station
    vector<int> lab;
    label(R,lab,4);
    const int cm=cell(cx[(q0+q1)/2],cy[(q0+q1)/2]);
    const int keep=(cm>=0) ? lab[cm] : 0;

    if(keep==0)
    {
        cout<<"!!! corridor grid: the centreline leaves the corridor (check R 2, R 3) !!!"<<endl;
        exit(1);
    }

    for(int q=0; q<N; ++q)
    R[q] = (lab[q]==keep);

    // centreline between the cuts
    auto trim=[&](vector<double> &v){ v=vector<double>(v.begin()+q0,v.begin()+q1+1); };
    trim(cx); trim(cy); trim(cnx); trim(cny); trim(cs);
    const double s0=cs[0];
    for(double &v : cs) v-=s0;

    long count=0;
    for(int q=0; q<N; ++q) count+=R[q];

    cout<<"corridor grid: length "<<cs.back()<<" m, area "<<count*h*h/1.0e6<<" km2"<<endl;
}
