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
#include<cmath>
#include<iostream>
#include<queue>
#include<tuple>

/*
Priority flood (Barnes, Lehman & Mulla 2014) with flow directions:
seeds are the pixels on the raster edge or next to a pixel without data. The pixel with the lowest
(filled) elevation is taken next; its unvisited neighbours get zf = max(z, zf of the pixel) and are pushed.
Ties are taken in the order of insertion, so flats drain in a breadth-first way towards their outlet.
The pop order never decreases in zf, so a pixel with a lower zf was taken earlier: pointing every pixel
to a lower neighbour or, in filled depressions and on flats, to the pixel it was reached from, gives
directions that point to pixels taken earlier, i.e. a tree, and the pop order is a topological order.
Pixels with a lower neighbour drain to the steepest one, (zf - zf_n)/distance (D8).
Seeds without a lower neighbour leave the raster (dn = -1).
*/
void catchment::flood()
{
    const int N=nx*ny;
    zf.assign(N,0.0);
    dn.assign(N,-1);
    order.clear();
    order.reserve(N);
    rank.assign(N,-1);

    vector<int> from(N,-1);
    vector<char> seen(N,0);

    typedef tuple<double,long,int> item;
    priority_queue<item,vector<item>,greater<item>> pq;
    long seq=0;

    for(int j=0; j<ny; ++j)
    for(int i=0; i<nx; ++i)
    {
        const int q=id(i,j);
        if(!dem.valid(q))
        continue;

        bool edge = (i==0 || j==0 || i==nx-1 || j==ny-1);
        for(int dj=-1; dj<=1 && !edge; ++dj)
        for(int di=-1; di<=1; ++di)
        if(!dem.valid(id(i+di,j+dj)))
        edge=true;

        if(edge)
        {
            zf[q]=dem.v[q];
            seen[q]=1;
            pq.push(item(zf[q],seq++,q));
        }
    }

    while(!pq.empty())
    {
        const int q=get<2>(pq.top());
        pq.pop();
        rank[q]=int(order.size());
        order.push_back(q);

        const int i=q%nx, j=q/nx;
        for(int dj=-1; dj<=1; ++dj)
        for(int di=-1; di<=1; ++di)
        {
            const int ii=i+di, jj=j+dj;
            if((di==0 && dj==0) || ii<0 || jj<0 || ii>=nx || jj>=ny)
            continue;

            const int n=id(ii,jj);
            if(seen[n] || !dem.valid(n))
            continue;

            seen[n]=1;
            zf[n]=max(dem.v[n],zf[q]);
            from[n]=q;
            pq.push(item(zf[n],seq++,n));
        }
    }

    long nfill=0;
    for(int q : order)
    {
        const int i=q%nx, j=q/nx;
        double best=0.0;
        int bn=-1;

        for(int dj=-1; dj<=1; ++dj)
        for(int di=-1; di<=1; ++di)
        {
            const int ii=i+di, jj=j+dj;
            if((di==0 && dj==0) || ii<0 || jj<0 || ii>=nx || jj>=ny)
            continue;

            const int n=id(ii,jj);
            if(!dem.valid(n))
            continue;

            const double s=(zf[q]-zf[n])/(dx*sqrt(double(di*di+dj*dj)));
            if(s>best)
            {
                best=s;
                bn=n;
            }
        }

        dn[q] = (bn>=0) ? bn : from[q];

        if(zf[q]>dem.v[q])
        ++nfill;
    }

    cout<<"priority flood: "<<order.size()<<" pixels, "<<nfill<<" in filled depressions"<<endl;
}

// upstream area: pixels are taken upstream first (reverse pop order)
void catchment::accumulate()
{
    acc.assign(nx*ny,0.0);

    for(int q : order)
    acc[q]=dx*dx;

    for(int k=int(order.size())-1; k>=0; --k)
    {
        const int q=order[k];
        if(dn[q]>=0)
        acc[dn[q]]+=acc[q];
    }
}

// pixel with the largest upstream area within radius r of (x,y), the nearest pixel for r <= 0
int catchment::snap(double x, double y, double r) const
{
    const int ic=int(floor((x-dem.x0)/dx)), jc=int(floor((y-dem.y0)/dx));
    const int w=max(0,int(ceil(r/dx)));
    int best=-1;

    for(int jj=jc-w; jj<=jc+w; ++jj)
    for(int ii=ic-w; ii<=ic+w; ++ii)
    {
        if(ii<0 || jj<0 || ii>=nx || jj>=ny)
        continue;

        const int q=id(ii,jj);
        if(!dem.valid(q))
        continue;

        if(r>0.0 && pow(xc(q)-x,2)+pow(yc(q)-y,2)>r*r && !(ii==ic && jj==jc))
        continue;

        if(best<0 || acc[q]>acc[best])
        best=q;
    }

    return best;
}

void catchment::delineate(lexer *p)
{
    const int N=nx*ny;
    inside.assign(N,0);
    label.assign(N,-1);

    outlet=-1;
    if(p->W20==1)
    {
        outlet=snap(p->W20_x,p->W20_y,p->W23);
        if(outlet<0)
        {
            cout<<"!!! W 20: the outlet is outside the DEM !!!"<<endl;
            exit(1);
        }
    }

    // gauge 0: the outlet (or the pixel with the largest upstream area without W 20)
    gpix.clear();
    if(outlet>=0)
    gpix.push_back(outlet);
    else
    {
        int b=order[0];
        for(int q : order)
        if(acc[q]>acc[b])
        b=q;
        gpix.push_back(b);
    }

    for(size_t g=0; g<p->W21_id.size(); ++g)
    {
        const int q=snap(p->W21_x[g],p->W21_y[g],p->W23);
        if(q<0)
        {
            cout<<"!!! W 21 "<<p->W21_id[g]<<": the gauge is outside the DEM !!!"<<endl;
            exit(1);
        }
        gpix.push_back(q);
    }

    vector<int> gid(N,-1);
    for(size_t g=1; g<gpix.size(); ++g)
    gid[gpix[g]]=p->W21_id[g-1];

    for(int q : order)
    {
        inside[q] = (outlet<0) || q==outlet || (dn[q]>=0 && inside[dn[q]]);

        if(!inside[q])
        continue;

        if(gid[q]>=0)
        label[q]=gid[q];
        else if(q==outlet || dn[q]<0)
        label[q]=0;
        else
        label[q]=label[dn[q]];
    }

    double area=0.0;
    for(int q : order)
    if(inside[q])
    area+=dx*dx;

    cout<<"catchment: "<<area*1.0e-6<<" km2";
    if(outlet>=0)
    cout<<", outlet at ("<<xc(outlet)<<", "<<yc(outlet)<<"), upstream area "<<acc[outlet]*1.0e-6<<" km2";
    cout<<endl;

    for(size_t g=1; g<gpix.size(); ++g)
    {
        const int q=gpix[g];
        cout<<"gauge "<<p->W21_id[g-1]<<" at ("<<xc(q)<<", "<<yc(q)<<"), upstream area "<<acc[q]*1.0e-6<<" km2";
        if(!inside[q])
        cout<<"   !!! outside the catchment, ignored";
        cout<<endl;
    }
}
