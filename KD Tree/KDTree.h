#include<vector>
#include<iostream>
class Point2D
{
	int x;
	int y;
public:
	Point2D(){}
	Point2D(int, int);
	const int operator[](int) const;
	void Display();
};
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
class LeafNode : public Node
{
public:
	std::vector<Point2D*> bucket;
	LeafNode(){ std::cout << "Constructing LeafNode"<<std::endl; }
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
class NonLeafNode : public Node
{
public:
	int cuttingDimention;
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
	~KDTree();
};