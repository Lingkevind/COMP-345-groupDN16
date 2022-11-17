#pragma once
#pragma once
#include <iostream>
#include <string>
#include "MapLoader.h"

using std::string;

class MapDriver {
public:

	/**
	* Entry point of the program
	* 
	* @return the return of the program, which represents its execution state.
	*/
	int main();

	/**
	* Tests the creation and integry of all the map files contained in the sample.
	* 
	* @param mapFileSample the vector of map file to test.
	*/
	void testLoadMaps(vector<string> mapFileSample);
};

// free operator declaration
//ostream& operator<<(ostream& os, const MapDriver& mapDriver);

