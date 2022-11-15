#include <iostream>
#include "Map.h"
#include <map>
#include <windows.h> 


using namespace std;

Map::Map() : continents() { }

void Map::addContinent(Continent* continent) {
	this->continents.push_back(continent);
}

vector<Continent*>  Map::getContinents() {
	return continents;
}

string Map::getAuthor() {
	return author;
}
void Map::setAuthor(string author) {
	this->author = author;
}

string Map::getImageFile() {
	return imageFile;
}

void Map::setImageFile(string imageFile) {
	this->imageFile = imageFile;
}

bool Map::validate() {
    // handle that helps manipulate the console properties, such as the color.
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    // Setting the console color to green.
    SetConsoleTextAttribute(hConsole, 10);
    cout << "SUCCESS" << endl;

    // Setting the console color to red.
    SetConsoleTextAttribute(hConsole, 15);
    cout << "-> The map is a connected graph... ";

    // If the connected subgraph method returns true, it means both
    // the territories and the continent are connected subgraphs.
    bool connectedGraphResult = isMapConnectedSubgraph();

    if (connectedGraphResult) {
        SetConsoleTextAttribute(hConsole, 10);
        cout << "SUCCESS" << endl;
    }
    else {
        SetConsoleTextAttribute(hConsole, 12);
        cout << "FAILURE" << endl;
    }
    SetConsoleTextAttribute(hConsole, 15);
    cout << "-> Continents are connected subgraphs... ";

    if (connectedGraphResult) {
        SetConsoleTextAttribute(hConsole, 10);
        cout << "SUCCESS" << endl;
    }
    else {
        SetConsoleTextAttribute(hConsole, 12);
        cout << "FAILURE" << endl;
        return false;
    }

    SetConsoleTextAttribute(hConsole, 15);

    cout << "-> Each country belongs to one and only one continent.. ";
    if (eachCountryBelongsToOneAndOnlyContinent()) {
        SetConsoleTextAttribute(hConsole, 10);
        cout << "SUCCESS" << endl;
    }
    else {
        SetConsoleTextAttribute(hConsole, 12);
        cout << "FAILURE" << endl;
        return false;
    }
    SetConsoleTextAttribute(hConsole, 15);
    cout << endl;
    return true;
}

bool Map::isMapConnectedSubgraph() {
    std::map<string, bool> visitationMatrix;
    std::map<string, bool> continentVisitationMatrix;

    // First the visitation matrix is initialized to false for all territories snd continents.
    for (size_t i = 0; i < this->getContinents().size(); i++)
    {
        continentVisitationMatrix[this->getContinents()[i]->getName()] = false;
        for (size_t j = 0; j < this->getContinents()[i]->getTerritories().size(); j++)
        {
            visitationMatrix[this->getContinents()[i]->getTerritories()[j]->getName()] = false;
        }
    }

    visitAdjacentTerritories(this->getContinents()[0]->getTerritories()[0], visitationMatrix, continentVisitationMatrix);

    // Makes sure all territories are connected.
    for (auto const& t : visitationMatrix)
    {
        if (!t.second) {
            return false;
        }
    }

    // Makes sure all continents are connected.
    for (auto const& c : continentVisitationMatrix)
    {
        if (!c.second) {
            return false;
        }
    }

    return true;
}

void Map::visitAdjacentTerritories(Territory* territory, std::map<string, bool>& visitationMatrix, std::map<string, bool>& continentVisitationMatrix) {
    
    // The current node is set to 'visited'
    visitationMatrix[territory->getName()] = true;
    continentVisitationMatrix[territory->getContinent()] = true;
    for (size_t i = 0; i < territory->getAdjacentTerritories().size(); i++)
    {
        // If the current adjacent has not been visited yet, visit all of its adjacent node.
        if (!visitationMatrix[territory->getAdjacentTerritories()[i]->getName()]) {
            visitAdjacentTerritories(territory->getAdjacentTerritories()[i], visitationMatrix, continentVisitationMatrix);
        }
    }
}

bool Map::eachCountryBelongsToOneAndOnlyContinent() {
    // Map used to store the continent of each contry
    std::map<string, string> territoryContinent;

    for (size_t i = 0; i < this->getContinents().size(); i++)
    {
        for (size_t j = 0; j < this->getContinents()[i]->getTerritories().size(); j++)
        {
            // If the current territory has no continent, assign an entry in the territory/continent map, otherwise return false, indicating that the check fails.
            if (territoryContinent.count(this->getContinents()[i]->getTerritories()[j]->getName())) {
                if (territoryContinent[this->getContinents()[i]->getTerritories()[j]->getName()] != this->getContinents()[i]->getTerritories()[j]->getContinent()) {
                    return false;
                }
            }
            else {
                territoryContinent[this->getContinents()[i]->getTerritories()[j]->getName()] = this->getContinents()[i]->getTerritories()[j]->getContinent();
            }
        }
    }
}

vector<Territory*> Map::getTerritories() {
    vector<Territory*> territories;;

    for (size_t i = 0; i < this->getContinents().size(); i++)
    {
        for (size_t j = 0; j < this->getContinents()[i]->getTerritories().size(); j++)
        {
            territories.push_back(this->getContinents()[i]->getTerritories()[j]);
        }
    }

    return territories;
}

Territory* Map::findTerritorybyName(string name) {
    vector<Territory*> tList=getTerritories();
    for (int i = 0; i < getTerritories().size(); i++) {
        if (tList[i]->getName() == name) {
            return tList[i];
        }
    }
    cout << "Territory named "<<name<<" does not exist"<<endl;
};