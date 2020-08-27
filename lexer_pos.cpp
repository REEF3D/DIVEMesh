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

#include"lexer.h"

double lexer::posc_x()
{
    double pos=XP[IP];

    return pos;
}

double lexer::posc_y()
{
    double pos=YP[JP];

    return pos;
}

double lexer::posc_z()
{
    double pos=ZP[KP];

    return pos;
}

int lexer::posf_i(double xs)
{
    int is,ie,iloc;
    int stop=0;
    int count=0;
    is = -marge;
    ie = knox+marge+1;
    
    
    count=0;
    do{
    iloc = ihalf(is,ie);
    
    if(count%3==0)
    iloc+=1;
    
    //cout<<"iloc: "<<iloc<<" is: "<<is<<" ie: "<<ie<<endl;
    
        // out of bounds
        if(xs<XN[0])
        {
            ii = -marge;
            
            //cout<<"EXIT 0m"<<endl;
   
         stop=1;
         break;   
        }
        
        // out of bounds
        if(xs>XN[knox+marge])
        {
            ii = knox+marge;
            
            //cout<<"EXIT 0p"<<endl;
   
         stop=1;
         break;   
        }
        
        
        // matching criterion
        if(xs<XN[iloc+marge] && xs>=XN[iloc-1+marge] && stop==0)
        {
            ii = iloc-1;
            
            //cout<<"EXIT 1   "<<ii<<endl;
            
         stop=1;
         break;   
        }
        
        if(xs>=XN[iloc+marge] && xs<XN[iloc+1+marge] && stop==0)
        {
            ii = iloc;
            
            //cout<<"EXIT 2   "<<ii<<endl;
   
         stop=1;
         break;   
        }
        
        
        // further division
        if(xs<XN[iloc+marge] && xs<XN[iloc-1+marge])
        ie=iloc;
        
        if(xs>XN[iloc+marge] && xs>XN[iloc+1+marge])
        is=iloc;
        
        
        ++count;
    }while(stop==0 && count<1000);
    
    
    return ii;
}

int lexer::posf_j(double ys)
{
    int js,je,jloc;
    int stop=0;
    int count=0;
    js = -marge;
    je = knoy+marge+1;

    
    count=0;
    do{
    jloc = ihalf(js,je);
    
    if(count%3==0)
    jloc+=1;
    
    //cout<<"jloc: "<<jloc<<" js: "<<js<<" je: "<<je<<endl;
        
        
        // out of bounds
        if(ys<YN[0])
        {
            jj = -marge;
            
            //cout<<"EXIT 0m"<<endl;
   
         stop=1;
         break;   
        }
        
        // out of bounds
        if(ys>YN[knoy+marge])
        {
            jj = knoy+marge;
            
            //cout<<"EXIT 0p"<<endl;
   
         stop=1;
         break;   
        }
        
        
        
        // matching criterion
        if(ys<YN[jloc+marge] && ys>=YN[jloc-1+marge] && stop==0)
        {
            jj = jloc-1;
            
            //cout<<"EXIT 1   "<<jj<<"  "<<YN[jloc+marge]<<"  "<<YN[jloc-1+marge]<<"  "<<YN[jloc+1+marge]<<endl;
            
         stop=1;
         break;   
        }
        
        if(ys>=YN[jloc+marge] && ys<YN[jloc+1+marge] && stop==0)
        {
            jj = jloc;
            
            //cout<<"EXIT 2   "<<jj<<endl;
   
         stop=1;
         break;   
        }
        
        // further divjsion
        if(ys<YN[jloc+marge] && ys<YN[jloc-1+marge])
        je=jloc;
        
        if(ys>YN[jloc+marge] && ys>YN[jloc+1+marge])
        js=jloc;
        
        
        ++count;
    }while(stop==0 && count<1000);
    
    
    return jj;
}

int lexer::posf_k(double zs)
{
    int ks,ke,kloc;
    int stop=0;
    int count=0;
    ks = -marge;
    ke = knoz+marge+1;

    
    count=0;
    do{
    kloc = ihalf(ks,ke);
    
    if(count%3==0)
    kloc+=1;
    
    //cout<<"zs: "<<zs<<" kloc: "<<kloc<<" ks: "<<ks<<" ke: "<<ke<<endl;
        
         // out of bounds
        if(zs<ZN[0])
        {
            kk = -marge;
            
            //cout<<"EXIT 0m "<<zs<<endl;
   
         stop=1;
         break;   
        }
        
        // out of bounds
        if(zs>ZN[knoz+marge])
        {
            kk = knoz+marge;
            
            //cout<<"EXIT 0p "<<zs<<endl;
   
         stop=1;
         break;   
        }
        
        // matching criterion
        if(zs<ZN[kloc+marge] && zs>=ZN[kloc-1+marge] && stop==0)
        {
            kk = kloc-1;
            
            //cout<<"EXIT 1"<<endl;
            
         stop=1;
         break;   
        }
        
        if(zs>=ZN[kloc+marge] && zs<ZN[kloc+1+marge] && stop==0)
        {
            kk = kloc;
            
            //cout<<"EXIT 2"<<endl;
   
         stop=1;
         break;   
        }
        
        
        // further divksion
        if(zs<ZN[kloc+marge] && zs<ZN[kloc-1+marge])
        ke=kloc;
        
        if(zs>ZN[kloc+marge] && zs>ZN[kloc+1+marge])
        ks=kloc;
        
        
        ++count;
    }while(stop==0 && count<1000);
    
    
    return kk;
}

int lexer::ihalf(int a, int b)
{
    int c;
    double d,diff;

    c = b-a;
    
    d = double(c)*0.5;

    c = int( d) + a;

    return c;
}

int lexer::posc_i(double xs)
{
    int is,ie,iloc;
    int stop=0;
    int count=0;
    is = -marge;
    ie = knox+marge;
    
    count=0;
    do{
    iloc = ihalf(is,ie);
    
    if(count%3==0)
    iloc+=1;
    
    //cout<<"iloc: "<<iloc<<" is: "<<is<<" ie: "<<ie<<endl;
    
        // matching criterion
        if(xs<XP[iloc+marge] && xs>=XP[iloc-1+marge])
        {
            ii = iloc;
            
            //cout<<"EXIT_i_1 "<<iloc<<"   xs: "<<xs<<" XP[iloc+marge]: "<<XP[iloc+marge]<<" XP[iloc-1+marge]: "<<XP[iloc-1+marge]<<endl;
            
         stop=1;
         break;   
        }
        
        if(xs>=XP[iloc+marge] && xs<XP[iloc+1+marge])
        {
            ii = iloc+1;

            //cout<<"EXIT_i_2 "<<iloc<<"   xs: "<<xs<<" XP[iloc+marge]: "<<XP[iloc+marge]<<" XP[iloc+1+marge]: "<<XP[iloc+1+marge]<<endl;
   
         stop=1;
         break;   
        }
        
        // out of bounds
        if(xs<XP[0])
        {
            ii = -marge;
            
            //cout<<"EXIT 0m"<<" xs: "<<xs<<" XP: "<<XP[0+marge]<<endl;
   
         stop=1;
         break;   
        }
        
        // out of bounds
        if(xs>XP[knox-1+marge])
        {
            ii = knox+marge;
            
            //cout<<"EXIT 0p"<<endl;
   
         stop=1;
         break;   
        }
        
        // further division
        if(xs<XP[iloc+marge] && xs<XP[iloc-1+marge])
        ie=iloc;
        
        if(xs>XP[iloc+marge] && xs>XP[iloc+1+marge])
        is=iloc;
        
        
        ++count;
    }while(stop==0 && count<1000);
    
    
    return ii;
}

int lexer::posc_j(double ys)
{
    int js,je,jloc;
    int stop=0;
    int count=0;
    js = -marge;
    je = knoy+marge;
    
    count=0;
    do{
    jloc = ihalf(js,je);
    
    if(count%3==0)
    jloc+=1;
    
    //cout<<"ys: "<<ys<<" jloc: "<<jloc<<" js: "<<js<<" je: "<<je<<endl;
    
        // matching criterion
        if(ys<YP[jloc+marge] && ys>=YP[jloc-1+marge])
        {
            jj = jloc;
            
            //cout<<"EXIT 1 "<<jloc<<"   ys: "<<ys<<" YP[jloc+marge]: "<<YP[jloc+marge]<<" YP[jloc-1+marge]: "<<YP[jloc-1+marge]<<endl;
            
         stop=1;
         break;   
        }
        
        if(ys>=YP[jloc+marge] && ys<YP[jloc+1+marge])
        {
            jj = jloc+1;
            
            //cout<<"EXIT 2 "<<jloc<<"   ys: "<<ys<<" YP[jloc+marge]: "<<YP[jloc+marge]<<" YP[jloc+1+marge]: "<<YP[jloc+1+marge]<<endl;
   
         stop=1;
         break;   
        }
        
        // out of bounds
        if(ys<YP[0])
        {
            jj = -marge;
            
            //cout<<"EXIT 0m  ys: "<<ys<<" YP: "<<YP[0]<<endl;
   
         stop=1;
         break;   
        }
        
        // out of bounds
        if(ys>YP[knoy-1+marge])
        {
            jj = knoy+marge;
            
            //cout<<"EXIT 0p  "<<YP[knoy-1]<<endl;
   
         stop=1;
         break;   
        }
        
        // further divjsion
        if(ys<YP[jloc+marge] && ys<YP[jloc-1+marge])
        je=jloc;
        
        if(ys>YP[jloc+marge] && ys>YP[jloc+1+marge])
        js=jloc;
        
        
        ++count;
    }while(stop==0 && count<1000);
    
    
    return jj;
}



int lexer::posc_k(double zs)
{
    int ks,ke,kloc;
    int stop=0;
    int count=0;
    ks = -marge;
    ke = knoz+marge;


    count=0;
    do{
    kloc = ihalf(ks,ke);
    
    if(count%3==0)
    kloc+=1;
    
    //cout<<"kloc: "<<kloc<<" ks: "<<ks<<" ke: "<<ke<<endl;
    
        // matching criterion
        if(zs<ZP[kloc+marge] && zs>=ZP[kloc-1+marge])
        {
            kk = kloc;
            
            //cout<<"EXIT 1"<<endl;
            
         stop=1;
         break;   
        }
        
        if(zs>=ZP[kloc+marge] && zs<ZP[kloc+1+marge])
        {
            kk = kloc+1;
            
            //cout<<"EXIT 2"<<endl;
   
         stop=1;
         break;   
        }
        
        // out of bounds
        if(zs<ZP[0])
        {
            kk = -marge;
            
            //cout<<"EXIT 0m"<<endl;
   
         stop=1;
         break;   
        }
        
        // out of bounds
        if(zs>ZP[knoz-1+marge])
        {
            kk = knoz+marge;
            
            //cout<<"EXIT 0p"<<endl;
   
         stop=1;
         break;   
        }
        
        // further divksion
        if(zs<ZP[kloc+marge] && zs<ZP[kloc-1+marge])
        ke=kloc;
        
        if(zs>ZP[kloc+marge] && zs>ZP[kloc+1+marge])
        ks=kloc;
        
        
        ++count;
    }while(stop==0 && count<1000);
    
    
    return kk;
}


int lexer::poscgen_i(double xs, double *XC, int kx)
{
    int is,ie,iloc;
    int stop=0;
    int count=0;
    is = -marge;
    ie = kx+marge;
    
    
    count=0;
    do{
    iloc = ihalf(is,ie);
    
    if(count%3==0)
    iloc+=1;
    
    
        // matching criterion
        if(xs<XC[iloc+marge] && xs>=XC[iloc-1+marge])
        {
            ii = iloc;
            
         stop=1;
         break;   
        }
        
        if(xs>=XC[iloc+marge] && xs<XC[iloc+1+marge])
        {
            ii = iloc+1;

         stop=1;
         break;   
        }
        
        /*
        // out of bounds
        if(xs<XC[0])
        {
            ii = -3;
            
            cout<<" xs: "<<xs<<" XC[0]: "<<XC[0]<<endl;
             
         stop=1;
         break;   
        }
        
        // out of bounds
        if(xs>XC[kx-1+marge])
        {
            ii = kx+marge+3;
            cout<<" xs: "<<xs<<" XC[kx-1+marge]: "<<XC[kx-1+marge]<<endl;
         stop=1;
         break;   
        }*/
        
        // further division
        if(xs<XC[iloc+marge] && xs<XC[iloc-1+marge])
        ie=iloc;
        
        if(xs>XC[iloc+marge] && xs>XC[iloc+1+marge])
        is=iloc;
        
        
        ++count;
    }while(stop==0 && count<1000);
    
    /*
    ii=MAX(ii,-3);
    ii=MIN(ii,kx+2);*/
    
    
    return ii;
}

int lexer::poscgen_j(double ys, double *YC, int ky)
{
    int js,je,jloc;
    int stop=0;
    int count=0;
    js = -marge;
    je = ky+marge;
    

    count=0;
    do{
    jloc = ihalf(js,je);
    
    if(count%3==0)
    jloc+=1;
    
        // matching criterion
        if(ys<YC[jloc+marge] && ys>=YC[jloc-1+marge])
        {
            jj = jloc;
                     
         stop=1;
         break;   
        }
        
        if(ys>=YC[jloc+marge] && ys<YC[jloc+1+marge])
        {
            jj = jloc+1;
            
         stop=1;
         break;   
        }
        
        /*
        // out of bounds
        if(ys<YC[0])
        {
            jj = -3;
            
         stop=1;
         break;   
        }
        
        // out of bounds
        if(ys>YC[ky-1+marge])
        {
            jj = ky+marge+3;
            
         stop=1;
         break;   
        }*/
        
        // further divjsion
        if(ys<YC[jloc+marge] && ys<YC[jloc-1+marge])
        je=jloc;
        
        if(ys>YC[jloc+marge] && ys>YC[jloc+1+marge])
        js=jloc;
        
        
        ++count;
    }while(stop==0 && count<1000);
    
    /*
    jj=MAX(jj,-3);
    jj=MIN(jj,ky+2);
    */
    
    return jj;
}
