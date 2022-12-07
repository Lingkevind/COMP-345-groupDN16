#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Territory.h"
#include "Hand.h"
#include "Orders.h"
#include "Continent.h"
#include "PlayerStrategy.h"
#include "Map.h"
#include "Deck.h"

 static int playerNum = 0;
class Player
{
	std::vector <Territory*> playerOccupied;//get method
	//pointer
	std::vector <Player>* playerOrderVector;
	Hand* playerHand = nullptr;
	vector<Order>* playerOrderPtr = nullptr;
	
public:
	void setStrategy(PlayerStrategy* strategy);
	friend ostream& operator<<(ostream& os, const Player& d);
	int pid = -1;
	Order playerOrderlist;//old
	OrderList* oList; //new
	int ArmyUnit ;//new
	PlayerStrategy* strategy;
	Player();
	Player(std::string newName);
	Player(const Player& copyPlayer);
	Player(std::string newName, int newPid, std::vector <Territory*> newplayerOccupied, Hand* h);
	~Player();
	std::vector <Territory*>toDefend();
	std::vector <Territory*>toAttack();
	bool issueOrder(Deck* deck, Map* map);
	void issueDeploy();
	void playCard(string card);
	void attack(Player pd); 
	void leaveTerritory(Territory* t);
	string occupy(Territory * t);
	string occupy(Territory* t, Player defeatedPlayer);
	string annex( Player*p);
	bool isLosttheGame();
	void displayerOcc();
	void displayOcc(vector <Territory*> occVector);
	std::vector <Territory*> getFrontierT();
	void setPlayerName(string newName);
	void setArmyUnit(int i);
	std::string getPlayerName();
	Hand* getplayerHand();
	std::vector <Territory*> getplayerOccupied();
	Territory* getTerritoryFromPlayerOccupied(string);
	Territory* getTerritoryFromAvailableToMoveTo(string);
	std::vector <Territory*> getAvailableToMoveTo();

	int  getplayerOccupiedsize();
	std::string playerName;
};

/*class PlayerList
{
public:
	std::vector<Player> list;
	PlayerList();
	PlayerList(vector<Player>);
	PlayerList(const PlayerList& pl);
	void addPlayer(Player p);
	Player findPlayer(int i);
	Player findPlayerbyName(string name);

};*/

void testPlayer();


