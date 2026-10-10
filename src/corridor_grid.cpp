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
#include<cmath>
#include<fstream>
#include<iostream>
#include<iomanip>
#include<sstream>
#include<algorithm>
#include"increment.h"

// banks smoothed along the river (the corridor only follows it), straight ends, then Winslow
// smoothing of the interior starting from the harmonic grid
void corridor::smooth(lexer *p)
{
    const double sig=4.0;
    const int r=int(std::ceil(3.0*sig));

    auto gauss=[&](const vector<double> &v)
    {
        const int n=int(v.size());
        vector<double> o(n);
        for(int q=0; q<n; ++q)
        {
            double s=0.0, ws=0.0;
            for(int k=-r; k<=r; ++k)
            {
                const double w=std::exp(-0.5*k*k/(sig*sig));
                s+=w*v[std::min(std::max(q+k,0),n-1)];
                ws+=w;
            }
            o[q]=s/ws;
        }
        return o;
    };

    for(int jb=0; jb<=nj; jb+=nj)
    {
        vector<double> bx(ni+1),by(ni+1);
        for(int i=0; i<=ni; ++i) { bx[i]=X[nd(i,jb)]; by[i]=Y[nd(i,jb)]; }

        vector<double> gx=gauss(bx), gy=gauss(by);
        for(int i=1; i<ni; ++i) { bx[i]=gx[i]; by[i]=gy[i]; }

        // node spacing along the bank: smoothed version of the harmonic spacing
        vector<double> d(ni+1,0.0), dl(ni);
        for(int i=1; i<=ni; ++i)
        {
            dl[i-1]=std::hypot(bx[i]-bx[i-1],by[i]-by[i-1]);
            d[i]=d[i-1]+dl[i-1];
        }
        vector<double> dls=gauss(dl), w(ni+1,0.0);
        for(int i=1; i<=ni; ++i) w[i]=w[i-1]+dls[i-1];
        for(int i=0; i<=ni; ++i) w[i]*=d[ni]/w[ni];

        for(int i=0; i<=ni; ++i)
        {
            size_t k=std::upper_bound(d.begin(),d.end(),w[i])-d.begin();
            k=std::min(std::max(k,size_t(1)),size_t(ni));
            const double a=(d[k]>d[k-1]) ? (w[i]-d[k-1])/(d[k]-d[k-1]) : 0.0;
            X[nd(i,jb)]=bx[k-1]+a*(bx[k]-bx[k-1]);
            Y[nd(i,jb)]=by[k-1]+a*(by[k]-by[k-1]);
        }
    }

    for(int ib=0; ib<=ni; ib+=ni)
    for(int j=1; j<nj; ++j)
    {
        const double e=j/double(nj);
        X[nd(ib,j)]=X[nd(ib,0)]+e*(X[nd(ib,nj)]-X[nd(ib,0)]);
        Y[nd(ib,j)]=Y[nd(ib,0)]+e*(Y[nd(ib,nj)]-Y[nd(ib,0)]);
    }

    // Winslow: alpha f_xixi - 2 beta f_xieta + gamma f_etaeta = 0, Jacobi with relaxation 0.7
    vector<double> Xn=X, Yn=Y;
    for(int it=0; it<p->R6; ++it)
    {
        for(int j=1; j<nj; ++j)
        for(int i=1; i<ni; ++i)
        {
            const double xxi=0.5*(X[nd(i+1,j)]-X[nd(i-1,j)]), yxi=0.5*(Y[nd(i+1,j)]-Y[nd(i-1,j)]);
            const double xet=0.5*(X[nd(i,j+1)]-X[nd(i,j-1)]), yet=0.5*(Y[nd(i,j+1)]-Y[nd(i,j-1)]);
            const double al=xet*xet+yet*yet, be=xxi*xet+yxi*yet, ga=xxi*xxi+yxi*yxi;
            const double den=2.0*(al+ga);
            if(den<1.0e-30) continue;

            const double cxr=X[nd(i+1,j+1)]-X[nd(i+1,j-1)]-X[nd(i-1,j+1)]+X[nd(i-1,j-1)];
            const double cyr=Y[nd(i+1,j+1)]-Y[nd(i+1,j-1)]-Y[nd(i-1,j+1)]+Y[nd(i-1,j-1)];
            const double xn=(al*(X[nd(i+1,j)]+X[nd(i-1,j)])+ga*(X[nd(i,j+1)]+X[nd(i,j-1)])-0.5*be*cxr)/den;
            const double yn=(al*(Y[nd(i+1,j)]+Y[nd(i-1,j)])+ga*(Y[nd(i,j+1)]+Y[nd(i,j-1)])-0.5*be*cyr)/den;
            Xn[nd(i,j)]=0.7*xn+0.3*X[nd(i,j)];
            Yn[nd(i,j)]=0.7*yn+0.3*Y[nd(i,j)];
        }
        X.swap(Xn);
        Y.swap(Yn);
        for(int j=1; j<nj; ++j)
        for(int i=1; i<ni; ++i)
        {
            Xn[nd(i,j)]=X[nd(i,j)];
            Yn[nd(i,j)]=Y[nd(i,j)];
        }
    }
}

// bed level of the Cartesian grid, bilinear between its cell centres
double corridor::bed_at(lexer *p, dive *a, double x, double y) const
{
    const int m=increment::marge;

    auto loc=[&](const double *P, int n, double v, int &c, double &w)
    {
        const double *b=P+m, *e=P+m+n;
        c=int(std::upper_bound(b,e,v)-b)-1;
        c=std::min(std::max(c,0),n-2);
        w=(P[m+c+1]>P[m+c]) ? (v-P[m+c])/(P[m+c+1]-P[m+c]) : 0.0;
        w=std::min(std::max(w,0.0),1.0);
    };

    if(a->knox<2 || a->knoy<2)
    return a->bedlevel(0,0);

    int ci,cj;
    double wx,wy;
    loc(p->XP,a->knox,x,ci,wx);
    loc(p->YP,a->knoy,y,cj,wy);

    return (1.0-wx)*(1.0-wy)*a->bedlevel(ci,cj) + wx*(1.0-wy)*a->bedlevel(ci+1,cj)
         + (1.0-wx)*wy*a->bedlevel(ci,cj+1) + wx*wy*a->bedlevel(ci+1,cj+1);
}

void corridor::quality_and_output(lexer *p, dive *a)
{
    const int nn=(ni+1)*(nj+1), nc=ni*nj;

    ZB.assign(nn,0.0);
    for(int j=0; j<=nj; ++j)
    for(int i=0; i<=ni; ++i)
    ZB[nd(i,j)]=bed_at(p,a,X[nd(i,j)],Y[nd(i,j)]);

    // cell quality
    vector<double> zc(nc), dxi(nc), det(nc), dev(nc);
    int folded=0;
    double area=0.0;
    long wet=0;

    for(int j=0; j<nj; ++j)
    for(int i=0; i<ni; ++i)
    {
        const int c=i+ni*j;
        const double x00=X[nd(i,j)], x10=X[nd(i+1,j)], x01=X[nd(i,j+1)], x11=X[nd(i+1,j+1)];
        const double y00=Y[nd(i,j)], y10=Y[nd(i+1,j)], y01=Y[nd(i,j+1)], y11=Y[nd(i+1,j+1)];
        const double ex=0.5*(x10+x11-x00-x01), ey=0.5*(y10+y11-y00-y01);
        const double fx=0.5*(x01+x11-x00-x10), fy=0.5*(y01+y11-y00-y10);
        dxi[c]=std::hypot(ex,ey);
        det[c]=std::hypot(fx,fy);
        const double J=ex*fy-ey*fx;
        if(J<=0.0) ++folded;
        area+=J;
        const double ca=std::fabs(ex*fx+ey*fy)/std::max(dxi[c]*det[c],1.0e-30);
        dev[c]=std::asin(std::min(ca,1.0))*180.0/PI;
        zc[c]=0.25*(ZB[nd(i,j)]+ZB[nd(i+1,j)]+ZB[nd(i,j+1)]+ZB[nd(i+1,j+1)]);
        if(zc[c]<p->R2) ++wet;
    }

    auto pct=[](vector<double> v, double q)
    {
        if(v.empty()) return 0.0;
        const size_t k=std::min(v.size()-1,size_t(q*(v.size()-1)));
        std::nth_element(v.begin(),v.begin()+k,v.end());
        return v[k];
    };

    vector<double> detw;
    for(int c=0; c<nc; ++c) if(zc[c]<p->R2) detw.push_back(det[c]);

    double er_a=1.0, er_c=1.0;
    for(int j=0; j<nj; ++j)
    for(int i=1; i<ni; ++i)
    {
        const double r=dxi[i+ni*j]/dxi[i-1+ni*j];
        er_a=std::max(er_a,std::max(r,1.0/r));
    }
    for(int j=1; j<nj; ++j)
    for(int i=0; i<ni; ++i)
    {
        const double r=det[i+ni*j]/det[i+ni*(j-1)];
        er_c=std::max(er_c,std::max(r,1.0/r));
    }

    std::ostringstream st;
    st<<std::fixed<<std::setprecision(2);
    st<<"corridor grid "<<ni<<" x "<<nj<<" = "<<nc<<" columns, length "<<cs.back()<<" m, area "<<area/1.0e6<<" km2\n";
    st<<"  folded cells             "<<folded<<"\n";
    st<<"  wet below R 2            "<<100.0*wet/nc<<" %\n";
    st<<"  along spacing            median "<<pct(dxi,0.5)<<" m, max "<<pct(dxi,1.0)<<" m\n";
    st<<"  across spacing (wet)     median "<<pct(detw,0.5)<<" m, 95 % "<<pct(detw,0.95)<<" m, max (all) "<<pct(det,1.0)<<" m\n";
    st<<"  non-orthogonality        median "<<pct(dev,0.5)<<" deg, 95 % "<<pct(dev,0.95)<<" deg, max "<<pct(dev,1.0)<<" deg\n";
    st<<"  neighbour size ratio     along "<<std::setprecision(3)<<er_a<<", across "<<er_c<<"\n";

    cout<<st.str();
    if(folded>0)
    cout<<"!!! corridor grid: "<<folded<<" folded cells - increase R 6, R 8 or R 5, or give a centreline (R 7) !!!"<<endl;

    {
        std::ofstream log("DIVEMesh_Log/corridor.log");
        log<<st.str();
        log<<"  R 2 "<<p->R2<<"  R 3 "<<p->R3_wl<<" "<<p->R3_m<<"  R 4 "<<ni<<" "<<nj<<"  R 5 "<<p->R5
           <<"  R 6 "<<p->R6<<"  R 7 "<<p->R7<<"  R 8 "<<p->R8<<"  raster "<<nx<<" x "<<ny<<", h "<<h<<"\n";
    }

    // ParaView: structured grid with the nodes at the bed level
    {
        std::ofstream v("DIVEMesh_Paraview/corridor-grid.vtk");
        v<<"# vtk DataFile Version 3.0\nDIVEMesh corridor grid\nASCII\nDATASET STRUCTURED_GRID\n";
        v<<"DIMENSIONS "<<ni+1<<" "<<nj+1<<" 1\nPOINTS "<<nn<<" double\n";
        v<<std::setprecision(10);
        for(int j=0; j<=nj; ++j)
        for(int i=0; i<=ni; ++i)
        v<<X[nd(i,j)]<<" "<<Y[nd(i,j)]<<" "<<ZB[nd(i,j)]<<"\n";

        v<<"CELL_DATA "<<nc<<"\n";
        auto field=[&](const char *name, const vector<double> &f)
        {
            v<<"SCALARS "<<name<<" float 1\nLOOKUP_TABLE default\n";
            for(int c=0; c<nc; ++c) v<<float(f[c])<<"\n";
        };
        field("bed",zc);
        field("non_orthogonality_deg",dev);
        field("dx_along",dxi);
        field("dx_across",det);
    }

    // grid file section CURV
    a->gex.curv.ni=ni;
    a->gex.curv.nj=nj;
    a->gex.curv.par={p->R2,p->R3_wl,p->R3_m,p->R5,h};
    a->gex.curv.x=X;
    a->gex.curv.y=Y;
    a->gex.curv.zb=ZB;
}
