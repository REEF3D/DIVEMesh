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

#ifndef INT_TABLE_H_
#define INT_TABLE_H_

#include<cstdlib>
#include<cstddef>
#include<memory>
#include<new>

// rows x cols ints in one block, used as table[q][c]. calloc leaves large
// untouched blocks as unmapped zero pages, so over-allocated rows are free.
class int_table
{
public:
    void allocate(size_t rows, int cols)
    {
        ncols = size_t(cols);
        nrows = rows;
        data.reset(static_cast<int*>(std::calloc(rows*ncols>0 ? rows*ncols : 1, sizeof(int))));

        if(!data)
        throw std::bad_alloc();
    }

    inline int* operator[](size_t q) { return data.get() + q*ncols; }
    inline const int* operator[](size_t q) const { return data.get() + q*ncols; }

    size_t rows() const { return nrows; }

private:
    struct free_deleter { void operator()(int *ptr) const { std::free(ptr); } };

    std::unique_ptr<int,free_deleter> data;
    size_t ncols = 0, nrows = 0;
};

#endif
