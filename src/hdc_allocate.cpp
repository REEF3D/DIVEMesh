/*--------------------------------------------------------------------
REEF3D
Copyright 2008-2021 Hans Bihs

This file is part of REEF3D.

REEF3D is free software; you can redistribute it and/or modify it
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

#include"hdc.h"
#include"lexer.h"
#include"dive.h"

void hdc::allocate(lexer *p, dive *a)
{
    
    // allocated arrays
    p->Darray(X,NGx);
    p->Darray(Y,NGy);
    p->Darray(Z,NGz);
    p->Darray(bed,NGx,NGy);
        
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
    
    
    // allocate arrays
    p->Darray(X,NGx);
    p->Darray(Y,NGy);
    p->Darray(Z,NGz);
    p->Darray(eta,NGx,NGy);
    p->Darray(Fifsf,NGx,NGy);
    p->Darray(bed,NGx,NGy);
    p->Darray(U,NGx,NGy,NGz);
    p->Darray(V,NGx,NGy,NGz);
    p->Darray(W,NGx,NGy,NGz);
    
    
    
}