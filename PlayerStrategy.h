#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Territory.h"
#include "Deck.h"
#include "Map.h"

class PlayerStrategy
{
public:
	// Issues a deploy order
	virtual void issueDeploy() = 0;

	// Issue an order
	virtual bool issueOrder(Deck* deck, Map* gameMap) = 0;

	// Retrieves the territories to defend
	virtual std::vector <Territory*> toDefend() = 0;

	// Retrieves the territories to attack
	virtual std::vector <Territory*> toAttack() = 0;
};