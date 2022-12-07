#pragma once
#ifndef   GameEngine_h
#define   GameEngine_h
#include <string>
#include "CommandProcessing.h"
#include "Player.h"
#include "Territory.h"
#include "Coord.h"
#include "MapLoader.h"
#include <windows.h> 
#include "Orders.h"
#include <iostream>
#include "Territory.h"
#include "Coord.h"
#include "Tournament.h"
#include <map>
#include <windows.h> 
#include <iomanip>

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


	virtual void enterState(CommandProcessor* cp)	= 0;
	virtual void executeState(CommandProcessor* cp) = 0;
	virtual void exitState(CommandProcessor* cp)	= 0;
};


/***SECTION 2****
Interface for users
Keeps track of what subclass(state) we are currently in
*****************
*/
class StateController
{

public:
	Tournament* t= new Tournament();
	bool tournamentMode = false;
	StateInterface* currentState;
	Deck deck = Deck();
	std::string currentStateName;

	Map* gameMap = NULL;

	vector <Player*> playerCollection;		//vector of command objects 


	//Once a state has completed execution, it will change its state 
	void TransitionTo(StateInterface* state);

	~StateController();

	//Holds a reference to whichever state we are currently in
	StateController(StateInterface* state);


	/**
	* The Context delegates part of its behavior to the current State object.
	*/
	Player findPlayerbyName(string name, vector<Player*> Plist); 
	void enterState(CommandProcessor* cp);
	void executeState(CommandProcessor* cp);
	void exitState(CommandProcessor* cp);

	void setStateName(std::string s);

	std::string getStateName();

	int startupphase = 0;


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


class ReinforcementState : public StateInterface
{
	void pushPlayer();
	void enterState(CommandProcessor* cp) override;
	void reinforcement(Player *p);
	void executeState(CommandProcessor* cp) override;
	void exitState(CommandProcessor* cp) override;
};



class IssueOrderState : public StateInterface
{
	void enterState(CommandProcessor* cp) override;
	void IssueDeploy(Player *p);
	void IssueAdvance(Player *p);
	string CardPlayed(Player *p);
	void IssueAirlift(Player *p);
	void IssueBomb(Player *p);
	void IssueBlockade(Player *p);
	void IssueNegotiate(Player *p);
	bool allArmyUsed();
	void executeState(CommandProcessor* cp) override;
	void exitState(CommandProcessor* cp) override;

};

class ExecuteOrderState : public StateInterface
{
	void enterState(CommandProcessor* cp) override;
	bool gameEnd();
	bool finishExecute();
	void executeState(CommandProcessor* cp) override;
	void checkFailedPlayer();
	void makePlayerFail(string pName, vector<Player*>& pList);
	void exitState(CommandProcessor* cp) override;
};


class WinState : public StateInterface
{
	void enterState(CommandProcessor* cp) override;
	void executeState(CommandProcessor* cp) override;
	void exitState(CommandProcessor* cp) override;
};

class TournamentState : public StateInterface {
	//get the substring inside the M bracket convert the string into map list 
	void convertM(string m);
	//get the substring inside the P bracket convert the string into player list 
	void convertP(string p);
	void enterState(CommandProcessor* cp) override;
	//The win ends if only one player left
	bool checkWin();
	void play();
	//runs multiple time of plays() and returns the game result as string
	string run(int gameCount);
	void executeState(CommandProcessor* cp) override;
	//print the result table 
	void displayResult();
	void exitState(CommandProcessor* cp) override;
};

#endif 
