#include "KDTree.h"
#define DIM 2
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
	else if (root->IsLeaf() && (signed)root->GetBucket().size() < bucketSize) //Checking if the root (leaf node) is not full
	{
		root->GetBucket().push_back(nPoint); 
	}
	else
	{
		/* If root is a non-leaf node */

		Node* child = root; //Used to traverse the tree
		int currentDimension = beginWith; //To keep track of the dimension of split at each level

		while (!child->IsLeaf())
		{
			/* Travels till a leaf node by following Binary Search Tree properties */

			currentDimension = child->GetCuttingDimension();

			if (child->GetCuttingValue() > (*nPoint)[currentDimension])
			{
				child = child->left;
			}
			else
			{
				child = child->right;
			}
		}

		if ((signed)child->GetBucket().size() == bucketSize) 
		{
			/* If buffer is full, node needs to be split */

			NonLeafNode *nNonLeaf; //To hold the newly created non-leaf node
			if (child == root)
			{
				/* Updating the root */

				nNonLeaf = new NonLeafNode(beginWith, 0);
				root = nNonLeaf;
			}
			else
			{
				nNonLeaf = new NonLeafNode((currentDimension + 1) % DIM, 0);
			}
		
			nNonLeaf->parent = child->parent; //Updating the parent of the new non-leaf node

			/* Updating child's parent's left/right children to point to the new non-leaf node */
			if (child->parent!=NULL && child->parent->left == child) 
			{
				child->parent->left = nNonLeaf;
			}
			else if (child->parent!=NULL)
			{
				child->parent->right = nNonLeaf;
			}

			nNonLeaf->left = child; //The old, full leaf node becomes the newly created non-leaf node's left child-which is later split
			child->parent = nNonLeaf;

			nNonLeaf->SplitChild(nPoint); //Split function is called-splits left child of the calling object to left and right children
			nNonLeaf->SetCuttingValue((*(nNonLeaf->left->GetBucket().back()))[nNonLeaf->GetCuttingDimension()]); //The median is set as the cutting value
		}
		else
		{
			/* If the leaf is not full then new point is inserted */

			child->GetBucket().push_back(nPoint); 
		}
	}
}
void KDTree::DeleteTree(Node* del)
{
	/* A resursive method to delete the tree on call of the destructor */

	if (del != NULL)
	{
		DeleteTree(del->left);
		DeleteTree(del->right);
		delete del;
	}
}
void KDTree::Display(Node *disp)
{
	/* A recursive inorder traversal to display the tree */

	if (disp != NULL)
	{
		Display(disp->left);
		disp->Display();
		Display(disp->right);
	}
}
Point2D* KDTree::NearestNeighbor(Point2D *queryPoint)
{
	/* Gives the nearest neighbor of the query point calculted by Euclidean distance */

	Node* traverse = root; //Used to traverse the tree
	int currentDimension = beginWith; //To keep track of the dimension of split at each level

	while (!traverse->IsLeaf())
	{
		/* Travels till a leaf node by following Binary Search Tree properties */

		if (traverse->GetCuttingValue() > (*queryPoint)[currentDimension])
		{
			traverse = traverse->left;
			currentDimension = traverse->GetCuttingDimension();
		}
		else
		{
			traverse = traverse->right;
			currentDimension = traverse->GetCuttingDimension();
		}
	}

	int minDistance = -1;
	std::vector<Point2D*>::iterator result;
	for (std::vector<Point2D*>::iterator it = traverse->GetBucket().begin(); it != traverse->GetBucket().end(); it++)
	{
		int distance = queryPoint->EuclideanDistance(*it);
		if (distance < minDistance || minDistance < 0)
		{
			minDistance = distance;
			result = it;
		}
	}
	return *result;
}
KDTree::~KDTree()
{
	DeleteTree(root);
}