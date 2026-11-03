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
Architect: Hans Bihs
--------------------------------------------------------------------*/

#ifndef CATCHMENT_H_
#define CATCHMENT_H_

#include<string>
#include<vector>

class lexer;

using namespace std;

/*
Catchment preprocessing for REEF3D::HYDRO (W keywords)

Input:  catchment_dem.asc (ESRI ASCII grid, projected coordinates in m)
        optional catchment_glacier.asc (W 30 1), catchment_lake.asc (W 31 1), catchment_zone.asc (W 32 1),
        same raster geometry as the DEM
Steps:  1. depression filling and flow directions in one priority flood (Barnes et al. 2014):
           every pixel drains to the steepest lower neighbour (D8), pixels in filled depressions and on
           flats drain towards the spill point; the pop order of the flood is a topological order
        2. upstream area (flow accumulation)
        3. catchment above the outlet (W 20), sub-catchments above the gauges (W 21)
        4. hydrology cells of size W 11: area, elevation bands (W 12, equal area), outlet pixel
           (largest upstream area), downstream cell found along the fine flow path from outlet to outlet,
           channel length and slope along that path
Output: hydro_grid.dat (version 2: with the fine flow path of every cell; read by REEF3D, R 100),
        DIVEMesh_Hydro/hydro_cells.vtk, hydro_network.vtk,
        catchment_fine.vtk (W 40 1)
*/

class catchment
{
public:
    catchment(lexer*);
    void start(lexer*);

    struct raster
    {
        int nx=0, ny=0;
        double x0=0.0, y0=0.0, dx=1.0, nodata=-9999.0;
        vector<double> v;           // index i + nx*j, j=0 is the southern row
        bool valid(int q) const {return v[q]!=nodata;}
    };

    static bool read_raster(const string&, raster&);

private:
    int id(int i, int j) const {return i+nx*j;}
    double xc(int q) const {return dem.x0 + (q%nx + 0.5)*dx;}
    double yc(int q) const {return dem.y0 + (q/nx + 0.5)*dx;}

    void flood();                   // zf, dn, order
    void accumulate();              // acc
    int snap(double,double,double) const;
    void delineate(lexer*);         // inside, label
    void cells(lexer*);             // hydrology cells
    double path(int q0, int &qend, int &cend) const;  // fine path from q0 to the next cell outlet
    void write(lexer*);
    void write_vtk(lexer*);

    raster dem, glac, lake, zone;
    int nx, ny;
    double dx;

    vector<double> zf;              // filled elevation
    vector<int> dn;                 // downstream pixel, -1: leaves the raster
    vector<int> order;              // pop order of the flood: downstream before upstream
    vector<int> rank;               // position of a pixel in order
    vector<double> acc;             // upstream area [m2]
    vector<char> inside;            // pixel in the catchment
    vector<int> label;              // sub-catchment id, -1 outside
    int outlet;                     // outlet pixel (W 20), -1: every pixel of the raster
    vector<int> gpix;               // gauge pixels

    // hydrology cells, sorted upstream first
    struct hcell
    {
        int I, J;                   // index of the cell in the hydrology raster
        int out;                    // outlet pixel
        int down;                   // downstream cell, -1: outlet of the catchment
        double area, zmean, len, slope, aup, aup_cells;
        int sub, zone, npix;
        double lake;
        vector<double> bz, bf, bg;  // elevation, area fraction and glacier fraction of the bands
    };
    vector<hcell> hc;
    vector<int> gcell;              // hydrology cell of each gauge, -1 outside the catchment
    vector<int> cellout;            // hydrology cell of an outlet pixel, -1 other pixels
    int ni, nj, nb;
    double D;
};

#endif
