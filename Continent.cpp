#include <iostream>
#include <string>
#include "Continent.h"
#include <vector>

using namespace std;

Continent::Continent(string name, int territoryCount) : name(name), territoryCount(territoryCount) { }

string Continent::getName() {
	return name;
}

int Continent::getTerritoryCount() {
	return territoryCount;
}

vector<Territory*> Continent::getTerritories() {
	return territories;
}

void Continent::addTerritory(Territory* territory) {
	this->territories.push_back(territory);
}

ostream& operator<<(ostream& os, Continent& continent) {
	os << continent.getName() << " : owned countries are : " << endl;
	for (Territory* t : continent.getTerritories())
		os << t;
	cout << endl;
	return os;
}



