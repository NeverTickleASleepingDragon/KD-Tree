#include "KDTree.h"
#include<conio.h>
#include<chrono>
#include <fstream>
unsigned long TimeInMilliseconds()
{
	return  std::chrono::duration_cast<std::chrono::milliseconds>
		(std::chrono::system_clock::now().time_since_epoch()).count();

}
int main()
{
	KDTree *myTree = new KDTree(100000, 0);
	Point2D* point;
	int x, y;

	
	std::ifstream fin;
	std::ofstream ans;

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

	fin.open("query.txt");
	ans.open("results.txt");

	Point2D *qPoint;
	while (1)
	{
		fin >> x >> y;
		if (fin.eof())
		{
			break;
		}
		qPoint = new Point2D(x, y);

		unsigned long start = TimeInMilliseconds();
		point = myTree->NearestNeighbor(qPoint);
		unsigned long end = TimeInMilliseconds();

		std::cout << "The nearest neighbor is\n";
		point->Display();
		ans << (*point)[0] << "\t" << (*point)[1] << "\t" << (end - start) << "\n";
		std::cout << "	It took " << (end - start) << "  ms\n";

		delete qPoint;
	}
	fin.close();
	ans.close();

	//myTree->Display(myTree->GetRoot());
	delete myTree;
	_getch();
}