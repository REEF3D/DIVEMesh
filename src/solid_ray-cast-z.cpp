/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2020 Hans Bihs

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
--------------------------------------------------------------------*/

#include"solid.h"
#include"dive.h"
#include"lexer.h"


void solid::ray_cast_z(lexer* p, dive* a, int ts, int te)
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
	int is,ie,js,je,ks,ke;
	int ir,insidecheck;
	double u,v,w;
	double denom;
    double psi = 1.0e-8*p->DXM;

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
	
	xs = MIN3(Ax,Bx,Cx);
	xe = MAX3(Ax,Bx,Cx);
	
	ys = MIN3(Ay,By,Cy);
	ye = MAX3(Ay,By,Cy);
	
	is = p->posf_i(xs);
	ie = p->posf_i(xe);
	
	js = p->posf_j(ys);
	je = p->posf_j(ye);
    
    xs = MIN3(Ax,Bx,Cx) - epsi*p->DXP[is + marge];
	xe = MAX3(Ax,Bx,Cx) + epsi*p->DXP[ie + marge];
	
	ys = MIN3(Ay,By,Cy) - epsi*p->DYP[js + marge];
	ye = MAX3(Ay,By,Cy) + epsi*p->DYP[je + marge];
	
	is = p->posf_i(xs);
	ie = p->posf_i(xe);
	
	js = p->posf_j(ys);
	je = p->posf_j(ye);


	is = MAX(is,0);
	ie = MIN(ie,p->knox);
	
	js = MAX(js,0);
	je = MIN(je,p->knoy);
	
	
		for(i=is;i<ie;i++)
		for(j=js;j<je;j++)
		{
		Px = p->XP[IP]+psi;
		Py = p->YP[JP]+psi;
		Pz = p->zmin-10.0*p->DXM ;
		
		Qx = p->XP[IP]+psi;
		Qy = p->YP[JP]+psi;
		Qz = p->zmax+10.0*p->DXM ;
        
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
		if(fabs(u)<=1.0e-20 && fabs(v)<=1.0e-20 && fabs(w)<=1.0e-20)
		check = 0;
		
			if(((u>1.0e-20 && v>1.0e-20 && w>1.0e-20) || (u<-1.0e-20 && v<-1.0e-20 && w<-1.0e-20)) && check==1)
			{
			denom = 1.0/(u+v+w);
            
            //cout<<"u: "<<u<<" v: "<<v<<" w: "<<w<<" denom: "<<denom<<endl;
			u *= denom;
			v *= denom;
			w *= denom;
			
			Rz = u*Az + v*Bz + w*Cz;
			
			
			k = p->posf_k(Rz);
            
            //cout<<"k: "<<k<<" Rz: "<<Rz<<endl;
            int distcheck=1;
            
            if(Rz<p->ZP[KP])
            if(k>=0 && k<p->knoz)
            if(a->solid(i,j,k)<0 && a->solid(i,j,k-1)<0)
            distcheck=0;
            
            if(Rz>=p->ZP[KP])
            if(k>=0 && k<p->knoz)
            if(a->solid(i,j,k)<0 && a->solid(i,j,k+1)<0)
            distcheck=0;

            if(distcheck==1)
			for(k=0;k<p->knoz;++k)
			a->solid_dist(i,j,k)=MIN(fabs(Rz-p->ZP[KP]),a->solid_dist(i,j,k));
            
            if(Rz>p->zmin && Rz<p->zmax)
            {
            if(Rz<p->zmax-1.0e-10)
            a->bedlevel(i,j) = MAX(a->bedlevel(i,j),Rz);
			 } 
            
            }
		}
	}
}

