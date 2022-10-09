#include <iostream>
#include <string>
#include "Continent.h"
#include <vector>

Continent::Continent(string name, int territoryCount) : name(name), territoryCount(territoryCount) { }

Continent::Continent(const Continent& c) {
	name = c.name;
	territoryCount = c.territoryCount;
	territories = c.territories;
}

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
	os << continent.getName() << " : owned territories are : " << endl;
	for (Territory* t : continent.getTerritories())
		os << t;
	cout << endl;
	return os;
}

Continent& Continent::operator=(const Continent& c) {
	name = c.name;
	territories = c.territories;
	territoryCount = c.territoryCount;
	return *this;
};



