#ifndef HAND_H
#define HAND_H
#include"Card.cpp"
#include"Deck.cpp"
using namespace std;

class Hand {
public:
	vector<Card> cards;
	string name;
	Hand(string n);
	Hand(vector<Card> c, string n);
	Hand(const Hand& c);
	void display();
	void drawFrom(Deck& d);
	void playCards(int i, string target, Deck& d);
};
#endif
