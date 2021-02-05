#include <iostream>
#include "TransferWindowManager.h"

using namespace std;

int main(int argc, char** argv)
{
	TransferWindowManager transfer_window_manager(argv[1], atoi(argv[2]));		//Read input
	cout << transfer_window_manager << endl;				//Print out the Binary Tree
	TransferWindowManager::SoccerTeam team = transfer_window_manager.getBestTeam();		//Load Best Team's player into the Struct team
	cout << "Best Players" << endl;
	cout << team << endl;				//Print out the Best Team's member
	cout << "-----" << endl;
	cout << "The Transfer window close" << endl;
	cout << transfer_window_manager << endl;			//Print out the deleted Binary Tree
	
    return 0;
}

