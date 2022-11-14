#pragma once
#ifndef   GameEngine
#define   GameEngine
#include <string>
#include "CommandProcessing.h";


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


	virtual void enterState(CommandProcessor* cp) = 0;
	virtual void executeState(CommandProcessor* cp) = 0;
	virtual void exitState(CommandProcessor* cp) = 0;
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

	std::string currentStateName;

	//Once a state has completed execution, it will change its state 
	void TransitionTo(StateInterface* state);

	~StateController();

	//Holds a reference to whichever state we are currently in
	StateController(StateInterface* state);


	/**
	* The Context delegates part of its behavior to the current State object.
	*/

	void enterState(CommandProcessor* cp);
	void executeState(CommandProcessor* cp);
	void exitState(CommandProcessor* cp);

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


class AssignReinforcementState : public StateInterface
{
	void enterState(CommandProcessor* cp) override;
	void executeState(CommandProcessor* cp) override;
	void exitState(CommandProcessor* cp) override;
};



class IssueOrderState : public StateInterface
{
	void enterState(CommandProcessor* cp) override;
	void executeState(CommandProcessor* cp) override;
	void exitState(CommandProcessor* cp) override;

};

class ExecuteOrderState : public StateInterface
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




#endif 
