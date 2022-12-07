#include <fstream>
#include <string>
#include <vector>
#include "LoggingObserver.h"
#include "PlayerStrategy.h"
#include "HumanPlayerStrategy.h"

using namespace std;

HumanPlayerStrategy::HumanPlayerStrategy(Player* p) {
	this->player = p;
}

HumanPlayerStrategy::HumanPlayerStrategy(const HumanPlayerStrategy& c) {
	player = c.player;
}


void HumanPlayerStrategy::issueDeploy() {
	cout << this->player->getPlayerName() << ", please enter the amount of army you want to deploy, you have " << this->player->ArmyUnit << " undeployed unit" << endl;
	int army;
	cin >> army;
	cout << "please enter the target territory you wish to deploy." << endl;
	cout << "Avaiable : ";
	for (int i = 0; i < this->player->getplayerOccupied().size(); i++) {
		cout << this->player->getplayerOccupied()[i]->getName() << "(" << this->player->getplayerOccupied()[i]->getArmySize() << " unit)" << ", ";
	}
	cout << " : " << endl;
	string tName;
	cin >> tName;
	Territory* t = this->player->getTerritoryFromPlayerOccupied(tName);
	Deploy d = Deploy(this->player, army, t);
	this->player->ArmyUnit -= army;
	t->setArmySize(t->getArmySize() + army);
	this->player->oList->add(&d);
}

bool HumanPlayerStrategy::issueOrder(Deck* deck, Map* gameMap) {
	cout << "Player " << this->player->getPlayerName() << ", please select your action" << endl << "1.advance units" << endl << "2.play cards" << endl << "3.pass turn" << endl;
	int option;
	cin >> option;
	
	// Skipping the turn
	if (option == 3) {
		return true;
	}
	if (option == 1) {
		cout <<this->player->getPlayerName() << ", please enter the territory you want to move from." << endl << "Avaiable : ";
		for (int i = 0; i < this->player->getplayerOccupied().size(); i++) {
			cout << this->player->getplayerOccupied()[i]->getName() << "(" << this->player->getplayerOccupied()[i]->getArmySize() << " unit)" << ", ";
		}
		cout << " : " << endl;

		string tName;
		cin >> tName;
		Territory* from = this->player->getTerritoryFromPlayerOccupied(tName);

		if (from != NULL) {
			cout << "please enter the amount of army you want to move (" << from->getArmySize() << "unit available) " << endl;
		}
		int army;
		cin >> army;
		cout << "please enter the territory you want to move to." << endl << "Avaiable : ";
		for (int i = 0; i < from->getAdjacentTerritories().size(); i++) {
			cout << from->getAdjacentTerritories()[i]->getName() << "(" << from->getAdjacentTerritories()[i]->getArmySize() << " unit)" << ", ";
		}
		cout << " : " << endl;
		cin >> tName;
		Territory* to = this->player->getTerritoryFromAvailableToMoveTo(tName);
		Advance a = Advance(this->player, army, from, to);
		this->player->oList->add(&a);
		this->player->ArmyUnit -= army;
	}
	if (option == 2) {
		string cardToPlay;

		cout << "please enter the index of the card you wanna play, enter 0 to skip.";
		this->player->getplayerHand()->display();
		if (this->player->getplayerHand()->cards.size() != 0) {
			int index;
			cin >> index;
			Hand *h = this->player->getplayerHand();
			string card = h->playCards(index - 1, *deck);
			cardToPlay = card;
		}
		else {
			cardToPlay = "";
		}

		if (cardToPlay != "") {
			if (cardToPlay == "Airlift") {
				cout << this->player->getPlayerName() << ", please enter the territory you want to lift from." << endl;
				string tName;
				cin >> tName;
				Territory* from = this->player->getTerritoryFromPlayerOccupied(tName);
				cout << "please enter the amount of army you want to move." << endl;
				int army;
				cin >> army;
				cout << "please enter the territory you want to drop to." << endl;;
				cin >> tName;
				Territory* to = gameMap->findTerritorybyName(tName);
				Airlift a = Airlift(this->player, army, from, to);
				this->player->oList->add(&a);
			}
			if (cardToPlay == "Bomb") {
				cout << this->player->getPlayerName() << ", please enter the territory you want to place tha bomb." << endl;
				string tName;
				cin >> tName;
				Territory* target = gameMap->findTerritorybyName(tName);
				Bomb b = Bomb(this->player, target);
				this->player->oList->add(&b);
			}
			if (cardToPlay == "Blockade") {
				cout << this->player->getPlayerName() << ", please enter the territory you want to place tha blockade." << endl;
				string tName;
				cin >> tName;
				Territory* target = gameMap->findTerritorybyName(tName);
				Blockade b = Blockade(this->player, target);
				this->player->oList->add(&b);
			}
		}
		else {
			cout << "There is no card in your hand.";
		}
	}
	
	return false;
}


std::vector<Territory*> HumanPlayerStrategy::toAttack() {
	std::vector<Territory*> v;
	for (Territory * t : player->getplayerOccupied()) {
		std::vector<Territory*> tPla = t->getAdjacentTerritories();
		for (Territory * t1 : tPla) {
			if (std::find(v.begin(), v.end(), t1) != v.end()) {
				v.insert(v.end(), t1);
			}
		}
	}
	return v;
}

std::vector<Territory*> HumanPlayerStrategy::toDefend() {
	return this->player->getplayerOccupied();

}

ostream& operator<<(ostream& os, HumanPlayerStrategy& humanPlayerStrategy) {
	os << humanPlayerStrategy.player->getPlayerName() << "'s strategy is " << typeid(humanPlayerStrategy).name() << "\n";
	return os;
}

HumanPlayerStrategy& HumanPlayerStrategy::operator=(const HumanPlayerStrategy& c) {
	player = c.player;
	return *this;
};
