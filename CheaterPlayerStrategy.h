#include <iostream>
#include <string>
#include <vector>
#include "Player.h"
#include "PlayerStrategy.h"

class CheaterPlayerStrategy : public PlayerStrategy
{
public:
	Player* player;
	CheaterPlayerStrategy(Player*);
	CheaterPlayerStrategy(const CheaterPlayerStrategy& c);
	friend ostream& operator<<(ostream& os, const CheaterPlayerStrategy& continent);

	CheaterPlayerStrategy& operator= (const CheaterPlayerStrategy& c);


	void issueDeploy();
	bool issueOrder(Deck* deck, Map* gameMap);
	std::vector <Territory*> toDefend();
	std::vector <Territory*> toAttack();
};



