
// C++ program to declare
// a class with name main

#include <iostream>
#include "Territory.h"
#include "Coord.h"
#include <map>
#include "MapLoader.h"
#include "MapDriver.h";
#include <windows.h> 


// Main code & entry point of the program


void MapDriver::testLoadMaps(vector<string> mapFileSample)
{
    MapLoader* mapLoader = new MapLoader();

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int i = 0; i < mapFileSample.size(); i++)
    {
        SetConsoleTextAttribute(hConsole, 15);
        cout << "Testing '" << mapFileSample[i] << "'.." << endl;

        Map* testMap = mapLoader->loadMap(mapFileSample[i]);
        cout << "-> Loading the map from the file... ";
        if (testMap != NULL) {
            testMap->validate();

        }
        else {
            SetConsoleTextAttribute(hConsole, 12);
            cout << "FAILURE" << endl;
            cout << endl;
            SetConsoleTextAttribute(hConsole, 15);
        }
    }
}

