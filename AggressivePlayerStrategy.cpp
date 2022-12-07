#include <fstream>
#include <string>
#include <vector>
#include "LoggingObserver.h"
#include "PlayerStrategy.h"
#include "AggressivePlayerStrategy.h"

using namespace std;

AggressivePlayerStrategy::AggressivePlayerStrategy(Player* p) {
	this->player = p;
}

AggressivePlayerStrategy::AggressivePlayerStrategy(const AggressivePlayerStrategy& c) {
	player  = c.player;
}

void AggressivePlayerStrategy::issueDeploy() {
	// Finding the most powerful territory
	Territory* mostConcentratedTerritory = this->player->getplayerOccupied()[0];

	for (int i = 0; i < this->player->getplayerOccupied().size(); i++) {
		if (this->player->getplayerOccupied()[i]->getArmySize() > mostConcentratedTerritory->getArmySize()) {
			mostConcentratedTerritory = this->player->getplayerOccupied()[i];
		}
	}
	
	int armyUnitToDeploy = this->player->ArmyUnit;
	// Deploying units to the most powerful country
	Deploy d = Deploy(this->player, armyUnitToDeploy, mostConcentratedTerritory);
	this->player->ArmyUnit -= armyUnitToDeploy;
	mostConcentratedTerritory->setArmySize(mostConcentratedTerritory->getArmySize() + armyUnitToDeploy);
	this->player->oList->add(&d);

	cout << "Aggressive player deployed " << armyUnitToDeploy << "unit to his most concentrated territory, " << mostConcentratedTerritory->getName() << "." << endl;
}

bool AggressivePlayerStrategy::issueOrder(Deck* deck, Map* map) {
	// First checking if the player has any offensive cards 
	Hand *h = this->player->getplayerHand();
	bool cardPlayed = false;
	
	// If the aggressive player has a bomb, uses it.
	for (int i = 0; i < h->cards.size(); i++) {
		if (h->cards[i].type == "Bomb") {
			Territory* mostConcentratedTerritory = this->player->getplayerOccupied()[0];

			for (int i = 0; i < this->player->getplayerOccupied().size(); i++) {
				if (this->player->getplayerOccupied()[i]->getArmySize() > mostConcentratedTerritory->getArmySize()) {
					mostConcentratedTerritory = this->player->getplayerOccupied()[i];
				}
			}

			Bomb b = Bomb(this->player, mostConcentratedTerritory);
			this->player->oList->add(&b);
			this->player->getplayerHand()->playCards(i, *deck);
			cardPlayed = true;
		} 
	}

	// If no cards were played, attack with full force.
	if (!cardPlayed) {
		Territory* mostConcentratedTerritory = this->player->getplayerOccupied()[0];

		for (int i = 0; i < this->player->getplayerOccupied().size(); i++) {
			if (this->player->getplayerOccupied()[i]->getArmySize() > mostConcentratedTerritory->getArmySize()) {
				mostConcentratedTerritory = this->player->getplayerOccupied()[i];
			}
		}

		if (this->toAttack().size() > 0) {
			cout << "Aggressive player " << this->player->getPlayerName() <<
				" advanced to territory \"" << this->toAttack()[0]->getName() <<
				"\" from \"" << mostConcentratedTerritory->getName() << "\" with " << mostConcentratedTerritory->getArmySize() << " army unit" << endl;
			Advance a = Advance(this->player, mostConcentratedTerritory->getArmySize(), mostConcentratedTerritory, this->toAttack()[0]);
			this->player->oList->add(&a);
			this->player->ArmyUnit -= this->player->ArmyUnit;
		}

	}

	return true;
}

std::vector<Territory*> AggressivePlayerStrategy::toAttack() {
	vector<Territory*> toAttack;

	// Gets the most powerful country
	Territory* mostConcentratedTerritory = this->player->getplayerOccupied()[0];

	for (int i = 0; i < this->player->getplayerOccupied().size(); i++) {
		if (this->player->getplayerOccupied()[i]->getArmySize() > mostConcentratedTerritory->getArmySize()) {
			mostConcentratedTerritory = this->player->getplayerOccupied()[i];
		}
	}

	// Attacks one of the most powerful country's adjacent territroy with full force!
	for (Territory* t : mostConcentratedTerritory->getAdjacentTerritories()) {
		if (t->getControllingPlayer()->getPlayerName() != this->player->getPlayerName()) {
			toAttack.push_back(t);
			return toAttack;
		}
	}

	return toAttack;
}

std::vector<Territory*> AggressivePlayerStrategy::toDefend() {
	 vector<Territory*> toDefend;

	 return toDefend;
}

ostream& operator<<(ostream& os, AggressivePlayerStrategy& aggressivePlayerStrategy) {
	os << aggressivePlayerStrategy.player->getPlayerName() << "'s strategy is " << typeid(aggressivePlayerStrategy).name() << "\n";
	return os;
}

AggressivePlayerStrategy& AggressivePlayerStrategy::operator=(const AggressivePlayerStrategy& c) {
	player = c.player;
	return *this;
};
