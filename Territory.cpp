#include <iostream>
#include <string>
#include "Territory.h"
//#include "Coord.h"
#include <vector>

using namespace std;

Territory::Territory(string name) {
	setName(name);
}

Territory::Territory() {
	name = "default";
}

string Territory::getName() {
	return name;
}
void Territory::setName(string newName) {
	name = newName;

}

