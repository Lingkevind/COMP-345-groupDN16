#pragma once
#pragma once
#include <iostream>
#include <string>
using std::string;
#include <vector>
using std::vector;
#include "Coord.h"
#include "Territory.h"
#include "Map.h"

class MapLoader {
public:
	MapLoader();
	Map* loadMap(string);

private:
	Map* map;
	
	// The territories loaded by the map loader. Used as a way to keep track of which territory as been created or not
	// during the parsing.
	vector<Territory*> territories;

	// The name of the map file to extract the Map from.
	string mapFile;

	/**
	* Parses the line as a line containing general information about the map.
	* 
	* @param line The extract line from the map file to be parsed.
	*/
	void parseMapLine(string line);

	/**
	* Parses the line as a line containing general information about the continent.
	*
	* @param line The extract line from the map file to be parsed.
	*/
	void parseContinentsLine(string line);

	/**
	* Parses the line as a line containing general information about the territory.
	*
	* @param line The extract line from the map file to be parsed.
	*/
	void parseTerritoriesLine(string line);


	/**
	* Finds or create the territory with the given name. If a territory with the given name already exists, it returns it.
	* If a territory with the given name does not exist yet, it creates it and return it.
	*
	* @param name The name of the territory to be found or created.
	*/
	Territory* findOrCreateTerritory(string name);

	/**
	* Adds the given territory to the map.
	*
	* @param territory The territory to be added to the map.
	*/
	void addTerritoryToMap(Territory* territory);
};

// free operator declaration
ostream& operator<<(ostream& os, const MapLoader& mapLoader);
