#pragma once
#include <iostream>
#include "Continent.h"
#include <map>


// Class Declaration 
class Map {

public:
	/**
	* Constructs the Map object
	*
	*/
	Map();

	/*
	* Adds the given continent to the Map.
	* 
	* @param continent The continent to be added to the map.
	*/
	void addContinent(Continent* continent);

	vector<Continent*> getContinents();

	string getAuthor();
	void setAuthor(string);

	string getImageFile();
	void setImageFile(string imageFile);

	/**
	* Validates the map to see if it meets the integrity requirement for a map.
	*/
	bool validate();
private:
	vector<Continent*> continents;
	string author;
	string imageFile;

	/**
	* Checks if the map is a connected subgraph by using a Depth First Traversal. 
	* The success of this check indicates that both the territories and continents are a connected subgraph.
	*/
	bool isMapConnectedSubgraph();

	/**
	* Checks if each countries belongs to one an only one continent.
	*/
	bool eachCountryBelongsToOneAndOnlyContinent();

	/**
	* Recursive methods that marks the current territory as visited and visits the territory's adjacent nodes. Part of the DFT algorithm.
	*/
	void visitAdjacentTerritories(Territory* territory, std::map<string, bool>& visitationMatrix, std::map<string, bool>& continentVisitationMatrix);
};

// free operator declaration
ostream& operator<<(ostream& os, const Map& map);

