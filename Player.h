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
	std::vector <Territory*> playerOccupied;//get method
	//pointer
	std::vector <Player>* playerOrderVector;
	Hand* playerHand = nullptr;
	vector<Order>* playerOrderPtr = nullptr;
	
public:
	friend ostream& operator<<(ostream& os, const Player& d);
	int pid = -1;
	Order playerOrderlist;//old
	OrderList oList; //new
	int ArmyUnit;//new
	Player();
	Player(std::string newName);
	Player(const Player& copyPlayer);
	Player(std::string newName, int newPid, std::vector <Territory*> newplayerOccupied, Hand h);
	std::vector <Territory*>toDefend();
	std::vector <Territory*>toAttack();
	void issueOrder();
	void attack(Player pd); 
	void leaveTerritory(Territory* t);
	string occupy(Territory * t);
	string occupy(Territory* t, Player defeatedPlayer);
	string annex( Player*p);
	bool isLosttheGame();
	//bool ownTerritory(Territory t); 
	//Severity	Code	Description	Project	File	Line	Suppression State
	//	Error	C2679	binary '==': no operator found which takes a right - hand operand of type 'const _Ty' (or there is no acceptable conversion)	
	//	Community\VC\Tools\MSVC\14.33.31629\include\xutility	5268
	void displayerOcc();
	void displayOcc(vector <Territory*> occVector);
	std::vector <Territory*> getFrontierT();
	void setPlayerName(string newName);
	std::string getPlayerName();
	std::vector <Territory*> getplayerOccupied();
	std::string playerName;
};

class PlayerList
{
public:
	std::vector<Player> list;
	PlayerList();
	PlayerList(const PlayerList& pl);
	void addPlayer(Player p);
	Player findPlayer(int i);
	Player findPlayerbyName(string name);
};

void testPlayer();
