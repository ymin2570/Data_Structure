#include "Graph.h"
#include<utility>
#include<iostream>
#include<fstream>
#include<string.h>

using namespace std;

class Manager
{
public:
	AVLTree * avl;
	Graph * gp;

	char * cmd;
	char * cpy;
	int iter;

public:
	Manager();
	~Manager();

	ofstream flog;
	ifstream fin;

	void run(const char * command);		//Run function
	bool LOAD();												//LOAD Data
	bool INSERT(CityData *);					 //INSERT NODE
	bool PRINT_AVL();									//PRINT AVL Tree
	bool SEARCH_AVL(int num);				//SEARCH Node
	bool DELETE_AVL(int num);				//DELETE Node
	bool BUILD_GP();									//BUILD Graph
	bool PRINT_GP();									//PRINT Graph
	bool BUILD_MST();							//BUILD MST
	bool PRINT_MST();						//PRINT MST
	void EXIT();											//EXIT

	void printErrorCode(int n, const char * cmdname);		//ERROR message
	void printErrorCodeNUM(int n, const char * cmdname, int num); //ERROR message with num
	void printSuccessCode(const char * cmdname);				//SUCCESS message
	void printSuccessCodeINS(const char * cmdname, CityData *Cityname);	//INSERT SUCCESS message
	void printSuccessCodePRI(const char * cmdname);	//PRINT SUCCESS message
	void printSuccessCodeDEL(const char * cmdname, int num);	//DELETE SUCCESS message
	void printSuccessCodeSEA(const char * cmdname, int num, CityData *data);	//SEARCH SUCCESS message
	void printSuccessCodePRI_GP(const char * cmdname);	//PRINT_GP SUCCESS message
	void printSuccessCodePRI_MST(const char * cmdname); //PRINT_MST SUCCESS message
};
