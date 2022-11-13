#pragma once
#include <iostream>
#include <string>
#include <vector>
//#include "Territory.h"
#include "p4/Hand.h"
#include "OrdersList/Orders.h"
#include "Map/Continent.h"

static int playerNum = 0;
class Player
{
	std::vector <Territory*> playerOccupied;//get method
	//pointer
	std::vector <Player>* playerOrderVector;
	Hand* playerHand = nullptr;
	vector<Order>* playerOrderPtr = nullptr;
	
public:
	friend ostream& operator<<(ostream& os, const Player& d);
	int pid = -1;
	Order playerOrderlist;
	Player();
	Player(std::string newName);
	Player(const Player& copyPlayer);
	Player(std::string newName, int newPid, std::vector <Territory*> newplayerOccupied, Hand h);
	std::vector <Territory>toDefend();
	std::vector <Territory>toAttack();
	void issueOrder();
	void attack(Player pd); 
	void occupy(Territory * t);
	void occupy(vector <Territory>* t);
	void occupy(Player p);
	void displayerOcc();
	static void displayOcc(vector <Territory*> occVector);
	void setPlayerName(string newName);
	
	std::string getPlayerName();
	std::vector <Territory*> getplayerOccupied();
	std::string playerName;
};
void testPlayer();


