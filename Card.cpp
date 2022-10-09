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

	Card& Card::operator=(const Card &c) {
		type = c.type;
		return *this;
	};

	string Card::play(string target) {
		string s = type + " on " + target;
		return s;
	}

	ostream& operator<<(ostream& os, const Card& c) {
		os <<"Type:" << c.type;
		return os;
	}