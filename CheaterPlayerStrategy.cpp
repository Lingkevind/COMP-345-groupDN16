#include <fstream>
#include <string>
#include <vector>
#include "LoggingObserver.h"
#include "PlayerStrategy.h"
#include "CheaterPlayerStrategy.h"

using namespace std;

CheaterPlayerStrategy::CheaterPlayerStrategy(Player* p) {
	this->player = p;
}

CheaterPlayerStrategy::CheaterPlayerStrategy(const CheaterPlayerStrategy& c) {
	player = c.player;
}

void CheaterPlayerStrategy::issueDeploy() {
	// Cheater player equally allocates unit to each territories
	int ownedTerritoriesCount = this->player->getplayerOccupied().size();

	int unitPerTerritory = this->player->ArmyUnit / ownedTerritoriesCount;
	int remaining = this->player->ArmyUnit % ownedTerritoriesCount;

	for (int i = 0; i < ownedTerritoriesCount; i++) {
		Deploy d = Deploy(this->player, unitPerTerritory, this->player->getplayerOccupied()[i]);
		this->player->ArmyUnit -= unitPerTerritory;
		this->player->getplayerOccupied()[i]->setArmySize(this->player->getplayerOccupied()[i]->getArmySize() + unitPerTerritory);
		this->player->oList->add(&d);

		cout << "Cheater player deployed " << unitPerTerritory << "unit to " << this->player->getplayerOccupied()[i]->getName() << "." << endl;
	}

	// Deploying the rest to the first territory
	if (remaining > 0) {
		Deploy d = Deploy(this->player, remaining, this->player->getplayerOccupied()[0]);
		this->player->ArmyUnit -= remaining;
		this->player->getplayerOccupied()[0]->setArmySize(this->player->getplayerOccupied()[0]->getArmySize() + remaining);
		this->player->oList->add(&d);
		cout << "Cheater player deployed " << remaining << "unit to " << this->player->getplayerOccupied()[0]->getName() << "." << endl;
	}
}

bool CheaterPlayerStrategy::issueOrder(Deck* deck, Map* map) {
	// The cheater hijacks every adjacent territory without spending any unit (what a scumbag).
	for (int i = 0; i < this->player->getAvailableToMoveTo().size(); i++) {
		this->player->getAvailableToMoveTo()[i]->setControllingPlayer(this->player);
		cout << "Cheater player just hijacked " << this->player->getAvailableToMoveTo()[i]->getName() <<
			" by corrupting " << this->player->getAvailableToMoveTo()[i]->getArmySize() << " soldiers" << endl;
		this->player->occupy(this->player->getAvailableToMoveTo()[i]);
	}

	return true;
}

std::vector<Territory*> CheaterPlayerStrategy::toAttack() {
	vector<Territory*> toAttack;

	Territory* mostConcentratedTerritory = this->player->getplayerOccupied()[0];

	for (int i = 0; i < this->player->getplayerOccupied().size(); i++) {
		if (this->player->getplayerOccupied()[i]->getArmySize() > mostConcentratedTerritory->getArmySize()) {
			mostConcentratedTerritory = this->player->getplayerOccupied()[i];
		}
	}

	toAttack.push_back(mostConcentratedTerritory);

	return toAttack;
}

std::vector<Territory*> CheaterPlayerStrategy::toDefend() {
	vector<Territory*> toDefend;

	return toDefend;
}

ostream& operator<<(ostream& os, CheaterPlayerStrategy& aggressivePlayerStrategy) {
	os << aggressivePlayerStrategy.player->getPlayerName() << "'s strategy is " << typeid(aggressivePlayerStrategy).name() << "\n";
	return os;
}

CheaterPlayerStrategy& CheaterPlayerStrategy::operator=(const CheaterPlayerStrategy& c) {
	player = c.player;
	return *this;
};
