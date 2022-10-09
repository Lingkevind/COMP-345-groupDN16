#include"Deck.h"
using namespace std;
	Deck::Deck() {
		list = vector<Card>();
	}
	Deck::Deck(vector<Card> l) {
		list = l;
	}
	Deck::Deck(const Deck& d) {
		list = d.list;
	}

	Deck& Deck::operator=(const Deck& d) {
		list = d.list;
		return *this;
	};

	void Deck::initialize() {
		vector<Card> newList;
		int i = 0;
		while (i < 5) {
			Card New = Card("Bomb");
			newList.push_back(New);
			i++;
		}
		i = 0;
		while (i < 5) {
			Card New = Card("Reinforcement");
			newList.push_back(New);
			i++;
		}
		i = 0;
		while (i < 5) {
			Card New = Card("Blockade");
			newList.push_back(New);
			i++;
		}
		i = 0;
		while (i < 5) {
			Card New = Card("Airlift");
			newList.push_back(New);
			i++;
		}
		i = 0;
		while (i < 5) {
			Card New = Card("Diplomacy");
			newList.push_back(New);
			i++;
		}
		list = newList;
	}

	void Deck::shuffleOnce() {
		int a = rand() % list.size();
		int b = rand() % list.size();
		Card A = list[a];
		Card B = list[b];
		Card C = A;
		A = B;
		B = C;
		list[a] = A;
		list[b] = B;
	}

	void Deck::randomShuffle() {
		int i = 0;
		while (i < 499) {
			shuffleOnce();
			i++;
		}
	}

	void Deck::addToDeck(Card c) {
		list.push_back(c);
		randomShuffle();
	}

	Card Deck::draw() {
		Card c = list[0];
		list.erase(list.begin());
		return c;
	}

	void Deck::display() {
		cout << "\ncards remain:" << list.size() << "\ncurrent cards: \n";
		for (int i = 0; i < list.size(); i++) {
			cout << list[i].type << "\n";
		}
	}

	ostream& operator<<(ostream& os, const Deck& d) {
		os << typeid(d).name()<<", Card remain:"<<d.list.size();
		return os;
	}