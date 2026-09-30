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

#ifndef READ_POINTS_H_
#define READ_POINTS_H_

#include<cctype>
#include<cstdlib>
#include<fstream>
#include<iterator>
#include<string>
#include<vector>

// Read "x y z" records (optionally preceded by one character, letter=1)
// until the first incomplete record. The file is read once and parsed in
// memory; strtod gives the same values as operator>>.
// Returns false if the file cannot be opened.
inline bool read_points(const char *filename, int letter, std::vector<double> &x, std::vector<double> &y, std::vector<double> &z)
{
    x.clear();
    y.clear();
    z.clear();

    std::ifstream file(filename, std::ios_base::in | std::ios_base::binary);

    if(!file)
    return false;

    const std::string text((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    x.reserve(text.size()/24);
    y.reserve(text.size()/24);
    z.reserve(text.size()/24);

    const char *c = text.c_str();
    char *end;

    while(true)
    {
        if(letter==1)
        {
            while(std::isspace(static_cast<unsigned char>(*c)))
            ++c;

            if(*c=='\0')
            break;

            ++c;
        }

        double v[3];
        int k;
        for(k=0;k<3;++k)
        {
            v[k] = std::strtod(c,&end);

            if(end==c)
            break;

            c = end;
        }

        if(k<3)
        break;

        x.push_back(v[0]);
        y.push_back(v[1]);
        z.push_back(v[2]);
    }

    return true;
}

#endif
