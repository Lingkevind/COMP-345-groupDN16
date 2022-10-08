#pragma once
#include <iostream>
#include <string>
using std::string;
#include <vector>
using std::vector;
#include "Coord.h"

class Territory {
public:
	Territory(string name);
	Territory();
	string getName();
	string getControllingPlayerName();
	string getContinent();
	vector<Territory*> getAdjacentTerritories();
	void addAjacentTerritory(Territory* territory);

	int getArmySize();
	void setName(string name);
	void setControllingPlayerName(string playerName);
	void setContinent(string continent);
	void setCoordX(int x);
	void setCoordY(int y);

	void setArmySize(int newArmySize);
	Coord* getCoordinates();

private:
	string name;
	string controllingPlayerName;			//@TODO Change type to Player*
	string continent;
	vector<Territory*> adjacentTerritories;
	int armySize;
	Coord* coordinates;
};

// free operator declaration
ostream& operator<<(ostream& os, const Territory& territory);