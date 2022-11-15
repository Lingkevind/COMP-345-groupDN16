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

StateController::StateController(StateInterface* state, PlayerList* pList, Deck* d) : currentState(nullptr) {
	this->TransitionTo(state);
	this->pList = pList;
	this->deck = d;
};


StateController:: ~StateController(){
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
	cout << "The Valid Command For StartState Is Being executed..."<<endl;
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
	cp->commandCollection.at(size - 1)->saveEffect("SUCCESSFUL!");

	//PART 2 CODE HERE 
	//SAVE EFFECT HERE 
	//int size = cp->commandCollection.size();
    //cp->commandCollection.at(size - 1)->saveEffect("YOUR MESSAGE");
};

void MapLoadState::exitState(CommandProcessor* cp)
{
	cout << "The Valid Command For MapLoadState Has Been executed... " << endl;

	//Get last command to see if we are re-entering MapLoadState or entering MapValidatedState

	int size			 = cp->commandCollection.size();
	string commandString = cp->commandCollection.at(size - 1)->getCommand();



	cout << "the latest command was: " << commandString <<endl;

	if (commandString == "loadmap")
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
	cp->commandCollection.at(size - 1)->saveEffect("SUCCESSFUL!");

	//PART 2 CODE HERE 
	//SAVE EFFECT HERE 
	//int size = cp->commandCollection.size();
	//cp->commandCollection.at(size - 1)->saveEffect("YOUR MESSAGE");
};

void MapValidatedState::exitState(CommandProcessor* cp)
{
	cout << "The Valid Command For MapValidatedState Has Been executed... " << endl;
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
	string command = cp->commandCollection.at(size - 1)->getCommand();

	if (command == "addplayer") 
	{
		cout << "The Valid Command(addplayer) For PlayersAdded is being executed..." << endl;
		//PART2 CODE HERE FOR ADD PLAYER
	
	}

	if (command == "gamestart") 
	{
		cout << "The Valid Command(gamsestart) For PlayersAdded is being executed..." << endl;
		//PART2 CODE HERE FOR GAMESTART COMMAND

	}


	//Please put appropriate message here 
	cp->commandCollection.at(size - 1)->saveEffect("SUCCESSFUL!");


};

void PlayersAddedState::exitState(CommandProcessor* cp)
{
	cout << "The Valid Command For PlayersAdded Has Been executed... " << endl;



	int size = cp->commandCollection.size();
	string commandString = cp->commandCollection.at(size - 1)->getCommand();

	cout << "the latest command was: " << commandString << endl;

	if (commandString == "addplayer")
	{
		this->context_->TransitionTo(new PlayersAddedState);
	}

	else if (commandString == "gamestart") {
		this->context_->TransitionTo(new ReinforcementState);
	}

};

void ReinforcementState::enterState(CommandProcessor* cp)
{
	cout << "Begin reinforcement" << std::endl;
};

void ReinforcementState::reinforcement(Player* p) {
	int army =  p->getplayerOccupied().size() / 3;
	cout << p->getPlayerName()<<" obtained "<<army<<" from their territories.";
	p->ArmyUnit += army;
};


void ReinforcementState::executeState(CommandProcessor* cp)
{
	for (int i = 0; i < this->context_->pList->list.size();i++) {
		reinforcement(&this->context_->pList->findPlayer(i));
	}
};


void ReinforcementState::exitState(CommandProcessor* cp)
{
	this->context_->TransitionTo(new IssueOrderState());

};

void IssueOrderState::enterState(CommandProcessor* cp)
{
	cout << "Begin creating order" << endl;
};

void IssueOrderState::IssueDeploy(Player p) {
	cout << p.getPlayerName() << ", please enter the amount of army you want to deploy, you have "<<p.ArmyUnit<<" undeployed unit" << endl;
	int* army;
	cin >> *army;
	cout << "please enter the target territory you wish to deploy." << endl;
	string tName;
	cin >> tName;
	Territory* t = this->context_->map->findTerritorybyName(tName);
	Deploy d = Deploy(&p, *army, t);
	p.oList.add(&d);
};

void IssueOrderState::IssueAdvance(Player p) {
	cout << p.getPlayerName() << ", please enter the territory you want to move from." << endl;
	string* tName;
	cin >> *tName;
	Territory* from = this->context_->map->findTerritorybyName(*tName);
	cout << "please enter the amount of army you want to move." << endl;
	int* army;
	cin >> *army;
	cout << "please enter the territory you want to move to." << endl;;
	cin >> *tName;
	Territory* to = this->context_->map->findTerritorybyName(*tName);
	Advance a = Advance(&p, *army, from, to);
	p.oList.add(&a);

};

string IssueOrderState::CardPlayed(Player p) {
	cout << p.getPlayerName()<<", please enter the index of the card you wanna play, enter 0 to skip.";
	int* index;
	cin >> *index;
	if (*index = 0) {
		return NULL;
	}
	else {
		string card = p.playerHand->playCards(*index - 1, *this->context_->deck);
		return card;
	}
};

void IssueOrderState::IssueAirlift(Player p) {
	cout << p.getPlayerName() << ", please enter the territory you want to lift from." << endl;
	string* tName;
	cin >> *tName;
	Territory* from = this->context_->map->findTerritorybyName(*tName);
	cout << "please enter the amount of army you want to move." << endl;
	int* army;
	cin >> *army;
	cout << "please enter the territory you want to drop to." << endl;;
	cin >> *tName;
	Territory* to = this->context_->map->findTerritorybyName(*tName);
	Airlift a=Airlift(&p,*army,from,to);
	p.oList.add(&a);
};

void IssueOrderState::IssueBomb(Player p) {
	cout << p.getPlayerName() << ", please enter the territory you want to place tha bomb." << endl;
	string* tName;
	Territory* target = this->context_->map->findTerritorybyName(*tName);
	Bomb b = Bomb(&p, target);
	p.oList.add(&b);
};

void IssueOrderState::IssueBlockade(Player p) {
	cout << p.getPlayerName() << ", please enter the territory you want to place tha blockade." << endl;
	string* tName;
	Territory* target = this->context_->map->findTerritorybyName(*tName);
	Blockade b = Blockade(&p, target);
	p.oList.add(&b);
};

void IssueOrderState::IssueNegotiate(Player p) {
	cout << p.getPlayerName() << ", please enter the player you want to negotiate with." << endl;
	string* pName;
	Player targetPlayer = this->context_->pList->findPlayerbyName(*pName);
	Negotiate n = Negotiate(&p, &targetPlayer);
	p.oList.add(&n);
};

bool IssueOrderState::allArmyUsed() {
	for (int i = 0; i < this->context_->pList->list.size(); i++) {
		if (this->context_->pList->list[i].ArmyUnit!=0) {
			return false;
		}
	}
	return true;
};

bool turnEnd(vector<int> indicator) {
	for (int i = 0; i < indicator.size(); i++) {
		if (indicator[i] != 3) {
			return false;
		}
	}
	return true;
};

void IssueOrderState::executeState(CommandProcessor* cp)
{
	int pAmount = this->context_->pList->list.size();
	vector<int> endTurnIndicator(pAmount);
	fill(endTurnIndicator.begin(), endTurnIndicator.end(), 0);
	cout << "now begins deploying phase";
	for (int i = 0; i < pAmount; i++) {
		IssueDeploy(this->context_->pList->findPlayer(i));
	}
	while(allArmyUsed == false) {
		for (int i = 0; i < pAmount; i++) {
			if (this->context_->pList->findPlayer(i).ArmyUnit != 0) {
				cout << this->context_->pList->findPlayer(i).getPlayerName() << " still owns unassigned army unit, please deploy all of them before proceed.";
				IssueDeploy( this->context_->pList->findPlayer(i));
			}
		}
	}
	cout << "now player may advance army or play cards in hand";
	while (turnEnd(endTurnIndicator)==false) {
		for (int i = 0; i < pAmount; i++) {
			if (endTurnIndicator[i] != 3) {
				cout << this->context_->pList->findPlayer(i).getPlayerName() << ", please select your action" << endl << "1. advance units" << endl << "2.play cards" << endl << "3.pass turn" << endl;
				int option;
				cin >> option;
				endTurnIndicator[i] = option;
				if (option = 1) {
					IssueAdvance(this->context_->pList->findPlayer(i));
				}
				if (option = 2) {
					string card = CardPlayed(this->context_->pList->findPlayer(i));
					if (card == "Airlift") {
						IssueAirlift(this->context_->pList->findPlayer(i));
					}
					if (card == "Bomb") {
						IssueBomb(this->context_->pList->findPlayer(i));
					}
					if (card == "Blockade") {
						IssueBlockade(this->context_->pList->findPlayer(i));
					}
					if (card == "Negotiate") {
						IssueNegotiate(this->context_->pList->findPlayer(i));
					}
				}
				if (option = 3) {
					cout << "turn end, please wait for other players";
				}
			}
		}
	}
};

void IssueOrderState::exitState(CommandProcessor* cp)
{
	this->context_->TransitionTo(new ExecuteOrderState());
};
//create temp. orderlist, 
bool ExecuteOrderState::gameEnd() {
	if (this->context_->pList->list.size()==1) {
		return true;
	}
	else {
		return false;
	}
};


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
	if (gameEnd()) {
		this->context_->TransitionTo(new WinState);
	}
	else {
		this->context_->TransitionTo(new ReinforcementState);
	}
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



