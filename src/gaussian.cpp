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

#include"gaussian.h"
#include"dive.h"
#include"lexer.h"

gaussian::gaussian(lexer *p, dive *a)
{
    sigma=5.0*p->DXM;

    cutoff  = 3.0*sigma;

}

gaussian::~gaussian()
{
}

void gaussian::start(lexer *p, dive *a, int numpt, double *Fx, double *Fy, double *Fz, double *XC, double *YC, int kx, int ky, double **f)
{
    setup(p,a,Fx,Fy,Fz,XC,YC,kx,ky);

    counter=0;
    for(i=0;i<kx;++i)
    for(j=0;j<ky;++j)
    {
        f[i+3][j+3] = gxy(p,a,Fx,Fy,Fz,XC,YC,kx,ky,f);
        ++counter;

        if(counter%1000==0)
        cout<<"> processed cells: "<<counter<<endl;
    }
}

double gaussian::gxy(lexer *p, dive *a, double *Fx, double *Fy, double *Fz, double *XC, double *YC, int kx, int ky, double **f)
{
    xc = XC[IP];
    yc = YC[JP];

    g=0.0;
    wsum=0.0;

    int radius=3;

    double zmean=0.0;
    cp=0;
    do{
        is=MAX(i-dij-cp,-radius);
        ie=MIN(i+dij+cp,Nx-radius);

        js=MAX(j-dij-cp,-radius);
        je=MIN(j+dij+cp,Ny-radius);


        zmean=0.0;
        count=0;
        for(r=is;r<ie;++r)
        {
            for(s=js;s<je;++s)
            {
                for(t=0;t<ptnum[r+dd][s+dd];++t)
                {
                    q = ptid[r+dd][s+dd][t];

                    dist = sqrt(pow(xc-Fx[q],2.0) + pow(yc-Fy[q],2.0));

                    rx = xc-Fx[q];
                    ry = yc-Fy[q];
                    r2 = rx*rx + ry*ry;

                    //if(w<1.0e-15)
                    //cout<<"GEO smal w !!!!!!!! %%%%%%%"<<endl;

                    //if(r2<cutoff)
                    //{
                    w = exp(-r2 / (2.0*sigma*sigma));

                    wsum+=w;

                        g += w*Fz[q];

                        ++count;
                        zmean+=Fz[q];
                    //}
                }


            }

        }
        if(count>0)
        zmean=zmean/double(count);

    cp+=2;//*(count+1);
    //cout<<"IWD  cp: "<<cp<<" count: "<<count<<endl;
    }while(count<MIN(p->G18,p->Np));

    if(wsum>0.0)
    g/=wsum;

    if(wsum==0.0)
    g/=1.0e20;

    return g;
}








