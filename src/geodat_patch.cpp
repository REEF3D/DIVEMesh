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

#include"geodat.h"
#include"dive.h"
#include"lexer.h"
#include"interpolation.h"

void geodat::geo_patch(lexer *p, dive *a, double *&Fx, double *&Fy, double *&Fz, int &Np)
{
    p->Darray(gpf,kx+2*dd+1,ky+2*dd+1);

    // read geo_patch
    geo_patch_read(p,a);

    // correct geo.dat
    double radius,dist;
    int dij=2*int(p->G62)+1;

    for(n=0;n<numGP;++n)
    {
        i = p->poscgen_i(GP_x[n],XC,kx);
        j = p->poscgen_j(GP_y[n],YC,ky);

        radius = p->G62*sqrt(p->DX[IP]*p->DX[IP] + p->DY[JP]*p->DY[JP]);

        is=MAX(i-dij,-3);
        ie=MIN(i+dij,Nx-3);

        js=MAX(j-dij,-3);
        je=MIN(j+dij,Ny-3);

        for(r=is;r<ie;++r)
        for(s=js;s<je;++s)
        for(t=0;t<ptnum[r+dd][s+dd];++t)
        {
            q = ptid[r+dd][s+dd][t];

            dist = sqrt(pow(Fx[q]-GP_x[n],2.0) + pow(Fy[q]-GP_y[n],2.0))/radius;

            Fz[q] = geo_patch_kernel(dist)*GP_z[n] + (1.0-geo_patch_kernel(dist))*Fz[q];
        }
    }


    cout<<"patch bed "<<endl;

    print(p,a,numGP,GP_x,GP_y,GP_z,2);

    // add geo_patch
    if(p->G61==1)
    {
        p->Dresize(Fx,Np,Np+numGP);
        p->Dresize(Fy,Np,Np+numGP);
        p->Dresize(Fz,Np,Np+numGP);


        for(n=0;n<numGP;++n)
        {
            Fx[n+Np] = GP_x[n];
            Fy[n+Np] = GP_y[n];
            Fz[n+Np] = GP_z[n];
        }

        Np=Np+numGP;
    }
}

double geodat::geo_patch_kernel(double dist)
{
    double D = 0.0;

    if (fabs(dist) <= 0.5)
    {
        D = 1.0/3.0*(1.0 + sqrt(-3*dist*dist + 1));
    }
    else if (fabs(dist) <= 1.5)
    {
        D = 1.0/6.0*(5.0 - 3.0*fabs(dist) - sqrt(-3*(1 - fabs(dist))*(1 - fabs(dist)) + 1));
    }

    return D;
}

void geodat::geo_patch_read(lexer *p, dive *a)
{
// read geo_patch

        cout<<"open geo_patch.dat and count entries"<<endl;
        double val;
        char cval;
        ifstream geo("geo_patch.dat", ios_base::in);

        while(!geo.eof())
        {
        if(p->G19==0)
        geo>>val>>val>>val;

        if(p->G19==1)
        geo>>cval>>val>>val>>val;

        ++countGP;
    }

    numGP=countGP-1;
    cout<<"> geo_patch entries: "<<numGP<<endl;
    geo.close();

    GP_x = new double[countGP];
    GP_y = new double[countGP];
    GP_z = new double[countGP];


        cout<<"read geo_patch.dat"<<endl;

        geo.open("geo_patch.dat", ios_base::in);

        countGP=0;
        while(!geo.eof()&&countGP<numGP)
        {
        if(p->G19==0)
        geo>>GP_x[countGP]>>GP_y[countGP]>>GP_z[countGP];

        if(p->G19==1)
        geo>>cval>>GP_x[countGP]>>GP_y[countGP]>>GP_z[countGP];
        ++countGP;
        }

        geo.close();

        cout<<"read geo_patch.dat finish"<<endl;

		if(p->G13>0)
		{


			double xval,yval;
			for(n=0;n<numGP;++n)
			{
			xval = p->G14_x + (GP_x[n]-p->G14_x)*cos(p->G13_phi) - (GP_y[n]-p->G14_y)*sin(p->G13_phi);
			yval = p->G14_y + (GP_x[n]-p->G14_x)*sin(p->G13_phi) + (GP_y[n]-p->G14_y)*cos(p->G13_phi);

			GP_x[n] = xval;
			GP_y[n] = yval;
			}
		}


}