#include <iostream>
#include <string>
#include <vector>
#include "Player.h"
#include "PlayerStrategy.h"


class BenevolentPlayerStrategy : public PlayerStrategy
{
public:
	Player* player;
	BenevolentPlayerStrategy(const BenevolentPlayerStrategy& c);

	friend ostream& operator<<(ostream& os, const BenevolentPlayerStrategy& continent);

	BenevolentPlayerStrategy& operator= (const BenevolentPlayerStrategy& c);

	BenevolentPlayerStrategy(Player*);

	void issueDeploy();
	bool issueOrder(Deck* deck, Map* gameMap);

	std::vector <Territory*> toDefend();
	std::vector <Territory*> toAttack();
};
