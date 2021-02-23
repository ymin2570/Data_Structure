#include "Graph.h"
#include <map>
#include<iomanip>
#include<algorithm>

Graph::Graph(ofstream * flog)		//Constructor
{
	this->flog = flog;
	mstMatrix = NULL;
	size = 1;	
	mList = new map<int,int>[size];
}

Graph::~Graph()
{
}

bool Graph::Build(AVLTree * root)
{
	if (mList != NULL)
		mList = NULL;
	root->Inorder(root->Getroot());		//Fill the vector
	size = root->array_AVL.size();				//Set size
	vertex = new CityData *[size];				//Dynamic allocation
	for (int i = 0; i < size; i++)					//Fill vertex vector
	{
		vertex[i] = root->array_AVL.front()->GetCityData();
		root->array_AVL.erase(root->array_AVL.begin());
	}
	mList = new map<int, int>[size];	//Dynamic allocation
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (vertex[i]->GetLocationId() > vertex[j]->GetLocationId())
				mList[i].insert(pair<int,int>(j, vertex[i]->GetLocationId() - vertex[j]->GetLocationId())); //Insert from, to, height
			else
				mList[i].insert(pair<int,int>(j, vertex[j]->GetLocationId() - vertex[i]->GetLocationId()));
		}
	}
	return true;
}

bool Graph::Print_GP()
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			*flog << setw(6) << mList[i][j];		//Print all of mList
		}
		*flog << endl;
	}
	return true;
}

bool Graph::Print_MST()
{
	int b = 0;
	int Total = 0;
	int Start = -1;
	int Last = -1;
	int temp;
	int *Count = new int[size];
	for (int i = 0; i < size; i++)		//Reset count;
	{
		Count[i] = 0;
	}
	for (int j = 0; j < size * (size-1) / 2; j++)		//Fill count array to find the end
	{
		Count[mstFinal[j].to_vertex]++;
		Count[mstFinal[j].from_vertex]++;
		if (j == End-1)
			break;
	}
	for (int k = 0; k < size; k++)
	{
		if (Count[k] == 1)			//Find the End point
		{
			if (Start == -1)		
			{
				Start = k;			//Change
			}
			else
				Last = k;			//Find another End point
		}
	}
	if (Start > Last)			//If start index > Last index
	{
		temp = Start;			//swap
		Start = Last;
		Last = temp;
	}
	while (b!=End)	
	{
		for (int l = 0; l < End; l++)
		{
			if (mstFinal[l].to_vertex == Start || mstFinal[l].from_vertex == Start)
			{
				if (mstFinal[l].to_vertex == Start)
				{//Print out
					*flog << "(" << vertex[mstFinal[l].to_vertex]->Getname() << ", " << vertex[mstFinal[l].from_vertex]->Getname() << "), " << mstFinal[l].wei << endl;
					Total += mstFinal[l].wei;					//Calculate Total
					Start = mstFinal[l].from_vertex;		//Change Start
					b++;										//Increase b
				}
				else
				{//Print out
					*flog << "(" << vertex[mstFinal[l].from_vertex]->Getname() << ", " << vertex[mstFinal[l].to_vertex]->Getname() << "), " << mstFinal[l].wei << endl;
					Total += mstFinal[l].wei;				//Calculate Total
					Start = mstFinal[l].to_vertex;		//Change Start
					b++;									//Increase b
				}
			}
		}
	}
	//Print out Total
	*flog << "Total : " << Total << endl;
	
	return true;
	
}

bool Graph::Kruskal()
{
	if (mstMatrix != NULL)		//If MST is not NULL
		mstMatrix = NULL;			//Reset
	int k = 1;
	int A = 0;
	int temp = 0;
	int Ym = 0;
	mstFinal = new mstNode[size*(size - 1) / 2];			//Dynamic allocation
	for (int i = 0; i < size*(size - 1) / 2; i++)
	{
		mstFinal[i] = mstNode(0, 0, 0);								//Initialize
	}
	make_set();																	//Get mstMatrix
	for (int i = 0; i < size -1; i++)
	{
		for (int j = k; j < size; j++)
		{
			weight.push_back(mstNode(i,j,mList[i][j]));		//Push data into weight vector
		}
		k++;
	}
	sort(weight.begin(), weight.end());								//Sort by weight, Ascending

	while (!weight.empty())
	{
		int index_from = weight.begin()->from_vertex;	//Save from vertex
		int index_to = weight.begin()->to_vertex;//Save to vertex

		if (find(index_from) != find(index_to))		//If mstMatrix[from] != mstMatrix[to]
		{
			for (int l = 0; l < size * (size-1) / 2; l++)
			{
				if(index_to == mstFinal[l].to_vertex)		//If same to vertex is exist
				{
					Ym = 1;				//Ym = 1
				}
				
			}
			if (Ym == 1)		//If Ym == 1
			{
				temp = index_to;				//Swap
				index_to = index_from;
				index_from = temp;
			}
			union_set(index_from, index_to);				//Change mstMatrix
			weight.begin()->from_vertex = index_from;		//Store new data
			weight.begin()->to_vertex = index_to;					//Store new data
			mstFinal[A] = weight.front();									//Add
			weight.erase(weight.begin());									//Erase that edge
			A++;
		}
		else
			weight.erase(weight.begin());				//Erase begin of weight
		Ym = 0;
	}
	End = A;			//Find the End point
	return true;
}

void Graph::make_set()			//Made mstMatrix
{
	mstMatrix = new int[size];
	for (int i = 0; i < size; i++)
	{
		mstMatrix[i] = i;
	}
}

void Graph::union_set(int x, int y)
{
	if (mstMatrix[x] < mstMatrix[y])		
	{
		for (int i = 0; i < size; i++)
		{
			if (mstMatrix[i] == mstMatrix[y])		//Change same mstMatrix at once
				mstMatrix[i] = mstMatrix[x];
		}
	}
	else
	{
		for (int i = 0; i < size; i++)
		{
			if (mstMatrix[i] == mstMatrix[x])
				mstMatrix[i] = mstMatrix[y];
		}
	}
}

int Graph::find(int x)					//return mstMatrix[x]
{
	if (mstMatrix[x] == x)
		return mstMatrix[x];
	else
		return mstMatrix[x] = find(mstMatrix[x]);
}
