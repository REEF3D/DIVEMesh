/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2021 Hans Bihs

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

#include"solid.h"
#include"dive.h"
#include"lexer.h"

void solid::fluvial_box_fill_segments(lexer *p, dive *a, int rank, int &ts, int &te)
{
    xl[0] = x0;
    yl[0] = y0 + p->S306*0.5;
    
    xr[0] = x0;
    yr[0] = y0 - p->S306*0.5;
    
    // get left and right segment
    for(n=0;n<p->S300;++n)
    {
        //straight channel
        if(p->S300_ord[n]==1)
        {
        xl[countds] = xl[countds-1] + p->S310_l[countS310]*cos(phi0);
        yl[countds] = yl[countds-1] + p->S310_l[countS310]*sin(phi0);
        
        xr[countds] = xr[countds-1] + p->S310_l[countS310]*cos(phi0);
        yr[countds] = yr[countds-1] + p->S310_l[countS310]*sin(phi0);
        
        ++countds;
        ++countS310;
        }
        
        // left bend
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
        
        
        // right bend
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
            
            s = (p->S340_L[countS340]*p->S340_N[countS340])/double(ds_count);
            
            
            x1 = 0.5*(xl[lastds-1]+xr[lastds-1]);
            y1 = 0.5*(yl[lastds-1]+yr[lastds-1]);
            
            //cout<<"MEANDER dscount: "<<ds_count<<endl;
            
            for(q=1;q<=ds_count;++q)
            {
            teta = p->S340_teta[countS340]*cos(2.0*PI*(s*double(q))/p->S340_L[countS340] + p->S340_ds[countS340]*PI);
            
            xc = x1 + s*cos(teta);
            yc = y1 + s*sin(teta);
            
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
            
            //cout<<"MEANDER: "<<teta<<" "<<m<<" "<<nx<<" "<<ny<<endl;
            
            
            x1=xc;
            y1=yc;
            
            ++countds;
            }

            //phi0 -= p->S340_phi[countS340];
            ++countS340;
        }
    }
    
    numds = countds;
    
    
    
}