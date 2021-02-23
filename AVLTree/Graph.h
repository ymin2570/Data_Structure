#include "AVLTree.h"
#include <iostream>
#include <fstream>// header file declare
#include <map>
using namespace std;
class Graph
{
public:
	map<int, int> * mList;	// mList[from vetex] = map<to vertex, weigth>
	CityData * * vertex;			// vetex[index] = CityData * 
	int size;					// AVLTree size
	int End;					//End
	int * mstMatrix;			// MST

	ofstream * flog;

public:
	Graph(ofstream * flog);
	~Graph();

	class mstNode			//Class that save edge's information
	{
	public:
		int to_vertex;				//to vertex
		int from_vertex;			//from vertex
		int wei;						//weight

	public:
		mstNode() {}
		mstNode(int x, int y, int we) { to_vertex = x; from_vertex = y; wei = we; }		//Constructor
		bool operator <(mstNode &node) {		//Opertor overloading
			return this->wei < node.wei;
		}
	};

	vector <mstNode> weight;			//All edges
	mstNode *mstFinal;							//Final node
	bool	Build(AVLTree * root);		//Build Graph
	bool 	Print_GP();						//Print Graph
	bool	Print_MST();					//Print MST

	/*for Kruskal union_set*/
	bool	Kruskal();						//Build MST
	void 	make_set();					//Set mstMatrix
	void 	union_set(int x, int y);	//same parent
	int	find(int x);						//return mstMatrix[x]

};


