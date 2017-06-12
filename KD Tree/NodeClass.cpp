#include "KDTree.h"
#include <algorithm>

struct SortWithX
{
	bool operator()(const Point2D *lhs, const Point2D *rhs) 
	{
		return ((*lhs)[0] < (*rhs)[0]);
	}
};
struct SortWithY
{
	bool operator()(const Point2D *lhs, const Point2D *rhs)
	{
		return ((*lhs)[1] < (*rhs)[1]);
	}
};


/* Definition of class Node */

Node::Node()
{
	left = NULL;
	right = NULL;
	parent = NULL;
}

/* Definition of class LeafNode*/

bool LeafNode::IsLeaf()
{
	return true;
}
std::vector<Point2D*>& LeafNode::GetBucket()
{
	return bucket;
}
void LeafNode::Display()
{
	std::cout << std::endl << "Leaf Node Display" << std::endl;
	for (std::vector<Point2D*>::iterator it = bucket.begin(); it != bucket.end(); it++)
	{
		(*it)->Display();
	}
}
LeafNode::~LeafNode()
{
	for (std::vector<Point2D*>::iterator it = bucket.begin(); it != bucket.end(); ++it)
	{
		delete *it;
	}
}

/* Definition of NonLeafNode*/

NonLeafNode::NonLeafNode(int dim, int val)
{
	cuttingDimention = dim;
	cuttingValue = val;
}
bool NonLeafNode::IsLeaf()
{
	return false;
}
int NonLeafNode::GetCuttingDimension()
{
	return cuttingDimention;
}
int NonLeafNode::GetCuttingValue()
{
	return cuttingValue;
}
void NonLeafNode::SetCuttingValue(int val)
{
	cuttingValue = val;
}
void NonLeafNode::Display()
{
	std::cout << std::endl << "Non Leaf Node Display" << std::endl;
	std::cout << "Cutting dimension= " << cuttingDimention<<std::endl;
	std::cout << "Cuttting value= " << cuttingValue<<std::endl;
}
void NonLeafNode::SplitChild(Point2D *nPoint)
{
	std::vector<Point2D*>& toSplit=left->GetBucket();
	toSplit.push_back(nPoint);
	switch (cuttingDimention)
	{
	case 0:
		std::sort(toSplit.begin(), toSplit.end(), SortWithX());
		break;
	case 1:
		std::sort(toSplit.begin(), toSplit.end(), SortWithY());
		break;
	}

	LeafNode *nRightLeafNode = new LeafNode();

	nRightLeafNode->bucket.assign(toSplit.begin() + toSplit.size() / 2 , toSplit.end());
	toSplit.resize(toSplit.size() / 2);

	//nRightLeafNode->Display();
	
	nRightLeafNode->parent = this;
	right = nRightLeafNode;
}