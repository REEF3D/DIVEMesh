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

#include"geodat.h"
#include"dive.h"
#include"lexer.h"

void geodat::coarsen(lexer *p, dive *a)
{
    int count;
    
    // x
    count=0;
    ILOOP
    if(i%p->G30==0)
    {
    XC[count+marge]=p->XP[IP];
    ++count;
    }
    
    kx=count;
    
    //for(i=0;i<kx;++i)
    //cout<<"XC: "<<XC[i+marge]<<endl;
    
    // y
    count=0;
    JLOOP
    if(j%p->G30==0)
    {
    YC[count+marge]=p->YP[JP];
    ++count;
    }
    
    ky=count;
    
    p->Darray(topof,kx,ky);
    
    cout<<"coarsen knox:"<<p->knox<<" kx: "<<kx<<" | knoy:"<<p->knoy<<" ky: "<<ky<<endl;
    
    
    // bc
    XC[marge-1] = XC[marge+1]-XC[marge];
    XC[marge-2] = XC[marge+1]-XC[marge];
    XC[marge+kx+1] = XC[marge+kx-1]-XC[marge+kx-2];
    XC[marge+kx+2] = XC[marge+kx-1]-XC[marge+kx-2];
    
    YC[marge-1] = YC[marge+1]-YC[marge];
    YC[marge-2] = YC[marge+1]-YC[marge];
    YC[marge+ky+1] = YC[marge+ky-1]-YC[marge+ky-2];
    YC[marge+ky+2] = YC[marge+ky-1]-YC[marge+ky-2];
    
}

void geodat::prolong(lexer *p, dive *a)
{
    double xc,yc,val;

    cout<<"prolong "<<endl;
    
    XYLOOP
    {
    xc = p->XP[IP];
    yc = p->YP[JP];
    
    //cout<<"pos_xy: "<<i<<" "<<j<<" | "<<xc<<" "<<yc<<endl;
    
    val = ccipol(p,topof,xc,yc);   

    a->topo(i,j) = val;    
    }
}


double geodat::ccipol(lexer *p, double **f, double xp, double yp)
{
    iii=i;
    jjj=j;
    
    
    
    i = posc_i(xp);
    j = posc_j(yp);
    cout<<"pos_ij: "<<i<<" "<<j<<" | "<<xp<<" "<<yp<<endl;
		
    // wa
    wa = (XC[IP1]-xp)/(XC[IP1]-XC[IP]);
    
    if(wa<0.0)
    {
    wa = (XC[IP2]-xp)/(XC[IP1]-XC[IP]);
    ++i;
    }
    
    if(wa>1.0)
    {
    wa = (XC[IP]-xp)/(XC[IP1]-XC[IP]);
    --i;
    }
    

    // wb
    wb = (YC[JP1]-yp)/(YC[JP1]-YC[JP]);
    
    if(wb<0.0)
    {
    wb = (YC[JP2]-yp)/(YC[JP1]-YC[JP]);
    ++j;
    }
    
    if(wb>1.0)
    {
    wb = (YC[JP]-yp)/(YC[JP1]-YC[JP]);
    --j;
    }
    
    
    value =  lint(p,f,i,j,wa,wb);
    
    

    i=iii;
    j=jjj;
    
    return value;
}


double geodat::lint(lexer *p, double **f, int& i,int& j, double wa, double wb)
{
    v1=v2=v3=v4=0.0;
    c1=c2=c3=c4=0;


    if(i>=0 && i<kx && j>=0 && j<ky)
    {
    v1=f[i][j];
    c1=1;
    }
    
    if(i>=0 && i<kx && j+1>=0 && j+1<ky)
    {
    v2=f[i][j+1];
    c2=1;
    }
    
    if(i+1>=0 && i+1<kx && j>=0 && j<ky)
    {
    v3=f[i+1][j];
    c3=1;
    }
    
    if(i+1>=0 && i+1<kx && j+1>=0 && j+1<ky)
    {
    v4=f[i+1][j+1];
    c4=1;
    }

    
    // x1
    if(c1==1 && c3==1)
    x1 = wa*v1 + (1.0-wa)*v3;
    
    if(c1==1 && c3==0)
    x1 = v1;
    
    if(c1==0 && c3==1)
    x1 = v3;
    
    
    // x2
    if(c2==1 && c4==1)
    x2 = wa*v2 + (1.0-wa)*v4;
    
    if(c2==1 && c4==0)
    x2 = v2;
    
    if(c2==0 && c4==1)
    x2 = v4;
    
    if((c1==0 && c3==0) && (c2==1 || c4==1))
    wb=0.0;
    
    if((c2==0 && c4==0) && (c1==1 || c3==1))
    wb=1.0;
    
    if(c2==0 && c4==0 && c1==1 && c3==1)
    {
    x1=x2=0.0;
    }

    value = wb*x1 + (1.0-wb)*x2;
    
 return value;

}


int geodat::posc_i(double xs)
{
    int is,ie,iloc;
    int stop=0;
    int count=0;
    is = -marge;
    ie = kx+marge;
    
    
    
    xs-=XC[marge];
    
    count=0;
    do{
    iloc = ihalf(is,ie);
    
    if(count%3==0)
    iloc+=1;
    
    //cout<<"iloc: "<<iloc<<" is: "<<is<<" ie: "<<ie<<endl;
    
        // matching criterion
        if(xs<XC[iloc+marge] && xs>=XC[iloc-1+marge])
        {
            ii = iloc;
            
            //cout<<"EXIT_i_1 "<<iloc<<"   xs: "<<xs<<" XC[iloc+marge]: "<<XC[iloc+marge]<<" XC[iloc-1+marge]: "<<XC[iloc-1+marge]<<endl;
            
         stop=1;
         break;   
        }
        
        if(xs>=XC[iloc+marge] && xs<XC[iloc+1+marge])
        {
            ii = iloc+1;

            //cout<<"EXIT_i_2 "<<iloc<<"   xs: "<<xs<<" XC[iloc+marge]: "<<XC[iloc+marge]<<" XC[iloc+1+marge]: "<<XC[iloc+1+marge]<<endl;
   
         stop=1;
         break;   
        }
        
        // out of bounds
        if(xs<XC[0])
        {
            ii = -1;
            
            //cout<<"EXIT 0m"<<" xs: "<<xs<<" XP: "<<XC[0+marge]<<endl;
   
         stop=1;
         break;   
        }
        
        // out of bounds
        if(xs>XC[kx-1+marge])
        {
            ii = kx+marge;
            
            //cout<<"EXIT 0p"<<endl;
   
         stop=1;
         break;   
        }
        
        // further division
        if(xs<XC[iloc+marge] && xs<XC[iloc-1+marge])
        ie=iloc;
        
        if(xs>XC[iloc+marge] && xs>XC[iloc+1+marge])
        is=iloc;
        
        
        ++count;
    }while(stop==0 && count<1000);
    
    ii=MAX(ii,0);
    ii=MIN(ii,kx-1);
    
    
    return ii;
}

int geodat::posc_j(double ys)
{
    int js,je,jloc;
    int stop=0;
    int count=0;
    js = -marge;
    je = ky+marge;
    
    ys-=YC[marge];
    
    count=0;
    do{
    jloc = ihalf(js,je);
    
    if(count%3==0)
    jloc+=1;
    
    //cout<<"ys: "<<ys<<" jloc: "<<jloc<<" js: "<<js<<" je: "<<je<<endl;
    
        // matching criterion
        if(ys<YC[jloc+marge] && ys>=YC[jloc-1+marge])
        {
            jj = jloc;
            
            //cout<<"EXIT 1 "<<jloc<<"   ys: "<<ys<<" YC[jloc+marge]: "<<YC[jloc+marge]<<" YC[jloc-1+marge]: "<<YC[jloc-1+marge]<<endl;
            
         stop=1;
         break;   
        }
        
        if(ys>=YC[jloc+marge] && ys<YC[jloc+1+marge])
        {
            jj = jloc+1;
            
            //cout<<"EXIT 2 "<<jloc<<"   ys: "<<ys<<" YC[jloc+marge]: "<<YC[jloc+marge]<<" YC[jloc+1+marge]: "<<YC[jloc+1+marge]<<endl;
   
         stop=1;
         break;   
        }
        
        // out of bounds
        if(ys<YC[0])
        {
            jj = -1;
            
            //cout<<"EXIT 0m  ys: "<<ys<<" YP: "<<YC[0]<<endl;
   
         stop=1;
         break;   
        }
        
        // out of bounds
        if(ys>YC[ky-1+marge])
        {
            jj = ky+marge;
            
            //cout<<"EXIT 0p  "<<YC[ky-1]<<endl;
   
         stop=1;
         break;   
        }
        
        // further divjsion
        if(ys<YC[jloc+marge] && ys<YC[jloc-1+marge])
        je=jloc;
        
        if(ys>YC[jloc+marge] && ys>YC[jloc+1+marge])
        js=jloc;
        
        
        ++count;
    }while(stop==0 && count<1000);
    
    jj=MAX(jj,0);
    jj=MIN(jj,ky-1);
    
    
    return jj;
}


int geodat::ihalf(int a, int b)
{
    int c;
    double d,diff;

    c = b-a;
    
    d = double(c)*0.5;

    c = int( d) + a;

    return c;
}