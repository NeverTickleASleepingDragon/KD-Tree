#include<vector>
#include<iostream>

////////////////////////////////////////////////////////////////////////////////////////
/* Point2D is a class of 2 dimensional points that can used to represent spatial data */
////////////////////////////////////////////////////////////////////////////////////////

class Point2D
{
	int x;
	int y;
public:
	Point2D(){}
	Point2D(int, int);
	const int operator[](int) const;
	int EuclideanDistance(Point2D*);
	void Display();
};

//////////////////////////////////////////////////////
/*	 Node is a class represents a node of the KD Tree.
	It is of two types - leaf and non-leaf nodes	*/
//////////////////////////////////////////////////////

class Node
{
	
public:
	Node *left;
	Node *right;
	Node *parent;

	Node();
	virtual bool IsLeaf() = 0;
	virtual void Display() = 0;
	virtual std::vector<Point2D*>& GetBucket() = 0;
	virtual int GetCuttingValue()=0;
	virtual int GetCuttingDimension()=0;
	virtual void SetCuttingValue(int) = 0;
};

////////////////////////////////////////////////////
/* LeafNode represents a leaf node of the KD Tree */
////////////////////////////////////////////////////

class LeafNode : public Node
{
public:
	std::vector<Point2D*> bucket;
	LeafNode(){ /* Constructing LeafNode */ }
	bool IsLeaf();
	std::vector<Point2D*>& GetBucket();
	void Display();
	~LeafNode();
	int GetCuttingDimension()
	{
		return -1;
	}
	int GetCuttingValue()
	{
		return -1;
	}
	void SetCuttingValue(int dummy){}
};

////////////////////////////////////////////////////////////
/* NonLeafNode represents an internal node in the KD Tree */
////////////////////////////////////////////////////////////

class NonLeafNode : public Node
{
public:
	int cuttingDimension;
	int cuttingValue;

	NonLeafNode(){}
	NonLeafNode(int, int);
	bool IsLeaf();
	int GetCuttingDimension();
	int GetCuttingValue();
	void SetCuttingValue(int);
	void SplitChild(Point2D*);
	void Display();
	std::vector<Point2D*>& GetBucket()
	{
		std::vector<Point2D*> p;
		return p;
	}
};

///////////////////////////////////////////////
/* The class that represents the tree itself */
///////////////////////////////////////////////

class KDTree
{
	Node *root;
	int bucketSize;
	int beginWith;

public:
	KDTree(){}
	KDTree(int, int);
	void Insert(Point2D*);
	void Display(Node*);
	Node* GetRoot();
	void DeleteTree(Node*);
	Point2D* NearestNeighbor(Point2D*);
	~KDTree();
};