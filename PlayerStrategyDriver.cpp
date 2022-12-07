#include "GameEngine.h"
#include "CommandProcessing.h"
#include <windows.h>
#include "AggressivePlayerStrategy.h"
#include "NeutralPlayerStrategy.h"
#include "BenevolentPlayerStrategy.h"
#include "HumanPlayerStrategy.h"
#include "CheaterPlayerStrategy.h"
#include "Player.h"
#include "PlayerStrategyDriver.h"
#include <iostream>
#include "Deck.h"
#include "Map.h"
#include "Card.h"
#include "Continent.h"

int main()
{
	PlayerStrategyDriver* driver = new PlayerStrategyDriver();
	driver->testPlayerStrategies();
}

void PlayerStrategyDriver::testPlayerStrategies() {
	test_different_players_can_be_assigned_different_strategies_that_lead_to_different_behavior();
	test_strategy_adopted_by_a_player_can_be_changed_dynamically_during_play();
	test_Driver_that_demonstrates_that_the_human_player_makes_decisions_according_to_user_interaction();
}

void PlayerStrategyDriver::test_different_players_can_be_assigned_different_strategies_that_lead_to_different_behavior() {
	// Driver that demonstrates that different players can be assigned different strategies that lead to different behavior using the Strategy design pattern
	Player* joe = new Player("Joe");
	Player* steve = new Player("Steve");
	Player* bob = new Player("Bob");
	Player* chris = new Player("Chris");
	
	// Creating a deck of 1 useless card
	vector<Card> cards;
	cards.push_back(Card("useless card"));
	Deck* deck = new Deck(cards);

	// Setting the strategies for the 3 players
	joe->setStrategy(new AggressivePlayerStrategy(joe));
	bob->setStrategy(new BenevolentPlayerStrategy(bob));
	chris->setStrategy(new CheaterPlayerStrategy(chris));

	// Creating 4 territories controlled by joe and steve
	// Quebec is the strongest
	Territory* quebec = new Territory("Quebec");
	quebec->setArmySize(100);
	quebec->setControllingPlayer(joe);

	Territory* ontario = new Territory("Ontario");
	ontario->setArmySize(50);
	ontario->setControllingPlayer(joe);

	Territory* newBrunswick = new Territory("New Brunswick");
	newBrunswick->setArmySize(1);
	newBrunswick->setControllingPlayer(joe);

	Territory* vermont = new Territory("Vermont");
	vermont->setArmySize(1);
	vermont->setControllingPlayer(steve);
	quebec->addAjacentTerritory(vermont);

	// Creating a map with 1 continent containing 4 territories
	Map* map = new Map();
	Continent* northAmerica = new Continent("North America", 4);
	northAmerica->addTerritory(quebec);
	northAmerica->addTerritory(ontario);
	northAmerica->addTerritory(newBrunswick);
	northAmerica->addTerritory(vermont);

	map->addContinent(northAmerica);

	// Joe owns the 3 canadian provinces and deploys to Quebec since he's aggressive and Quebec is the strongest
	joe->occupy(quebec);
	joe->occupy(ontario);
	joe->occupy(newBrunswick);
	joe->setArmyUnit(12);
	joe->issueDeploy();

	// Asserting that the above statement is true
	if (assertEqual(std::to_string(quebec->getArmySize()), "112")) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 10);
		cout << "AggressivePlayerStrategy - deploy" << " -> SUCCESS" << endl;
		SetConsoleTextAttribute(hConsole, 15);
	}

	// Joe's order is to invade the weakest nearby adjacent territory with his strongest territory
	joe->issueOrder(deck, map);

	// Asserts that Joe invaded and took Vermont, which belonged to Steve
	if (assertEqual(vermont->getControllingPlayer()->getPlayerName(), "Joe")) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 10);
		cout << "AggressivePlayerStrategy - attack" << " -> SUCCESS" << endl;
		SetConsoleTextAttribute(hConsole, 15);
	}

	// Testing cheater player

	// A new province a created. It's a small one, but it's controlling player is surprisingly powerful

	Territory* princeEdwardIsland = new Territory("Prince Edward Island");
	princeEdwardIsland->setArmySize(1);
	princeEdwardIsland->setControllingPlayer(chris);
	princeEdwardIsland->addAjacentTerritory(vermont);
	princeEdwardIsland->addAjacentTerritory(quebec);
	princeEdwardIsland->addAjacentTerritory(ontario);
	princeEdwardIsland->addAjacentTerritory(newBrunswick);

	northAmerica->addTerritory(princeEdwardIsland);
	// Chris is a cheater and occupies P.E.I, whose adjacent territories are all 4 of the above
	chris->occupy(princeEdwardIsland);
	
	// Because he's a cheater, Chris automatically conquered it's adjacent territories.
	chris->issueOrder(deck, map);

	bool chrisOwned = true;
	for (Territory* t : map->getContinents()[0]->getTerritories()) {
		if (!assertEqual(t->getControllingPlayer()->getPlayerName(), "Chris")) {
			chrisOwned = false;
		}
	}

	// Asserting that the above statement is true.
	if (chrisOwned) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 10);
		cout << "CheaterPlayerStrategy" << " -> SUCCESS" << endl;
		SetConsoleTextAttribute(hConsole, 15);
	}
}

void PlayerStrategyDriver::test_strategy_adopted_by_a_player_can_be_changed_dynamically_during_play() {
	// Driver that demonstrates that the strategy adopted by a player can be changed dynamically during play

	// John and
	Player* mike = new Player("Mike");
	mike->setStrategy(new AggressivePlayerStrategy(mike));

	Player* john = new Player("John");

	john->setStrategy(new NeutralPlayerStrategy(john));

	Territory* patagonia = new Territory("Patagonia");
	patagonia->setControllingPlayer(john);

	// Since Mike attacked Patagonia and john was the owner, and also a neutral player
	// john now becomes aggressive.
	mike->occupy(patagonia);

	// Asserting that the above statement is true.
	if (assertEqual(typeid(*john->strategy).name(), typeid(AggressivePlayerStrategy).name())) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 10);
		cout << __FUNCTION__ << " -> SUCCESS" << endl;
		SetConsoleTextAttribute(hConsole, 15);
	}
}

void PlayerStrategyDriver::test_Driver_that_demonstrates_that_the_human_player_makes_decisions_according_to_user_interaction() {
	// John is a Human
	Player* john = new Player("John");
	john->setStrategy(new HumanPlayerStrategy(john));

	// Johns owns quebec with an army of 0
	Territory* quebec = new Territory("Quebec");
	quebec->setArmySize(0);
	quebec->setControllingPlayer(john);
	john->occupy(quebec);
	john->setArmyUnit(1);


	// John deploys 1 unit to Quebec. [requires human interaction at this point]
	john->issueDeploy();

	// Asserting that upon entering "1" then "Quebec" in the console, 1 army unit was deployed to Quebec (yay!)
	if (assertEqual(std::to_string(quebec->getArmySize()), "1")) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 10);
		cout << __FUNCTION__ << " -> SUCCESS" << endl;
		SetConsoleTextAttribute(hConsole, 15);
	}

}

// A simple method that receives an actual and expected string, compares them and outputs an error message if 
// the 2 strings are not equal.
bool PlayerStrategyDriver::assertEqual(string actual, string expected) {
	if (actual != expected) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 12);
		cout << "Test failed : actual was <" << actual << "> while expected was <" << expected << ">." << endl;
		SetConsoleTextAttribute(hConsole, 15);
		return false;
	}

	return true;
}



