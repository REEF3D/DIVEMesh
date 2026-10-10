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

#ifndef GRIDFILE_V2_H_
#define GRIDFILE_V2_H_

// DIVEMesh -> REEF3D grid format, version 2
//
// file     = magic[8] | int32 version | int32 endian marker | section* | "END "
// section  = char tag[4] | int64 nbytes | payload[nbytes]
//
// DIVEMesh_Grid/grid-geometry.dat (one file, all ranks)
//   GHDR  int32 nint, int32[nint], int32 ndbl, double[ndbl]
//   OBJS  int32 nobj, per object: int32 role, keyword, index, raymode, invert,
//                                 int64 tri offset, int64 tri count, int32 npar, double[npar]
//   VERT  int64 nvert, double[3*nvert]  unique vertices x y z
//   TIDX  table(ntri x 3)                vertex indices of the triangles
//   CURV  int32 nint=3, int32 layout version, ni, nj, int32 ndbl, double[ndbl] (R 2, R 3 wl,
//         R 3 margin, R 5, raster spacing), double x[n], y[n], zbed[n] with n = (ni+1)(nj+1),
//         node (i,j) at i + (ni+1)*j: river corridor grid (R 1 1), i along the river from the
//         inflow, j across from the right bank; only with R 1 1
//
// DIVEMesh_Grid/grid-%06i.dat (one file per rank)
//   HEAD  int32 nint, int32[nint], int32 ndbl, double[ndbl]
//   FLAG  run-length coded int32 cell flags, i-j-k order: int64 nrun, (int32 value, int32 length)[nrun]
//   NODE  double XN[knox+1+2*marge], YN[...], ZN[...]
//   SURF  table(nsurf x 5)               i j k side group
//   PARA  6 x table(n x 3)               i j k
//   PACO  6 x table(n x 3)               i j k
//   SLFL  run-length coded int32 column flags, i-j order
//   SLPA  4 x table(n x 2)               i j
//   SLPC  4 x table(n x 2)               i j
//
// table(n x c): int64 n, int32 c, then column by column the differences to the
//               previous row, zigzag and varint coded (1 byte for |difference| < 64)
//   GEOB  double[knox*knoy]              geodat bed level (if G 10 > 0)
//   DATA  double[knox*knoy]              interpolated data (if D 10 > 0)
//
// The layout of the HEAD and GHDR int/double lists is fixed by the version.
// Unknown sections are skipped by the reader.

#include<vector>
#include<cstring>
#include<cstdint>

namespace gridv2
{
    const char magic_grid[8] = {'D','M','G','R','I','D','0','2'};
    const char magic_geom[8] = {'D','M','G','E','O','M','0','2'};
    const int version = 2;
    const int endian = 0x01020304;

    struct writer
    {
        std::vector<char> buf;

        void put(const void *val, size_t bytes)
        {
            const size_t m = buf.size();
            buf.resize(m+bytes);
            std::memcpy(&buf[m],val,bytes);
        }

        void put_int(int val)          { put(&val,sizeof(int)); }
        void put_i64(long long val)    { int64_t v=val; put(&v,sizeof(int64_t)); }
        void put_double(double val)    { put(&val,sizeof(double)); }

        void start(const char magic[8])
        {
            put(magic,8);
            put_int(version);
            put_int(endian);
        }

        // returns the position of the length field
        size_t begin(const char tag[4])
        {
            put(tag,4);
            const size_t pos = buf.size();
            put_i64(0);
            return pos;
        }

        void end(size_t pos)
        {
            const int64_t n = int64_t(buf.size() - pos - sizeof(int64_t));
            std::memcpy(&buf[pos],&n,sizeof(int64_t));
        }

        void finish()
        {
            end(begin("END "));
        }

        void put_varint(uint64_t v)
        {
            while(v>=128u)
            {
                const unsigned char b = (unsigned char)(v & 127u) | 128u;
                put(&b,1);
                v >>= 7;
            }

            const unsigned char b = (unsigned char)v;
            put(&b,1);
        }

        // integer table, column by column: zigzag varint of the difference to the previous row
        template<class Get>
        void put_table(long long nrow, int ncol, Get get)
        {
            put_i64(nrow);
            put_int(ncol);

            for(int c=0; c<ncol; ++c)
            {
                long long prev=0;

                for(long long r=0; r<nrow; ++r)
                {
                    const long long v = get(r,c);
                    const long long d = v - prev;
                    prev = v;

                    put_varint((uint64_t(d) << 1) ^ uint64_t(d >> 63));
                }
            }
        }

        // run-length coding of an int sequence
        template<class Get>
        void put_rle(size_t num, Get get)
        {
            const size_t pos = buf.size();
            put_i64(0);

            long long nrun=0;
            size_t q=0;

            while(q<num)
            {
                const int val = get(q);
                size_t len=1;

                while(q+len<num && get(q+len)==val && len<2147483647u)
                ++len;

                put_int(val);
                put_int(int(len));
                ++nrun;
                q+=len;
            }

            const int64_t n = nrun;
            std::memcpy(&buf[pos],&n,sizeof(int64_t));
        }
    };
}

#endif
