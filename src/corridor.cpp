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

// corridor region: envelope of R 3 wl + margin, islands filled, inlets removed, banks smoothed,
// cut square to the channel at the first and last station whose cross-section fits the raster
void corridor::region(lexer *p)
{
    const int N=nx*ny;
    vector<double> d;

    env.assign(N,0);
    for(int q=0; q<N; ++q)
    env[q] = (bed[q]<p->R3_wl && !solid[q]);

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
