/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2021 Hans Bihs

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

#include"lexer.h"

void lexer::read_data()
{
	int countD10=0;
	int count=0;
	double val1,val2,val3;
// read geodat
	if(D10>0)
	{
        double val;
        char cval;
        ifstream dataset("gmdataset.dat", ios_base::in);

        while(!dataset.eof())
        {
			
        if(D19==0)
        dataset>>val>>val>>val;

        if(D19==1)
        dataset>>cval>>val>>val>>val;
		
		if(count%D13==0)
        ++countD10;
		
		++count;
        }
        D10=countD10;
        cout<<"DATA INTERPOLATION  "<<D10<<endl;
        dataset.close();

        D10_x = new double[countD10];
        D10_y = new double[countD10];
        D10_dataset = new double[countD10];


        dataset.open("gmdataset.dat", ios_base::in);
		
		count=0;
        countD10=0;
        while(!dataset.eof())
        {
			if(D19==0)
			dataset>>val1>>val2>>val3;

			if(D19==1)
			dataset>>cval>>val1>>val2>>val3;

			if(count%D13==0)
			{
			D10_x[countD10]=val1;
			D10_y[countD10]=val2;
			D10_dataset[countD10]=val3;

			++countD10;
			}
			
		++count;
        }

        dataset.close();

        
	}
}