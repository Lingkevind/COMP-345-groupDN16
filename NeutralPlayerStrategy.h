#include <iostream>
#include <string>
#include <vector>
#include "Player.h"
#include "PlayerStrategy.h"


class NeutralPlayerStrategy : public PlayerStrategy
{
public:
	Player* player;
	NeutralPlayerStrategy(Player*);
	NeutralPlayerStrategy(const NeutralPlayerStrategy& c);
	friend ostream& operator<<(ostream& os, const NeutralPlayerStrategy& continent);

	NeutralPlayerStrategy& operator= (const NeutralPlayerStrategy& c);

	void issueDeploy();
	bool issueOrder(Deck* deck, Map* gameMap);

	std::vector <Territory*> toDefend();
	std::vector <Territory*> toAttack();
};
