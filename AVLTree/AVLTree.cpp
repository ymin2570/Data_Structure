#include "AVLTree.h"

AVLTree::AVLTree(ofstream * flog)		//Constructor
{
	root = NULL;
	Object = NULL;
	Temp = NULL;
	this->flog = flog;
}

AVLTree::~AVLTree()
{
}

AVLNode * AVLTree::Getroot()		//return root
{
	return root;
}	

void AVLTree::Setroot(AVLNode * node)	//Set root
{
	root = node;
}

bool AVLTree::Insert(CityData * node)
{
	AVLNode *pNew = new AVLNode;				//New node
	pNew->SetCityData(node);							//Save Data
	char * pName = node->Getname();			//New node's name
	int rotation = 0;													//Variable to find which is heavier

	if (root == NULL) {											//if root == NULL
		root = pNew;
		return true;
	}
	AVLNode* a = root;
	AVLNode* pa = NULL;
	AVLNode* p = root;
	AVLNode* pp = NULL;
	AVLNode* rootSub = NULL;

	while (p != NULL) {
		if (p->GetmBF() != 0) {						//if BF of p is not 0
			pa = pp;
			a = p;
		}
		if (strcmp(pName, p->GetCityData()->Getname()) < 0) {			 //if New node's name is smaller than p's name
			pp = p;
			p = p->GetLeft();																					//Move
		}
		else if (strcmp(pName, p->GetCityData()->Getname()) > 0) {			 //if New node's name is bigger than p's name
			pp = p;
			p = p->GetRight();																				//Move
		}
		else return false;																						//If same name
	}
	if (strcmp(pName, pp->GetCityData()->Getname()) < 0)	pp->SetLeft(pNew);									//Place new node left of pp
	else if (strcmp(pName, pp->GetCityData()->Getname()) > 0)		pp->SetRight(pNew);								//Place new node right of pp

	AVLNode *b, *c;
	if (strcmp(pName, a->GetCityData()->Getname()) < 0) {		 //if New node's name is smaller than p's name
		b = p = a->GetLeft();
		rotation = 1;																						//L Rotation
	}
	else {																											 //if New node's name is bigger than p's name
		b = p = a->GetRight();
		rotation = -1;																						//R Rotation
	}

	while (p != pNew) {
		if (strcmp(pName, p->GetCityData()->Getname()) > 0) {		 //if New node's name is bigger than p's name
			p->SetmBF(-1);																					//Set Balance Factor
			p = p->GetRight();
		}
		else {																											 //if New node's name is smaller than p's name
			p->SetmBF(1);																					//Set Balance Factor
			p = p->GetLeft();
		}
	}

	if (a->GetmBF() == 0 || a->GetmBF() + rotation == 0) {		//If Tree is balanced
		a->SetmBF(a->GetmBF() + rotation);
		return true;
	}

	if (rotation == 1) {																					//Left rotation
		if (b->GetmBF() == 1) {																	//LL rotation
			a->SetLeft(b->GetRight());
			b->SetRight(a);
			a->SetmBF(0);
			b->SetmBF(0);
			rootSub = b;
		}
		else {																											//LR rotation
			c = b->GetRight();
			b->SetRight(c->GetLeft());
			a->SetLeft(c->GetRight());
			c->SetLeft(b);
			c->SetRight(a);
			switch (c->GetmBF()) {															//BF
			case 0:
				b->SetmBF(0);
				a->SetmBF(0);
				break;
			case 1:
				a->SetmBF(-1);
				b->SetmBF(0);
				break;
			case -1:
				b->SetmBF(1);
				a->SetmBF(0);
				break;
			}
			c->SetmBF(0);
			rootSub = c;
		}
	}
	else{
		if (b->GetmBF() == -1) {								//RR rotation
			a->SetRight(b->GetLeft());
			b->SetLeft(a); a->SetmBF(0); b->SetmBF(0);
			rootSub = b;
		}
		else {                                                                  //RL rotation
			c = b->GetLeft();
			b->SetLeft(c->GetRight());
			a->SetRight(c->GetLeft());
			c->SetRight(b);
			c->SetLeft(a);
			switch (c->GetmBF()) {                           //BF a, b
			case 0:
				a->SetmBF(0); b->SetmBF(0);
				break;
			case 1:
				b->SetmBF(-1); a->SetmBF(0);
				break;
			case -1:
				a->SetmBF(1); b->SetmBF(0);
				break;
			}
			c->SetmBF(0); 
			rootSub = c;											// c is the new root of the subtree
		}
	}
	if (pa == NULL) 	root = rootSub;
	else if (a == pa->GetLeft()) pa->SetLeft(rootSub);
	else pa->SetRight(rootSub);
	return true;
}

bool AVLTree::Delete(int num)
{
	Search(num);
	if (Object == NULL)	
		return false;

	char * pName = Object->GetCityData()->Getname();			//Delete node's name

	AVLNode* a = root;
	AVLNode* pa = NULL;
	AVLNode* p = root;
	AVLNode* pp = NULL;
	AVLNode* rootSub = NULL;
	AVLNode* ChangeNode;
	AVLNode* PrevChangeNode = NULL;

	//Deletion
	while (p != NULL) {
		if (strcmp(pName, p->GetCityData()->Getname()) < 0) {			 //if Delete node's name is smaller than p's name
			pp = p;
			p = p->GetLeft();																					//Move
		}
		else if (strcmp(pName, p->GetCityData()->Getname()) > 0) {			 //if Delete node's name is bigger than p's name
			pp = p;
			p = p->GetRight();																				//Move
		}
		else
			break;
	}

	if (pp == NULL && p->GetLeft() == NULL && p->GetRight() == NULL)		//Target Node is root node and has no child
	{
		root = NULL;			//Delete
		delete p;
	}
	else if ((p->GetLeft() == NULL) && (p->GetRight() == NULL))			//Target Node is Leaf Node
	{
		if (pp != NULL)				//If Node is not Root Node
		{
			if (pp->GetLeft() == p)
				pp->SetLeft(NULL);								//Disconnect
			else if (pp->GetRight() == p)
				pp->SetRight(NULL);						//Disconnect
		}
		delete p;			//Delete
	}
	else if ((p->GetLeft() != NULL) && (p->GetRight() == NULL))			//Target Node has only left child node
	{
		if (pp != NULL)
		{
			if(pp->GetLeft() == p)
				pp->SetLeft(p->GetLeft());	//Reconnect
			else if(pp->GetRight() == p)
				pp->SetRight(p->GetLeft());	//Reconnect
		}
		else
			root = p->GetLeft();		//Change Root Node
		delete p;										//Delete
	}
	else if ((p->GetLeft() == NULL) && (p->GetRight() != NULL))					//Target Node has only right child node
	{
		if (pp != NULL)
		{
			if (pp->GetLeft() == p)
				pp->SetLeft(p->GetRight());	//Reconnect
			else if (pp->GetRight() == p)
				pp->SetRight(p->GetRight());	//Reconnect
		}
		else
			root = p->GetRight();									//Change Root Node
		delete p;																				//Delete
	}
	else if ((p->GetLeft() != NULL) && (p->GetRight() != NULL))			//Target Node has both left and right child node
	{
		PrevChangeNode = p;
		ChangeNode = p->GetLeft();
		while (ChangeNode->GetRight() != NULL)			//Find the node that will be changed with the Target node
		{
			PrevChangeNode = ChangeNode;									//Set previous of Change node
			ChangeNode = ChangeNode->GetRight();
		}

		if (pp != NULL)
		{
			if (PrevChangeNode->GetLeft() == ChangeNode)
			{
				pp->SetLeft(ChangeNode);								//Reconnect
				PrevChangeNode->SetLeft(NULL);
				ChangeNode->SetRight(p->GetRight());		//Reconnect
				delete p;																		//Delete
			}
			else if (PrevChangeNode->GetRight() == ChangeNode)
			{
				if (ChangeNode->GetLeft() != NULL)
					PrevChangeNode->SetRight(ChangeNode->GetLeft());		//Reconnect
				else
					PrevChangeNode->SetRight(NULL);												//Disconnect

				if (strcmp(ChangeNode->GetCityData()->Getname(), pp->GetCityData()->Getname()) < 0)
					pp->SetLeft(ChangeNode);													//Reconnect
				else
					pp->SetRight(ChangeNode);
				ChangeNode->SetLeft(p->GetLeft());
				ChangeNode->SetRight(p->GetRight());
				delete p;																					//Delete
			}
		}
		else
		{
			if (PrevChangeNode->GetLeft() == ChangeNode)
			{
				root = ChangeNode;								//Reconnect
				PrevChangeNode->SetLeft(NULL);
				ChangeNode->SetRight(p->GetRight());		//Reconnect
				delete p;																		//Delete
			}
			else if (PrevChangeNode->GetRight() == ChangeNode)
			{
				if (ChangeNode->GetLeft() != NULL)
					PrevChangeNode->SetRight(ChangeNode->GetLeft());		//Reconnect
				else
					PrevChangeNode->SetRight(NULL);												//Disconnect

				root = ChangeNode;													//Reconnect
				ChangeNode->SetLeft(p->GetLeft());
				ChangeNode->SetRight(p->GetRight());
				delete p;																					//Delete
			}
		}
	}
	Object = NULL;													//Set Object NULL
	Postorder_Height(root);									//Correct all node's Height
	Postorder_BF(root);									//Correct all node's Balance Factor
	
	//Find a and pa
	Find_A(root);
	a = Object;
	if(Object == NULL)									//a is not founded = balanced
		return true;
	Find_PA(root);
	pa = Temp;

	//Rotate
	AVLNode *b, *c;
	
	if (a->GetmBF() > 1) {																					//Left rotation
		b = a->GetLeft();
		if (b->GetmBF() >= 0) {																	//LL rotation
			a->SetLeft(b->GetRight());
			b->SetRight(a);
			a->SetmBF(0);
			b->SetmBF(0);
			rootSub = b;
		}
		else {																											//LR rotation
			c = b->GetRight();
			b->SetRight(c->GetLeft());
			a->SetLeft(c->GetRight());
			c->SetLeft(b);
			c->SetRight(a);
			switch (c->GetmBF()) {															//BF
			case 0:
				b->SetmBF(0);
				a->SetmBF(0);
				break;
			case 1:
				a->SetmBF(-1);
				b->SetmBF(0);
				break;
			case -1:
				b->SetmBF(1);
				a->SetmBF(0);
				break;
			}
			c->SetmBF(0);
			rootSub = c;
		}
	}
	else if(a->GetmBF() < -1){
		b = a->GetRight();
		if (b->GetmBF() < 0) {								//RR rotation
			a->SetRight(b->GetLeft());
			b->SetLeft(a); a->SetmBF(0); b->SetmBF(0);
			rootSub = b;
		}
		else {                                                                  //RL rotation
			c = b->GetLeft();
			b->SetLeft(c->GetRight());
			a->SetRight(c->GetLeft());
			c->SetRight(b);
			c->SetLeft(a);
			switch (c->GetmBF()) {                           //BF a, b
			case 0:
				a->SetmBF(0); b->SetmBF(0);
				break;
			case 1:
				b->SetmBF(-1); a->SetmBF(0);
				break;
			case -1:
				a->SetmBF(1); b->SetmBF(0);
				break;
			}
			c->SetmBF(0);
			rootSub = c;											// c is the new root of the subtree
		}
	}
	if (pa == NULL) 	root = rootSub;
	else if (a == pa->GetLeft()) pa->SetLeft(rootSub);
	else pa->SetRight(rootSub);
	Object = NULL;											//Set Object NULL
	Postorder_Height(root);										//Correct all node's Height
	Postorder_BF(root);									//Correct all node's Balance Factor
	return true;
}

CityData * AVLTree::Search(int num)
{
	if (num < 1000 || num > 9999)			//Range
		return NULL;

	Find(root, num);										//Find node
	if (Object == NULL)		return NULL;	//Not founded
	else
		return Object->GetCityData();		//Return Data
}

void AVLTree::Find(AVLNode* node, int num)
{
	if (node)
	{
		if (node->GetCityData()->GetLocationId() == num) Object = node;		//Change Object in Preorder
		Find(node->GetLeft(),num);
		Find(node->GetRight(),num);
	}
	return;
}

void AVLTree::Inorder(AVLNode* node)
{
	if (node)
	{
		Inorder(node->GetLeft());
		array_AVL.push_back(node);				//Save the node into vector
		Inorder(node->GetRight());
	}
}

void AVLTree::Postorder_Height(AVLNode* node)
{
	if (node)
	{
		Postorder_Height(node->GetLeft());
		Postorder_Height(node->GetRight());
		node->SetHeight(get_Height(node));				//Change all node's height
	}
}

void AVLTree::Postorder_BF(AVLNode* node)
{
	if (node)
	{
		Postorder_BF(node->GetLeft());
		Postorder_BF(node->GetRight());
		if (node->GetLeft() == NULL && node->GetRight() == NULL)								//Change all node's Balance Factor
			node->SetmBF(0);
		else if (node->GetLeft() != NULL && node->GetRight() == NULL)
			node->SetmBF(node->GetLeft()->GetHeight());
		else if (node->GetLeft() == NULL && node->GetRight() != NULL)
			node->SetmBF(node->GetRight()->GetHeight() * -1);
		else if (node->GetLeft() != NULL && node->GetRight() != NULL)
			node->SetmBF(node->GetLeft()->GetHeight() - node->GetRight()->GetHeight());
	}
}

bool AVLTree::Print()
{
	if (root == NULL)
		return false;

	Inorder(root);				//Set Vector

	while (!array_AVL.empty())		//Print oout and erase vector
	{
		*flog << "( " << array_AVL.front()->GetCityData()->GetLocationId() << ", " << array_AVL.front()->GetCityData()->Getname() << ", " << array_AVL.front()->GetCityData()->Getcountry() << " )" << endl;
		array_AVL.erase(array_AVL.begin());
	}
	return true;
}

int AVLTree::get_Height(AVLNode *root)
{
	if (!root)
		return 0;
	else {
		int Left_Height = get_Height(root->GetLeft());
		int Right_Height = get_Height(root->GetRight());
		return (1 + ((Left_Height > Right_Height) ? Left_Height : Right_Height));	//Calculate Height
	}
}

void AVLTree::Find_A(AVLNode *root)
{
	if (root)
	{
		Find_A(root->GetLeft());
		Find_A(root->GetRight());
		if (root->GetmBF() == 2 || root->GetmBF() == -2)		//Find Unbalanced
			Object = root;
	}
}

void AVLTree::Find_PA(AVLNode *root)
{
	if (root)
	{				
		Find_PA(root->GetLeft());
		if (root->GetLeft() == Object || root->GetRight() == Object)	//Find Parent Node of a
		{
			Temp = root;
		}
		Find_PA(root->GetRight());
	}
}