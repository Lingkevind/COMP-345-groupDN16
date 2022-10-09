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

	/**
	* Construct the Territory object
	*
	* @param name Name of the territory.
	*/
	Territory(string name);
	Territory();
	Territory(const Territory& t);

	/**
	* Gets the name of the territory.
	*
	* @return the name of the territory.
	*/
	string getName();

	/**
	* Gets the controlling player of territory.
	*
	* @return the controlling player of the territory.
	*/
	Player* getControllingPlayer();

	/**
	* Gets the continent of the territory.
	*
	* @return the continent of the territory.
	*/
	string getContinent();

	/**
	* Gets the adjacent territories of the territory.
	*
	* @return the adjacent territories of the territory.
	*/
	vector<Territory*> getAdjacentTerritories();

	/**
	* Adds the given territory to the adjacent territories.
	*/
	void addAjacentTerritory(Territory* territory);

	/**
	* Gets the army size of the territory.
	*
	* @return the army size of the territory
	*/
	int getArmySize();

	/**
	* Sets the name of the territory.
	*
	* @param name The new name of the territory.
	*/
	void setName(string name);

	/**
	* Sets the controlling player of the territory.
	*
	* @param player The newcontrolling player of the territory.
	*/
	void setControllingPlayer(Player* player);

	/**
	* Sets the continent of the territory.
	*
	* @param continent The new continent of the territory.
	*/
	void setContinent(string continent);

	/**
	* Sets the x coordinate of the territory.
	*
	* @param x The new x coordinate of the territory.
	*/
	void setCoordX(int x);

	/**
	* Sets the y coordinate of the territory.
	*
	* @param y The new y coordinate of the territory.
	*/
	void setCoordY(int y);

	/**
	* Sets the army size of the territory.
	*
	* @param newArmySize The new army size of the territory.
	*/
	void setArmySize(int newArmySize);

	/**
	* Gets the coordinates of the territory.
	*
	* @return The coordinates of the territory.
	*/
	Coord* getCoordinates();

	// Assignment operator overide
	Territory& operator=(const Territory& t);

private:
	// The name of the territory
	string name;

	// The controlling player of the territory
	Player* controllingPlayer;

	// The continent of the territory
	string continent;

	// The adjacent territories of the territory
	vector<Territory*> adjacentTerritories;

	// The army size on the territory
	int armySize;

	// The coordinates of the territory
	Coord* coordinates;
};

