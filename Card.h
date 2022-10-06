#ifndef CARD_H
#define CARD_H
#include<iostream>
#include<string>
using namespace std;

class Card {
public:
	string type;
	Card();
	Card(string t);
	Card(const Card& c);
	string play(string target);
};
#endif