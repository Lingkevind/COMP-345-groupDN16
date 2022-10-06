#include "Card.h"
using namespace std;
	Card::Card() {
		type = "blank";
	}
	Card::Card(string t) {
		type = t;
	}
	Card::Card(const Card& c) {
		type = c.type;
	}

	string Card::play(string target) {
		string s = type + " on " + target;
		return s;
	}