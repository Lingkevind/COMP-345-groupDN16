#include <iostream>;
#include <cctype>;
#include <cstdlib>;
#include <string>


#include <iostream>
#include "Territory.h"
#include "Coord.h"
#include <map>
#include "MapLoader.h"
#include <windows.h> 
#include "Player.h"S


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

StateController::StateController(StateInterface* state) : currentState(nullptr) {
	this->TransitionTo(state);
};


StateController:: ~StateController() {
	delete currentState;
};





void StateController::TransitionTo(StateInterface* state)
{
	string stateName = typeid(*state).name();
	stateName = stateName.substr(6);
	//std::cout << stateName << endl;
	setStateName(stateName);

	std::cout << "Context: Transition to " << typeid(*state).name() << ".\n";
	if (this->currentState != nullptr)
	{
		delete this->currentState;
	}
	this->currentState = state;
	this->currentState->set_context(this);

};



void StateController::enterState(CommandProcessor* cp) {
	this->currentState->enterState(cp);
};

void StateController::executeState(CommandProcessor* cp) {
	this->currentState->executeState(cp);
};

void StateController::exitState(CommandProcessor* cp) {
	this->currentState->exitState(cp);
};



void StateController::setStateName(std::string s) {
	currentStateName = s;
};

std::string StateController::getStateName() {
	return currentStateName;
};


/*
******************SECTION 3******************
Defining methods for the StartState Class
**********************************************
*/


void StartState::enterState(CommandProcessor* cp)
{
	bool validCommand = false;
	std::cout << "***Welcome To StartState***" << std::endl;

	//Loop until we get valid command for the state 
	while (validCommand == false)
	{
		cp->getCommand();
		validCommand = cp->validate(this->context_->getStateName()); 
		int size = cp->commandCollection.size();
		if (validCommand == false) {
			cp->commandCollection.at(size - 1)->saveEffect("error in performing command");
		}
		else {
			cout << "Entered a valid command" << endl;
			cp->commandCollection.at(size - 1)->saveEffect("SUCCESS IN TRANSITIONING FROM startState");
		}
	}
};

void StartState::executeState(CommandProcessor* cp){

	cout << "The Valid Command For StartState Is Being executed..." << endl;


	int size = cp->commandCollection.size();
	string commandString = cp->commandCollection.at(size - 1)->getCommand();
	string mapName = "default";
	string effectMessage = "default";

	//Aquire just the map name without the command load
	char spaceCharacter = ' ';
	size_t found = commandString.find(spaceCharacter);
	mapName = commandString.substr(found);
	mapName.erase(mapName.find_last_not_of(" ") + 1);
	mapName.erase(0, mapName.find_first_not_of(" "));

	cout << "ATTEMPTING TO LOAD MAP: " << mapName << endl;

	//Load the Map 
	MapLoader* mapLoader = new MapLoader();
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	this->context_->gameMap = mapLoader->loadMap(mapName);

	//Map SUCCEED to loaded
	if (this->context_->gameMap != NULL)
	{
		cout << "SUCCESSFULLY LOADED MAP: " << mapName << endl;
		effectMessage = "SUCCESSFULLY LOADED MAP";
	}
	//Map FAILED to load
	else
	{
		cout << "FAILED TO LOADED MAP: " << mapName << endl;
		effectMessage = "FAILED TO LOADED MAP";
	}
	delete mapLoader;
	mapLoader = NULL;
	size = cp->commandCollection.size();
	cp->commandCollection.at(size - 1)->saveEffect(effectMessage);

};

void StartState::exitState(CommandProcessor* cp)
{
	this->context_->TransitionTo(new MapLoadState);
};



//******************SECTION 4******************
//Defining methods for the MapLoadState Class
//**********************************************


void MapLoadState::enterState(CommandProcessor* cp)
{
	cout << "***Welcome To MapLoadState***" << std::endl;

	bool validCommand = false;

	while (validCommand == false)
	{
		cp->getCommand();
		validCommand = cp->validate(this->context_->getStateName());
		int size = cp->commandCollection.size();

		if (validCommand == false) {
			cp->commandCollection.at(size - 1)->saveEffect("error in performing command");
		}
		else {
			cout << "Entered a valid command....Now executing command" << endl;
		}
	}
};

void MapLoadState::executeState(CommandProcessor* cp)
{
	cout << "The Valid Command For MapLoadState Is Being executed..." << endl;
	

	int size = cp->commandCollection.size();
	string commandString = cp->commandCollection.at(size - 1)->getCommand();


	if (commandString == "validatemap")
	{
		//Map meets all the validation requirements
		if (this->context_->gameMap->isMapConnectedSubgraph())
		{
			cout << "The Map you loaded is a valid." << endl;
			cp->commandCollection.at(size - 1)->saveEffect("The Map loaded is valid");

		}

		//Map does not meet all the validation requirements 
		else
		{
			cout << "The Map you loaded is not valid." << endl;
			cp->commandCollection.at(size - 1)->saveEffect("The Map loaded is NOT valid");
			//go back to load state and load another map
			this->context_->TransitionTo(new MapLoadState);


		}
	}

};

void MapLoadState::exitState(CommandProcessor* cp)
{
	cout << "The Valid Command For MapLoadState Has Been executed... " << endl;

	this->context_->TransitionTo(new MapValidatedState);
};




//******************SECTION 5******************
//Defining methods for the MapValidateState Class
//**********************************************


void MapValidatedState::enterState(CommandProcessor* cp)
{
	cout << "***Welcome To MapValidatedState***" << std::endl;

	bool validCommand = false;

	while (validCommand == false)
	{
		cp->getCommand();
		validCommand = cp->validate(this->context_->getStateName());
		int size = cp->commandCollection.size();

		if (validCommand == false) {
			cp->commandCollection.at(size - 1)->saveEffect("error in performing command");
		}
		else {
			cout << "Entered a valid command....Now executing command" << endl;
		}
	}
};

void MapValidatedState::executeState(CommandProcessor* cp)
{
	cout << "The Valid Command For MapValidateState Is Being executed..." << endl;


	int size = cp->commandCollection.size();
	string commandString = cp->commandCollection.at(size - 1)->getCommand();
	string playerName = "default";

	//GET THE PLAYER NAME FROM THE COMMAND
	if ((regex_match(commandString, regex("(addplayer )(.*)"))))
	{
		char spaceCharacter = ' ';
		// Find first occurrence of ' '
		size_t found = commandString.find(spaceCharacter);
		playerName = commandString.substr(found);
		playerName.erase(playerName.find_last_not_of(" \n\r\t") + 1);
		playerName.erase(0, playerName.find_first_not_of(" \n\r\t"));

		cout << "The Valid Command(addplayer) For PlayersAdded is being executed..." << endl;

		if (this->context_->playerCollection.size() < 6) 
		{
			this->context_->playerCollection.emplace_back(new Player(playerName));
			cout << playerName << " HAS BEEN ADDED" << endl;
		}
	}

	if (commandString == "gamestart" ) 
	{
	
	
	}



};

void MapValidatedState::exitState(CommandProcessor* cp)
{
	cout << "The Valid Command For MapValidatedState Has Been executed... " << endl;
	cout << "Transitioning to PlayersAddedState..." << endl;

	
	int size = cp->commandCollection.size();
	string latestCommand = cp->commandCollection.at(size - 1)->getCommand();
	
	if (latestCommand == "gamestart") 
	{
		this->context_->TransitionTo(new AssignReinforcementState);

	}

	this->context_->TransitionTo(new PlayersAddedState());

};



//******************SECTION 6******************
//Defining methods for the PlayersAddedState Class
//**********************************************



void PlayersAddedState::enterState(CommandProcessor* cp)
{
	cout << "***Welcome To PlayersAddedState***" << std::endl;

	bool validCommand = false;

	while (validCommand == false)
	{
		cp->getCommand();
		validCommand = cp->validate(this->context_->getStateName());
		int size = cp->commandCollection.size();

		if (validCommand == false) {
			cp->commandCollection.at(size - 1)->saveEffect("error in performing command");
		}
		else {
			cout << "Entered a valid command....Now executing command" << endl;
		}
	}
};

void PlayersAddedState::executeState(CommandProcessor* cp)
{
	int size = cp->commandCollection.size();
	string commandString = cp->commandCollection.at(size - 1)->getCommand();
	string playerName = "default";

	if ((regex_match(commandString, regex("(addplayer )(.*)"))))
	{
		char spaceCharacter = ' ';
		// Find first occurrence of ' '
		size_t found = commandString.find(spaceCharacter);
		playerName = commandString.substr(found);
		playerName.erase(playerName.find_last_not_of(" \n\r\t") + 1);
		playerName.erase(0, playerName.find_first_not_of(" \n\r\t"));

		cout << "The Valid Command(addplayer) For PlayersAdded is being executed..." << endl;
		//PART2 CODE HERE FOR ADD PLAYER
		//Please put appropriate message here 
		//cp->commandCollection.at(size - 1)->saveEffect("SUCCESSFUL!");

		cout << playerName << " HAS BEEN ADDED" << endl;
	

	}

	if (commandString == "gamestart")
	{
		cout << "The Valid Command(gamsestart) For PlayersAdded is being executed..." << endl;
		//PART2 CODE HERE FOR GAMESTART COMMAND
		//Please put appropriate message here 
		cp->commandCollection.at(size - 1)->saveEffect("SUCCESSFUL!");

	}




};

void PlayersAddedState::exitState(CommandProcessor* cp)
{
	cout << "The Valid Command For PlayersAdded Has Been executed... " << endl;



	int size = cp->commandCollection.size();
	string commandString = cp->commandCollection.at(size - 1)->getCommand();

	cout << "the latest command was: " << commandString << endl;

	if ((regex_match(commandString, regex("(addplayer )(.*)"))))
	{
		this->context_->TransitionTo(new PlayersAddedState);
	}

	else if (commandString == "gamestart") {
		this->context_->TransitionTo(new AssignReinforcementState);
	}

};



//******************SECTION 7******************
//Defining methods for the AssignReinforcementState Class
//**********************************************



void AssignReinforcementState::enterState(CommandProcessor* cp)
{
	cout << "***Welcome To AssignReinforcementState***" << std::endl;
};

void AssignReinforcementState::executeState(CommandProcessor* cp)
{
	cout << "The Valid Command For AssignReinforcementState Is Being executed..." << endl;

};

void AssignReinforcementState::exitState(CommandProcessor* cp)
{
	cout << "The Valid Command For AssignReinforcementState Has Been executed... " << endl;
	cout << "Transitioning to IssueOrderState..." << endl;


	this->context_->TransitionTo(new IssueOrderState());

};




//******************SECTION 8******************
//Defining methods for the IssueOrderState Class
//**********************************************


void IssueOrderState::enterState(CommandProcessor* cp)
{
	cout << "***Welcome To IssueOrderState***" << endl;
};


void IssueOrderState::executeState(CommandProcessor* cp)
{
	cout << "The Valid Command For IssueOrderState Is Being executed..." << endl;

};

void IssueOrderState::exitState(CommandProcessor* cp)
{
	cout << "The Valid Command For IssueOrderState Has Been executed... " << endl;
	this->context_->TransitionTo(new ExecuteOrderState());
};



//******************SECTION 9******************
//Defining methods for the ExecuteOrderState Class
//**********************************************

void ExecuteOrderState::enterState(CommandProcessor* cp)
{
	cout << "***Welcome To ExecuteOrderState***" << std::endl;


};

void ExecuteOrderState::executeState(CommandProcessor* cp)
{
	cout << "The Valid Command For ExecuteOrderState Is Being executed...";

};

void ExecuteOrderState::exitState(CommandProcessor* cp)
{
	cout << "The Valid Command For ExecuteOrderState Has Been executed... " << endl;
	this->context_->TransitionTo(new WinState);
};



//******************SECTION 10******************
//Defining methods for the WinState Class
//**********************************************

void WinState::enterState(CommandProcessor* cp)
{
	cout << "***Welcome To WinState***" << std::endl;


	bool validCommand = false;

	while (validCommand == false)
	{
		cp->getCommand();
		validCommand = cp->validate(this->context_->getStateName());
		int size = cp->commandCollection.size();

		if (validCommand == false) {
			cp->commandCollection.at(size - 1)->saveEffect("error in performing command");
		}
		else {
			cout << "Entered a valid command....Now executing command" << endl;
		}
	}
};

void WinState::executeState(CommandProcessor* cp)
{
	cout << "The Valid Command For WinState Is Being executed...";
	int size = cp->commandCollection.size();
	cp->commandCollection.at(size - 1)->saveEffect("SUCCESSFUL!");

};

void WinState::exitState(CommandProcessor* cp)
{
	cout << "The Valid Command For WinState Has Been executed... " << endl;

	int size = cp->commandCollection.size();
	string commandString = cp->commandCollection.at(size - 1)->getCommand();

	cout << "the latest command was: " << commandString << endl;

	if (commandString == "quit")
	{
		cout << "GAME OVER , EXITING...." << endl;
		int x = 5;
		cin >> x;
	}

	else if (commandString == "replay") {
		this->context_->TransitionTo(new StartState);
	}

};


