#include"Deck.h"
//default constructor
Deck::Deck() {
	list = vector<Card>();
}
//attribute constructor
Deck::Deck(vector<Card> l) {
	list = l;
}
//copy constructor
Deck::Deck(const Deck& d) {
	list = d.list;
}
//overiding '='
Deck& Deck::operator=(const Deck& d) {
	list = d.list;
	return *this;
};
//generate 25 cards add to the list with 5 of each type
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
//randomly choosing two card in the list and swap their index
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
//calling shuffleOnce() for 499 times in order to completly mix up the deck
void Deck::randomShuffle() {
	int i = 0;
	while (i < 499) {
		shuffleOnce();
		i++;
	}
}
//shuffle whenever a card is pushed to the deck
void Deck::addToDeck(Card c) {
	list.push_back(c);
	randomShuffle();
}
//remove and return the most front card on the list
Card Deck::draw() {
	Card c = list[0];
	list.erase(list.begin());
	return c;
}

//output the card item in list with the index
void Deck::display() {
	cout << "\ncards remain:" << list.size() << "\ncurrent cards: \n";
	for (int i = 0; i < list.size(); i++) {
		cout << list[i].type << "\n";
	}
}

//overiding '<<'
ostream& operator<<(ostream& os, const Deck& d) {
	os << typeid(d).name()<<", Card remain:"<<d.list.size();
	return os;
}