#include "Card.h"
//Default constructor
Card::Card() {
	type = "blank";
}
//Attribute constructor
Card::Card(string t) {
	type = t;
}
//Copy constructor
Card::Card(const Card& c) {
	type = c.type;
}
//Overriding '='
Card& Card::operator=(const Card& c) {
	type = c.type;
	return *this;
};
//play method which returns the second half of the command.
string Card::play(string target) {
	string s = type + " on " + target;
	return s;
}

//Overiding '<<'
ostream& operator<<(ostream& os, const Card& c) {
	os << c.type;
	return os;
}