#ifndef DECK_H
#define DECK_H
#include"Card.h"
#include<vector>
#include<random>
using namespace std;

class Deck {
public:
	vector<Card> list;
	Deck();
	Deck(vector<Card> l);
	Deck(const Deck& d);
	void initialize();
	void shuffleOnce();
	void randomShuffle();
	void addToDeck(Card c);
	Card draw();
	void display();
};
#endif