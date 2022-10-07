#include <iostream>;
#include <cctype>;
#include <cstdlib>;


using namespace std;
#include "GameEngine.h";

/*
******************SECTION 1******************
Defining methods for the StateInterface Class
*********************************************
*/

void StateInterface::set_context(StateController* context)
{
	this->context_ = context;
};

StateInterface::~StateInterface() = default;

/*
******************SECTION 2******************
Defining methods for the StateController Class
**********************************************
*/

void StateController::Initialize()
{
	currentState = new StartState();
};

StateController::StateController(StateInterface* state) : currentState(nullptr) {
	this->TransitionTo(state);
}


StateController:: ~StateController()
{
	delete currentState;
};


void StateController::TransitionTo(StateInterface* state)
{
	std::cout << "Context: Transition to " << typeid(*state).name() << ".\n";
	if (this->currentState != nullptr)
	{
		delete this->currentState;
	}
	this->currentState = state;
	this->currentState->set_context(this);

};

void StateController::UpdateState() {
	this->currentState->UpdateState();
}

/*
******************SECTION 3******************
Defining methods for the StartState Class
**********************************************
*/


void StartState::UpdateState() 
{
	std::cout << "***Welcome To Our VideoGame***" << std::endl;
	std::string v_userInputLoadMap;
	do
	{
		std::cout << "Type loadmap to enter to the MapLoad State" << std::endl;
		std::cin >> v_userInputLoadMap;

	
	} while (v_userInputLoadMap != "loadmap");

//Game switches state 
	
		this->context_->TransitionTo(new MapLoadState);
	
};


/*
******************SECTION 4******************
Defining methods for the MapLoadState Class
**********************************************
*/

void MapLoadState::UpdateState()
{
	std::cout << "***Welcome To MapLoadState***" << std::endl;
	std::string v_userInput = "";

//Determine which state to go to
	do
	{
		std::cout << "Type loadmap to re-execute the MapLoad State OR Type validatemap to enter the MapValidated State" << std::endl;
		std::cin >> v_userInput;
	} while (v_userInput != "loadmap" && v_userInput != "validatemap");

//Go To MapLoadState
	if (v_userInput == "loadmap")
	{
		this->context_->TransitionTo(new MapLoadState);
	}
//Go To ValidateMapState
	else if (v_userInput == "validatemap")
	{
		this->context_->TransitionTo(new MapValidatedState);
	}

};

/*
******************SECTION 5******************
Defining methods for the MapValidateState Class
**********************************************
*/


void MapValidatedState::UpdateState()
{
	std::cout << "***Welcome To MapValidated State***" << std::endl;
	std::string v_userInput = "";

	//Determine which state to go to
	do
	{
		std::cout << "Type addplayer to enter the PlayersAdded State" << std::endl;
		std::cin >> v_userInput;
	} while (v_userInput != "addplayer" );

	//Go To PlayersAddedState
	this->context_->TransitionTo(new PlayersAddedState);
};

/*
******************SECTION 6******************
Defining methods for the PlayersAddedState Class
**********************************************
*/

void PlayersAddedState::UpdateState()
{
	std::cout << "***Welcome To The PlayersAdded State***" << std::endl;
	std::string v_userInput = "";

	//Determine which state to go to
	do
	{
		std::cout << "Type addplayer to re-execute the PlayersAddedState State OR Type assigncountries to enter the AssignReinforcement State" << std::endl;
		std::cin >> v_userInput;
	} while (v_userInput != "addplayer" && v_userInput != "assigncountries");

	//Go To PlayersAddedState
	if (v_userInput == "addplayer")
	{
		this->context_->TransitionTo(new PlayersAddedState);
	}
	//Go To AssignReinforcementState
	else if (v_userInput == "assigncountries")
	{
		this->context_->TransitionTo(new AssignReinforcementState);
	}

};


/*
******************SECTION 7******************
Defining methods for the AssignReinforcementState Class
**********************************************
*/

void AssignReinforcementState::UpdateState()
{
	std::cout << "***Welcome To The AssignReinforcement State***" << std::endl;
	std::string v_userInput = "";

	//Determine which state to go to
	do
	{
		std::cout << "Type issueorder to enter the IssueOrders State" << std::endl;
		std::cin >> v_userInput;
	} while (v_userInput != "issueorder");

	//Go To IssueOrder State
	this->context_->TransitionTo(new IssueOrderState);
};

/*
******************SECTION 8******************
Defining methods for the IssueOrderState Class
**********************************************
*/

void IssueOrderState::UpdateState()
{
	std::cout << "***Welcome To The IssueOrder State***" << std::endl;
	std::string v_userInput = "";

	//Determine which state to go to
	do
	{
		std::cout << "Type issueorder to re-execute the IssueOrders State OR Type endissueorders to enter ExecuteOrders State" << std::endl;
		std::cin >> v_userInput;
	} while (v_userInput != "issueorder" && v_userInput!= "endissueorders");

	//Go To IssueOrderState
	if (v_userInput == "issueOrder")
	{
		this->context_->TransitionTo(new IssueOrderState);
	}
	//Go To ExecuteOrderState
	else if (v_userInput == "endissueorders")
	{
		this->context_->TransitionTo(new ExecuteOrderState);
	}
};

/*
******************SECTION 9******************
Defining methods for the ExecuteOrderState Class
**********************************************
*/


void ExecuteOrderState::UpdateState()
{
	std::cout << "***Welcome To The ExecuteOrder State***" << std::endl;
	std::string v_userInput = "";

	//Determine which state to go to
	do
	{
		std::cout << "Type execorder to re-execute the ExecuteOrder State OR Type endexecorders to enter AssignReinforcement  State OR Type win to enter Win State" << std::endl;
		std::cin >> v_userInput;
	} while (v_userInput != "execorder" && v_userInput != "endexecorders" && v_userInput != "win");

	//Go To ExecuteOrderState
	if (v_userInput == "execorder")
	{
		this->context_->TransitionTo(new ExecuteOrderState);
	}
	//Go To AssignReinforcementState
	else if (v_userInput == "endexecorders")
	{
		this->context_->TransitionTo(new AssignReinforcementState);
	}
	//Go To WinState
	else if (v_userInput == "win")
	{
		this->context_->TransitionTo(new WinState);
	}
};

/*
******************SECTION 10******************
Defining methods for the WinState Class
**********************************************
*/

void WinState::UpdateState()
{
	std::cout << "***Welcome To The Win State***" << std::endl;
	std::string v_userInput = "";

	//Determine which state to go to
	do
	{
		std::cout << "Type win to end the game OR Type play to enter Start State" << std::endl;
		std::cin >> v_userInput;
	} while (v_userInput != "win" && v_userInput != "play");

	//End Game
	if (v_userInput == "win")
	{
		std::cout << "Congrats the game is over! System terminating!" << std::endl;
	}
	//Go to StartState
	else if (v_userInput == "play")
	{
		this->context_->TransitionTo(new StartState);
	}
};









