#include "KDTree.h"
#include<conio.h>
int main()
{
	KDTree *myTree=new KDTree(3, 0);

	Point2D *p1 = new Point2D(1, 3);
	Point2D *p2 = new Point2D(2, 3);
	Point2D *p3 = new Point2D(3, 6);
	Point2D *p4 = new Point2D(4, 6);
	Point2D *p5 = new Point2D(5, 6);
	Point2D *p6 = new Point2D(1, 1);
	Point2D *p7 = new Point2D(1, 2);
	Point2D *p8 = new Point2D(1, 1);

	myTree->Insert(p1);
	myTree->Insert(p2);
	myTree->Insert(p3);
	myTree->Insert(p4);
	myTree->Insert(p5);
	myTree->Insert(p6);
	myTree->Insert(p7);

 	myTree->Display(myTree->GetRoot());

	p1 = myTree->NearestNeighbor(p8);
	std::cout << "\nThe nearest neighbor is\n";
	p1->Display();

	delete myTree;
	_getch();
}