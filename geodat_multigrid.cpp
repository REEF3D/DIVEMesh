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
    
}

void geodat::prolong(lexer *p, dive *a)
{
    
    XYLOOP
    {
    a->topo(i,j) = ccipol(p,topof,p->XP[IP],p->YP[JP]);       
    }
    
    
}



double geodat::ccipol(lexer *p, double **f, double xp, double yp)
{
    ii=i;
    jj=j;
    
    i = p->posc_i(xp);
    j = p->posc_j(yp);
		
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

    i=ii;
    j=jj;
    

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
    
    xs-=xmin;
    
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
        if(xs>XP[kx-1+marge])
        {
            ii = kx+marge;
            
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

int geodat::posc_j(double ys)
{
    int js,je,jloc;
    int stop=0;
    int count=0;
    js = -marge;
    je = ky+marge;
    
    ys-=ymin;
    
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
        if(ys>YP[ky-1+marge])
        {
            jj = ky+marge;
            
            //cout<<"EXIT 0p  "<<YP[ky-1]<<endl;
   
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


int geodat::ihalf(int a, int b)
{
    int c;
    double d,diff;

    c = b-a;
    
    d = double(c)*0.5;

    c = int( d) + a;

    return c;
}