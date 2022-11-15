#ifndef HAND_H
#define HAND_H
#include"Deck.h"
#include"Player.h"
using namespace std;

class Hand {
public:
	vector<Card> cards;
	Hand();
	Hand(vector<Card> c);
	Hand(const Hand& h);
	Hand& operator=(const Hand& h);
	friend ostream& operator<<(ostream& os, const Hand& h);
	void display();
	void drawFrom(Deck& d);
	string playCards(int i, Deck &d);
};

void testCards();
#endif
