#include <iostream>
#include <string>
#include <vector>
#include "Player.h"
#include "PlayerStrategy.h"

class AggressivePlayerStrategy : public PlayerStrategy 
{
public:
	Player* player;
	AggressivePlayerStrategy(Player*);
	AggressivePlayerStrategy(const AggressivePlayerStrategy& c);

	friend ostream& operator<<(ostream& os, const AggressivePlayerStrategy& continent);

	AggressivePlayerStrategy& operator= (const AggressivePlayerStrategy& c);


	void issueDeploy();
	bool issueOrder(Deck* deck, Map* gameMap);
	std::vector <Territory*> toDefend();
	std::vector <Territory*> toAttack();
};



