/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2018 Hans Bihs

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

#include<iostream>
#include<math.h>
#include"iterators.h"

#define MAX(aAa,bBb) ((aAa)>(bBb)?(aAa):(bBb))
#define MIN(aAa,bBb) ((aAa)<(bBb)?(aAa):(bBb))

#define MAX3(aAa,bBb,cCc) (((aAa)>(bBb)?(aAa):(bBb))>cCc?((aAa)>(bBb)?(aAa):(bBb)):cCc)
#define MIN3(aAa,bBb,cCc) (((aAa)<(bBb)?(aAa):(bBb))<cCc?((aAa)<(bBb)?(aAa):(bBb)):cCc)

#define IDIR if(a->i_dir==1)
#define JDIR if(a->j_dir==1)
#define KDIR if(a->k_dir==1)
	

#define ILOOP for(i=x1;i<a->knox+x1;++i)
#define JLOOP for(j=y1;j<a->knoy+y1;++j)
#define KLOOP for(k=z1;k<a->knoz+z1;++k)
#define LOOP ILOOP JLOOP KLOOP

#define IMALOOP for(i=x1-a->xma;i<a->knox+x1+a->xma;++i)
#define JMALOOP for(j=y1-a->yma;j<a->knoy+y1+a->yma;++j)
#define KMALOOP for(k=z1-a->zma;k<a->knoz+z1+a->zma;++k)
#define MALOOP IMALOOP JMALOOP KMALOOP

#define IOUTCHECK if(i<x1 || i>=a->knox+x1)
#define JOUTCHECK if(j<y1 || j>=a->knoy+y1)
#define KOUTCHECK if(k<z1 || k>=a->knoz+z1)
#define OUTCHECK if(i<x1 || i>=a->knox+x1 || j<y1 || j>=a->knoy+y1 || k<z1 || k>=a->knoz+z1)

#define IINCHECK if(i>=x1 && i<a->knox+x1)
#define JINCHECK if(j>=y1 && j<a->knoy+y1)
#define KINCHECK if(k>=z1 && k<a->knoz+z1)
#define INCHECK IINCHECK JINCHECK KINCHECK

#define XYLOOP ILOOP JLOOP
#define YXLOOP JLOOP ILOOP

#define XYMALOOP IMALOOP JMALOOP
#define YXMALOOP JMALOOP IMALOOP

#define XLOOP JLOOP KLOOP ILOOP
#define YLOOP ILOOP KLOOP JLOOP
#define ZLOOP ILOOP JLOOP KLOOP

#define INLOOP for(i=x1;i<=a->knox+x1;++i)
#define JNLOOP for(j=y1;j<=a->knoy+y1;++j)
#define KNLOOP for(k=z1;k<=a->knoz+z1;++k)
#define NODELOOP INLOOP JNLOOP KNLOOP

#define ALOOP for(aa=1;aa<=a->mx;++aa)
#define BLOOP for(bb=1;bb<=a->my;++bb)
#define CLOOP for(cc=1;cc<=a->mz;++cc)
#define NLOOP ALOOP BLOOP CLOOP

#define AMALOOP for(aa=0;aa<=a->mx+1;++aa)
#define BMALOOP for(bb=0;bb<=a->my+1;++bb)
#define CMALOOP for(cc=0;cc<=a->mz+1;++cc)
#define NMALOOP AMALOOP BMALOOP CMALOOP

#define SILOOP for(i=a->xnode[aa-1];i<a->xnode[aa];++i)
#define SJLOOP for(j=a->ynode[bb-1];j<a->ynode[bb];++j)
#define SKLOOP for(k=a->znode[cc-1];k<a->znode[cc];++k)
#define SUBLOOP SILOOP SJLOOP SKLOOP

#define SNODEILOOP for(i=a->xnode[aa-1]-marge;i<=a->xnode[aa]+marge;++i)
#define SNODEJLOOP for(j=a->ynode[bb-1]-marge;j<=a->ynode[bb]+marge;++j)
#define SNODEKLOOP for(k=a->znode[cc-1]-marge;k<=a->znode[cc]+marge;++k)
#define SUBNODELOOP SNODEILOOP SNODEJLOOP SNODEKLOOP

#define PARANUM (aa-1)*a->my*a->mz + (bb-1)*a->mz + cc;

#define PARANUM (aa-1)*a->my*a->mz + (bb-1)*a->mz + cc;

#define MAX(aAa,bBb) ((aAa)>(bBb)?(aAa):(bBb))
#define MIN(aAa,bBb) ((aAa)<(bBb)?(aAa):(bBb))

#ifndef INCREMENT_H_
#define INCREMENT_H_

#define PI 3.14159265359

using namespace std;

class increment
{
	public:
	increment();
	virtual ~increment();
	static int i,j,k,aa,bb,cc,n,q;
	static int qn;
	static int x1,x2,y1,y2,z1,z2;
	static int xma,yma,zma;
    static int marge;
    static int margin;

	int conv(double);
	int equals(double,double);

};
#endif
