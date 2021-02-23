#include "Manager.h"
#include <stdlib.h>
#include <fstream>
using namespace std;

Manager::Manager()												//Constructor
{
	flog.open("log.txt", ios::app);
	flog.setf(ios::fixed);

	avl = new AVLTree(&flog);
	gp = new Graph(&flog);
	iter = 0;
	cmd = NULL;
}

Manager::~Manager()
{
	flog.close();
}

void Manager::run(const char * command)
{
	fin.open(command);			//Open file

	cmd = new char[40];		//load


	while (!fin.eof())
	{
		iter = iter + 1;
		fin.getline(cmd, 40);

		char * one = strtok(cmd, " ");

		if (!strcmp(one, "LOAD")) {
			//call function()
			if (avl->Getroot() != NULL)	printErrorCode(100, "LOAD");		//ERROR
			else if (LOAD()) printSuccessCode("LOAD");		//SUCCESS
			else printErrorCode(100, "LOAD");		//ERROR
		}

		else if (!strcmp(one, "INSERT")) {
			//call function()
			CityData* New = new CityData;										//Set Citydata
			cpy = strtok(NULL, " ");		//Id
			New->SetLocationId(atoi(cpy));
			cpy = strtok(NULL, " ");	//City
			New->Setname(cpy);
			cpy = strtok(NULL, " ");		//Country
			New->Setcountry(cpy);

			if (avl->Getroot() == NULL) printErrorCode(200, "INSERT");		//ERROR
			else if (INSERT(New)) printSuccessCodeINS("INSERT", New);		//SUCCESS
			else printErrorCode(200, "INSERT");		//ERROR
		}

		else if (!strcmp(one, "PRINT_AVL")) {
			//call function()
			if (avl->Getroot() == NULL) printErrorCode(300, "PRINT_AVL");		//ERROR
			else printSuccessCodePRI("PRINT_AVL");		//SUCCESS
		}

		else if (!strcmp(one, "SEARCH_AVL")) {
			//call function()
			char *Id_SE = strtok(NULL, " ");		//Id
			int Id = atoi(Id_SE);

			if (Id_SE == "") printErrorCodeNUM(500, "SEARCH_AVL", Id);		//ERROR
			else if (SEARCH_AVL(Id)) {
				CityData *data = avl->Search(Id);
				printSuccessCodeSEA("SEARCH_AVL", Id,data);		//SUCCESS
			}
			else printErrorCodeNUM(500, "SEARCH_AVL", Id);		//ERROR

		}

		else if (!strcmp(one, "DELETE_AVL")) {
			//call function()
			char *Id_DE = strtok(NULL, " ");			//Id
			int Id = atoi(Id_DE);

			if (DELETE_AVL(Id)) 	printSuccessCodeDEL("DELETE_AVL", Id);		//SUCCESS
			else		printErrorCodeNUM(400, "DELETE_AVL", Id);		//ERROR
		}

		else if (!strcmp(one, "BUILD_GP")) {
			//call function()
			if (avl->Getroot() == NULL)		printErrorCode(600, "BUILD_GP");		//ERROR
			else if(BUILD_GP())		printSuccessCode("BUILD_GP");		//SUCCESS
			else  		printErrorCode(600, "BUILD_GP");		//ERROR
		}

		else if (!strcmp(one, "PRINT_GP")) {
			//call function()
			if (gp->mList->empty()) printErrorCode(700, "PRINT_GP");		//ERROR
			else printSuccessCodePRI_GP("PRINT_GP");		//SUCCESS
		}

		else if (!strcmp(one, "BUILD_MST")) {
			//call function()
			if (gp->mList->empty()) printErrorCode(800, "BUILD_MST");		//ERROR
			else if (BUILD_MST())	printSuccessCode("BUILD_MST");		//SUCCESS
			else	  printErrorCode(800, "BUILD_MST");		//ERROR
		}

		else if (!strcmp(one, "PRINT_MST")) {
			//call function()
			if (gp->mstMatrix == NULL)		printErrorCode(900, "PRINT_MST");		//ERROR
			else  printSuccessCodePRI_MST("PRINT_MST");		//SUCCESS
		}		
		else if (!strcmp(one, "EXIT")) {
			//call function()
			printSuccessCode("EXIT");		//SUCCESS
			EXIT();	
		}
		else {
			printErrorCode(0,"Unknown");		//ERROR
		}
	}
	fin.close();			//close
	return;
}

bool Manager::LOAD()
{
	ifstream City;
	char *buf;
	char *pName;
	char *pCountry;
	int Id;

	City.open("city_list.txt");		//Open file
	if (!City.is_open())			//if file is not opened
		return false;

	while (!City.eof())
	{
		buf = new char[100];			//Get string
		City.getline(buf, 100);
		char *tok1 = strtok(buf, "\t");		//Id
		Id = atoi(tok1);
		tok1 = strtok(NULL, "\t");			//City
		pName = tok1;
		tok1 = strtok(NULL, "\t");		//Country
		pCountry = tok1;

		CityData *Data = new CityData;		//Set Citydata
		Data->SetLocationId(Id);
		Data->Setname(pName);
		Data->Setcountry(pCountry);

		if (avl->Insert(Data) == false) {		//failed
			City.close();
			return false;
		}
	}
	City.close();				//close
	return true;
}

bool Manager::INSERT(CityData *Newdata)
{
	if (avl->Insert(Newdata))			//Insert success
		return true;
	else
		return false;
}

bool Manager::PRINT_AVL()
{
	if (avl->Print())			//Print success
		return true;
	else
		return false;
}

bool Manager::SEARCH_AVL(int num)
{
	if (avl->Search(num) != NULL)			//Search success
		return true;
	else
		return false;
}

bool Manager::DELETE_AVL(int num)
{
	if (avl->Delete(num))			//DELETE success
		return true;
	else
		return false;
}

bool Manager::BUILD_GP()
{
	if (gp->Build(avl))			//BUILD_GP success
		return true;
	else
		return false;
}

bool Manager::PRINT_GP()
{
	if (gp->Print_GP())			//PRINT_GP success
		return true;
	else
		return false;
}

bool Manager::BUILD_MST()
{
	if (gp->Kruskal())			//BUILD_MST success
		return true;
	else
		return false;
}

bool Manager::PRINT_MST()
{
	if (gp->Print_MST())			//PRINT_MST success
		return true;
	else
		return false;
}

void Manager::EXIT()
{
	exit(1);
}

void Manager::printErrorCode(int n, const char * cmdname) {//ERROR CODE PRINNT FUNCTION
	flog << "==> command " << iter << ") " << cmdname << endl;
	flog << "Error code : " << n << endl;
}

void Manager::printErrorCodeNUM(int n, const char * cmdname, int num) {//ERROR CODE PRINT FUNCTION
	flog << "==> command " << iter << ") " << cmdname << " " << num << endl;
	flog << "Error code : " << n << endl;
}

void Manager::printSuccessCode(const char * cmdname) {//SUCCESS CODE PRINT FUNCTION
	flog << "==> command " << iter << ") " << cmdname << endl;
	flog << "Success" << endl;
}

void Manager::printSuccessCodeINS(const char * cmdname, CityData *Cityname) {//SUCCESS CODE INSERT FUNCTION
	flog << "==> command " << iter << ") " << cmdname << endl;
	flog << "(" << Cityname->GetLocationId() << ", " << Cityname->Getname() << ", " << Cityname->Getcountry() << ")" << endl;
}

void Manager::printSuccessCodePRI(const char * cmdname) {//SUCCESS CODE PRINT FUNCTION
	flog << "==> command " << iter << ") " << cmdname << endl;
	PRINT_AVL();
}

void Manager::printSuccessCodeSEA(const char * cmdname, int num, CityData *data) {//SUCCESS CODE SEARCH FUNCTION AT SEARCH_AVL
	flog << "==> command " << iter << ") " << cmdname << " " << num << endl;
	flog << "(" << data->GetLocationId() << ", " << data->Getname() << ", " << data->Getcountry() << ")" << endl;
}

void Manager::printSuccessCodeDEL(const char * cmdname, int num) {//SUCCESS CODE DELETE FUNCTION
	flog << "==> command " << iter << ") " << cmdname << " " << num << endl;
	flog << "Success" << endl;
}

void Manager::printSuccessCodePRI_GP(const char * cmdname) {//SUCCESS CODE PRINT_GP FUNCTION
	flog << "==> command " << iter << ") " << cmdname << endl;
	PRINT_GP();
}

void Manager::printSuccessCodePRI_MST(const char * cmdname) {//SUCCESS CODE PRINT_MST FUNCTION
	flog << "==> command " << iter << ") " << cmdname << endl;
	PRINT_MST();
}