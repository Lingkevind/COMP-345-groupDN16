#pragma once
#include <iostream>
#include <string>
using std::string;
#include <vector>
using std::vector;
//#include "Coord.h"
class Territory
{
	public:
	Territory(string name);
	Territory();

	string getName();
	void setName(string newName);
private:
	string name;
	string controllingPlayerName;			//@TODO Change type to Player*
	//string continent;
	//vector<Territory*> adjacentTerritories;
	//int armySize;
	//Coord* coordinates;
};

