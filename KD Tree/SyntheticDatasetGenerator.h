#include<fstream>
//#include<iostream>
#include<ctime>
#include<cstdlib>

///////////////////////////////////////////////////////
/* This file creates synthetic spatial data.
	It considers a range of 0-100 for all dimensions */
///////////////////////////////////////////////////////

void RamdomData(int dimension, int size)
{
	srand((unsigned)time(NULL));

	std::ofstream fout;
	fout.open("data.txt");

	for (int i = 1; i <= size; i++)
	{
		for (int dim = 1; dim <= dimension; dim++)
		{
			fout << rand() % 101 << " ";
		}
		fout << "\n";
	}

	fout.close();
}