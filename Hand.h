#ifndef HAND_H
#define HAND_H
#include"Deck.h"
#include<stdexcept>
using namespace std;

class Hand {
public:
	//the vector storing cards
	vector<Card> cards;
	string name;
	Hand();
	Hand(string n);
	Hand(const Hand& h);
	Hand& operator=(const Hand& h);
	friend ostream& operator<<(ostream& os, const Hand& h);
	void display();
	void drawFrom(Deck& d);
	void playCards(int i, string target, Deck& d);
};

void testCards();
#endif