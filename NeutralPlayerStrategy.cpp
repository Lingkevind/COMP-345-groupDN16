#include <fstream>
#include <string>
#include <vector>
#include "LoggingObserver.h"
#include "PlayerStrategy.h"
#include "NeutralPlayerStrategy.h"

using namespace std;

NeutralPlayerStrategy::NeutralPlayerStrategy(Player* p) {
	this->player = p;
}

NeutralPlayerStrategy::NeutralPlayerStrategy(const NeutralPlayerStrategy& c) {
	player = c.player;
}



void NeutralPlayerStrategy::issueDeploy() {
	// The neutral player divides its units equally among its territories
	int ownedTerritoriesCount = this->player->getplayerOccupied().size();

	int unitPerTerritory = this->player->ArmyUnit / ownedTerritoriesCount;
	int remaining = this->player->ArmyUnit % ownedTerritoriesCount;

	for (int i = 0; i < ownedTerritoriesCount; i++) {
		Deploy d = Deploy(this->player, unitPerTerritory, this->player->getplayerOccupied()[i]);
		this->player->ArmyUnit -= unitPerTerritory;
		this->player->getplayerOccupied()[i]->setArmySize(this->player->getplayerOccupied()[i]->getArmySize() + unitPerTerritory);
		this->player->oList->add(&d);

		cout << "Neutral player deployed " << unitPerTerritory << "unit to " << this->player->getplayerOccupied()[i]->getName() << "." << endl;
	}

	// Deploying the rest to the first territory
	if (remaining > 0) {
		Deploy d = Deploy(this->player, remaining, this->player->getplayerOccupied()[0]);
		this->player->ArmyUnit -= remaining;
		this->player->getplayerOccupied()[0]->setArmySize(this->player->getplayerOccupied()[0]->getArmySize() + remaining);
		this->player->oList->add(&d);
		cout << "Neutral player deployed " << remaining << "unit to " << this->player->getplayerOccupied()[0]->getName() << "." << endl;
	}
}

bool NeutralPlayerStrategy::issueOrder(Deck* deck, Map* map) {
	cout << "Neutral player just skipped its turn." << endl;
	return true;
}

std::vector<Territory*> NeutralPlayerStrategy::toAttack() {
	vector<Territory*> toAttack;

	return toAttack;
}

std::vector<Territory*> NeutralPlayerStrategy::toDefend() {
	vector<Territory*> toDefend;

	return toDefend;
}

ostream& operator<<(ostream& os, NeutralPlayerStrategy& aggressivePlayerStrategy) {
	os << aggressivePlayerStrategy.player->getPlayerName() << "'s strategy is " << typeid(aggressivePlayerStrategy).name() << "\n";
	return os;
}

NeutralPlayerStrategy& NeutralPlayerStrategy::operator=(const NeutralPlayerStrategy& c) {
	player = c.player;
	return *this;
};