#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Territory.h"
#include "p4/Hand.h"
#include "OrdersList/Orders.h"

static int playerNum = 0;
class Player
{
	std::vector <Territory> playerOccupied;
	//pointer
	std::vector <Player>* playerOrderVector;
	Hand* playerHand = nullptr;
	vector<Order>* playerOrderPtr = nullptr;
public:
	int pid = -1;
	Player();
	Player(std::string newName, int newPid);
	Player(const Player& copyPlayer);
	Player(std::string newName, int newPid, std::vector <Territory> newplayerOccupied, Hand h);
	std::vector <Territory>toDefend();
	std::vector <Territory>toAttack();
	void subissueOrder();
	std::vector <Player> issueOrder();
	void attack(Player pd); 
	void occupy(Territory t);
	void occupy(Player p);
	void displayerOcc();
	static void displayOcc(vector <Territory> occVector);
	void setPlayerName(string newName);
	std::string getPlayerName();
	
private:
	std::string playerName = "default";
};



