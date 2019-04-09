/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2019 Hans Bihs

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

void solid::fluvial_box(lexer *p, dive *a, int rank, int &ts, int &te)
{
    // 307 depth
    // 308 origin xy
    // 309 min. left and right margins
    
    // 310 straight
    // 320 left bend
    // 330 right bend
    
    /*
    1. read, order decides 
    2. two lines define: left and right bank
    3. for fluvial box xs,xe,ys,ye: add margin
    4. fill bank curves:
        a. go along x-axis, fill yl or yr coordinates
        b. 
    
    */
    cout<<"fluvial box start"<<endl;
    int countS310=0;
    int countS320=0;
    int countS330=0;
    int countS340=0;
    int countds=1;
    int numds=0;
    int ds_count;
    double dangle,length;
    double *xl,*yl,*xr,*yr;
    double x0=0.0; // add origin afterwards
    double y0=0.0; // add origin
    double xe=x0;
    double ye=y0;
    double phi0 = 0.0;
    double deltax,deltay;
    int lastds;
    
    double nx,ny,norm,xc,yc,x1,y1,teta,ds,m;

    p->Darray(xl,p->S300_ds);
    p->Darray(yl,p->S300_ds);
    p->Darray(xr,p->S300_ds);
    p->Darray(yr,p->S300_ds);
    
    
    xl[0] = x0;
    yl[0] = y0 + p->S306*0.5;
    
    xr[0] = x0;
    yr[0] = y0 - p->S306*0.5;
    
    

    // get left and right segment
    for(n=0;n<p->S300;++n)
    {
        //straight
        if(p->S300_ord[n]==1)
        {
        xl[countds] = xl[countds-1] + p->S310_l[countS310]*cos(phi0);
        yl[countds] = yl[countds-1] + p->S310_l[countS310]*sin(phi0);
        
        xr[countds] = xr[countds-1] + p->S310_l[countS310]*cos(phi0);
        yr[countds] = yr[countds-1] + p->S310_l[countS310]*sin(phi0);
        
        ++countds;
        ++countS310;
        }
        
        // left
        if(p->S300_ord[n]==2)
        {
            lastds = countds;
            length = (p->S320_r[countS320])*p->S320_phi[countS320];
            ds_count = int(length/(p->S305*p->DXM));
            dangle = p->S320_phi[countS320]/double(ds_count);
            
            deltax = xl[lastds-1] - (p->S320_r[countS320]-p->S306*0.5)*cos(dangle*double(0)+phi0-0.5*PI);
            deltay = yl[lastds-1] - (p->S320_r[countS320]-p->S306*0.5)*sin(dangle*double(0)+phi0-0.5*PI);
            
            for(q=1;q<=ds_count;++q)
            {
            xl[countds] = deltax + (p->S320_r[countS320]-p->S306*0.5)*cos(dangle*double(q)+phi0-0.5*PI);
            yl[countds] = deltay + (p->S320_r[countS320]-p->S306*0.5)*sin(dangle*double(q)+phi0-0.5*PI);
            
            xr[countds] = deltax + (p->S320_r[countS320]+p->S306*0.5)*cos(dangle*double(q)+phi0-0.5*PI);
            yr[countds] = deltay + (p->S320_r[countS320]+p->S306*0.5)*sin(dangle*double(q)+phi0-0.5*PI);

            ++countds;   
            }
            
            phi0 += p->S320_phi[countS320];
            ++countS320;
        }
        
        
        // right
        if(p->S300_ord[n]==3)
        {
            lastds = countds;
            length = (p->S330_r[countS330])*p->S330_phi[countS330];
            ds_count = int(length/(p->S305*p->DXM));
            dangle = -p->S330_phi[countS330]/double(ds_count);
            
            deltax = xl[lastds-1] - (p->S330_r[countS330]+p->S306*0.5)*cos(dangle*double(0)+phi0-1.5*PI);
            deltay = yl[lastds-1] - (p->S330_r[countS330]+p->S306*0.5)*sin(dangle*double(0)+phi0-1.5*PI);
        
            for(q=1;q<=ds_count;++q)
            {
            xl[countds] = deltax + (p->S330_r[countS330]+p->S306*0.5)*cos(dangle*double(q)+phi0-1.5*PI);
            yl[countds] = deltay + (p->S330_r[countS330]+p->S306*0.5)*sin(dangle*double(q)+phi0-1.5*PI);
            
            xr[countds] = deltax + (p->S330_r[countS330]-p->S306*0.5)*cos(dangle*double(q)+phi0-1.5*PI);
            yr[countds] = deltay + (p->S330_r[countS330]-p->S306*0.5)*sin(dangle*double(q)+phi0-1.5*PI);

            ++countds;   
            }


            phi0 -= p->S330_phi[countS330];
            ++countS330;
        }
        
        
        // meander
        if(p->S300_ord[n]==4)
        {
            lastds = countds;
        
            ds_count = int((p->S340_L[countS340]*p->S340_N[countS340])/(p->S305*p->DXM));  
            
            x1 = 0.5*(xl[lastds-1]+xr[lastds-1]);
            y1 = 0.5*(yl[lastds-1]+yr[lastds-1]);
            
            cout<<"MEANDER dscount: "<<ds_count<<endl;
            
            for(q=1;q<=ds_count;++q)
            {
            teta = p->S340_teta[countS340]*cos(2.0*PI*(p->S305*p->DXM*double(q))/p->S340_L[countS340] + p->S340_ds[countS340]*PI);
            
            xc = x1 + p->S305*p->DXM*cos(teta);
            yc = y1 + p->S305*p->DXM*sin(teta);
            
            m = (yc-y1)/(xc-x1);
            
            nx = -m;
            ny = 1.0;

            norm = sqrt(nx*nx + ny*ny);
            
            nx/=fabs(norm>1.0e-20)?norm:1.0e20;
            ny/=fabs(norm>1.0e-20)?norm:1.0e20;
            
            xl[countds] = xc + nx*0.5*p->S306;
            yl[countds] = yc + ny*0.5*p->S306;
            
            xr[countds] = xc - nx*0.5*p->S306;
            yr[countds] = yc - ny*0.5*p->S306;
            
            cout<<"MEANDER: "<<teta<<" "<<m<<" "<<nx<<" "<<ny<<endl;
            
            
            x1=xc;
            y1=yc;
            
            ++countds;
            }

            //phi0 -= p->S340_phi[countS340];
            ++countS340;
        }
    }
    
    numds = countds;
    cout<<"numds: "<<numds<<endl;
    cout<<"phi0: "<<phi0*180/PI<<endl;
 
    for(n=0;n<numds;++n)
    {
    xl[n] += p->S308_x;
    xr[n] += p->S308_x;
    
    yl[n] += p->S308_y;
    yr[n] += p->S308_y;
    }
        
    // with filled segment: get min/max coord, move accordingly
    double xmin,xmax,ymin,ymax;
    
    xmin=1.0e8;
    xmax=-1.0e8;
    ymin=1.0e8;
    ymax=-1.0e8;
    
    for(n=0;n<numds;++n)
    {
    xmin = MIN(xmin,xl[n]);
    xmin = MIN(xmin,xr[n]);
    
    xmax = MAX(xmax,xl[n]);
    xmax = MAX(xmax,xr[n]);
    
    
    ymin = MIN(ymin,yl[n]);
    ymin = MIN(ymin,yr[n]);
    
    ymax = MAX(ymax,yl[n]);
    ymax = MAX(ymax,yr[n]);
    }
    
    double box_xs,box_xe,box_ys,box_ye,box_zs,box_ze;
    
    box_xs = xmin - p->S309_x;
    box_xe = xmax + p->S309_x;
    
    box_ys = ymin - p->S309_y;
    box_ye = ymax + p->S309_y;
    
    box_zs = -p->S307_bh - p->S309_z;
    box_ze =  p->S307_fh + p->S309_z;
    
    
    cout<<"fluvial box extend - xs: "<<box_xs<<" xe: "<<box_xe<<" ys: "<<box_ys<<" ye: "<<box_ye<<" zs: "<<box_zs<<" ze: "<<box_ze<<endl;
    
    
    // add the rest of the solid geometry
    ts=p->tricount;
    
    // Front Face
	// Tri 1
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = box_xs;
	p->tri_y[p->tricount][0] = box_ye;
	p->tri_z[p->tricount][0] = box_zs;
	
	p->tri_x[p->tricount][1] = box_xs;
	p->tri_y[p->tricount][1] = yl[0];
	p->tri_z[p->tricount][1] = box_ze;
	
	p->tri_x[p->tricount][2] = box_xs;
	p->tri_y[p->tricount][2] = yl[0];
	p->tri_z[p->tricount][2] = box_zs;
	++p->tricount;
	
	// Tri 2
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = box_xs;
	p->tri_y[p->tricount][0] = box_ye;
	p->tri_z[p->tricount][0] = box_zs;
	
	p->tri_x[p->tricount][1] = box_xs;
	p->tri_y[p->tricount][1] = box_ye;
	p->tri_z[p->tricount][1] = box_ze;
	
	p->tri_x[p->tricount][2] = box_xs;
	p->tri_y[p->tricount][2] = yl[0];
	p->tri_z[p->tricount][2] = box_ze;
	++p->tricount;
    
    // Tri 3
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = box_xs;
	p->tri_y[p->tricount][0] = yl[0];
	p->tri_z[p->tricount][0] = box_zs;
	
	p->tri_x[p->tricount][1] = box_xs;
	p->tri_y[p->tricount][1] = yl[0];
	p->tri_z[p->tricount][1] = box_zs+p->S307_bh;
	
	p->tri_x[p->tricount][2] = box_xs;
	p->tri_y[p->tricount][2] = yr[0];
	p->tri_z[p->tricount][2] = box_zs+p->S307_bh;
	++p->tricount;
    
    // Tri 4
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = box_xs;
	p->tri_y[p->tricount][0] = yl[0];
	p->tri_z[p->tricount][0] = box_zs;
	
	p->tri_x[p->tricount][1] = box_xs;
	p->tri_y[p->tricount][1] = yr[0];
	p->tri_z[p->tricount][1] = box_zs;
	
	p->tri_x[p->tricount][2] = box_xs;
	p->tri_y[p->tricount][2] = yr[0];
	p->tri_z[p->tricount][2] = box_zs+p->S307_bh;
	++p->tricount;
    
    // Tri 5
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = box_xs;
	p->tri_y[p->tricount][0] = yr[0];
	p->tri_z[p->tricount][0] = box_zs;
	
	p->tri_x[p->tricount][1] = box_xs;
	p->tri_y[p->tricount][1] = box_ys;
	p->tri_z[p->tricount][1] = box_ze;
	
	p->tri_x[p->tricount][2] = box_xs;
	p->tri_y[p->tricount][2] = box_ys;
	p->tri_z[p->tricount][2] = box_zs;
	++p->tricount;
    
    // Tri 6
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = box_xs;
	p->tri_y[p->tricount][0] = yr[0];
	p->tri_z[p->tricount][0] = box_zs;
	
	p->tri_x[p->tricount][1] = box_xs;
	p->tri_y[p->tricount][1] = yr[0];
	p->tri_z[p->tricount][1] = box_ze;
	
	p->tri_x[p->tricount][2] = box_xs;
	p->tri_y[p->tricount][2] = box_ys;
	p->tri_z[p->tricount][2] = box_ze;
	++p->tricount;
    
    
    
    // Back Face
	// Tri 1
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = box_xe;
	p->tri_y[p->tricount][0] = box_ye;
	p->tri_z[p->tricount][0] = box_zs;
	
	p->tri_x[p->tricount][1] = box_xe;
	p->tri_y[p->tricount][1] = yl[numds-1];
	p->tri_z[p->tricount][1] = box_ze;
	
	p->tri_x[p->tricount][2] = box_xe;
	p->tri_y[p->tricount][2] = yl[numds-1];
	p->tri_z[p->tricount][2] = box_zs;
	++p->tricount;
	
	// Tri 2
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = box_xe;
	p->tri_y[p->tricount][0] = box_ye;
	p->tri_z[p->tricount][0] = box_zs;
	
	p->tri_x[p->tricount][1] = box_xe;
	p->tri_y[p->tricount][1] = box_ye;
	p->tri_z[p->tricount][1] = box_ze;
	
	p->tri_x[p->tricount][2] = box_xe;
	p->tri_y[p->tricount][2] = yl[numds-1];
	p->tri_z[p->tricount][2] = box_ze;
	++p->tricount;
    
    // Tri 3
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = box_xe;
	p->tri_y[p->tricount][0] = yl[numds-1];
	p->tri_z[p->tricount][0] = box_zs;
	
	p->tri_x[p->tricount][1] = box_xe;
	p->tri_y[p->tricount][1] = yl[numds-1];
	p->tri_z[p->tricount][1] = box_zs+p->S307_bh;
	
	p->tri_x[p->tricount][2] = box_xe;
	p->tri_y[p->tricount][2] = yr[numds-1];
	p->tri_z[p->tricount][2] = box_zs+p->S307_bh;
	++p->tricount;
    
    // Tri 4
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = box_xe;
	p->tri_y[p->tricount][0] = yl[numds-1];
	p->tri_z[p->tricount][0] = box_zs;
	
	p->tri_x[p->tricount][1] = box_xe;
	p->tri_y[p->tricount][1] = yr[numds-1];
	p->tri_z[p->tricount][1] = box_zs;
	
	p->tri_x[p->tricount][2] = box_xe;
	p->tri_y[p->tricount][2] = yr[numds-1];
	p->tri_z[p->tricount][2] = box_zs+p->S307_bh;
	++p->tricount;
    
    // Tri 5
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = box_xe;
	p->tri_y[p->tricount][0] = yr[numds-1];
	p->tri_z[p->tricount][0] = box_zs;
	
	p->tri_x[p->tricount][1] = box_xe;
	p->tri_y[p->tricount][1] = box_ys;
	p->tri_z[p->tricount][1] = box_ze;
	
	p->tri_x[p->tricount][2] = box_xe;
	p->tri_y[p->tricount][2] = box_ys;
	p->tri_z[p->tricount][2] = box_zs;
	++p->tricount;
    
    // Tri 6
	p->trivec_x[p->tricount] = 0.0;
	p->trivec_y[p->tricount] = -1.0;
	p->trivec_z[p->tricount] = 0.0;
	
	p->tri_x[p->tricount][0] = box_xe;
	p->tri_y[p->tricount][0] = yr[numds-1];
	p->tri_z[p->tricount][0] = box_zs;
	
	p->tri_x[p->tricount][1] = box_xe;
	p->tri_y[p->tricount][1] = yr[numds-1];
	p->tri_z[p->tricount][1] = box_ze;
	
	p->tri_x[p->tricount][2] = box_xe;
	p->tri_y[p->tricount][2] = box_ys;
	p->tri_z[p->tricount][2] = box_ze;
	++p->tricount;
    
    for(n=0; n<numds-1;++n)
    {

        // Face 1
        // Tri 1
        p->trivec_x[p->tricount] = 0.0;
        p->trivec_y[p->tricount] = -1.0;
        p->trivec_z[p->tricount] = 0.0;
        
        p->tri_x[p->tricount][0] = xr[n];
        p->tri_y[p->tricount][0] = box_ys;
        p->tri_z[p->tricount][0] = box_zs;
        
        p->tri_x[p->tricount][1] = xr[n+1];
        p->tri_y[p->tricount][1] = box_ys;
        p->tri_z[p->tricount][1] = box_zs;
        
        p->tri_x[p->tricount][2] = xl[n];
        p->tri_y[p->tricount][2] = box_ye;
        p->tri_z[p->tricount][2] = box_zs;
        ++p->tricount;
        
        // Tri 2
        p->trivec_x[p->tricount] = 0.0;
        p->trivec_y[p->tricount] = -1.0;
        p->trivec_z[p->tricount] = 0.0;
        
        p->tri_x[p->tricount][0] = xr[n+1];
        p->tri_y[p->tricount][0] = box_ys;
        p->tri_z[p->tricount][0] = box_zs;
        
        p->tri_x[p->tricount][1] = xl[n+1];
        p->tri_y[p->tricount][1] = box_ye;
        p->tri_z[p->tricount][1] = box_zs;
        
        p->tri_x[p->tricount][2] = xl[n];
        p->tri_y[p->tricount][2] = box_ye;
        p->tri_z[p->tricount][2] = box_zs;
        ++p->tricount;
        
        
        // Face 2
        // Tri 1
        p->trivec_x[p->tricount] = 0.0;
        p->trivec_y[p->tricount] = -1.0;
        p->trivec_z[p->tricount] = 0.0;
        
        p->tri_x[p->tricount][0] = xr[n];
        p->tri_y[p->tricount][0] = box_ys;
        p->tri_z[p->tricount][0] = box_zs;
        
        p->tri_x[p->tricount][1] = xr[n+1];
        p->tri_y[p->tricount][1] = box_ys;
        p->tri_z[p->tricount][1] = box_zs;
        
        p->tri_x[p->tricount][2] = xr[n];
        p->tri_y[p->tricount][2] = box_ys;
        p->tri_z[p->tricount][2] = box_ze;
        ++p->tricount;
        
        // Tri 2
        p->trivec_x[p->tricount] = 0.0;
        p->trivec_y[p->tricount] = -1.0;
        p->trivec_z[p->tricount] = 0.0;
        
        p->tri_x[p->tricount][0] = xr[n+1];
        p->tri_y[p->tricount][0] = box_ys;
        p->tri_z[p->tricount][0] = box_zs;
        
        p->tri_x[p->tricount][1] = xr[n+1];
        p->tri_y[p->tricount][1] = box_ys;
        p->tri_z[p->tricount][1] = box_ze;
        
        p->tri_x[p->tricount][2] = xr[n];
        p->tri_y[p->tricount][2] = box_ys;
        p->tri_z[p->tricount][2] = box_ze;
        ++p->tricount;
        
        
        // Face 3
        // Tri 1
        p->trivec_x[p->tricount] = 0.0;
        p->trivec_y[p->tricount] = -1.0;
        p->trivec_z[p->tricount] = 0.0;
        
        p->tri_x[p->tricount][0] = xr[n];
        p->tri_y[p->tricount][0] = box_ys;
        p->tri_z[p->tricount][0] = box_ze;
        
        p->tri_x[p->tricount][1] = xr[n+1];
        p->tri_y[p->tricount][1] = box_ys;
        p->tri_z[p->tricount][1] = box_ze;
        
        p->tri_x[p->tricount][2] = xr[n];
        p->tri_y[p->tricount][2] = yr[n];
        p->tri_z[p->tricount][2] = box_ze;
        ++p->tricount;
        
        // Tri 2
        p->trivec_x[p->tricount] = 0.0;
        p->trivec_y[p->tricount] = -1.0;
        p->trivec_z[p->tricount] = 0.0;
        
        p->tri_x[p->tricount][0] = xr[n+1];
        p->tri_y[p->tricount][0] = box_ys;
        p->tri_z[p->tricount][0] = box_ze;
        
        p->tri_x[p->tricount][1] = xr[n+1];
        p->tri_y[p->tricount][1] = yr[n+1];
        p->tri_z[p->tricount][1] = box_ze;
        
        p->tri_x[p->tricount][2] = xr[n];
        p->tri_y[p->tricount][2] = yr[n];
        p->tri_z[p->tricount][2] = box_ze;
        ++p->tricount;
        
        
        // Face 4
        // Tri 1
        p->trivec_x[p->tricount] = 0.0;
        p->trivec_y[p->tricount] = -1.0;
        p->trivec_z[p->tricount] = 0.0;
        
        p->tri_x[p->tricount][0] = xr[n];
        p->tri_y[p->tricount][0] = yr[n];
        p->tri_z[p->tricount][0] = box_zs+p->S307_bh;
        
        p->tri_x[p->tricount][1] = xr[n+1];
        p->tri_y[p->tricount][1] = yr[n+1];
        p->tri_z[p->tricount][1] = box_zs+p->S307_bh;
        
        p->tri_x[p->tricount][2] = xr[n];
        p->tri_y[p->tricount][2] = yr[n];
        p->tri_z[p->tricount][2] = box_ze;
        ++p->tricount;
        
        // Tri 2
        p->trivec_x[p->tricount] = 0.0;
        p->trivec_y[p->tricount] = -1.0;
        p->trivec_z[p->tricount] = 0.0;
        
        p->tri_x[p->tricount][0] = xr[n+1];
        p->tri_y[p->tricount][0] = yr[n+1];
        p->tri_z[p->tricount][0] = box_zs+p->S307_bh;
        
        p->tri_x[p->tricount][1] = xr[n+1];
        p->tri_y[p->tricount][1] = yr[n+1];
        p->tri_z[p->tricount][1] = box_ze;
        
        p->tri_x[p->tricount][2] = xr[n];
        p->tri_y[p->tricount][2] = yr[n];
        p->tri_z[p->tricount][2] = box_ze;
        ++p->tricount;
        
        
        // Face 5
        // Tri 1
        p->trivec_x[p->tricount] = 0.0;
        p->trivec_y[p->tricount] = -1.0;
        p->trivec_z[p->tricount] = 0.0;
        
        p->tri_x[p->tricount][0] = xr[n];
        p->tri_y[p->tricount][0] = yr[n];
        p->tri_z[p->tricount][0] = box_zs+p->S307_bh;
        
        p->tri_x[p->tricount][1] = xr[n+1];
        p->tri_y[p->tricount][1] = yr[n+1];
        p->tri_z[p->tricount][1] = box_zs+p->S307_bh;
        
        p->tri_x[p->tricount][2] = xl[n];
        p->tri_y[p->tricount][2] = yl[n];
        p->tri_z[p->tricount][2] = box_zs+p->S307_bh;
        ++p->tricount;
        
        // Tri 2
        p->trivec_x[p->tricount] = 0.0;
        p->trivec_y[p->tricount] = -1.0;
        p->trivec_z[p->tricount] = 0.0;
        
        p->tri_x[p->tricount][0] = xr[n+1];
        p->tri_y[p->tricount][0] = yr[n+1];
        p->tri_z[p->tricount][0] = box_zs+p->S307_bh;
        
        p->tri_x[p->tricount][1] = xl[n+1];
        p->tri_y[p->tricount][1] = yl[n+1];
        p->tri_z[p->tricount][1] = box_zs+p->S307_bh;
        
        p->tri_x[p->tricount][2] = xl[n];
        p->tri_y[p->tricount][2] = yl[n];
        p->tri_z[p->tricount][2] = box_zs+p->S307_bh;
        ++p->tricount;
        
        
        // Face 6
        // Tri 1
        p->trivec_x[p->tricount] = 0.0;
        p->trivec_y[p->tricount] = -1.0;
        p->trivec_z[p->tricount] = 0.0;
        
        p->tri_x[p->tricount][0] = xl[n];
        p->tri_y[p->tricount][0] = yl[n];
        p->tri_z[p->tricount][0] = box_zs+p->S307_bh;
        
        p->tri_x[p->tricount][1] = xl[n+1];
        p->tri_y[p->tricount][1] = yl[n+1];
        p->tri_z[p->tricount][1] = box_zs+p->S307_bh;
        
        p->tri_x[p->tricount][2] = xl[n];
        p->tri_y[p->tricount][2] = yl[n];
        p->tri_z[p->tricount][2] = box_ze;
        ++p->tricount;
        
        // Tri 2
        p->trivec_x[p->tricount] = 0.0;
        p->trivec_y[p->tricount] = -1.0;
        p->trivec_z[p->tricount] = 0.0;
        
        p->tri_x[p->tricount][0] = xl[n+1];
        p->tri_y[p->tricount][0] = yl[n+1];
        p->tri_z[p->tricount][0] = box_zs+p->S307_bh;
        
        p->tri_x[p->tricount][1] = xl[n+1];
        p->tri_y[p->tricount][1] = yl[n+1];
        p->tri_z[p->tricount][1] = box_ze;
        
        p->tri_x[p->tricount][2] = xl[n];
        p->tri_y[p->tricount][2] = yl[n];
        p->tri_z[p->tricount][2] = box_ze;
        ++p->tricount;
        
        
        // Face 7
        // Tri 1
        p->trivec_x[p->tricount] = 0.0;
        p->trivec_y[p->tricount] = -1.0;
        p->trivec_z[p->tricount] = 0.0;
        
        p->tri_x[p->tricount][0] = xl[n];
        p->tri_y[p->tricount][0] = yl[n];
        p->tri_z[p->tricount][0] = box_ze;
        
        p->tri_x[p->tricount][1] = xl[n+1];
        p->tri_y[p->tricount][1] = yl[n+1];
        p->tri_z[p->tricount][1] = box_ze;
        
        p->tri_x[p->tricount][2] = xl[n];
        p->tri_y[p->tricount][2] = box_ye;
        p->tri_z[p->tricount][2] = box_ze;
        ++p->tricount;
        
        // Tri 2
        p->trivec_x[p->tricount] = 0.0;
        p->trivec_y[p->tricount] = -1.0;
        p->trivec_z[p->tricount] = 0.0;
        
        p->tri_x[p->tricount][0] = xl[n+1];
        p->tri_y[p->tricount][0] = yl[n+1];
        p->tri_z[p->tricount][0] = box_ze;
        
        p->tri_x[p->tricount][1] = xl[n+1];
        p->tri_y[p->tricount][1] = box_ye;
        p->tri_z[p->tricount][1] = box_ze;
        
        p->tri_x[p->tricount][2] = xl[n];
        p->tri_y[p->tricount][2] = box_ye;
        p->tri_z[p->tricount][2] = box_ze;
        ++p->tricount;
        
        
        // Face 8
        // Tri 1
        p->trivec_x[p->tricount] = 0.0;
        p->trivec_y[p->tricount] = -1.0;
        p->trivec_z[p->tricount] = 0.0;
        
        p->tri_x[p->tricount][0] = xl[n];
        p->tri_y[p->tricount][0] = box_ye;
        p->tri_z[p->tricount][0] = box_zs;
        
        p->tri_x[p->tricount][1] = xl[n+1];
        p->tri_y[p->tricount][1] = box_ye;
        p->tri_z[p->tricount][1] = box_zs;
        
        p->tri_x[p->tricount][2] = xl[n];
        p->tri_y[p->tricount][2] = box_ye;
        p->tri_z[p->tricount][2] = box_ze;
        ++p->tricount;
        
        // Tri 2
        p->trivec_x[p->tricount] = 0.0;
        p->trivec_y[p->tricount] = -1.0;
        p->trivec_z[p->tricount] = 0.0;
        
        p->tri_x[p->tricount][0] = xl[n+1];
        p->tri_y[p->tricount][0] = box_ye;
        p->tri_z[p->tricount][0] = box_zs;
        
        p->tri_x[p->tricount][1] = xl[n+1];
        p->tri_y[p->tricount][1] = box_ye;
        p->tri_z[p->tricount][1] = box_ze;
        
        p->tri_x[p->tricount][2] = xl[n];
        p->tri_y[p->tricount][2] = box_ye;
        p->tri_z[p->tricount][2] = box_ze;
        ++p->tricount;
    }
    
    te=p->tricount;
    
    
    
    cout<<"fluvial box end  "<<te<<endl<<endl<<endl;
    
}









