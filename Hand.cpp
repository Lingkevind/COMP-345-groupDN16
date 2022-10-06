#include"Hand.h"
using namespace std;

	Hand::Hand(string n) {
		cards = vector<Card>();
		name = n;
	}
	Hand::Hand(vector<Card> c,string n) {
		cards = c;
		name = n;
	}
	Hand::Hand(const Hand& c) {
		cards = c.cards;
		name = c.name;
	}

	void Hand::display() {
		cout << "\ncards amount:" << cards.size();
		for (int i = 0; i < cards.size(); i++) {
			cout<<"\n"<< i+1 << " " << cards[i].type;
		}
	}

	void Hand::drawFrom(Deck& d) {
		if (d.list.size() == 0) {
			cout << "There is no more cards remain in the deck.";
		}
		else {
			Card c = d.draw();
			cards.push_back(c);
			cout << "Player " << name << " drew card: " << cards[cards.size() - 1].type;
		}
	}

	void Hand::playCards(int i, string target, Deck& d) {
		if (i >= cards.size() || i < 0) {
			cout << "Player " << name << " does not have card with this index";
		}
		else {
				string s = "Player " + name + " played " + cards[i].play(target);
				d.list.push_back(cards[i]);
				d.randomShuffle();
				cards.erase(cards.begin()+i);
				cout << s;
		}
	}