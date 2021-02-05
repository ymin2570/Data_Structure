#pragma once

#include "TreeNode.h"
#include <iostream>

static void Inorder(TreeNode* tree)			//Print out all of the Binary Tree using Inorder method
{
	if (tree != NULL)
	{
		Inorder(tree->getLeftNode());		//Go to the left node
		std::cout << tree << std::endl;		//Print out the node's data
		Inorder(tree->getRightNode());		//Go to the right node
	}
}

class BinarySearchTree
{
	friend class TransferWindowManager;
private:
	TreeNode * m_root;								//Root of Tree

public:
	BinarySearchTree() { m_root = NULL; }		//Constructor
	~BinarySearchTree();										//Destructor

	void insert(SoccerPlayerData& data);				//Insert node 
	void deletion(int ability); // ability = key
	TreeNode * getRoot() const { return m_root; }		//Return the root of the tree
	void Clear(TreeNode *tree);									//Clear the TreeNode 

	friend std::ostream& operator<<(std::ostream& os, const BinarySearchTree& tree) {

	// fill in your code to print in-order traversal of a binary search tree
		Inorder(tree.getRoot());		//Print out using Inorder method
		return os;
	}
};

