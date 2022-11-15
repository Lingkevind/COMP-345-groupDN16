#pragma once
#include <iostream>
#include <string>
#include <vector>
//#include "Territory.h"
#include "Hand.h"
#include "Orders.h"
#include "Continent.h"

static int playerNum = 0;
class Player
{
 public:
	std::vector <Territory*> playerOccupied;//get method
	//pointer
	std::vector <Player>* playerOrderVector;
	Hand* playerHand;
	OrderList oList;
	friend ostream& operator<<(ostream& os, const Player& d);
	int pid = -1;
	int ArmyUnit;
	Player();
	~Player();
	Player(std::string newName);
	Player(const Player& copyPlayer);
	Player(std::string newName, int newPid, std::vector <Territory*> newplayerOccupied, Hand h, int au);
	bool ownTerritory(Territory t);
	std::vector <Territory>toDefend();
	std::vector <Territory>toAttack();
	std::vector<Order> playerOrderlist; 
	void issueOrder();
	void attack(Player pd); 
	void leaveTerritory(Territory* t);
	string occupy(Territory * t);
	string occupy(Territory* t, Player defeatedPlayer);
	string annex( Player*p);
	void displayerOcc();
	void displayOcc(vector <Territory*> occVector);
	void setPlayerName(string newName);
	std::string getPlayerName();
	std::vector <Territory*> getplayerOccupied();
	std::string playerName;
};

class PlayerList 
{public:
	std::vector<Player> list;
	PlayerList();
	PlayerList(const PlayerList& pl);
	void addPlayer(Player p) ;
	Player findPlayer(int i) ;
	Player findPlayerbyName(string name);
};

void testPlayer();


