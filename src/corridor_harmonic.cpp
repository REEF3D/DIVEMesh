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
#include<iostream>
#include<cstdlib>
#include<algorithm>

// Laplace equation on the corridor cells R: 5-point stencil, Neumann at the region edge, Dirichlet
// values val on the cells fix; Jacobi-preconditioned conjugate gradients.  f: NAN outside R.
void corridor::harmonic(const vector<char> &fix, const vector<double> &val, vector<double> &f)
{
    const int N=nx*ny;
    vector<int> row(N,-1);
    int n=0;
    for(int q=0; q<N; ++q)
    if(R[q] && !fix[q])
    row[q]=n++;

    vector<double> b(n,0.0), diag(n,0.0);
    for(int q=0; q<N; ++q)
    if(row[q]>=0)
    {
        const int qi=q%nx, qj=q/nx;
        const int nb[4][2]={{qi-1,qj},{qi+1,qj},{qi,qj-1},{qi,qj+1}};
        for(int k=0; k<4; ++k)
        {
            const int ii=nb[k][0], jj=nb[k][1];
            if(ii<0 || ii>=nx || jj<0 || jj>=ny) continue;
            const int r=id(ii,jj);
            if(!R[r]) continue;
            diag[row[q]]+=1.0;
            if(fix[r]) b[row[q]]+=val[r];
        }
    }

    vector<int> act;
    act.reserve(n);
    for(int q=0; q<N; ++q)
    if(row[q]>=0)
    act.push_back(q);

    for(double &dg : diag)
    dg=std::max(dg,1.0);

    auto apply=[&](const vector<double> &x, vector<double> &y)
    {
        for(int q : act)
        {
            const int qi=q%nx, qj=q/nx;
            double s=diag[row[q]]*x[row[q]];
            if(qi>0    && row[q-1]>=0)  s-=x[row[q-1]];
            if(qi<nx-1 && row[q+1]>=0)  s-=x[row[q+1]];
            if(qj>0    && row[q-nx]>=0) s-=x[row[q-nx]];
            if(qj<ny-1 && row[q+nx]>=0) s-=x[row[q+nx]];
            y[row[q]]=s;
        }
    };

    vector<double> x(n,0.5), r(n), z(n), pv(n), Ap(n);
    apply(x,Ap);
    double bn=0.0;
    for(int k=0; k<n; ++k)
    {
        r[k]=b[k]-Ap[k];
        bn+=b[k]*b[k];
    }
    bn=std::sqrt(std::max(bn,1.0e-300));

    double rz=0.0;
    for(int k=0; k<n; ++k)
    {
        z[k]=r[k]/diag[k];
        pv[k]=z[k];
        rz+=r[k]*z[k];
    }

    int it=0;
    double rn=0.0;
    for(; it<50000; ++it)
    {
        apply(pv,Ap);
        double pAp=0.0;
        for(int k=0; k<n; ++k) pAp+=pv[k]*Ap[k];
        const double al=rz/pAp;
        rn=0.0;
        for(int k=0; k<n; ++k)
        {
            x[k]+=al*pv[k];
            r[k]-=al*Ap[k];
            rn+=r[k]*r[k];
        }
        if(std::sqrt(rn)<1.0e-10*bn)
        break;
        double rz2=0.0;
        for(int k=0; k<n; ++k)
        {
            z[k]=r[k]/diag[k];
            rz2+=r[k]*z[k];
        }
        const double be=rz2/rz;
        rz=rz2;
        for(int k=0; k<n; ++k)
        pv[k]=z[k]+be*pv[k];
    }

    f.assign(N,NAN);
    for(int q=0; q<N; ++q)
    {
        if(row[q]>=0) f[q]=x[row[q]];
        else if(R[q]) f[q]=val[q];
    }

    cout<<"corridor grid: harmonic solve "<<n<<" cells, "<<it+1<<" CG iterations, res "<<std::sqrt(rn)/bn<<endl;
}

// phi: 0 at the inflow cut, 1 at the outflow cut; psi: 0 on the right bank, 1 on the left bank
void corridor::solve_fields(lexer *p)
{
    const int N=nx*ny;

    vector<char> nb(N,0), near_in(N,0), near_out(N,0);
    for(int jj=0; jj<ny; ++jj)
    for(int ii=0; ii<nx; ++ii)
    {
        const int q=id(ii,jj);
        if(!R[q]) continue;
        bool edge = (ii==0 || ii==nx-1 || jj==0 || jj==ny-1);
        if(!edge)
        edge = !R[q-1] || !R[q+1] || !R[q-nx] || !R[q+nx];
        nb[q]=edge;
        near_in[q]  = std::fabs(cut_t[0][q])<2.6*h && std::fabs(cut_n[0][q])<cut_L[0];
        near_out[q] = std::fabs(cut_t[1][q])<2.6*h && std::fabs(cut_n[1][q])<cut_L[1];
    }

    vector<char> ends(N);
    for(int q=0; q<N; ++q) ends[q]=near_in[q]||near_out[q];
    dilate4(ends,2);

    vector<char> bank(N);
    for(int q=0; q<N; ++q) bank[q]=nb[q] && !ends[q];

    // left/right: each boundary piece by the side of the centreline it lies on (majority)
    vector<int> lab;
    const int nl=label(bank,lab,8);
    vector<double> vote(nl+1,0.0);
    const int ns=int(cx.size());
    for(int q=0; q<N; ++q)
    if(bank[q])
    {
        const double X=x0+(q%nx)*h, Y=y0+(q/nx)*h;
        int best=0;
        double dm=1.0e300;
        for(int s=0; s<ns; s+=2)
        {
            const double dd=(X-cx[s])*(X-cx[s])+(Y-cy[s])*(Y-cy[s]);
            if(dd<dm) { dm=dd; best=s; }
        }
        vote[lab[q]] += ((X-cx[best])*cnx[best]+(Y-cy[best])*cny[best]>0.0) ? 1.0 : -1.0;
    }

    vector<char> fix(N,0);
    vector<double> val(N,0.0);

    for(int q=0; q<N; ++q)
    if(near_in[q] || near_out[q])
    {
        fix[q]=1;
        val[q]=near_out[q] ? 1.0 : 0.0;
    }
    harmonic(fix,val,phi);

    int nleft=0, nright=0;
    for(int q=0; q<N; ++q)
    {
        fix[q]=0;
        val[q]=0.0;
        if(bank[q])
        {
            fix[q]=1;
            val[q]=(vote[lab[q]]>0.0) ? 1.0 : 0.0;
            if(val[q]>0.5) ++nleft; else ++nright;
        }
    }

    if(nleft==0 || nright==0)
    {
        cout<<"!!! corridor grid: could not separate the left and right bank !!!"<<endl;
        exit(1);
    }

    harmonic(fix,val,psi);
}

// nodes: for every phi level (uniform in centreline arc length) the level line is followed from the
// centreline to both banks; the nodes are placed on it at uniform steps of psi
void corridor::trace_grid(lexer *p)
{
    const int N=nx*ny;

    // fields extended a few cells beyond R for the interpolation, and their gradients
    auto extend=[&](vector<double> f)
    {
        vector<char> ok(N);
        for(int q=0; q<N; ++q) ok[q]=R[q];
        for(int pass=0; pass<4; ++pass)
        {
            vector<double> g=f;
            vector<char> ok2=ok;
            for(int jj=0; jj<ny; ++jj)
            for(int ii=0; ii<nx; ++ii)
            {
                const int q=id(ii,jj);
                if(ok[q]) continue;
                double s=0.0; int c=0;
                if(ii>0    && ok[q-1])  { s+=f[q-1];  ++c; }
                if(ii<nx-1 && ok[q+1])  { s+=f[q+1];  ++c; }
                if(jj>0    && ok[q-nx]) { s+=f[q-nx]; ++c; }
                if(jj<ny-1 && ok[q+nx]) { s+=f[q+nx]; ++c; }
                if(c>0) { g[q]=s/c; ok2[q]=1; }
            }
            f=g; ok=ok2;
        }
        for(int q=0; q<N; ++q) if(!ok[q]) f[q]=0.0;
        return f;
    };

    const vector<double> PH=extend(phi), PS=extend(psi);

    auto grad=[&](const vector<double> &f, vector<double> &gx, vector<double> &gy)
    {
        gx.assign(N,0.0); gy.assign(N,0.0);
        for(int jj=0; jj<ny; ++jj)
        for(int ii=0; ii<nx; ++ii)
        {
            const int q=id(ii,jj);
            const int a=std::max(ii-1,0), b=std::min(ii+1,nx-1), c=std::max(jj-1,0), d=std::min(jj+1,ny-1);
            gx[q]=(f[id(b,jj)]-f[id(a,jj)])/((b-a)*h);
            gy[q]=(f[id(ii,d)]-f[id(ii,c)])/((d-c)*h);
        }
    };
    vector<double> pgx,pgy,sgx,sgy;
    grad(PH,pgx,pgy);
    grad(PS,sgx,sgy);

    // phi along the centreline -> levels uniform in arc length
    const int ns=int(cx.size());
    vector<double> pc(ns), sc;
    vector<double> pcm;
    for(int s=0; s<ns; ++s)
    {
        const int c=cell(cx[s],cy[s]);
        pc[s] = (c>=0 && R[c]) ? bilin(PH,cx[s],cy[s]) : -1.0;
    }
    vector<double> cxs,cys;
    for(int s=0; s<ns; ++s)
    if(pc[s]>0.002 && pc[s]<0.998)
    {
        const double v = pcm.empty() ? pc[s] : std::max(pcm.back(),pc[s]);
        pcm.push_back(v);
        sc.push_back(cs[s]);
        cxs.push_back(cx[s]);
        cys.push_back(cy[s]);
    }

    if(pcm.size()<10)
    {
        cout<<"!!! corridor grid: phi does not rise along the centreline !!!"<<endl;
        exit(1);
    }

    const double L=sc.back()-sc.front();

    // number of cells: R 4, ni from about 3:1 cells when R 4 ni = 0
    nj = p->R4_nj;
    if(p->R4_ni>0)
    ni = p->R4_ni;
    else
    {
        long count=0;
        for(int q=0; q<N; ++q) count+=R[q];
        const double width=count*h*h/L;
        ni = std::max(10,int(std::round(L/(3.0*width/nj))));
    }

    X.assign((ni+1)*(nj+1),0.0);
    Y.assign((ni+1)*(nj+1),0.0);

    auto interp_s=[&](const vector<double> &v, double s)
    {
        size_t k=std::upper_bound(sc.begin(),sc.end(),s)-sc.begin();
        k=std::min(std::max(k,size_t(1)),sc.size()-1);
        const double a=(sc[k]>sc[k-1]) ? (s-sc[k-1])/(sc[k]-sc[k-1]) : 0.0;
        return v[k-1]+a*(v[k]-v[k-1]);
    };

    const double step=0.25*h;
    const int maxstep=int(4000.0/step);
    int short_lines=0;

    for(int i=0; i<=ni; ++i)
    {
        const double s=sc.front()+L*i/double(ni);
        double lv=interp_s(pcm,s);
        lv=std::min(std::max(lv,0.003),0.997);

        double Px=interp_s(cxs,s), Py=interp_s(cys,s);

        auto project=[&](double &x, double &y)
        {
            for(int k=0; k<3; ++k)
            {
                const double gx=bilin(pgx,x,y), gy=bilin(pgy,x,y), g2=gx*gx+gy*gy;
                if(g2<1.0e-30) return;
                const double e=lv-bilin(PH,x,y);
                x+=e*gx/g2;
                y+=e*gy/g2;
            }
        };
        project(Px,Py);

        // follow the level line in both directions: points (x, y, psi)
        vector<double> lx,ly,lp;
        for(int dir=-1; dir<=1; dir+=2)
        {
            double x=Px, y=Py;
            vector<double> tx,ty,tp;
            for(int k=0; k<maxstep; ++k)
            {
                const double gx=bilin(pgx,x,y), gy=bilin(pgy,x,y), gl=std::hypot(gx,gy);
                if(gl<1.0e-30) break;
                double ux=-gy/gl, uy=gx/gl;
                const double sgn=(ux*bilin(sgx,x,y)+uy*bilin(sgy,x,y)>0.0) ? 1.0 : -1.0;
                ux*=sgn*dir; uy*=sgn*dir;
                double xn=x+step*ux, yn=y+step*uy;
                project(xn,yn);
                const int c=cell(xn,yn);
                if(c<0 || !R[c]) break;
                x=xn; y=yn;
                tx.push_back(x); ty.push_back(y); tp.push_back(bilin(PS,x,y));
            }
            if(dir<0)
            {
                for(int k=int(tx.size())-1; k>=0; --k)
                { lx.push_back(tx[k]); ly.push_back(ty[k]); lp.push_back(tp[k]); }
                lx.push_back(Px); ly.push_back(Py); lp.push_back(bilin(PS,Px,Py));
            }
            else
            for(size_t k=0; k<tx.size(); ++k)
            { lx.push_back(tx[k]); ly.push_back(ty[k]); lp.push_back(tp[k]); }
        }

        // psi increasing along the line, then nodes at uniform psi between its ends
        if(lp.front()>lp.back())
        {
            std::reverse(lx.begin(),lx.end());
            std::reverse(ly.begin(),ly.end());
            std::reverse(lp.begin(),lp.end());
        }
        for(size_t k=1; k<lp.size(); ++k)
        lp[k]=std::max(lp[k],lp[k-1]+1.0e-12);

        if(lp.size()<4) ++short_lines;

        if(lp.size()<2)
        {
            for(int j=0; j<=nj; ++j)
            {
                X[nd(i,j)]=Px;
                Y[nd(i,j)]=Py;
            }
            continue;
        }

        for(int j=0; j<=nj; ++j)
        {
            const double e=lp.front()+(lp.back()-lp.front())*j/double(nj);
            size_t k=std::upper_bound(lp.begin(),lp.end(),e)-lp.begin();
            k=std::min(std::max(k,size_t(1)),lp.size()-1);
            const double a=(e-lp[k-1])/(lp[k]-lp[k-1]);
            X[nd(i,j)]=lx[k-1]+a*(lx[k]-lx[k-1]);
            Y[nd(i,j)]=ly[k-1]+a*(ly[k]-ly[k-1]);
        }
    }

    if(short_lines>0)
    cout<<"corridor grid: WARNING "<<short_lines<<" cross-sections shorter than 4 trace steps"<<endl;

    cout<<"corridor grid: "<<ni<<" x "<<nj<<" cells traced"<<endl;
}
