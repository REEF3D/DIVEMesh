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

#ifndef CORRIDOR_H_
#define CORRIDOR_H_

#include<vector>

class lexer;
class dive;

using namespace std;

//  Curvilinear corridor grid for a river (R 1 1).
//
//  The grid follows the river corridor, not the banks: the banks are wet/dry fronts in the
//  hydrodynamic model, so one grid serves all water levels and stays smooth and close to
//  orthogonal.  It is built from the bed level and the solid columns of the Cartesian grid,
//  sampled on a uniform working raster (spacing R 9, default max(DXM,1 m)):
//
//   1 centreline   least-cost path along the medial ridge of the wet area below R 2, between the
//                  wet runs on the inflow and outflow sides (C 1x = 1 and 2), smoothed over R 8 m;
//                  with R 7 1 the polyline in corridor-centreline.dat (x y, inflow to outflow)
//   2 corridor     area below R 3 wl (connected to the river) plus a dry margin of R 3 m, islands
//                  filled, side inlets narrower than 2 x R 5 removed, banks smoothed; cut square
//                  to the channel near the domain edges
//   3 harmonic grid  phi = 0/1 at the two cuts (Neumann on the banks) gives the cross-sections,
//                  psi = 0/1 on the right/left bank (Neumann at the cuts) the along-channel lines;
//                  phi levels uniform in centreline arc length; nodes traced along the phi levels
//   4 clean-up     banks smoothed along the river, R 6 Winslow iterations from the harmonic grid
//
//  Output: the grid as section CURV of DIVEMesh_Grid/grid-geometry.dat (REEF3D skips it until it
//  reads curvilinear grids), DIVEMesh_Paraview/corridor-grid.vtk and DIVEMesh_Log/corridor.log.
//  The Cartesian grid and all other output are unchanged.

class corridor
{
public:
    corridor(lexer*, dive*);
    virtual ~corridor();

    void start(lexer*, dive*);

private:
    // ---- working raster
    int nx,ny;
    double x0,y0,h;
    vector<double> bed;
    vector<char> solid;
    int id(int i, int j) const { return i + nx*j; }
    void build_raster(lexer*, dive*);

    // raster tools (corridor_raster.cpp)
    void main_component(vector<char>&, int conn) const;
    int label(const vector<char>&, vector<int>&, int conn) const;
    void fill_holes(vector<char>&) const;
    void dist_to(const vector<char>&, vector<double>&) const;      // distance (m) to the nearest true cell
    void blur(vector<double>&, double sigma) const;                 // Gaussian, sigma in m
    void dilate4(vector<char>&, int it) const;
    double bilin(const vector<double>&, double x, double y) const;
    int cell(double x, double y) const;                             // nearest cell, -1 outside

    // ---- centreline (corridor_path.cpp)
    vector<double> cx,cy,cnx,cny,cs;
    void centreline(lexer*);
    bool read_centreline(lexer*);
    void stations(vector<double>&, vector<double>&, double sigma);
    void side_runs(const vector<char>&, int &start, int &end, lexer*) const;

    // ---- corridor region
    vector<char> env, R;
    double reach(int q, double sign) const;
    void region(lexer*);
    vector<double> cut_t[2], cut_n[2];
    double cut_L[2];

    // ---- harmonic grid (corridor_harmonic.cpp)
    vector<double> phi,psi;
    void harmonic(const vector<char> &fix, const vector<double> &val, vector<double> &f);
    void solve_fields(lexer*);
    void trace_grid(lexer*);

    // ---- grid, clean-up and output (corridor_grid.cpp)
    int ni,nj;
    vector<double> X,Y,ZB;          // nodes (ni+1)*(nj+1), index i + (ni+1)*j
    int nd(int i, int j) const { return i + (ni+1)*j; }
    void smooth(lexer*);
    void quality_and_output(lexer*, dive*);
    double bed_at(lexer*, dive*, double x, double y) const;
};

#endif
