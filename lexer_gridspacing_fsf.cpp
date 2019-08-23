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

#include "lexer.h"

void lexer::gridspacing_fsf()
{
   int maxiter =200000;
    double lx,ly,lz;
    double ex,ey,ez;
    double fac;
    double s;
    double c;
    double epsi=1.0e-3*DXM;
    int stop,count;
    double dx0,dx1;
    
    lx = xmax-xmin;
    ly = ymax-ymin;
    lz = zmax-zmin;
    
    ex = 1.0/double(knox);
    ey = 1.0/double(knoy);
    ez = 1.0/double(knoz);
  
    fac = B111;
    
//  x-dir
    if(B101==1)
    for(i=0;i<knox+1;++i)
    {
    XN[IP] = lx * 0.5*(1.0 + sinh(2.0*B111*(ex*double(i)-0.5))/sinh(B111));
    }
    
    if(B101==2)
    for(i=0;i<knox+1;++i)
    {
    XN[IP] = lx * 0.5*(1.0 + tanh(2.0*B111*(ex*double(i)-0.5))/tanh(B111));
    }
    
    if(B101==3)
    for(i=0;i<knox+1;++i)
    {
    XN[IP] = lx * (exp(ex*double(i)*B111)-1.0)/(exp(B111-1.0));
    }
    
    if(B101==4)
    {
    double c;
    c = 1.0 - (B114_x-xmin)/lx;
        for(i=0;i<knox+1;++i)
        {
        XN[IP] = lx * (tanh(B111*(ex*double(i)-c)) - tanh(-B111*c)) / (tanh(B111*(1.0-c))-tanh(-B111*c));
        }
    }
  
    if(B101==5)
    {
        bool focused = false;
        int nLoop = 0;
        double fp = B114_x;
        double tol = 0.01;
        double xn, min_dx, min_x;
        
        while(focused == false)
        {
            c = (fp - xmin)/lx;

            double xn_m1 = xmax;
            double min_dx = lx;
            
            for (int i=0; i < knox + 1; ++i)
            {
                xn = lx * (sinh(B111*(ex*double(i)-c)) - sinh(-B111*c)) / (sinh(B111*(1.0-c))-sinh(-B111*c));

                if (abs(xn - xn_m1) < min_dx)
                {
                    min_dx = abs(xn - xn_m1);
                    min_x = xn;
                }

                xn_m1 = xn;
            }
        
            if (abs(min_x - B114_x) > tol && nLoop < 10000)
            {
                if (min_x > B114_x)
                {
                    fp = fp - tol;
                }
                else
                {
                    fp = fp + tol;  
                }
                
                nLoop++;
            }
            else
            {
                focused = true;
            }
        }
        
        c = (fp-xmin)/lx;
        
        for(i=0;i<knox+1;++i)
        {
            XN[IP] = lx * (sinh(B111*(ex*double(i)-c)) - sinh(-B111*c)) / (sinh(B111*(1.0-c))-sinh(-B111*c));
        }
    }
    

    if(B101==6)
    {
        bool focused = false;
        int nLoop = 0;
        double fp = B114_x;
        double tol = 0.01;
        double xn, min_dx, min_x;
        
        while(focused == false)
        {
            double xn_m1 = xmax;
            double min_dx = lx;
            
            for (int i=0; i < knox + 1; ++i)
            {
                s = ex*double(i);
                xn = lx * s + B111*(fp-lx*s)*s*(1.0-s);

                if (abs(xn - xn_m1) < min_dx)
                {
                    min_dx = abs(xn - xn_m1);
                    min_x = xn;
                }

                xn_m1 = xn;
            }
        
            if (abs(min_x - B114_x) > tol && nLoop < 10000)
            {
                if (min_x > B114_x)
                {
                    fp = fp - tol;
                }
                else
                {
                    fp = fp + tol;  
                }
                
                nLoop++;
            }
            else
            {
                focused = true;
            }
        }
        
        for(i=0;i<knox+1;++i)
        {
            s = ex*double(i);
    
            XN[IP] = lx * s + B111*(fp-lx*s)*s*(1.0-s);
        }
    }

    
    if(B101==8)
    {
    double lx1 = B121_x1-xmin;
    double lx2 = B121_x2-B121_x1;
    double lx3 = xmax-B121_x2;
    
    double ex1 = (1.0/double(B121_N1));
    double ex2 = (1.0/double(B121_N2));
    double ex3 = (1.0/double(B121_N3));
    
    
    for(i=0;i<B121_N1;++i)
    XN[IP] = lx1 * ex1 * double(i);
    
    for(i=B121_N1;i<B121_N2+B121_N1;++i)
    XN[IP] = lx2 * ex2 * double(i-B121_N1) + B121_x1;
    
    for(i=B121_N2+B121_N1;i<knox;++i)
    XN[IP] = lx3 * ex3 * double(i-B121_N2-B121_N1) + B121_x2;
    }
    
    
    if(B101==9)
    {
    //  PART 1
    dx0 = 0.1*DXM;
    dx1 = 0.1*DXM;
    
    XN[marge]=xmin;
    
    stop=0;
    count=0;
    do
    {

        for(i=1;i<=B124_N1;++i)
        {
        XN[IP] = XN[IM1] +  dx1*pow(double(i),-B124_f1);
        }
        
        
            if(XN[marge+B124_N1]>B124_x1+epsi)
            dx1-=1.0e-3*DXM;
            
            
            if(XN[marge+B124_N1]<B124_x1-epsi)
            dx1+=1.0e-3*DXM;
            
            
            if(XN[marge+B124_N1]>=B124_x1-epsi && XN[marge+B124_N1]<=B124_x1+epsi)
            stop=1;
        
        //if(count%1000==0)
        //cout<<count<<" XN: "<<XN[marge+B124_N1]<<" dx1: "<<dx1<<" stop: "<<stop<<endl;
        
        ++count;        
    }while(stop==0  && count<maxiter);
    
    
    // ------- 
    // PART 2   

    lx = B124_x3-B124_x1;
    ex = 1.0/double(B124_N2);

    bool focused = false;
    int nLoop = 0;
    double fp = B124_x2;
    double tol = 0.005;
    double xn, min_dx, min_x;
        
    while(focused == false)
    {
        c = (fp-xmin-B124_x1)/lx;

        double xn_m1 = B124_x3;
        double min_dx = lx;
            
        for (int i=0; i < knox + 1; ++i)
        {
            xn = lx * (sinh(B124_f2*(ex*double(i)-c)) - sinh(-B124_f2*c)) / (sinh(B124_f2*(1.0-c))-sinh(-B124_f2*c))  + XN[marge+B124_N1];

            if (abs(xn - xn_m1) < min_dx)
            {
                min_dx = abs(xn - xn_m1);
                min_x = xn;
            }

            xn_m1 = xn;
        }
        
        if (abs(min_x - B124_x2) > tol && nLoop < 10000)
        {
            if (min_x > B124_x2)
            {
                fp = fp - tol;
            }
            else
            {
                fp = fp + tol;  
            }
                
            nLoop++;
        }
        else
        {
            focused = true;
        }
    }
    
    c = (fp-xmin-B124_x1)/lx;
    

    for(i=1;i<B124_N2+1;++i)
    {
    XN[IP+B124_N1] = lx * (sinh(B124_f2*(ex*double(i)-c)) - sinh(-B124_f2*c)) / (sinh(B124_f2*(1.0-c))-sinh(-B124_f2*c))  + XN[marge+B124_N1];
    }

    // ------- 
    // PART 3
    
    dx0 = 0.1*DXM;
    dx1 = 0.1*DXM;
    
    stop=0;
    count=0;
    do
    {
        
        for(i=1;i<B124_N3+1;++i)
        {
        XN[IP+B124_N2+B124_N1] = XN[IM1+B124_N2+B124_N1] +  dx1*pow(double(i),B124_f3);
        }
        
        
            if(XN[marge+knox]>xmax+epsi)
            dx1-=1.0e-3*DXM;
            
            
            if(XN[marge+knox]<xmax-epsi)
            dx1+=1.0e-3*DXM;
            
            
            if(XN[marge+knox]>=xmax-epsi && XN[marge+knox]<=xmax+epsi)
            stop=1;
        
        ++count;
        
    }while(stop==0  && count<maxiter);
    
    }
    
    
    if(B101==10)
    {
        char name[100];
        double val;
        int count;
        
        sprintf(name,"x-spacing.dat");

    // open file------------
        ifstream file(name, ios_base::in);
        
        if(!file)
        {
            cout<<endl<<("no 'x-spacing.dat' file found")<<endl<<endl;

        }
        
        count=0;
        while(!file.eof())
        {
        file>>val;
        cout<<"val: "<<val<<endl;
        XN[count+marge]=val;
        ++count;
        }
        
        file.close();

    }

    
    
// ---------------------------------------------------------------------------------------
//  YDIR

    if(B102==1)
    for(j=0;j<knoy+1;++j)
    {
    YN[JP] = ly * 0.5*(1.0 + sinh(2.0*B112*(ey*double(j)-0.5))/sinh(B112));
    }
    
    if(B102==2)
    for(j=0;j<knoy+1;++j)
    {
    YN[JP] = ly * 0.5*(1.0 + tanh(2.0*B112*(ey*double(j)-0.5))/tanh(B112));
    }
    
    if(B102==3)
    for(j=0;j<knoy+1;++j)
    {
    YN[JP] = ly * (exp(ey*double(j)*B112)-1.0)/(exp(B112-1.0));
    }
    
    if(B102==4)
    {
    double c;
    c = 1.0 - (B115_y-ymin)/ly;
        for(j=0;j<knoy+1;++j)
        {
        YN[JP] = ly * (tanh(B112*(ey*double(j)-c)) - tanh(-B112*c)) / (tanh(B112*(1.0-c))-tanh(-B112*c));
        }
    }
    
   if(B102==5)
    {
        bool focused = false;
        int nLoop = 0;
        double fp = B115_y;
        double tol = 0.01;
        double yn, min_dy, min_y;
        
        while(focused == false)
        {
            c = (fp - ymin)/ly;

            double yn_m1 = ymax;
            double min_dy = ly;
            
            for (int j=0; j < knoy + 1; ++j)
            {
                yn = ly * (sinh(B112*(ey*double(j)-c)) - sinh(-B112*c)) / (sinh(B112*(1.0-c))-sinh(-B112*c));

                if (abs(yn - yn_m1) < min_dy)
                {
                    min_dy = abs(yn - yn_m1);
                    min_y = yn;
                }

                yn_m1 = yn;
            }
        
            if (abs(min_y - B115_y) > tol && nLoop < 10000)
            {
                if (min_y > B115_y)
                {
                    fp = fp - tol;
                }
                else
                {
                    fp = fp + tol;  
                }
                
                nLoop++;
            }
            else
            {
                focused = true;
            }
        }
        
        c = (fp-ymin)/ly;
            
        for(j=0;j<knoy+1;++j)
        {
            YN[JP] = ly * (sinh(B112*(ey*double(j)-c)) - sinh(-B112*c)) / (sinh(B112*(1.0-c))-sinh(-B112*c));
        }
    }

  if(B102==6)
    {
        bool focused = false;
        int nLoop = 0;
        double fp = B115_y;
        double tol = 0.01;
        double yn, min_dy, min_y;
        
        while(focused == false)
        {
            c = (fp - ymin)/ly;

            double yn_m1 = ymax;
            double min_dy = ly;
            
            for (int j=0; j < knoy + 1; ++j)
            {
                s = ey*double(j);
        
                yn = ly * s + B112*(fp-ly*s)*s*(1.0-s);

                if (abs(yn - yn_m1) < min_dy)
                {
                    min_dy = abs(yn - yn_m1);
                    min_y = yn;
                }

                yn_m1 = yn;
            }
        
            if (abs(min_y - B115_y) > tol && nLoop < 10000)
            {
                if (min_y > B115_y)
                {
                    fp = fp - tol;
                }
                else
                {
                    fp = fp + tol;  
                }
                
                nLoop++;
            }
            else
            {
                focused = true;
            }
        }
        
        for(j=0;j<knoy+1;++j)
        {
            s = ey*double(j);
        
            YN[JP] = ly * s + B112*(fp-ly*s)*s*(1.0-s);
        }
    }
    
    
    if(B102==8)
    {
    double ly1 = B122_y1-ymin;
    double ly2 = B122_y2-B122_y1;
    double ly3 = ymax-B122_y2;
    
    double ey1 = (1.0/double(B122_N1));
    double ey2 = (1.0/double(B122_N2));
    double ey3 = (1.0/double(B122_N3));
    
    
    for(j=0;j<B122_N1;++j)
    YN[JP] = ly1 * ey1 * double(j);
    
    for(j=B122_N1;j<B122_N2+B122_N1;++j)
    YN[JP] = ly2 * ey2 * double(j-B122_N1) + B122_y1;
    
    for(j=B122_N2+B122_N1;j<knoy;++j)
    YN[JP] = ly3 * ey3 * double(j-B122_N2-B122_N1) + B122_y2;
    }
    
    
    if(B102==9)
    {
    //  PART 1
    dx0 = 0.1*DXM;
    dx1 = 0.1*DXM;
    
    YN[marge]=ymin;
    
    stop=0;
    count=0;
    do
    {

        for(j=1;j<=B125_N1;++j)
        {
        YN[JP] = YN[JM1] +  dx1*pow(double(j),-B125_f1);
        }
        
        
            if(YN[marge+B125_N1]>B125_y1+epsi)
            dx1-=1.0e-3*DXM;
            
            
            if(YN[marge+B125_N1]<B125_y1-epsi)
            dx1+=1.0e-3*DXM;
            
            
            if(YN[marge+B125_N1]>=B125_y1-epsi && YN[marge+B125_N1]<=B125_y1+epsi)
            stop=1;
        
        ++count;        
    }while(stop==0  && count<maxiter);
    
    // ------- 
    // PART 2   

    ly = B125_y3-B125_y1;
    ey = 1.0/double(B125_N2);

    bool focused = false;
    int nLoop = 0;
    double fp = B125_y2;
    double tol = 0.005;
    double yn, min_dy, min_y;
        
    while(focused == false)
    {
        c = (fp-ymin-B125_y1)/ly;

        double yn_m1 = B125_y3;
        double min_dy = ly;
            
        for (int j=0; j < knoy + 1; ++j)
        {
            yn = ly * (sinh(B125_f2*(ey*double(j)-c)) - sinh(-B125_f2*c)) / (sinh(B125_f2*(1.0-c))-sinh(-B125_f2*c))  + YN[marge+B125_N1];

            if (abs(yn - yn_m1) < min_dy)
            {
                min_dy = abs(yn - yn_m1);
                min_y = yn;
            }

            yn_m1 = yn;
        }
        
        if (abs(min_y - B125_y2) > tol && nLoop < 10000)
        {
            if (min_y > B125_y2)
            {
                fp = fp - tol;
            }
            else
            {
                fp = fp + tol;  
            }
                
            nLoop++;
        }
        else
        {
            focused = true;
        }
    }
    
    c = (fp-ymin-B125_y1)/ly;
    
    for(j=1;j<B125_N2+1;++j)
    {
    YN[JP+B125_N1] = ly * (sinh(B125_f2*(ey*double(j)-c)) - sinh(-B125_f2*c)) / (sinh(B125_f2*(1.0-c))-sinh(-B125_f2*c))  + YN[marge+B125_N1];
    }
  

    // ------- 
    // PART 3
    
    dx0 = 0.1*DXM;
    dx1 = 0.1*DXM;
    
    stop=0;
    count=0;
    do
    {
        
        for(j=1;j<B125_N3+1;++j)
        {
        YN[JP+B125_N2+B125_N1] = YN[JM1+B125_N2+B125_N1] +  dx1*pow(double(j),B125_f3);
        }
        
        
            if(YN[marge+knoy]>ymax+epsi)
            dx1-=1.0e-3*DXM;
            
            
            if(YN[marge+knoy]<ymax-epsi)
            dx1+=1.0e-3*DXM;
            
            
            if(YN[marge+knoy]>=ymax-epsi && YN[marge+knoy]<=ymax+epsi)
            stop=1;
        
        ++count;
        
    }while(stop==0  && count<maxiter);
    
    
    }
    

    if(B102==10)
    {
        char name[100];
        double val;
        int count;
        
        sprintf(name,"y-spacing.dat");

    // open file------------
        ifstream file(name, ios_base::in);
        
        if(!file)
        {
            cout<<endl<<("no 'y-spacing.dat' file found")<<endl<<endl;

        }
        
        count=0;
        while(!file.eof())
        {
        file>>val;
        cout<<"val: "<<val<<endl;
        YN[count+marge]=val;
        ++count;
        }
        
        file.close();

    }    
    
    

// ---------------------------------------------------------------------------------------
//  ZDIR

    if(B103==1)
    for(k=0;k<knoz+1;++k)
    {
    ZN[KP] = lz * 0.5*(1.0 + sinh(2.0*B113*(ez*double(k)-0.5))/sinh(B113));
    }
    
    if(B103==2)
    for(k=0;k<knoz+1;++k)
    {
    ZN[KP] = lz * 0.5*(1.0 + tanh(2.0*B113*(ez*double(k)-0.5))/tanh(B113));
    }
    
    
    
    if(B103==3)
    for(k=0;k<knoz+1;++k)
    {
    ZN[KP] = lz * (1.0-(exp(ez*double(knoz-k)*B113)-1.0)/(exp(B113)-1.0));
    }


    if(B103==4)
    for(k=0;k<knoz+1;++k)
    {
    ZN[KP] = lz * sin(0.5*PI*double(k)/double(knoz));
    }
    

    if(B103==5)
    {
        bool focused = false;
        int nLoop = 0;
        double fp = B116_z;
        double tol = 0.01;
        double zn, min_dz, min_z;
        
        while(focused == false)
        {
            c = (fp - zmin)/lz;

            double zn_m1 = zmax;
            double min_dz = lz;
            
            for (int k=0; k < knoz + 1; ++k)
            {
                zn = lz * (sinh(B113*(ez*k - c)) - sinh(-B113*c)) / (sinh(B113*(1.0-c))-sinh(-B113*c));
                
                if (abs(zn - zn_m1) < min_dz)
                {
                    min_dz = abs(zn - zn_m1);
                    min_z = zn;
                }

                zn_m1 = zn;
            }
        
            if (abs(min_z - B116_z) > tol && nLoop < 10000)
            {
                if (min_z > B116_z)
                {
                    fp = fp - tol;
                }
                else
                {
                    fp = fp + tol;  
                }
                
                nLoop++;
            }
            else
            {
                focused = true;
            }
        }
        
        c = (fp-zmin)/lz;
    
        for(k=0;k<knoz+1;++k)
        {
        ZN[KP] = lz * (sinh(B113*(ez*double(k)-c)) - sinh(-B113*c)) / (sinh(B113*(1.0-c))-sinh(-B113*c));
        }
    }

    
    if(B103==6)
    {
        bool focused = false;
        int nLoop = 0;
        double fp = B116_z;
        double tol = 0.01;
        double zn, min_dz, min_z;
        
        while(focused == false)
        {
            double zn_m1 = zmax;
            double min_dz = lz;
            
            for (int k=0; k < knoz + 1; ++k)
            {
                s = ez*double(k);
                zn = lz * s + B113*(fp-lz*s)*s*(1.0-s);
                
                if (abs(zn - zn_m1) < min_dz)
                {
                    min_dz = abs(zn - zn_m1);
                    min_z = zn;
                }

                zn_m1 = zn;
            }
        
            if (abs(min_z - B116_z) > tol && nLoop < 10000)
            {
                if (min_z > B116_z)
                {
                    fp = fp - tol;
                }
                else
                {
                    fp = fp + tol;  
                }
                
                nLoop++;
            }
            else
            {
                focused = true;
            }
        }
        
        for(k=0; k<knoz + 1; ++k)
        {
            s = ez*double(k);
        
            ZN[KP] = lz * s + B113*(fp-lz*s)*s*(1.0-s);
        }
    }
    
    
    if(B103==7)
    {
        int count=0;
        int stop=0;
        double f = B113;
        
        ZN[0]=zmin;
        do
        {
            
            for(k=1;k<knoz+1;++k)
            {
            s = ez*double(k);
            
            ZN[KP] = ZN[KM1] + dx*(1.0+pow(f*double(k),2.0));
            }
            
            if(ZN[knoz+marge]<zmax+1.0e-5 && ZN[knoz+marge]>zmax-1.0e-5)
            stop=1;
            
            if(ZN[knoz+marge]>zmax+1.0e-5)
            f-=1.0e-5;
            
            if(ZN[knoz+marge]<zmax-1.0e-5)
            f+=1.0e-5;
            
            ++count;
            
        }while(stop==0 && count<1.e4);
    }
    
    if(B103==8)
    { 
    double lz1 = B123_z1-zmin;
    double lz2 = B123_z2-B123_z1;
    double lz3 = zmax-B123_z2;
    
    double ez1 = (1.0/double(B123_N1));
    double ez2 = (1.0/double(B123_N2));
    double ez3 = (1.0/double(B123_N3));
    
    
    for(k=0;k<B123_N1;++k)
    ZN[KP] = lz1 * ez1 * double(k);
    
    for(k=B123_N1;k<B123_N2+B123_N1;++k)
    ZN[KP] = lz2 * ez2 * double(k-B123_N1) + B123_z1;
    
    for(k=B123_N2+B123_N1;k<knoz;++k)
    ZN[KP] = lz3 * ez3 * double(k-B123_N2-B123_N1) + B123_z2;
    }
    
    if(B103==9)
    {

    //  PART 1
    dx0 = 0.1*DXM;
    dx1 = 0.1*DXM;
    
    ZN[marge]=zmin;
    
    
    stop=0;
    count=0;
    do
    {

        for(k=1;k<=B126_N1;++k)
        {
        ZN[KP] = ZN[KM1] +  dx1*pow(double(k),-B126_f1);// + dx0;
        }
        
        
            if(ZN[marge+B126_N1]>B126_z1+epsi)
            dx1-=1.0e-3*DXM;
            
            
            if(ZN[marge+B126_N1]<B126_z1-epsi)
            dx1+=1.0e-3*DXM;
            
            
            if(ZN[marge+B126_N1]>=B126_z1-epsi && ZN[marge+B126_N1]<=B126_z1+epsi)
            stop=1;
            
        //if(count%1000==0)
        //cout<<count<<" ZN: "<<ZN[marge+B126_N1]<<" dx1: "<<dx1<<" stop: "<<stop<<endl;
    
        ++count;        
    }while(stop==0  && count<maxiter);
    
    
    // ------- 
    // PART 2   

    lz = B126_z3-B126_z1;
    ez = 1.0/double(B126_N2);

    bool focused = false;
    int nLoop = 0;
    double fp = B126_z2;
    double tol = 0.005;
    double zn, min_dz, min_z;
        
    while(focused == false)
    {
        c = (fp-zmin-B126_z1)/lz;

        double zn_m1 = B126_z3;
        double min_dz = lz;
            
        for (int k=0; k < knoz + 1; ++k)
        {
            zn = lz * (sinh(B126_f2*(ez*double(k)-c)) - sinh(-B126_f2*c)) / (sinh(B126_f2*(1.0-c))-sinh(-B126_f2*c))  + ZN[marge+B126_N1];

            if (abs(zn - zn_m1) < min_dz)
            {
                min_dz = abs(zn - zn_m1);
                min_z = zn;
            }

            zn_m1 = zn;
        }
        
        if (abs(min_z - B126_z2) > tol && nLoop < 10000)
        {
            if (min_z > B126_z2)
            {
                fp = fp - tol;
            }
            else
            {
                fp = fp + tol;  
            }
                
            nLoop++;
        }
        else
        {
            focused = true;
        }
    }
    
    c = (fp-zmin-B126_z1)/lz;
    
    for(k=1;k<B126_N2+1;++k)
    {
    ZN[KP+B126_N1] = lz * (sinh(B126_f2*(ez*double(k)-c)) - sinh(-B126_f2*c)) / (sinh(B126_f2*(1.0-c))-sinh(-B126_f2*c))  + ZN[marge+B126_N1];
    }

    // ------- 
    // PART 3
    
    dx0 = 0.1*DXM;
    dx1 = 0.1*DXM;
    
    stop=0;
    count=0;
    do
    {
        
        for(k=1;k<B126_N3+1;++k)
        {
        ZN[KP+B126_N2+B126_N1] = ZN[KM1+B126_N2+B126_N1] +  dx1*pow(double(k),B126_f3);// + dx0;
        }
        
        
            if(ZN[marge+knoz]>zmax+epsi)
            dx1-=1.0e-3*DXM;
            
            
            if(ZN[marge+knoz]<zmax-epsi)
            dx1+=1.0e-3*DXM;
            
            
            if(ZN[marge+knoz]>=zmax-epsi && ZN[marge+knoz]<=zmax+epsi)
            stop=1;
        
        ++count;
        
    //if(count%1000==0)
    //cout<<count<<" ZN: "<<ZN[marge+knoz]<<" dx0: "<<dx0<<" stop: "<<stop<<endl;
        
    }while(stop==0  && count<maxiter);
    
    
    }
    
    if(B103==10)
    {
        char name[100];
        double val;
        int count;
        
        sprintf(name,"z-spacing.dat");

    // open file------------
        ifstream file(name, ios_base::in);
        
        if(!file)
        {
            cout<<endl<<("no 'z-spacing.dat' file found")<<endl<<endl;

        }
        
        count=0;
        while(!file.eof())
        {
        file>>val;
        cout<<"val: "<<val<<endl;
        ZN[count+marge]=val;
        ++count;
        }
        
        file.close();

    }
    
    
    
    double mindx=1e20;
    double mindz=1e20;
    
    for(i=1;i<knox;++i)
    mindx = MIN(mindx,XN[IP1]-XN[IP]);

    for(k=1;k<knoz;++k)
    mindz = MIN(mindz,ZN[KP1]-ZN[KP]);
   /* 
    cout<<endl<<endl;
    for(k=0;k<knoz+1;++k)
    cout<<"Z: "<<ZN[KP]<<endl;*/
    
    /*
    cout<<endl<<endl;
    for(i=0;i<knox+1;++i)
    cout<<i<<"  X: "<<XN[IP]<<endl;
    
    
    cout<<"MINDX: "<<mindx<<endl;
    cout<<"MINDZ: "<<mindz<<endl;*/
}