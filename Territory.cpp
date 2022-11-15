#include <iostream>
#include <string>
#include "Territory.h"
#include "Coord.h"
#include <vector>
//#include "Player.h"

Territory::Territory(string name) : name(name), adjacentTerritories()  { 
	this->coordinates = new Coord(-1, -1);
}

Territory::Territory() {}

Territory::Territory(const Territory& t) {
	name = t.name;
	controllingPlayer = t.controllingPlayer;
	continent = t.continent;
	armySize = t.armySize;
	adjacentTerritories = t.adjacentTerritories;
	coordinates = t.coordinates;
}

string Territory::getName() {
	return name;
}

Player* Territory::getControllingPlayer() {
	return controllingPlayer;
}

string Territory::getContinent() {
	return continent;
}

int Territory::getArmySize() {
	return armySize;
}

vector<Territory*> Territory::getAdjacentTerritories() {
	return adjacentTerritories;
}

void Territory::addAjacentTerritory(Territory* territory) {
	this->adjacentTerritories.push_back(territory);
}

Coord* Territory::getCoordinates() {
	return coordinates;
}

void Territory::setName(string name) {
	this->name = name;
}

void Territory::setControllingPlayer(Player* player) {
	this->controllingPlayer = player;
}

void Territory::setContinent(string continent) {
	this->continent = continent;
}

void Territory::setCoordX(int x) {
	this->coordinates->x = x;
}

void Territory::setCoordY(int y) {
	this->coordinates->y = y;
}

void Territory::setArmySize(int newArmySize) {
	this->armySize = newArmySize;
}

Territory& Territory::operator=(const Territory& t) {
	name = t.name;
	controllingPlayer = t.controllingPlayer;
	continent = t.continent;

	return *this;
};
