#include "KDTree.h"
#include<iostream>
Point2D::Point2D(int a, int b)
{
	std::cout << "Constructing Point2D"<<std::endl;
	x = a;
	y = b;
}
const int Point2D::operator[](int dim)const
{
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
	std::cout << std::endl;
	std::cout << "x=" << x;
	std::cout << "y=" << y;
}