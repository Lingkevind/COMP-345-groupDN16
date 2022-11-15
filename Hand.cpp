#include"Hand.h"
using namespace std;


	Hand::Hand() {
		cards = vector<Card>();
	}
	Hand::Hand(vector<Card> c) {
		cards = c;
	}
	Hand::Hand(const Hand& h) {
		cards = h.cards;
	}

	Hand& Hand::operator=(const Hand& h) {
		cards = h.cards;
		return *this;
	};

	void Hand::display() {
		cout << "\ncards amount:" << cards.size();
		for (int i = 0; i < cards.size(); i++) {
			cout<<"\n"<< i+1 << " " << cards[i].type;
		}
	}

	void Hand::drawFrom(Deck& d) {
		if (d.list.size() == 0) {
			cout << "\nThere is no more cards remain in the deck.";
		}
		else {
			Card c = d.draw();
			cards.push_back(c);
		}
	}



	string Hand::playCards(int i, Deck &d) {
		if (i >= cards.size() || i < 0) {
			cout << "Player does not have card with this index";
			return " ";
		}
		else {
				Card c = cards[i];
				d.list.push_back(cards[i]);
				d.randomShuffle();
				cards.erase(cards.begin()+i);
				return c.type;
		}
	}

	ostream& operator<<(ostream& os, Hand& h) {
		os << "\nCard amount:" << h.cards.size()<<"\n";
		return os;
	}

	/*void testCards() {
		cout << "Welcome to Warzone card system tester 1.1!\n=========================================";
		int option = 0;
		while (option == 0) {
			cout << "\nInput 1 to create deck ";
			cin >> option;
			while (option != 1) {
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
				cout << "\nThat's not a valid input";
				cout << "\nInput 2 to create hand ";
				cin >> option;
			}
			Hand player = Hand("AI");
			cout << "\nHand created\n";
			cout << player;
			cout <<"\n=========================================";
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
				cout << "\nThat's not a valid input";
				cout << "\nInput 3 to play all cards in player's hand ";
				cin >> option;
			}
			while (player.cards.size() > 0) {
				player.playCards(0, "defaultMap", d);
			}
			cout << "\n=========================================\nProgress has finished, input 0 to rerun, input any other int to exit ";
			cin >> option;
		}

		cout << "Terminating the program, thanks for using.";
	};*/