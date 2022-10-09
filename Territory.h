#pragma once
#include <iostream>
#include <string>
using std::string;
#include <vector>
using std::vector;
#include "Coord.h"
#include "Player.h"

class Player;

class Territory {
public:
	Territory(string name);
	Territory();
	string getName();
	Player* getControllingPlayer();
	string getContinent();
	vector<Territory*> getAdjacentTerritories();
	void addAjacentTerritory(Territory* territory);

	int getArmySize();
	void setName(string name);
	void setControllingPlayer(Player* player);
	void setContinent(string continent);
	void setCoordX(int x);
	void setCoordY(int y);

	void setArmySize(int newArmySize);
	Coord* getCoordinates();

	Territory& operator=(const Territory& t);

private:
	string name;
	Player* controllingPlayer;		
	string continent;
	vector<Territory*> adjacentTerritories;
	int armySize;
	Coord* coordinates;
};

