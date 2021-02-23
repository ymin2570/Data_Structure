#include "AVLNode.h"

AVLNode::AVLNode()		//Constructor
{
	pRight = NULL;
	pLeft = NULL;
	mBF = 0;
	Height = 0;
}

AVLNode::~AVLNode()
{
}

CityData * AVLNode::GetCityData()	//Return CityData
{
	return pCityData;
}

AVLNode * AVLNode::GetLeft()//Return Left Child
{
	return pLeft;
}

AVLNode * AVLNode::GetRight()//Return Right Child
{
	return pRight;
}

int AVLNode::GetmBF()//Return Balance Factor
{
	return mBF;
}

int AVLNode::GetHeight()//Return Height
{
	return Height;;
}

void AVLNode::SetCityData(CityData * node)//Change CityData
{
	pCityData = node;
}

void AVLNode::SetLeft(AVLNode * node)//Change Left child
{
	pLeft = node;
}

void AVLNode::SetRight(AVLNode * node)//Change Right child
{
	pRight = node;
}

void AVLNode::SetmBF(int n)//Change Balance Factor
{
	mBF = n;
}

void AVLNode::SetHeight(int n)//Change Height
{
	Height = n;
}