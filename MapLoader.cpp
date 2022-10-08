#include <iostream>
#include <string>
#include <vector>
#include "MapLoader.h"
#include <fstream>

using namespace std;

MapLoader::MapLoader() {
	this->map = new Map();
}

enum Section { None, MapSection, ContinentSection, TerritorySection };

Map* MapLoader::loadMap(string fileName) {
	string nextLine;

	Section section = None;

	try {
		// Read from the text file
		ifstream MapFile(fileName);

		// Use a while loop together with the getline() function to read the file line by line
		while (getline(MapFile, nextLine)) {
			// Reaching a square bracket means we
			if (nextLine[0] == '[') {
				switch (section) {
				case None:
					section = MapSection;
					break;
				case MapSection:
					section = ContinentSection;
					break;
				case ContinentSection:	
					section = TerritorySection;
					break;
				}
			}
			else if (nextLine != "") {
				switch (section) {
				case None:
					break;
				case MapSection:
					parseMapLine(nextLine);
					break;
				case ContinentSection:
					parseContinentsLine(nextLine);
					break;
				case TerritorySection:
					parseTerritoriesLine(nextLine);
					break;
				}
			}
		}

		// Close the file
		MapFile.close();

		return section == None ? NULL : map;
	}
	catch (std::ifstream::failure e) {
		cout << "The map file you're trying to open doesn't exist or cannot be opened." << endl;
		return NULL;
	}
	catch (...) {
		cout << "An error occurred while loading the map. Please make sure your map file uses a valid syntax." << endl;
		return NULL;
	}
}

void MapLoader::parseMapLine(string line) {
	string key = line.substr(0, line.find('='));
	string value = line.substr(line.find('=') + 1);

	if (key == "author") {
		map->setAuthor(value);
	}
	else if (key == "image") {
		this->map->setImageFile(value);
	}
	// @TODO parse map info if needed
}
void MapLoader::parseContinentsLine(string line) {
	string name = line.substr(0, line.find('='));
	string territoryCount = line.substr(line.find('=') + 1);

	Continent* continent = new Continent(name, stoi(territoryCount));
	map->addContinent(continent);
}

void MapLoader::parseTerritoriesLine(string line) {
	Territory* territory = new Territory();
	
	string delimiter = ",";
	int pos = 0;
	int counter = 0;
	string element;

	while ((pos = line.find(delimiter)) != std::string::npos) {
		element = line.substr(0, pos);
		switch (counter) {
		// Name	for 0
		case 0:
			territory = findOrCreateTerritory(element);
			break;
		// Position for 1 & 2
		case 1:
			territory->setCoordX(stoi(element));
			break;
		case 2:
			territory->setCoordY(stoi(element));
			break;
		// Continent
		case 3:
			territory->setContinent(element);
			break;
		// Adjacent territories for 4+
		default:
			Territory* adjacentTerritory = findOrCreateTerritory(element);
			territory->addAjacentTerritory(adjacentTerritory);
			break;
		}


		line.erase(0, pos + delimiter.length());

		counter++;
	}

	Territory* adjacentTerritory = findOrCreateTerritory(line);
	territory->addAjacentTerritory(adjacentTerritory);
	this->addTerritoryToMap(territory);
	//std::cout << s << std::endl;
}

Territory* MapLoader::findOrCreateTerritory(string name) {
	for (size_t i = 0; i < territories.size(); i++)
	{
		if (territories[i]->getName() == name) {
			return territories[i];
		}
	}

	Territory* territory = new Territory(name);
	this->territories.push_back(territory);
	return territory;
}

void MapLoader::addTerritoryToMap(Territory* territory) {
	for (size_t i = 0; i < map->getContinents().size(); i++)
	{
		if (map->getContinents()[i]->getName() == territory->getContinent()) {
			map->getContinents()[i]->addTerritory(territory);
		}
	}
}

