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
int Point2D::EuclideanDistance(Point2D *A)
{
	return sqrt(pow((*A)[0] - (*this)[0], 2) + pow((*A)[1] - (*this)[1], 2));
}
void Point2D::Display()
{
	/* Display function of Point2D*/

	std::cout << std::endl;
	std::cout << "x=" << x;
	std::cout << "y=" << y;
}