#include "KDTree.h"
#include<conio.h>
int main()
{
	KDTree myTree(3, 0);

	Point2D *p1 = new Point2D(2, 3);
	Point2D *p2 = new Point2D(4, 3);
	Point2D *p3 = new Point2D(2, 6);
	Point2D *p4 = new Point2D(1, 6);
	Point2D *p5 = new Point2D(5, 6);
	myTree.Insert(p1);
	myTree.Insert(p2);
	myTree.Insert(p3);
	myTree.Insert(p4);
	myTree.Insert(p5);
	myTree.Display(myTree.GetRoot());
	_getch();
}