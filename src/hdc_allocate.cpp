/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2022 Hans Bihs

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

#include"hdc.h"
#include"lexer.h"
#include"dive.h"

void hdc::allocate(lexer *p, dive *a)
{
    // allocated arrays
    result = new ifstream[numprocs];
    wfile  = new ofstream[p->M10];
    
    p->Darray(X,NGx);
    p->Darray(Y,NGy);
    p->Darray(Z,NGz);
    p->Darray(bed,NGx,NGy);

    p->Farray(eta,NGx,NGy);
    p->Farray(Fifsf,NGx,NGy);
    
    p->Farray(U,NGx,NGy,NGz);
    p->Farray(V,NGx,NGy,NGz);
    p->Farray(W,NGx,NGy,NGz);
    
    p->Iarray(orig_i,numprocs);
    p->Iarray(orig_j,numprocs);
    p->Iarray(orig_k,numprocs);
    
    p->Darray(orig_x,numprocs);
    p->Darray(orig_y,numprocs);
    p->Darray(orig_z,numprocs);
    
    p->Iarray(nb1,numprocs);
    p->Iarray(nb2,numprocs);
    p->Iarray(nb3,numprocs);
    p->Iarray(nb4,numprocs);
    
    p->Iarray(NLx,numprocs);
    p->Iarray(NLy,numprocs);
    p->Iarray(NLz,numprocs);
    
}