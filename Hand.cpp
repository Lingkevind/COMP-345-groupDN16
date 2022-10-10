#include"Hand.h"
//default constructor
Hand::Hand() {
	cards = vector<Card>();
	name = "anonymous";
}
//attribute constructor
Hand::Hand(string n) {
	cards = vector<Card>();
	name = n;
}
//copy constructor
Hand::Hand(const Hand& h) {
	cards = h.cards;
	name = h.name;
}
//overriding '='
Hand& Hand::operator=(const Hand& h) {
	cards = h.cards;
	name = h.name;
	return *this;
};
//output the card item in list with the index
void Hand::display() {
	cout << "\ncards amount:" << cards.size();
	for (int i = 0; i < cards.size(); i++) {
		cout << "\n" << i + 1 << " " << cards[i];
	}
}
//takes the card item returned from Draw() and push to the list
void Hand::drawFrom(Deck& d) {
	if (d.list.size() == 0) {
		cout << "\nThere is no more cards remain in the deck.";
	}
	else {
		Card c = d.draw();
		cards.push_back(c);
		cout << "\nPlayer " << name << " drew card: " << cards[cards.size() - 1].type;
	}
}
//find the corresponding card item to the i inputted, trigger its play() method, erase the item, while push a copy of it to the deck
void Hand::playCards(int i, string target, Deck& d) {
	if (i >= cards.size() || i < 0) {
		cout << "Player " << name << " does not have card with this index";
	}
	else {
		string s = name + " played " + cards[i].play(target);
		d.list.push_back(cards[i]);
		d.randomShuffle();
		cards.erase(cards.begin() + i);
		cout << s << "\n";
	}
}
//overiding '<<'
ostream& operator<<(ostream& os, const Hand& h) {
	os << "Player name: " << h.name << "\nCard amount:" << h.cards.size()<<"\n";
	return os;
}

//free function for merging all above methods with exception handling
void testCards() {
	cout << "Welcome to Warzone card system tester 1.1!\n=========================================";
	int option = 4;
	while (option == 4) {
		try {
			cout << "\nInput 1 to create deck ";
			cin >> option;
			while (option != 1) {
				if (!cin) {
					throw 505;
				}
				cout << "\nThat's not a valid input";
				cout << "\nInput 1 to create deck ";
				cin >> option;
			}
			Deck d = Deck();
			d.initialize();
			d.randomShuffle();
			cout << "\nDeck created\n=========================================";
			d.display();
			cout << "\n=========================================\nInput 2 to create hand ";
			cin >> option;
			while (option != 2) {
				if (!cin) {
					throw 505;
				}
				cout << "\nThat's not a valid input";
				cout << "\nInput 2 to create hand ";
				cin >> option;
			}
			Hand player = Hand("AI");
			cout << "\nHand created\n";
			cout << player;
			cout << "\n=========================================";
			cout << "\nInput the amount of cards to draw ";
			cin >> option;
			for (int i = 0; i < option; i++) {
				player.drawFrom(d);
			}
			cout << "\n" << player.cards.size() << " cards drawn\n";
			player.display();
			cout << "\n=========================================\nInput 3 to play all cards in player's hand ";
			cin >> option;
			while (option != 3) {
				if (!cin) {
					throw 505;
				}
				cout << "\nThat's not a valid input";
				cout << "\nInput 3 to play all cards in player's hand ";
				cin >> option;
			}
			while (player.cards.size() > 0) {
				player.playCards(0, "defaultMap", d);
			}
			cout << "\n=========================================\nProgress has finished, input 4 to rerun, input any other int to exit ";
			cin >> option;
			if (!cin) {
				throw 505;
			}
		}
		catch (...) {
			cout << "\nYou have entered non-integer value, run failed, how unfortunate.\n";
		}
	}

	cout << "Terminating the program, thanks for using.";
};