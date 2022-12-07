#include <iostream>
#include <string>
#include <vector>
#include "Player.h"
#include "PlayerStrategy.h"


class HumanPlayerStrategy : public PlayerStrategy
{
public:
	Player* player;
	HumanPlayerStrategy(Player*);
	HumanPlayerStrategy(const HumanPlayerStrategy& c);
	friend ostream& operator<<(ostream& os, const HumanPlayerStrategy& continent);

	HumanPlayerStrategy& operator= (const HumanPlayerStrategy& c);


	void issueDeploy();
	bool issueOrder(Deck* deck, Map* gameMap);

	std::vector <Territory*> toDefend();
	std::vector <Territory*> toAttack();
};
