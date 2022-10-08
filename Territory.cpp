#include <iostream>
#include <string>
#include "Territory.h"
#include "Coord.h"
#include <vector>

using namespace std;

Territory::Territory(string name) : name(name), adjacentTerritories()  { 
	this->coordinates = new Coord(-1, -1);
}

Territory::Territory() {}

string Territory::getName() {
	return name;
}

string Territory::getControllingPlayerName() {
	return controllingPlayerName;
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

void Territory::setControllingPlayerName(string playerName) {
	this->controllingPlayerName = playerName;
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
