#pragma once
#ifndef   GameEngine
#define   GameEngine


 class StateController;

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
	virtual void UpdateState() = 0;
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

	 //Calls the starting state of the game. 
	 void Initialize();

	 //Each game state will modify the game slightly. 
	 void Update();

	 //Once a state has completed execution, it will change its state 
	 void TransitionTo(StateInterface* state);

	 //Destructor
	 ~StateController();

	 //Holds a reference to whichever state we are currently in
	 StateController(StateInterface* state);


	 /**
     * The Context delegates part of its behavior to the current State object.
     */
	 void UpdateState();
 };


/***SECTION 3****
The states in which the game goes through
StartState is the initial state
*****************
*/

class StartState : public StateInterface 
{
  void UpdateState() override; 
};


class MapLoadState				: public StateInterface 
{
	void UpdateState() override;
};


class MapValidatedState			: public StateInterface
{
	void UpdateState() override;
};


class PlayersAddedState			: public StateInterface 
{
	void UpdateState() override;

};

class AssignReinforcementState	: public StateInterface 
{
	void UpdateState() override;
};

class IssueOrderState			: public StateInterface 
{
	void UpdateState() override;
};

class ExecuteOrderState			: public StateInterface 
{
	void UpdateState() override;
};

class WinState					: public StateInterface 
{
	void UpdateState() override;
};



#endif 

