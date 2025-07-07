/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2025 Hans Bihs

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

void geometry::fluvial_box_fill_segments(lexer *p, dive *a, int rank, int &ts, int &te)
{
    countG310=0;
    countG320=0;
    countG330=0;
    countG340=0;
    
    xl[0] = x0;
    yl[0] = y0 + G306*0.5;
    
    xr[0] = x0;
    yr[0] = y0 - G306*0.5;
    
    // get left and right segment
    for(n=0;n<G300;++n)
    {
        //straight channel
        if(G300_ord[n]==1)
        {
        xl[countds] = xl[countds-1] + G310_l[countG310]*cos(phi0);
        yl[countds] = yl[countds-1] + G310_l[countG310]*sin(phi0);
        
        xr[countds] = xr[countds-1] + G310_l[countG310]*cos(phi0);
        yr[countds] = yr[countds-1] + G310_l[countG310]*sin(phi0);
        
        ++countds;
        ++countG310;
        }
        
        // left bend
        if(G300_ord[n]==2)
        {
            lastds = countds;
            length = (G320_r[countG320])*G320_phi[countG320];
            ds_count = int(length/(G305*p->DXM));
            dangle = G320_phi[countG320]/double(ds_count);
            
            deltax = xl[lastds-1] - (G320_r[countG320]-G306*0.5)*cos(dangle*double(0)+phi0-0.5*PI);
            deltay = yl[lastds-1] - (G320_r[countG320]-G306*0.5)*sin(dangle*double(0)+phi0-0.5*PI);
            
            for(q=1;q<=ds_count;++q)
            {
            xl[countds] = deltax + (G320_r[countG320]-G306*0.5)*cos(dangle*double(q)+phi0-0.5*PI);
            yl[countds] = deltay + (G320_r[countG320]-G306*0.5)*sin(dangle*double(q)+phi0-0.5*PI);
            
            xr[countds] = deltax + (G320_r[countG320]+G306*0.5)*cos(dangle*double(q)+phi0-0.5*PI);
            yr[countds] = deltay + (G320_r[countG320]+G306*0.5)*sin(dangle*double(q)+phi0-0.5*PI);

            ++countds;   
            }
            
            phi0 += G320_phi[countG320];
            ++countG320;
            
        }
        
        // right bend
        if(G300_ord[n]==3)
        {
            lastds = countds;
            length = (G330_r[countG330])*G330_phi[countG330];
            ds_count = int(length/(G305*p->DXM));
            dangle = -G330_phi[countG330]/double(ds_count);
            
            deltax = xl[lastds-1] - (G330_r[countG330]+G306*0.5)*cos(dangle*double(0)+phi0-1.5*PI);
            deltay = yl[lastds-1] - (G330_r[countG330]+G306*0.5)*sin(dangle*double(0)+phi0-1.5*PI);
        
            for(q=1;q<=ds_count;++q)
            {
            xl[countds] = deltax + (G330_r[countG330]+G306*0.5)*cos(dangle*double(q)+phi0-1.5*PI);
            yl[countds] = deltay + (G330_r[countG330]+G306*0.5)*sin(dangle*double(q)+phi0-1.5*PI);
            
            xr[countds] = deltax + (G330_r[countG330]-G306*0.5)*cos(dangle*double(q)+phi0-1.5*PI);
            yr[countds] = deltay + (G330_r[countG330]-G306*0.5)*sin(dangle*double(q)+phi0-1.5*PI);

            ++countds;   
            }


            phi0 -= G330_phi[countG330];
            ++countG330;
        }

        // meander
        if(G300_ord[n]==4)
        {
            lastds = countds;
        
            ds_count = int((G340_L[countG340]*G340_N[countG340])/(G305*p->DXM));  
            
            s = (G340_L[countG340]*G340_N[countG340])/double(ds_count);
            
            
            x1 = 0.5*(xl[lastds-1]+xr[lastds-1]);
            y1 = 0.5*(yl[lastds-1]+yr[lastds-1]);
            
            cout<<"MEANDER dscount: "<<ds_count<<" "<<G340_L[countG340]<<" "<<G340_N[countG340]<<" "<<G305*p->DXM<<endl;
            
            for(q=1;q<=ds_count;++q)
            {
            teta = G340_teta[countG340]*cos(2.0*PI*(s*double(q))/G340_L[countG340] + G340_ds[countG340]*PI);
            
            xc = x1 + s*cos(teta);
            yc = y1 + s*sin(teta);
            
            m = (yc-y1)/(xc-x1);
            
            nx = -m;
            ny = 1.0;

            norm = sqrt(nx*nx + ny*ny);
            
            nx/=fabs(norm>1.0e-20)?norm:1.0e20;
            ny/=fabs(norm>1.0e-20)?norm:1.0e20;
            
            xl[countds] = xc + nx*0.5*G306;
            yl[countds] = yc + ny*0.5*G306;
            
            xr[countds] = xc - nx*0.5*G306;
            yr[countds] = yc - ny*0.5*G306;
            
            //cout<<"MEANDER: "<<teta<<" "<<m<<" "<<nx<<" "<<ny<<" "<<countds<<endl;
            
            
            x1=xc;
            y1=yc;
            
            ++countds;
            }

            //phi0 -= G340_phi[countG340];
            ++countG340;
        }
    }
    
    numds = countds;
    
    
    
}