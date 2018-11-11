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

#include"dxf.h"
#include"dive.h"
#include"lexer.h"

void dxf::reader(lexer *p, dive *a)
{
    string s;

	int plinenum=100;
	int vertnum=1000;
	int pline_count=0;
	int vert_count=0;
    int line_count, arc_count, spline_count;
	double ***pline;
	int *plinewall,*pline_vertnum;
	
	a->Darray(pline,plinenum,vertnum,3);
	a->Iarray(plinewall,plinenum);
	a->Iarray(pline_vertnum,plinenum);

    line_count=arc_count=spline_count=0;

    ifstream read("grid.dxf", ios_base::in);
    if(!read)
    {
        cout<<("no 'grid.dxf' found !");
        //exit(0);
    }
// int Wall Type, Entity Type, XYZ

    while(!read.eof())
	{
        read>>s;
        if(s.compare("0")==0)
        {

            read>>s;
            if(s.compare("SECTION")==0)
            {
                read>>s;
                if(s.compare("2")==0)
                {
                     read>>s;
                     if(s.compare("ENTITIES")==0)
                     {
                         while(!read.eof())
                         {
                             read>>s;
                             if(s.compare("0")==0)
                             {
                                 read>>s;
                                 if(s.compare("LWPOLYLINE")==0)
                                 {
                                    ++pline_count;
                                    // Wall Type
                                    while(!read.eof())
                                    {
                                        read>>s;
                                        if(s.compare("8")==0)
                                        {
                                        read>>s;
										
										  if(s.compare("wall")==0)
										  plinewall[pline_count]=21;
										  
										  if(s.compare("inflow")==0)
										  plinewall[pline_count]=1;
										  
										  if(s.compare("outflow")==0)
										  plinewall[pline_count]=2;
										  
										  if(s.compare("symmetry")==0)
										  plinewall[pline_count]=3;
										  
										  if(s.compare("wave")==0)
										  plinewall[pline_count]=6;
										  
										  if(s.compare("beach")==0)
										  plinewall[pline_count]=7;
										  
                                        break;
                                        }
                                    }
									
									  while(!read.eof())
                                    {
                                        read>>s;
                                        if(s.compare("90")==0)
                                        {
                                        read>>pline_vertnum[pline_count];
										
                                        break;
                                        }
                                    }

                                   // X Start
                                    while(!read.eof() && vert_count>pline_vertnum[pline_count])
                                    {
                                        read>>s;
										
										
                                        if(s.compare("10")==0)
                                        {
                                        read>>pline[pline_count][vert_count][0];
                                        ++vert_count;
                                        }
                                    
                                    // Y  Start

                                        if(s.compare("20")==0)
                                        {
                                        read>>pline[pline_count][vert_count][1];
                            
                                        }
                                    

                                    // Bulge
                                    
										  pline[pline_count][vert_count][2]=0.0;
                                        if(s.compare("42")==0)
                                        {
                                        read>>pline[pline_count][vert_count][2];
                                        }
                                    
									  }
								   }
                             }
                         }
                     }
                }
            }
        }
	}
	read.close();


}
