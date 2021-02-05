#pragma once

#include "SoccerPlayerData.h"
#include <iostream>

class TreeNode
{
	friend class BinarySearchTree;
	friend class TransferWindowManager;
private:
	SoccerPlayerData m_data;	//data of player
	TreeNode* m_left;				//left child node
	TreeNode* m_right;			//right child node
public:
	TreeNode() :m_left(NULL), m_right(NULL) {}		//Constructor with no data input
	~TreeNode() { }			//Destructor
	TreeNode(SoccerPlayerData & data, TreeNode* left = NULL, TreeNode* right = NULL)		//Constructor with  data inputted
	{
		this->m_data = data;
		this->m_left = left;
		this->m_right = right;
	}
	
	TreeNode* getLeftNode() const { return m_left; }			//return left child node
	TreeNode* getRightNode() const { return m_right; }		//return right child node

	friend std::ostream& operator<<(std::ostream& os, const TreeNode* node)
	{
		if (node != NULL)
			os << node->m_data;		//Print out data
		return os;
	}
};
