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
			/* If buffer is full, node needs to be split */

			NonLeafNode *nNonLeaf; //To hold the newly created non-leaf node
			if (child == root)
			{
				/* Updating the root */

				nNonLeaf = new NonLeafNode((currentDimension) % 2, 0);
				root = nNonLeaf;
			}
			else
			{
				nNonLeaf = new NonLeafNode((currentDimension + 1) % 2, 0);
			}
		
			nNonLeaf->parent = child->parent; //Updating the parent of the new non-leaf node

			nNonLeaf->left = child; //The old, full leaf node becomes the newly created non-leaf node's left child-which is later split
			child->parent = nNonLeaf;

			nNonLeaf->SplitChild(nPoint); //Split function is called-splits left child of the calling object to left and right children
			nNonLeaf->SetCuttingValue((*(nNonLeaf->left->GetBucket().back()))[currentDimension]); //The median is set as the cutting value
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
KDTree::~KDTree()
{
	DeleteTree(root);
}