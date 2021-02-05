#include "TransferWindowManager.h"
#include <fstream>
#include <string>
#include <vector>

std::vector<TreeNode*>fwNodes;		//Vector to store the data
std::vector<TreeNode*>mfNodes;
std::vector<TreeNode*>dfNodes;
std::vector<TreeNode*>gkNodes;

void Pushfw(TreeNode* tree) {			//Save Binary Tree's data into the fw vector using Inorder method
	if (tree != NULL)
	{
		Pushfw(tree->getLeftNode());
		fwNodes.push_back(tree);
		Pushfw(tree->getRightNode());
	}
}
void Pushmf(TreeNode* tree) {			//Save Binary Tree's data into the mf vector using Inorder method
	if (tree != NULL)
	{
		Pushmf(tree->getLeftNode());
		mfNodes.push_back(tree);
		Pushmf(tree->getRightNode());
	}
}
void Pushdf(TreeNode* tree) {			//Save Binary Tree's data into the df vector using Inorder method
	if (tree != NULL)
	{
		Pushdf(tree->getLeftNode());
		dfNodes.push_back(tree);
		Pushdf(tree->getRightNode());
	}
}
void Pushgk(TreeNode* tree) {			//Save Binary Tree's data into the gk vector using Inorder method
	if (tree != NULL)
	{
		Pushgk(tree->getLeftNode());
		gkNodes.push_back(tree);
		Pushgk(tree->getRightNode());
	}
}
TransferWindowManager::SoccerTeam::SoccerTeam()
{
	//You don't need to edit this function.
}

TransferWindowManager::SoccerTeam::SoccerTeam(SoccerPlayerData fw, SoccerPlayerData mf, SoccerPlayerData df, SoccerPlayerData gk)		//Struct
{
	this->fw = fw;
	this->mf = mf;
	this->df = df;
	this->gk = gk;

	this->sum_transfer_fee = fw.m_transfer_fee + mf.m_transfer_fee + df.m_transfer_fee + gk.m_transfer_fee;
	this->sum_ability = fw.m_ability + mf.m_ability + df.m_ability + gk.m_ability;
}

std::ostream& operator<<(std::ostream& os, const TransferWindowManager::SoccerTeam& team)
{
	os << team.fw << std::endl;			//Print out the data of Soccer Team
	os << team.mf << std::endl;
	os << team.df << std::endl;
	os << team.gk << std::endl;

	os << "sum_transfer_fee " << team.sum_transfer_fee << std::endl;
	os << "sum_ability " << team.sum_ability << std::endl;

	return os;
}


TransferWindowManager::TransferWindowManager(std::string file_dir, int budget)		//Read input, file and budget
{
	m_budget = budget;
	if (budget < 1664)
		exit(0);
	std::ifstream in(file_dir);
	std::string line;
	std::string Name;
	std::string Position;
	std::string Name_characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ -";			//String that consists of characters to save the player's name and position
	std::string Number = "0123456789";						//String that consists of numbers to save the player's price and status
	std::string temp;			//temp variable to change string into int type
	int price;
	int status;

	while (std::getline(in, line))
	{
	//Fill in the code to initialize 4 Binary Search Trees(fw, mf, df, gk)
		std::string::iterator i = line.begin();		//iterator to check string one by one
		for (; i != line.end(); i++)
		{
			if (Name_characters.find(*i) != std::string::npos) {		//Save player's name
				Name += *i;
				continue;
			}
			i += 2;
			break;
		}
		for (; i != line.end(); i++)
		{
			if (Name_characters.find(*i) != std::string::npos) {		//Save player's position
				Position += *i;
				continue;
			}
			i += 2;
			break;
		}
		for (; i != line.end(); i++)
		{
			if (Number.find(*i) != std::string::npos) {			//Save player's price
				temp += *i;
				continue;
			}
			price = atoi(temp.c_str());		//Save price in int type
			i += 2;
			temp = "";
			break;
		}
		for (; i != line.end(); i++)
		{
			if (Number.find(*i) != std::string::npos) {		//Save player's status
				temp += *i;
				continue;
			}
		}
		status = atoi(temp.c_str());

		SoccerPlayerData Player = SoccerPlayerData(Name, Position, price, status);	//Made 1 player

		if (Position == "Forward") {		//Check the position
			if (fwBST.m_root == NULL) {		//If no Node exist
				TreeNode *Node = new TreeNode(Player);		
				fwBST.m_root = Node;				//New node is root node
			}
			else
				fwBST.insert(Player);			//Insert player's node into BinaryTree
		}
		else if (Position == "Midfielder") {	//Check the position
			if (mfBST.m_root == NULL) {	//If no Node exist
				TreeNode *Node = new TreeNode(Player);
				mfBST.m_root = Node;			//New node is root node
			}
			else
				mfBST.insert(Player);			//Insert player's node into BinaryTree
		}
		else if (Position == "Defender") {	//Check the position
			if (dfBST.m_root == NULL) {	//If no Node exist
				TreeNode *Node = new TreeNode(Player);
				dfBST.m_root = Node;			//New node is root node
			}
			else
				dfBST.insert(Player);			//Insert player's node into BinaryTree
		}
		else if (Position == "Goalkeeper") {	//Check the position
			if (gkBST.m_root == NULL) {	//If no Node exist
				TreeNode *Node = new TreeNode(Player);
				gkBST.m_root = Node;			//New node is root node
			}
			else
				gkBST.insert(Player);			//Insert player's node into BinaryTree
		}

		Name = "";
		Position = "";
		temp = "";
		line = "";
	}
}

std::ostream& operator<<(std::ostream& os, const TransferWindowManager& manager)
{
	os << "********Forward List********" << std::endl;			//Print out all of Forward BinarySearchTree's data
	os << manager.fwBST;
	os << "****************************" << std::endl;

	os << "********Midfilder List********" << std::endl;		//Print out all of Midfilder BinarySearchTree's data
	os << manager.mfBST;
	os << "*****************************" << std::endl;

	os << "********Defender List********" << std::endl;		//Print out all of Defender BinarySearchTree's data
	os << manager.dfBST;
	os << "*****************************" << std::endl;

	os << "********Goalkeeper List********" << std::endl;		//Print out all of Goalkeeper BinarySearchTree's data
	os << manager.gkBST;
	os << "*******************************" << std::endl;

	return os;
}


TransferWindowManager::SoccerTeam TransferWindowManager::getBestTeam()
{
	SoccerTeam best_team;
	best_team.sum_ability = 0;								//initialize
	best_team.sum_transfer_fee = 10000;

	TreeNode* CurrNode;
	CurrNode = fwBST.m_root;
	Pushfw(CurrNode);					//Fill the fw vector
	CurrNode = mfBST.m_root;
	Pushmf(CurrNode);					//Fill the mf vector
	CurrNode = dfBST.m_root;
	Pushdf(CurrNode);					//Fill the df vector
	CurrNode = gkBST.m_root;
	Pushgk(CurrNode);					//Fill the gk vector

	for(TreeNode *fw : fwNodes)					//Check the all cases
		for (TreeNode* mf : mfNodes)
			for (TreeNode* df : dfNodes)
				for (TreeNode*gk : gkNodes)
				{
					if (fw->m_data.m_ability + mf->m_data.m_ability + df->m_data.m_ability + gk->m_data.m_ability > best_team.sum_ability)	//if new team's ability is bigger than previous team
					{
						if (fw->m_data.m_transfer_fee + mf->m_data.m_transfer_fee + df->m_data.m_transfer_fee + gk->m_data.m_transfer_fee <= m_budget)		//If new team's budget is less or same with budget
						{
							best_team.sum_ability = fw->m_data.m_ability + mf->m_data.m_ability + df->m_data.m_ability + gk->m_data.m_ability;												//Change the Best Team's data
							best_team.sum_transfer_fee = fw->m_data.m_transfer_fee + mf->m_data.m_transfer_fee + df->m_data.m_transfer_fee + gk->m_data.m_transfer_fee;
							best_team.fw = fw->m_data;
							best_team.mf = mf->m_data;
							best_team.df = df->m_data;
							best_team.gk = gk->m_data;
						}
					}
					else if (fw->m_data.m_ability + mf->m_data.m_ability + df->m_data.m_ability + gk->m_data.m_ability == best_team.sum_ability)		//if new team's ability is same with the previous team
					{
						if (fw->m_data.m_transfer_fee + mf->m_data.m_transfer_fee + df->m_data.m_transfer_fee + gk->m_data.m_transfer_fee < best_team.sum_transfer_fee)		//If transfer fee is less than previous team
						{
							best_team.sum_ability = fw->m_data.m_ability + mf->m_data.m_ability + df->m_data.m_ability + gk->m_data.m_ability;										//Change the Best Team's data
							best_team.sum_transfer_fee = fw->m_data.m_transfer_fee + mf->m_data.m_transfer_fee + df->m_data.m_transfer_fee + gk->m_data.m_transfer_fee;
							best_team.fw = fw->m_data;
							best_team.mf = mf->m_data;
							best_team.df = df->m_data;
							best_team.gk = gk->m_data;
						}
					}
				}
	//Fill in the code to search the best_team from 4 BSTs
	//The datas for best team must be stored in the variable best_team.
	//*best team means the most powerful team that is defined in the project introduction file. 

	if (!fwNodes.empty())				//Clear vectors
	{
		std::vector<TreeNode*> ().swap(fwNodes);
	}
	if (!mfNodes.empty())
	{
		std::vector<TreeNode*>().swap(mfNodes);
	}
	if (!dfNodes.empty())
	{
		std::vector<TreeNode*>().swap(dfNodes);
	}
	if (!gkNodes.empty())
	{
		std::vector<TreeNode*>().swap(gkNodes);
	}
	
	fwBST.deletion(best_team.fw.m_ability);			//Delete the Best Team's member of BinarySearchTree
	mfBST.deletion(best_team.mf.m_ability);
	dfBST.deletion(best_team.df.m_ability);
	gkBST.deletion(best_team.gk.m_ability);

	return best_team;													//return
}
