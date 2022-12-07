#include <iostream>
#include <string>
#include <vector>
#include "Player.h"
#include "PlayerStrategy.h"



class PlayerStrategyDriver {
public:
	void testPlayerStrategies();

	void test_different_players_can_be_assigned_different_strategies_that_lead_to_different_behavior();

	void test_strategy_adopted_by_a_player_can_be_changed_dynamically_during_play();

	void test_Driver_that_demonstrates_that_the_human_player_makes_decisions_according_to_user_interaction();

	bool assertEqual(string, string);
};
