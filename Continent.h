#pragma once
#include <iostream>
#include <string>
using std::string;
#include <vector>
using std::vector;
#include "Coord.h"
#include "Territory.h"

using std::ostream;

class Continent {
public:

	/**
	* Construct the Continent object
	* 
	* @param name Name of the continent.
	* @param territoryCount Number of territories in the continent.
	*/
	Continent(string name, int territoryCount);
	Continent(const Continent& c);


	/**
	* Gets the name of the continent.
	* 
	* @return the name of the continent.
	*/
	string getName();

	// free operator declaration
	friend ostream& operator<<(ostream& os, const Continent& continent);

	Continent& operator= (const Continent& c);

	/**
	* Gets the number of territories in the continent.
	*
	* @return the name of the continent.
	*/
	int getTerritoryCount();

	vector<Territory*> getTerritories();

	/**
	* Adds a territory to the continent
	* 
	* @param territory The territory object pointer to be added to the continent
	*/
	void addTerritory(Territory* territory);

	bool OwnedContinent(Player* player);

private:
	string name;
	int territoryCount;
	vector<Territory*> territories;
};

