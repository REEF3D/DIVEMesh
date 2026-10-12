/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2026 Hans Bihs

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

#ifndef MULTIBLOCK_H_
#define MULTIBLOCK_H_

#include<vector>
#include<string>

class lexer;

using namespace std;

//  Multi-block curvilinear grid (R 20 1): several structured blocks of 2D nodes that meet along
//  their faces, the level-0 grids of REEF3D::SFLOW (G 50 1).
//
//  Input blocks.dat in the case folder: the number of blocks, then per block "ni nj" and the
//  (ni+1)(nj+1) nodes "x y zb", i fastest (as curvgrid.dat).  Blocks touch where their face nodes
//  coincide: the interfaces are found here, as segments of a face (a run of coincident nodes),
//  each with the neighbour block, its face and the index transform (8 orientations).
//
//  Block 0 becomes the grid of the run (DIVEMesh box and CURV section, as R 1 2): its own cells
//  plus a ring of R 21 cells on every face with an interface, whose nodes are the nodes of the
//  neighbour block (REEF3D computes the ring redundantly and refills it before every stage).  Its
//  interfaces have to cover whole faces.  All blocks, their segments and the nodes of blocks 1..
//  go into the section BLKS of DIVEMesh_Grid/grid-geometry.dat.
//
//  Transform of a segment (cells): the neighbour cell of cell (i,j) of this block is
//      i' = sign[0]*c[perm[0]] + off[0],  j' = sign[1]*c[perm[1]] + off[1],  c = (i,j)
//  valid for the cells next to the segment on both sides (also the ghost cells beyond the face).

class multiblock
{
public:
    struct seg
    {
        int face;               // 0: -i, 1: +i, 2: -j, 3: +j
        int lo, hi;             // cells along the face
        int nbr, nface;         // neighbour block and its face
        int perm[2], sign[2], off[2];   // cell transform
        int t[2];               // node transform offset: node' = sign*N[perm] + t
    };

    struct block
    {
        int ni=0, nj=0;
        vector<double> x, y, zb;            // nodes, index i + (ni+1)*j
        vector<seg> segs;
        int ring[4] = {0,0,0,0};            // block 0: ring cells on the faces
    };

    multiblock();

    // read blocks.dat, find the interfaces, check them; false: message printed
    bool start(lexer*);

    // the grid of the run: block 0 with its ring (nodes, bed levels)
    int box_ni() const { return b[0].ni + b[0].ring[0] + b[0].ring[1]; }
    int box_nj() const { return b[0].nj + b[0].ring[2] + b[0].ring[3]; }
    double spacing() const { return hm; }
    vector<double> X0, Y0, Z0;

    vector<block> b;
    int W;

private:
    void find_interfaces(lexer*);
    bool node_of(int blk, int K, int L, int depth, double &x, double &y, double &z) const;
    void box_nodes();
    void log(lexer*) const;

    double hm, tol;
    vector<string> msg;
};

#endif
