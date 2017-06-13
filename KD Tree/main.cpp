#include "KDTree.h"
#include "SyntheticDatasetGenerator.h"
#include<conio.h>
#include <fstream>

int main()
{
	//RandomData(2, 10000);
	KDTree *myTree = new KDTree(4, 0);
	Point2D* point;
	int x, y;

	std::ifstream fin;
	fin.open("data.txt");

	while (1)
	{
		fin >> x >> y;
		if (fin.eof())
		{
			break;
		}
		point = new Point2D(x, y);
		myTree->Insert(point);
	}
	fin.close();

	myTree->Display(myTree->GetRoot());

	Point2D *qPoint = new Point2D(1, 1);
	point = myTree->NearestNeighbor(qPoint);
	std::cout << "\nThe nearest neighbor is\n";
	point->Display();

	delete myTree;
	_getch();
}