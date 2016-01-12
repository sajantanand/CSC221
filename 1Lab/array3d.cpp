#include <iostream>
#include <fstream>
#include <cstdlib>
#include <assert.h>
#include "array3d.h"

using namespace std;

array3d::array3d()
{
	m = 0;
	n = 0;
	p = 0;
}

void array3d::init()
{
	cout << p << m << n << endl;
	if (p)
	{
		dataTable = new (nothrow) char** [p];
		assert(dataTable);
		for (int i = 0; i < p; i++)
		{
			dataTable[i] = new (nothrow) char* [m];
			assert(dataTable[i]);
		
			for (int j = 0; j < m; j++)
			{
				dataTable[i][j] = new (nothrow) char[n]; 			//Initialize array in pages-rows-columns
				assert(dataTable[i][j]);
			}
		}
	}
}


array3d::~array3d()
{
	if(p == 0 && m == 0 && n == 0)
	{
		delete dataTable;
		dataTable = 0;
	}
	else
	{
		for (int i = 0; i < p; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if (dataTable[i][j])
				{
					delete [] dataTable[i][j];
					dataTable[i][j] = 0;
				}
			}
			if (dataTable[i])
			{
				delete [] dataTable[i];
				dataTable[i] = 0;
			}
		}
		if (dataTable)
		{
			delete dataTable;
			dataTable = 0;
		}
	}
}

bool array3d::read (char * fname)
{
	bool status = false;
	
	ifstream ifs;
	ifs.open (fname);
	if (ifs.fail())
	{
		cerr << "Unable to open file '" << *fname << "'." << endl;
		return status;
	}
	
	ifs.read( (char *) &n, sizeof(int));			//rows
	ifs.read( (char *) &m, sizeof(int));			//columns	
	ifs.read( (char *) &p, sizeof(int));			//pages

	init();

	if (!ifs)
	{
		cerr << "Unable to read file '" << *fname << "'." << endl;
		return status;
	}

	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < m; k++)
			{
				ifs.read( (char *) &dataTable[i][k][j], sizeof(char));			//Array is in pages-rows-columns notation, while data is pages-columns-rows(column major order)
			}
		}
	}

	return true;
}
	

void array3d::get_sizes (int & m, int & n, int & p)
{
	m = this->m;
	n = this->n;
	p = this->p;
}

char array3d::get_zmap_value (int x, int y)														//x = column y = row
{
	for (int i = p-1; i >= 0; i--)
	{
		if (dataTable[i][x][y])																//i x y
			return i;
	}
	return 0;
}
				
