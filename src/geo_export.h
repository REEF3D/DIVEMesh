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

#ifndef GEO_EXPORT_H_
#define GEO_EXPORT_H_

#include<vector>
#include<initializer_list>

class lexer;

// Solid (S) and topo (T) geometry handed to REEF3D (grid format v2).
//
// Every S/T entity is collected as the triangle surface DIVEMesh ray casts
// (after scaling, translation and rotation), plus the entity's keyword,
// parameters and inside/outside convention. REEF3D builds the solid and topo
// representations of each hydrodynamic model from it; the grid files no longer
// carry solid_dist/topo_dist.

class geo_export
{
public:
    // object roles
    static const int role_solid = 1;   // S: solid
    static const int role_topo  = 2;   // T: topo
    static const int role_plate = 3;   // S/T 201: zero-thickness plate (wall surfaces only)

    struct object
    {
        int role;
        int keyword;              // DIVEMesh keyword: 1 STL, 10 box, 11 box array, ...
        int index;                // entity number of the keyword
        int raymode;              // S 18 at the time of the ray cast: 1 odd crossings inside, 2 even crossings inside
        int invert;               // S 9 / T 9 2: inside and outside swapped (applied to the field after this entity)
        long long ts, nt;         // triangle offset and count
        std::vector<double> param;
    };

    geo_export();

    // entity description for the next add()
    void meta(int keyword, int index, std::initializer_list<double> par);

    // copy the triangles ts..te of p->tri_x/y/z as one object
    void add(lexer*, int role, int ts, int te, int raymode);

    // last object of a role is inverted
    void invert_last(int role);

    int count(int role) const;

    // DIVEMesh_Grid/grid-geometry.dat
    bool write(lexer*, const char *name, int solidread, int toporead, int geodat) const;

    std::vector<object> obj;
    std::vector<double> tri;      // 9 doubles per triangle

    // river corridor grid (R 1 1), written as section CURV when ni > 0
    struct curvgrid
    {
        int ni=0, nj=0;
        std::vector<double> par;                  // R 2, R 3 wl, R 3 margin, R 5, raster spacing
        std::vector<double> x, y, zb;             // nodes, index i + (ni+1)*j
    } curv;

private:
    int kw, idx;
    std::vector<double> par;
};

#endif
