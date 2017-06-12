#include "KDTree.h"
#include <algorithm>

struct SortWithX
{
	/* To overload the '<' operator as vector of pointers is used 
		Sorts according to X dimension */

	bool operator()(const Point2D *lhs, const Point2D *rhs) 
	{
		return ((*lhs)[0] < (*rhs)[0]);
	}
};
struct SortWithY
{
	/* To overload the '<' operator as vector of pointers is used
	Sorts according to Y dimension */

	bool operator()(const Point2D *lhs, const Point2D *rhs)
	{
		return ((*lhs)[1] < (*rhs)[1]);
	}
};

//////////////////////////////
/* Definition of class Node */
//////////////////////////////

Node::Node()
{
	/* Constructing Node */

	left = NULL;
	right = NULL;
	parent = NULL;
}

///////////////////////////////////////////////////////////////////
/* Definition of class LeafNode - publically inherited from Node */
///////////////////////////////////////////////////////////////////

bool LeafNode::IsLeaf()
{
	/* A utility function to check if the node is a leaf node */

	return true;
}
std::vector<Point2D*>& LeafNode::GetBucket()
{
	/* Utility function to return address of bucket/buffer */

	return bucket;
}
void LeafNode::Display()
{
	/* Leaf node display function-iteraters through the vector and calls the display function for each point */

	std::cout << std::endl << "Leaf Node Display";
	for (std::vector<Point2D*>::iterator it = bucket.begin(); it != bucket.end(); it++)
	{
		(*it)->Display();
	}
}
LeafNode::~LeafNode()
{
	/* A method that cleans memory due to vector of pointers */

	for (std::vector<Point2D*>::iterator it = bucket.begin(); it != bucket.end(); ++it)
	{
		delete *it;
	}
}

////////////////////////////////////////////////////////////////
/* Definition of NonLeafNode - publically inherited from Node */
////////////////////////////////////////////////////////////////

NonLeafNode::NonLeafNode(int dim, int val)
{
	/* Constructing NonLeafNode */

	cuttingDimension = dim;
	cuttingValue = val;
}
bool NonLeafNode::IsLeaf()
{
	/* A utility function to check if the node is a leaf node */

	return false;
}
int NonLeafNode::GetCuttingDimension()
{
	/* A utility function that returns cutting dimension */

	return cuttingDimension;
}
int NonLeafNode::GetCuttingValue()
{
	/* A utility function that returns cutting value */

	return cuttingValue;
}
void NonLeafNode::SetCuttingValue(int val)
{
	/* A mutator function that sets cutting value */
	cuttingValue = val;
}
void NonLeafNode::Display()
{
	/* Non leaf node display function - displays cutting dimension and value */

	std::cout << "\n\nNon Leaf Node Display" << std::endl;
	std::cout << "Cutting dimension= " << cuttingDimension<<std::endl;
	std::cout << "Cuttting value= " << cuttingValue<<std::endl;
}
void NonLeafNode::SplitChild(Point2D *nPoint)
{
	/* Splits the left child of calling object and creates a right child */

	std::vector<Point2D*>& toSplit=left->GetBucket(); //points to left child of calling object
	toSplit.push_back(nPoint); //Inserts the point to be added to the tree
	switch (cuttingDimension)
	{
		/* Sorts the vector according to the cutting dimension */

	case 0:
		std::sort(toSplit.begin(), toSplit.end(), SortWithX());
		break;
	case 1:
		std::sort(toSplit.begin(), toSplit.end(), SortWithY());
		break;
	}

	LeafNode *nRightLeafNode = new LeafNode(); // new leaf node that contains the excess elements of the buffer

	nRightLeafNode->bucket.assign(toSplit.begin() + (toSplit.size() + 1) / 2 , toSplit.end()); //splits left child buffer and assigns it to the newly created leaf node
	toSplit.resize((toSplit.size() + 1)/ 2); //resizes left child
	cuttingValue = (*toSplit.back())[cuttingDimension]; //The median is set as the cutting value

	nRightLeafNode->parent = this; 
	right = nRightLeafNode; //newly created leaf node becomes right child
}