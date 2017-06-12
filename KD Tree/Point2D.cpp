#include "KDTree.h"
#include<iostream>
Point2D::Point2D(int a, int b)
{
	/* Constructing Point2D */

	x = a;
	y = b;
}
const int Point2D::operator[](int dim)const
{
	/* A utility function that returns value at given dimension */

	switch (dim)
	{
	case 0:
		return x;
	case 1:
		return y;
	default:
		return -1;
	}
	
}
void Point2D::Display()
{
	/* Display function of Point2D*/

	std::cout << std::endl;
	std::cout << "x=" << x;
	std::cout << "y=" << y;
}