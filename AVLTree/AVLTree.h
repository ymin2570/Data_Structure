#include "AVLNode.h"
#include <iostream>
#include <fstream>// header file declare
using namespace std;
class AVLTree
{
public:
	AVLNode * root;	// AVLTree Root
	ofstream * flog;
	AVLNode * Object;	//Object node
	AVLNode * Temp;	//Temporary node
public:
	AVLTree(ofstream * flog);
	~AVLTree();
	vector<AVLNode*> array_AVL;		//Save all node of tree

	AVLNode  *  Getroot();				//Get root
	void	 	Setroot(AVLNode * node);		//Set root
	bool		Insert(CityData * node);			//Insert node into tree
	bool	Delete(int num);						//Delete node
	CityData *	Search(int num);				//Search node
	void Find(AVLNode* node, int num);	//Recursive function to search node
	void Postorder_Height(AVLNode* node);	//Change whole node's height
	void Postorder_BF(AVLNode* node); //Change whole node's Balance Factor
	void Inorder(AVLNode* node); //Save nodes into vector
	bool		Print();	//Print all node info
	int get_Height(AVLNode *root); //Get Height
	void Find_A(AVLNode *root);	//Find A
	void Find_PA(AVLNode *root); //Find Parent of A
};

