#pragma once
#ifndef   GameEngine
#define   GameEngine
#include <string>
#include "CommandProcessing.h";
#include "player.h"


class StateController;
class CommandProcessor;

/*
***SECTION 1*****
Interface for different states of the game mode
Keeps reference to context to allow for transitioning to different states
*****************
*/

class StateInterface
{
public:
	StateController* context_;

	void set_context(StateController* context);
	virtual ~StateInterface();

	PlayerList pList;

	virtual void enterState	 (CommandProcessor* cp);
	virtual void executeState(CommandProcessor* cp);
	virtual void exitState	 (CommandProcessor* cp);
};


/***SECTION 2****
Interface for users
Keeps track of what subclass(state) we are currently in
*****************
*/
class StateController
{

public:

	StateInterface* currentState;
	PlayerList* pList;
	Deck* deck = NULL;
	Map* map = NULL;

	std::string currentStateName;

	//Once a state has completed execution, it will change its state 
	void TransitionTo(StateInterface* state);

	~StateController();

	//Holds a reference to whichever state we are currently in
	StateController(StateInterface* state, PlayerList* pList, Deck* d);


	/**
	* The Context delegates part of its behavior to the current State object.
	*/

	void enterState(CommandProcessor* cp);
	void executeState(CommandProcessor* cp);
	void exitState(CommandProcessor* cp);
	void mainGameLoop();

	void setStateName(std::string s);
	
	std::string getStateName();

	
};


/***SECTION 3****
The states in which the game goes through
StartState is the initial state
*****************
*/

class StartState : public StateInterface
{
	void enterState(CommandProcessor* cp) override;
	void executeState(CommandProcessor* cp) override;
	void exitState(CommandProcessor* cp) override;
};


class MapLoadState : public StateInterface
{
	void enterState(CommandProcessor* cp) override;
	void executeState(CommandProcessor* cp) override;
	void exitState(CommandProcessor* cp) override;

};


class MapValidatedState : public StateInterface
{
	void enterState(CommandProcessor* cp) override;
	void executeState(CommandProcessor* cp) override;
	void exitState(CommandProcessor* cp) override;

};



class PlayersAddedState : public StateInterface
{
	void enterState(CommandProcessor* cp) override;
	void executeState(CommandProcessor* cp) override;
	void exitState(CommandProcessor* cp) override;


};



class WinState : public StateInterface
{
	void enterState(CommandProcessor* cp) override;
	void executeState(CommandProcessor* cp) override;
	void exitState(CommandProcessor* cp) override;
};


class ReinforcementState : public StateInterface
{
	void enterState(CommandProcessor* cp) override;
	void reinforcement(Player *p);
	void executeState(CommandProcessor* cp) override;
	void exitState(CommandProcessor* cp) override;
};



class IssueOrderState : public StateInterface
{
	void enterState(CommandProcessor* cp) override;
	void IssueDeploy(Player p);
	void IssueAdvance(Player p);
	string CardPlayed(Player p);
	void IssueAirlift(Player p);
	void IssueBomb(Player p);
	void IssueBlockade(Player p);
	void IssueNegotiate(Player p);
	bool allArmyUsed();
	void executeState(CommandProcessor* cp) override;
	void exitState(CommandProcessor* cp) override;

};

class ExecuteOrderState : public StateInterface
{
	bool gameEnd();
	void enterState(CommandProcessor* cp) override;
	void executeState(CommandProcessor* cp) override;
	void exitState(CommandProcessor* cp) override;
};

#endif 

