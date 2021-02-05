#include "BinarySearchTree.h"

void BinarySearchTree::insert(SoccerPlayerData& data)
{
	TreeNode *CurrNode;
	TreeNode *NewNode = new TreeNode(data);		//New node for input data
	CurrNode = m_root;			//Load the root of Tree into the CurrNode

	while (CurrNode != NULL)		//Input node into the Tree
	{
		if (CurrNode->m_data.m_ability > data.m_ability)	//If input ability is smaller than CurrNode
		{
			if (CurrNode->m_left != NULL) {				//If CurrNode's left child node is not NULL
				CurrNode = CurrNode->m_left;				//CurrNode is CurrNode's left child node
			}
			else {
				CurrNode->m_left = NewNode;			//Else, input New node into the CurrNode's left child node
				break;
			}
		}

		else if (CurrNode->m_data.m_ability < data.m_ability)			//If input ability is bigger than CurrNode
		{
			if (CurrNode->m_right != NULL) {			//If CurrNode's right child node is not NULL
				CurrNode = CurrNode->m_right;			//CurrNode is CurrNode's right child node
			}
			else {
				 CurrNode->m_right = NewNode;		//Else, input New node into the CurrNode's right child node
				break;
			}
		}
	}
}

void BinarySearchTree::deletion(int ability)
{
	TreeNode *CurrNode;
	TreeNode *PrevNode = NULL;
	TreeNode *ChangeNode;
	TreeNode *PrevChangeNode = NULL;
	CurrNode = m_root;

	while (CurrNode != NULL)		//Find the Node that has the same ability
	{
		if (CurrNode->m_data.m_ability > ability)		//If target's ability is smaller than CurrNode
		{
			PrevNode = CurrNode;
			CurrNode = CurrNode->m_left;					//Go to the left child node
		}
		else if (CurrNode->m_data.m_ability < ability)		//Else if target's ability is bigger than CurrNode
		{
			PrevNode = CurrNode;
			CurrNode = CurrNode->m_right;				//Go to the right child node
		}
		else
			break;
	}
	if (PrevNode == NULL && CurrNode->getLeftNode() == NULL && CurrNode->getRightNode() == NULL)		//Target Node is root node and has no child
	{
		m_root = NULL;			//Delete
		delete CurrNode;
	}
	else if ((CurrNode->getLeftNode() == NULL) && (CurrNode->getRightNode() == NULL))			//Target Node is Leaf Node
	{
		if (PrevNode != NULL)				//If Node is Root Node
		{
			if (PrevNode->getLeftNode() == CurrNode)	
				PrevNode->m_left = NULL;								//Disconnect
			else if (PrevNode->getRightNode() == CurrNode)
				PrevNode->m_right = NULL;						//Disconnect
		}
		delete CurrNode;			//Delete
	}
	else if ((CurrNode->getLeftNode() != NULL) && (CurrNode->getRightNode() == NULL))			//Target Node has only left child node
	{
		if(PrevNode != NULL)
			PrevNode->m_left = CurrNode->getLeftNode();	//Reconnect
		else
			m_root = CurrNode->getLeftNode();		//Change Root Node
		delete CurrNode;										//Delete
	}
	else if ((CurrNode->getLeftNode() == NULL) && (CurrNode->getRightNode() != NULL))					//Target Node has only right child node
	{
		if (PrevNode != NULL)
			PrevNode->m_right = CurrNode->getRightNode();				//Reconnect
		else
			m_root = CurrNode->getRightNode();									//Change Root Node
		delete CurrNode;																				//Delete
	}
	else if ((CurrNode->getLeftNode() != NULL) && (CurrNode->getRightNode() != NULL))			//Target Node has both left and right child node
	{
		PrevChangeNode = CurrNode;
		ChangeNode = CurrNode->getLeftNode();
		while (ChangeNode->getRightNode() != NULL)			//Find the node that will be changed with the Target node
		{
			PrevChangeNode = ChangeNode;									//Set previous of Change node
			ChangeNode = ChangeNode->getRightNode();
		}

		if (PrevNode != NULL)
		{
			if (PrevChangeNode->getLeftNode() == ChangeNode)
			{
				PrevNode->m_left = ChangeNode;								//Reconnect
				ChangeNode->m_right = CurrNode->getRightNode();		//Reconnect
				delete CurrNode;																		//Delete
			}
			else if (PrevChangeNode->getRightNode() == ChangeNode)
			{
				if (ChangeNode->getLeftNode() != NULL)
					PrevChangeNode->m_right = ChangeNode->getLeftNode();		//Reconnect
				else
					PrevChangeNode->m_right = NULL;												//Disconnect

				PrevNode->m_left = ChangeNode;													//Reconnect
				ChangeNode->m_left = CurrNode->getLeftNode();
				ChangeNode->m_right = CurrNode->getRightNode();
				delete CurrNode;																					//Delete
			}
		}
		else
		{
			if (PrevChangeNode->getLeftNode() == ChangeNode)
			{
				m_root = ChangeNode;								//Reconnect
				ChangeNode->m_right = CurrNode->getRightNode();		//Reconnect
				delete CurrNode;																		//Delete
			}
			else if (PrevChangeNode->getRightNode() == ChangeNode)
			{
				if (ChangeNode->getLeftNode() != NULL)
					PrevChangeNode->m_right = ChangeNode->getLeftNode();		//Reconnect
				else
					PrevChangeNode->m_right = NULL;												//Disconnect

				ChangeNode = m_root;													//Reconnect
				ChangeNode->m_left = CurrNode->getLeftNode();
				ChangeNode->m_right = CurrNode->getRightNode();
				delete CurrNode;																					//Delete
			}
		}
	}
}

void BinarySearchTree::Clear(TreeNode *tree)			//Clear all of tree if input node is root node
{
	if (tree != NULL)
	{
		Clear(tree->getLeftNode());
		Clear(tree->getRightNode());
		delete tree;																//Delete
	}
}

BinarySearchTree ::~BinarySearchTree()				//Destructor
{
	Clear(m_root);
}