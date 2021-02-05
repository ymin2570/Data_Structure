#pragma once

#include "BinarySearchTree.h"

#include <iostream>
#include <string>

class TransferWindowManager
{
private:
	int m_budget;		//inputted budget

	BinarySearchTree fwBST;			//four position's Binary Search Tree
	BinarySearchTree mfBST;
	BinarySearchTree dfBST;
	BinarySearchTree gkBST;

public:

	struct SoccerTeam				//Struct of Team
	{
		SoccerPlayerData fw;
		SoccerPlayerData mf;
		SoccerPlayerData df;
		SoccerPlayerData gk;

		int sum_transfer_fee;
		int sum_ability;

		SoccerTeam();
		SoccerTeam(SoccerPlayerData fw, SoccerPlayerData mf, SoccerPlayerData df, SoccerPlayerData gk);		//Constructor
		friend std::ostream& operator<<(std::ostream& os, const SoccerTeam& team);		//Operator overloading
	};

	TransferWindowManager(std::string file_dir, int budget);		//Read the file and budget
	

	friend std::ostream& operator<<(std::ostream& os, const TransferWindowManager& manager);


	SoccerTeam getBestTeam();		//Make the Best Team
};

