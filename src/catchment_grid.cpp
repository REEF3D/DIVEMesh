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
Architect: Hans Bihs
--------------------------------------------------------------------*/

#include"catchment.h"
#include"lexer.h"
#include<algorithm>
#include<cmath>
#include<iostream>
#include<map>

// fine flow path from pixel q0 to the outlet pixel of the next hydrology cell (cend, qend) or out of the
// catchment (cend = -1, qend = last pixel inside); returns the length of the path [m]
double catchment::path(int q0, int &qend, int &cend) const
{
    double len=0.0;
    int q=q0;

    while(true)
    {
        const int n=dn[q];
        if(n<0 || !inside[n])
        {
            qend=q;
            cend=-1;
            return len;
        }

        const int di=abs(n%nx-q%nx), dj=abs(n/nx-q/nx);
        len += dx*((di+dj==2) ? sqrt(2.0) : 1.0);
        q=n;

        const int c=cellout[q];
        if(c>=0)
        {
            qend=q;
            cend=c;
            return len;
        }
    }
}

void catchment::cells(lexer *p)
{
    D = max(p->W11,dx);
    nb = max(1,p->W12);
    ni = int(ceil(nx*dx/D - 1.0e-9));
    nj = int(ceil(ny*dx/D - 1.0e-9));

    // pixels of every hydrology cell (centre of the pixel inside the cell)
    const int NC=ni*nj;
    vector<int> start(NC+1,0), cellof(nx*ny,-1);
    for(int q=0; q<nx*ny; ++q)
    if(inside[q])
    {
        const int I=min(ni-1,int(floor((xc(q)-dem.x0)/D)));
        const int J=min(nj-1,int(floor((yc(q)-dem.y0)/D)));
        cellof[q]=I+ni*J;
        ++start[cellof[q]+1];
    }
    for(int c=0; c<NC; ++c)
    start[c+1]+=start[c];

    vector<int> pix(start[NC]), fillpos(start.begin(),start.end()-1);
    for(int q=0; q<nx*ny; ++q)
    if(cellof[q]>=0)
    pix[fillpos[cellof[q]]++]=q;

    // cells with pixels, outlet pixel = largest upstream area
    hc.clear();
    vector<int> raw;
    for(int c=0; c<NC; ++c)
    if(start[c+1]>start[c])
    {
        hcell h;
        h.I=c%ni;
        h.J=c/ni;
        h.npix=start[c+1]-start[c];
        h.area=h.npix*dx*dx;
        h.out=pix[start[c]];
        for(int k=start[c]; k<start[c+1]; ++k)
        if(acc[pix[k]]>acc[h.out] || (acc[pix[k]]==acc[h.out] && rank[pix[k]]<rank[h.out]))
        h.out=pix[k];

        // elevation bands of equal area
        vector<double> z(h.npix), g(h.npix,0.0);
        vector<int> ord(h.npix);
        double lk=0.0;
        map<int,int> zc;
        for(int k=0; k<h.npix; ++k)
        {
            const int q=pix[start[c]+k];
            z[k]=dem.v[q];
            ord[k]=k;
            if(p->W30>0 && glac.valid(q))
            g[k]=min(1.0,max(0.0,glac.v[q]));
            if(p->W31>0 && lake.valid(q))
            lk+=min(1.0,max(0.0,lake.v[q]));
            if(p->W32>0 && zone.valid(q))
            ++zc[int(lround(zone.v[q]))];
        }
        sort(ord.begin(),ord.end(),[&](int a, int b){return z[a]<z[b];});

        h.zmean=0.0;
        for(double v : z)
        h.zmean+=v/h.npix;

        h.bz.assign(nb,h.zmean);
        h.bf.assign(nb,0.0);
        h.bg.assign(nb,0.0);
        for(int b=0; b<nb; ++b)
        {
            const int k0=int((long(b)*h.npix)/nb), k1=int((long(b+1)*h.npix)/nb);
            if(k1<=k0)
            continue;

            double s=0.0, sg=0.0;
            for(int k=k0; k<k1; ++k)
            {
                s+=z[ord[k]];
                sg+=g[ord[k]];
            }
            h.bz[b]=s/(k1-k0);
            h.bg[b]=sg/(k1-k0);
            h.bf[b]=double(k1-k0)/h.npix;
        }

        h.lake=lk/h.npix;
        h.zone=0;
        int best=-1;
        for(auto &e : zc)
        if(e.second>best)
        {
            best=e.second;
            h.zone=e.first;
        }

        h.sub=label[h.out];
        h.down=-1;
        raw.push_back(c);
        hc.push_back(h);
    }

    // upstream first: the outlet pixel of the downstream cell lies downstream on the fine path, it was taken earlier by the flood
    vector<int> srt(hc.size());
    for(size_t n=0; n<hc.size(); ++n)
    srt[n]=int(n);
    sort(srt.begin(),srt.end(),[&](int a, int b){return rank[hc[a].out]>rank[hc[b].out];});

    vector<hcell> tmp(hc.size());
    for(size_t n=0; n<hc.size(); ++n)
    tmp[n]=hc[srt[n]];
    hc.swap(tmp);

    cellout.assign(nx*ny,-1);
    for(size_t n=0; n<hc.size(); ++n)
    cellout[hc[n].out]=int(n);

    const double smin = (p->W24>0.0) ? p->W24 : 1.0e-4;
    int nout=0;

    for(size_t n=0; n<hc.size(); ++n)
    {
        hcell &h=hc[n];
        int qend, cend;
        h.len=path(h.out,qend,cend);
        h.down=cend;
        h.aup=acc[h.out];

        double drop=zf[h.out]-zf[qend];

        // outlet of the catchment: at least half a cell, slope along the main upstream path
        if(cend<0)
        {
            ++nout;
            if(h.len<0.5*D)
            {
                int q=h.out;
                double l=0.0;
                while(l<D)
                {
                    int up=-1;
                    const int i=q%nx, j=q/nx;
                    for(int dj=-1; dj<=1; ++dj)
                    for(int di=-1; di<=1; ++di)
                    {
                        const int ii=i+di, jj=j+dj;
                        if((di==0 && dj==0) || ii<0 || jj<0 || ii>=nx || jj>=ny)
                        continue;
                        const int m=id(ii,jj);
                        if(dem.valid(m) && inside[m] && dn[m]==q && (up<0 || acc[m]>acc[up]))
                        up=m;
                    }
                    if(up<0)
                    break;
                    l += dx*((up%nx!=q%nx && up/nx!=q/nx) ? sqrt(2.0) : 1.0);
                    q=up;
                }
                drop = (l>0.0) ? (zf[q]-zf[h.out])*0.5*D/l : 0.0;
                h.len=0.5*D;
            }
        }

        h.slope = (h.len>0.0) ? max(smin,drop/h.len) : smin;

        if(cend>=0 && cend<=int(n))
        {
            cout<<"!!! catchment: the hydrology cells are not in topological order !!!"<<endl;
            exit(1);
        }
    }

    // upstream area from the cells
    for(hcell &h : hc)
    h.aup_cells=h.area;
    for(size_t n=0; n<hc.size(); ++n)
    if(hc[n].down>=0)
    hc[hc[n].down].aup_cells+=hc[n].aup_cells;

    // gauges: first cell outlet at or downstream of the gauge pixel
    gcell.assign(gpix.size(),-1);
    for(size_t g=0; g<gpix.size(); ++g)
    {
        const int q=gpix[g];
        if(!inside[q])
        continue;

        if(cellout[q]>=0)
        gcell[g]=cellout[q];
        else
        {
            int qend;
            path(q,qend,gcell[g]);
            if(gcell[g]<0)
            {
                const int I=min(ni-1,int(floor((xc(qend)-dem.x0)/D))), J=min(nj-1,int(floor((yc(qend)-dem.y0)/D)));
                for(size_t n=0; n<hc.size(); ++n)
                if(hc[n].I==I && hc[n].J==J)
                gcell[g]=int(n);
            }
        }
    }

    double amin=1.0e30, amax=0.0;
    for(const hcell &h : hc)
    {
        amin=min(amin,h.area);
        amax=max(amax,h.area);
    }
    cout<<"hydrology cells: "<<hc.size()<<" of "<<ni<<" x "<<nj<<", area "<<amin*1.0e-6<<" - "<<amax*1.0e-6<<" km2, "<<nout<<" outlet(s)"<<endl;
}
