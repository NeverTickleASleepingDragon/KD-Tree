#include "KDTree.h"

/* Definition of class KDTree*/

KDTree::KDTree(int bSize, int dim)
{
	std::cout << "Constructing Tree" << std::endl;
	beginWith = dim;
	bucketSize = bSize;
}
Node* KDTree::GetRoot()
{
	return root;
}
void KDTree::Insert(Point2D *nPoint)
{
	if (root == NULL)
	{
		/* Creating a new Leaf Node and 
		inserting nPoint into the bucket*/

		LeafNode *nLeaf = new LeafNode();
		nLeaf->bucket.push_back(nPoint);

		/* Initializing root to the newly created Leaf Node */
		root = nLeaf;

	}
	else if (root->IsLeaf() && (signed)root->GetBucket().size() < bucketSize)
	{
		root->GetBucket().push_back(nPoint);
	}
	else
	{
		Node* child = root;
		int currentDimension = beginWith;
		while (!child->IsLeaf())
		{
			if (child->GetCuttingValue() > (*nPoint)[currentDimension])
			{
				child = child->left;
				currentDimension = child->GetCuttingDimension();
			}
			else
			{
				child = child->right;
				currentDimension = child->GetCuttingDimension();
			}
		}

		if ((signed)child->GetBucket().size() == bucketSize)
		{
			NonLeafNode *nNonLeaf;
			if (child == root)
			{
				nNonLeaf = new NonLeafNode((currentDimension) % 2, 0);
				root = nNonLeaf;
			}
			else
			{
				nNonLeaf = new NonLeafNode((currentDimension + 1) % 2, 0);
			}
		
			nNonLeaf->parent = child->parent;

			nNonLeaf->left = child;
			child->parent = nNonLeaf;

			nNonLeaf->SplitChild(nPoint);
			nNonLeaf->SetCuttingValue((*(nNonLeaf->left->GetBucket().back()))[currentDimension]);

		}
		else
		{
			child->GetBucket().push_back(nPoint);
		}
	}
}
void KDTree::DeleteTree(Node* del)
{
	if (del != NULL)
	{
		DeleteTree(del->left);
		DeleteTree(del->right);
		delete del;
	}
}
void KDTree::Display(Node *disp)
{
	if (disp != NULL)
	{
		Display(disp->left);
		disp->Display();
		Display(disp->right);
	}
}
KDTree::~KDTree()
{
	DeleteTree(root);
}