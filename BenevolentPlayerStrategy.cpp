#include <fstream>
#include <string>
#include <vector>
#include "LoggingObserver.h"
#include "PlayerStrategy.h"
#include "BenevolentPlayerStrategy.h"

using namespace std;

BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* p) {
	this->player = p;
}

BenevolentPlayerStrategy::BenevolentPlayerStrategy(const BenevolentPlayerStrategy& c) {
	player = c.player;
}




void BenevolentPlayerStrategy::issueDeploy() {
	// Finds the weakest of its territories
	Territory* weakestTerritory = this->player->getplayerOccupied()[0];

	for (Territory* t : this->player->getplayerOccupied()) {
		if (t->getArmySize() < weakestTerritory->getArmySize()) {
			weakestTerritory = t;
		}
	}

	int armyUnitToDeploy = this->player->ArmyUnit;
	// Deploys unit to its weakest territories
	Deploy d = Deploy(this->player, armyUnitToDeploy, weakestTerritory);
	this->player->ArmyUnit -= armyUnitToDeploy;
	weakestTerritory->setArmySize(weakestTerritory->getArmySize() + armyUnitToDeploy);
	this->player->oList->add(&d);

	cout << "Benevolent player deployed " << armyUnitToDeploy << "unit to his weakest territory, " << weakestTerritory->getName() << "." << endl;
}


bool BenevolentPlayerStrategy::issueOrder(Deck* deck, Map* map) {
	Territory* weakestTerritory = this->player->getplayerOccupied()[0];

	for (Territory* t : this->player->getplayerOccupied()) {
		if (t->getArmySize() < weakestTerritory->getArmySize()) {
			weakestTerritory = t;
		}
	}
	
	// Reinforces its weakest territories
	if (this->toDefend().size() > 0) {
		cout << "Benevolent player " << this->player->getPlayerName() <<
			" advanced to territory \"" << this->toAttack()[0]->getName() <<
			"\" from \"" << weakestTerritory->getName() << "\" with " << weakestTerritory->getArmySize() << " army unit" << endl;
		Advance a = Advance(this->player, weakestTerritory->getArmySize(), weakestTerritory, this->toDefend()[0]);
		this->player->oList->add(&a);
		this->player->ArmyUnit -= this->player->ArmyUnit;
	}

	return true;
}


std::vector<Territory*> BenevolentPlayerStrategy::toAttack() {
	// Does NOT attack
	vector<Territory*> toAttack;

	return toAttack;
}

std::vector<Territory*> BenevolentPlayerStrategy::toDefend() {
	vector<Territory*> toDefend;

	Territory* weakestTerritory = this->player->getplayerOccupied()[0];

	for (Territory* t : this->player->getplayerOccupied()) {
		if (t->getArmySize() < weakestTerritory->getArmySize()) {
			weakestTerritory = t;
		}
	}

	// Returns the weakest territory so it can be defended
	toDefend.push_back(weakestTerritory);

	return toDefend;
}

ostream& operator<<(ostream& os, BenevolentPlayerStrategy& aggressivePlayerStrategy) {
	os << aggressivePlayerStrategy.player->getPlayerName() << "'s strategy is " << typeid(aggressivePlayerStrategy).name() << "\n";
	return os;
}

BenevolentPlayerStrategy& BenevolentPlayerStrategy::operator=(const BenevolentPlayerStrategy& c) {
	player = c.player;
	return *this;
};