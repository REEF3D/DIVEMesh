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

#include "lexer.h"


double lexer::cellBasedSpacing
(
const double& p1, 
const double& p4, 
const double& pf_aim, 
const double& delta_f_aim,
const double& min_dp_aim, 
const double& max_dp_aim, 
const double& maxRatio_aim
)
{
    int nKnot = 0;
    
    cellBasedSpacing(p1, p4, pf_aim, delta_f_aim, min_dp_aim, max_dp_aim, maxRatio_aim, nKnot);
    
    return nKnot;
}


void lexer::cellBasedSpacing
(
const double& p1, 
const double& p4, 
const double& pf_aim, 
const double& delta_f_aim,
const double& min_dp_aim, 
const double& max_dp_aim, 
const double& maxRatio_aim,
int& index
)
{
    // Ini values
    
    double tol_min = 0.05*min_dp_aim;
    double tol_max = 0.1*max_dp_aim;
    double tol_focus = 3.0*min_dp_aim;
    double sf = 5.0;

    double delta_f = delta_f_aim;
    double p2 = pf_aim - delta_f/2;
    double p3 = pf_aim + delta_f/2; 
    double lp = p3 - p2;
    int knotp_2 = MAX(round(lp/(2.0*max_dp_aim)), 10);
    
    double min_dp, max_ratio;
    double pf = pf_aim;
    double max_dp = max_dp_aim;
    
    
    // Fit stretching zone
    
    bool fit_outer, fit_inner; 
    
    int nLoop_outer = 0;
    fit_outer = false;
    
    while (fit_outer == false)
    {
        p2 = pf_aim - delta_f/2;
        p3 = pf_aim + delta_f/2; 

        int nLoop_inner = 0;
        fit_inner = false;
        
        while (fit_inner == false)
        {
            fitFocusPoint(pf, p1, p2, p3, knotp_2, pf_aim, sf, tol_focus);
            max_ratio = fitStretching(pf, p1, p2, p3, knotp_2, maxRatio_aim, sf, tol_focus);
            min_dp = fitMinSize(fit_inner, pf, p1, p2, p3, knotp_2, min_dp_aim, sf, tol_min);

            if (nLoop_inner < 10000)
            {
                nLoop_inner++;
            }
            else
            {
                fit_inner = true;
            }
        }
        
        max_dp = fitMaxSize(fit_outer, delta_f, pf, p1, p2, p3, knotp_2, max_dp_aim, sf, tol_max);
        
        p2 = max(pf - delta_f/2, p1);
        p3 = min(pf + delta_f/2, p4); 
            
        if (p2 == p1 || p3 == p4) 
        {
            fit_outer = true;
        }
        
        if (nLoop_outer < 1000)
        {
            nLoop_outer++; 
        }
        else
        {
            fit_outer = true;
        }    
    }  


    // Define side zones
    
    int knotp_1 = round((p2 - p1)/max_dp);
    double dp_1 = (p2 - p1)/knotp_1;

    int knotp_3 = round((p4 - p3)/max_dp);
    double dp_3 = (p4 - p3)/knotp_3;


    // Determine field size
    if (index == 0)
    {
        for (int i = 0; i < knotp_1; i++)
        {
            index++;
        } 
    
        for (int i = 0; i <= knotp_2; i++)
        {
            index++;      
        } 
        
        for (int i = 1; i <= knotp_3; i++)
        {
            index++;     
        } 
        
        index--;
        
        /*
        cout<<"\nNumber of cells = "<<index<<endl; 
        cout<<"Min cell size = "<<min_dp<<endl;
        cout<<"Max cell size = "<<max_dp<<endl;
        cout<<"Focus point at "<<pf<<endl;
        cout<<"Max cell ratio = "<<max_ratio<<"\n"<<endl; 
        */
    }
    else
    {
        // Write field

        if (index == 1)  // x-field
        {
            for (int i = 0; i < knotp_1; i++)
            {
                XN[i + marge] = p1 + dp_1*double(i);
            }

            lp = p3 - p2;
            double c = (pf - p1 - p2)/lp;
            
            for (int i = 0; i <= knotp_2; i++)
            {
                XN[knotp_1 + i + marge] = p2 + lp * (sinh(sf*(1.0/double(knotp_2)*double(i)-c)) - sinh(-sf*c)) / (sinh(sf*(1.0-c))-sinh(-sf*c));      
            }

            for (int i = 1; i <= knotp_3; i++)
            {
                XN[knotp_1 + knotp_2 + i + marge] = p3 + dp_3*double(i);     
            }             
        }
        else if (index == 2) // y-field
        {
            for (int i = 0; i < knotp_1; i++)
            {
                YN[i + marge] = p1 + dp_1*double(i);
            }

            lp = p3 - p2;
            double c = (pf - p1 - p2)/lp;
            
            for (int i = 0; i <= knotp_2; i++)
            {
                YN[knotp_1 + i + marge] = p2 + lp * (sinh(sf*(1.0/double(knotp_2)*double(i)-c)) - sinh(-sf*c)) / (sinh(sf*(1.0-c))-sinh(-sf*c));      
            }

            for (int i = 1; i <= knotp_3; i++)
            {
                YN[knotp_1 + knotp_2 + i + marge] = p3 + dp_3*double(i);    
            }               
        }
        else    // z-field
        {
            for (int i = 0; i < knotp_1; i++)
            {
                ZN[i + marge] = p1 + dp_1*double(i);
            }

            lp = p3 - p2;
            double c = (pf - p1 - p2)/lp;
            
            for (int i = 0; i <= knotp_2; i++)
            {
                ZN[knotp_1 + i + marge] = p2 + lp * (sinh(sf*(1.0/double(knotp_2)*double(i)-c)) - sinh(-sf*c)) / (sinh(sf*(1.0-c))-sinh(-sf*c));      
            }

            for (int i = 1; i <= knotp_3; i++)
            {
                ZN[knotp_1 + knotp_2 + i + marge] = p3 + dp_3*double(i);    
            } 
        }
    }
}


void lexer::fitFocusPoint
(
    double& focus_point,
    const double& p1,
    const double& p2,
    const double& p3,
    const int& knotp,
    const double& focusPoint_aim,
    const double& stretchFactor,
    const double& tol
)
{
    bool fitted = false;
    int nLoop = 0;
    
    double c, pn, pn_m1, min_p, min_dp;
    
    double lp = p3 - p2;
    
    while(fitted == false)
    {
        c = (focus_point - p1 - p2)/lp;

        pn_m1 = p3;
        
        min_dp = lp;
        
        for (int i=0; i <= knotp; i++)
        {
            pn = p2 + lp * (sinh(stretchFactor*(1.0/double(knotp)*double(i)-c)) - sinh(-stretchFactor*c)) / (sinh(stretchFactor*(1.0-c))-sinh(-stretchFactor*c));

            if (fabs(pn - pn_m1) < min_dp)
            {
                min_dp = fabs(pn - pn_m1);
                min_p = pn;
            }

            pn_m1 = pn;
        }


        fitted = true;

        if (fabs(min_p - focusPoint_aim) > tol)
        {
            focus_point -= copysign(1.0, min_p - focusPoint_aim)*tol;
            fitted = false;
        }

        if (nLoop < 1000)
        {
            nLoop++; 
        }
        else
        {
            fitted = true;
        }
    }      
}


double lexer::fitStretching
(
    const double& focus_point,
    const double& p1,
    const double& p2,
    const double& p3,
    const int& knotp,
    const double& maxRatio_aim,
    double& stretchFactor,
    const double& tol
)
{
    bool fitted = false;
    int nLoop = 0;
    
    double c, pn, pn_m1, pn_m2, max_ratio, ratio;
    
    double lp = p3 - p2;
    
    while(fitted == false)
    {
        c = (focus_point - p1 - p2)/lp;

        pn_m1 = p3;
        pn_m2 = p3;
        
        max_ratio = 1.0;
        
        for (int i=0; i <= knotp; i++)
        {
            pn = p2 + lp * (sinh(stretchFactor*(1.0/double(knotp)*double(i)-c)) - sinh(-stretchFactor*c)) / (sinh(stretchFactor*(1.0-c))-sinh(-stretchFactor*c));

            ratio = (pn - pn_m1)/(pn_m1 - pn_m2);
            
            ratio = ratio < 1.0 ? 1.0/ratio : ratio;
            
            if (ratio > max_ratio)
            {
                max_ratio = ratio;
            }
            
            pn_m2 = pn_m1;
            pn_m1 = pn;
        }


        fitted = true;

        if (fabs(max_ratio - maxRatio_aim) > tol)
        {
            stretchFactor -=  copysign(1.0, max_ratio - maxRatio_aim)*tol;
            fitted = false;
        }

        if (nLoop < 1000)
        {
            nLoop++; 
        }
        else
        {
            fitted = true;
        }
    } 

    return max_ratio;
}


double lexer::fitMinSize
(
    bool& fitted,
    const double& focus_point,
    const double& p1,
    const double& p2,
    const double& p3,
    int& knotp,
    const double& min_dp_aim,
    double& stretchFactor,
    const double& tol
)
{
    fitted = true;
    
    double pn, pn_m1, min_dp;
    
    double lp = p3 - p2;
    double c = (focus_point - p1 - p2)/lp;

    pn_m1 = p3;
    min_dp = lp;
        
    for (int i=0; i <= knotp; i++)
    {
        pn = p2 + lp * (sinh(stretchFactor*(1.0/double(knotp)*double(i)-c)) - sinh(-stretchFactor*c)) / (sinh(stretchFactor*(1.0-c))-sinh(-stretchFactor*c));

        if (fabs(pn - pn_m1) < min_dp)
        {
           min_dp = fabs(pn - pn_m1);
        }
        
        pn_m1 = pn;
    }

    if (fabs(min_dp - min_dp_aim) > tol)
    {
        knotp +=  copysign(1.0, min_dp - min_dp_aim)*MAX(round(knotp/20),5);
        fitted = false;
    }
    
    return min_dp;
}


double lexer::fitMaxSize
(
    bool& fitted,
    double& delta_f,
    const double& focus_point,
    const double& p1,
    const double& p2,
    const double& p3,
    const int& knotp,
    const double& max_dp_aim,
    double& stretchFactor,
    const double& tol    
)
{
    double pn, pn_m1;
    
    double lp = p3 - p2;
    double c = (focus_point - p1 - p2)/lp;

    pn_m1 = p3;
    double max_dp = 0.0;
        
    for (int i=0; i <= knotp; i++)
    {
        pn = p2 + lp * (sinh(stretchFactor*(1.0/double(knotp)*double(i)-c)) - sinh(-stretchFactor*c)) / (sinh(stretchFactor*(1.0-c))-sinh(-stretchFactor*c));

        if ((fabs(pn - pn_m1) > max_dp) && i > 0)
        {
           max_dp = fabs(pn - pn_m1);
        }
        
        pn_m1 = pn;
    }
    
    
    fitted = true;
    
    if (fabs(max_dp - max_dp_aim) > tol)
    {
        delta_f -= copysign(1, max_dp - max_dp_aim)*0.01*delta_f;
        
        fitted = false;
    }
    
    return max_dp;
}