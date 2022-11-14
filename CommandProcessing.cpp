#include <iostream>;
#include <cctype>;
#include <cstdlib>;
#include <string>

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

/*
	Each state class, has 3 state methods. enterState, executeState, exitState

	The purpose of enterState is to greet the player with the current state we are in.
	Afterwards, it will keep asking for a command from the user until it gets the valid command for the state.

	The purpose of executeState is to perform the execution of the command. Some states do not perform any action but transition
	to the next state. Example, the StartState, it will get the mapload command and just transition to the mapload state(happens in exitState)
	Once a command has been executed, the effect of it is saved.

	The purpose of exitState is to perform the action that transitions to the next state.

*/



void StartState::enterState(CommandProcessor* cp)
{
	std::cout << "***Welcome To StartState***" << std::endl;

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
			cout << "Entered a valid command" << endl;
		}
	}
};

void StartState::executeState(CommandProcessor* cp)
{
	cout << "The Valid Command For StartState Is Being executed..." << endl;
};

void StartState::exitState(CommandProcessor* cp)
{
	cout << "The Valid Command For StartState Has Been executed... " << endl;

	int size = cp->commandCollection.size();
	cp->commandCollection.at(size - 1)->saveEffect("SUCCESSFUL!");

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
	string mapName = "default";


	if ((regex_match(commandString, regex("(loadmap )(.*)"))))
	{
		char spaceCharacter = ' ';
		// Find first occurrence of ' '
		size_t found = commandString.find(spaceCharacter);
		mapName = commandString.substr(found);
		mapName.erase(mapName.find_last_not_of(" ") + 1);
		mapName.erase(0, mapName.find_first_not_of(" "));

		cout << mapName << " IS GOING TO BE LOADED " << endl;


		//PART 2 CODE HERE 
		//SAVE EFFECT HERE 
		//int size = cp->commandCollection.size();
		//cp->commandCollection.at(size - 1)->saveEffect("YOUR MESSAGE");

	}

	if (commandString == "validatemap")
	{
		cout << "YOU ARE HAPPY WITH THE MAP YOU LOADED " << endl;
	}




};

void MapLoadState::exitState(CommandProcessor* cp)
{
	cout << "The Valid Command For MapLoadState Has Been executed... " << endl;

	//Get last command to see if we are re-entering MapLoadState or entering MapValidatedState

	int size = cp->commandCollection.size();
	string commandString = cp->commandCollection.at(size - 1)->getCommand();



	cout << "the latest command was: " << commandString << endl;

	if ((regex_match(commandString, regex("(loadmap )(.*)"))))
	{
		this->context_->TransitionTo(new MapLoadState);
	}

	else if (commandString == "validatemap") {
		this->context_->TransitionTo(new MapValidatedState);
	}


};




//******************SECTION 5******************
//Defining methods for the MapValidateState Class
//**********************************************


void MapValidatedState::enterState(CommandProcessor* cp)
{
	cout << "***Welcome To MapValidatedState***" << std::endl;


};

void MapValidatedState::executeState(CommandProcessor* cp)
{
	cout << "The Valid Command For MapValidateState Is Being executed..." << endl;

	int size = cp->commandCollection.size();
	string commandString = cp->commandCollection.at(size - 1)->getCommand();


	//PART2 CODE GOES HERE TO VALIDATE THE MAP
	//SAVE EFFECT HERE 
	//cp->commandCollection.at(size - 1)->saveEffect("YOUR MESSAGE");



};

void MapValidatedState::exitState(CommandProcessor* cp)
{
	cout << "The Valid Command For MapValidatedState Has Been executed... " << endl;


	//get transition to go to addplayerstate

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
			cp->commandCollection.at(size - 1)->saveEffect("SUCCESS");
		}
	}

	cout << "Transitioning to PlayersAddedState..." << endl;
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

string CommandProcessor::StringToLog() {
	Command* latestCommand = this->commandCollection[this->commandCollection.size() - 1];
	return "Command : " + latestCommand->commandName
		+ "\nCommand's effect : " + latestCommand->effectName;
}

string StateController::StringToLog() {
	return "Game engine's new state : " + this->currentStateName;
}
