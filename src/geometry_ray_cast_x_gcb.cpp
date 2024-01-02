/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2024 Hans Bihs

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

#include"geometry.h"
#include"dive.h"
#include"lexer.h"
#include"field.h"
#include"intfield.h"

void geometry::ray_cast_x_gcb(lexer* p, dive* a, int ts, int te, intfield &flag, field &dist)
{
	double ys,ye,zs,ze;
	double Px,Py,Pz;
	double Qx,Qy,Qz;
	double Rx,Ry,Rz;
	double Ax,Ay,Az;
	double Bx,By,Bz;
	double Cx,Cy,Cz;
	double PQx,PQy,PQz;
	double PAx,PAy,PAz;
	double PBx,PBy,PBz;
	double PCx,PCy,PCz;
	double Mx,My,Mz;
	int js,je,ks,ke;
	int ir;
	double u,v,w;
	double denom;

    is_count=0;

    for(j=0;j<maxpt;++j)
    for(k=0;k<maxpt;++k)
    is_num[j][k]=0;

	for(n=ts; n<te; ++n)
	{
	Ax = p->tri_x[n][0];
	Ay = p->tri_y[n][0];
	Az = p->tri_z[n][0];

	Bx = p->tri_x[n][1];
	By = p->tri_y[n][1];
	Bz = p->tri_z[n][1];

	Cx = p->tri_x[n][2];
	Cy = p->tri_y[n][2];
	Cz = p->tri_z[n][2];

// --
    ys = MIN3(Ay,By,Cy);
	ye = MAX3(Ay,By,Cy);

	zs = MIN3(Az,Bz,Cz);
	ze = MAX3(Az,Bz,Cz);

    js = p->posc_j(ys);
    js = p->posc_j(ye);

	ks = p->posc_k(zs);
    ke = p->posc_k(ze);
// --

	ys = MIN3(Ay,By,Cy) - 0.6*p->DY[js];
	ye = MAX3(Ay,By,Cy) + 0.6*p->DY[je];

	zs = MIN3(Az,Bz,Cz) - 0.6*p->DZ[ks];
	ze = MAX3(Az,Bz,Cz) + 0.6*p->DZ[ke];

	js = p->posc_j(ys);
    js = p->posc_j(ye);

	ks = p->posc_k(zs);
    ke = p->posc_k(ze);

	js = MAX(js,0);
	je = MIN(je,p->knoy);

	ks = MAX(ks,0);
	ke = MIN(ke,p->knoz);


		for(j=js;j<je;j++)
		for(k=ks;k<ke;k++)
		{


		Px = p->xmin-10.0*p->dx ;
		Py = p->YP[JP];
		Pz = p->ZP[KP];

		Qx = p->xmax+10.0*p->dx ;
		Qy = p->YP[JP];
		Qz = p->ZP[KP];


		PQx = Qx-Px;
		PQy = Qy-Py;
		PQz = Qz-Pz;

		PAx = Ax-Px;
		PAy = Ay-Py;
		PAz = Az-Pz;

		PBx = Bx-Px;
		PBy = By-Py;
		PBz = Bz-Pz;

		PCx = Cx-Px;
		PCy = Cy-Py;
		PCz = Cz-Pz;

		// uvw
		Mx = PQy*Pz - PQz*Py;
		My = PQz*Px - PQx*Pz;
		Mz = PQx*Py - PQy*Px;


		u = PQx*(Cy*Bz - Cz*By) + PQy*(Cz*Bx - Cx*Bz) + PQz*(Cx*By - Cy*Bx)
		  + Mx*(Cx-Bx) + My*(Cy-By) + Mz*(Cz-Bz);

		v = PQx*(Ay*Cz - Az*Cy) + PQy*(Az*Cx - Ax*Cz) + PQz*(Ax*Cy - Ay*Cx)
		  + Mx*(Ax-Cx) + My*(Ay-Cy) + Mz*(Az-Cz);

		w = PQx*(By*Az - Bz*Ay) + PQy*(Bz*Ax - Bx*Az) + PQz*(Bx*Ay - By*Ax)
		  + Mx*(Bx-Ax) + My*(By-Ay) + Mz*(Bz-Az);


		int check=1;
		if(u==0.0 && v==0.0 && w==0.0)
		check = 0;

			if((u>=0.0 && v>=0.0 && w>=0.0) || (u<0.0 && v<0.0 && w<0.0) && check==1)
			{
			denom = 1.0/(u+v+w);
			u *= denom;
			v *= denom;
			w *= denom;

			Rx = u*Ax + v*Bx + w*Cx;

            is_R[j][k][is_num[j][k]] = Rx;

            ++is_num[j][k];
			}
		}
	}



    //sort entries
    JLOOP
    KLOOP
    {
    sort(is_R[j][k],0,is_num[j][k]-1);
    }

    // gcb from intersects
    JLOOP
    KLOOP
    for(n=0;n<is_num[j][k];++n)
    {

    if((n+1)%2!=0)
    i = p->posc_i(is_R[j][k][n]);

    if((n+1)%2==0)
    i = p->posc_i(is_R[j][k][n]);

        a->surf_solid[a->surfcount_solid][0]=i;
        a->surf_solid[a->surfcount_solid][1]=j;
        a->surf_solid[a->surfcount_solid][2]=k;

        if((n+1)%2!=0)
        a->surf_solid[a->surfcount_solid][3]=4;
        if((n+1)%2==0)
        a->surf_solid[a->surfcount_solid][3]=1;

        a->surf_solid[a->surfcount_solid][4]=21;


        //cout<<"is_num: "<<is_num[j][k]<<" n: "<<n<<"is_R: "<<is_R[j][k][n]<<"  i: "<<i<<" k: "<<k<<" gcside: "<<a->surf_solid[a->surfcount_solid][3]<<endl;
        a->surfcount_solid++;

        if(a->surfcount_solid>=a->surfnum_solid)
        {
        p->Iresize(a->surf_solid,a->surfnum_solid,a->surfnum_solid+maxpt,5,5);
        a->surfnum_solid+=maxpt;
        }
    }

	cout<<"Number of solid intersections in x-dir: "<<is_count<<endl;

}


void geometry::sort(double *a, int left, int right)
 {

  if (left < right)
  {

    double pivot = a[right];
    int l = left;
    int r = right;

    do {
      while (a[l] < pivot) l++;

      while (a[r] > pivot) r--;

      if (l <= r) {
          double swap = a[l];

          a[l] = a[r];
          a[r] = swap;

          l++;
          r--;
      }
    } while (l <= r);

    sort(a, left, r);
    sort(a, l, right);
  }
}
