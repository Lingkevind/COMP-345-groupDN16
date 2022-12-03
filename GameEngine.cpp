#include <iostream>
#include <cctype>
#include <cstdlib>
#include <string>


#include <iostream>
#include "Territory.h"
#include "Coord.h"
#include <map>
#include "MapLoader.h"
#include <windows.h> 
#include "Player.h"


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

Player StateController::findPlayerbyName(string name, vector<Player*> pList) {
	for (int i = 0; i < pList.size(); i++) {
		if (pList[i]->getPlayerName() == name) {
			return *pList[i];
		}
	}
	cout << "player " << name << " not found";
	return Player();
}

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
	//Keep asking until we get a valid command for the state 
	bool validCommand = false;
	std::cout << "***Welcome To StartState***" << std::endl;

	//Loop until we get valid command for the state 
	while (validCommand == false)
	{
		cp->getCommand();
		validCommand = cp->validate(this->context_->getStateName()); 
		int size = cp->commandCollection.size();
		if (validCommand == false) {
			cp->commandCollection.at(size - 1)->saveEffect("incorrect command for state");
		}
		else {
			cout << "Entered a valid command" << endl;
		}
	}
};

void StartState::executeState(CommandProcessor* cp){

	cout << "The Valid Command For StartState Is Being executed..." << endl;


	int size = cp->commandCollection.size();
	string commandString = cp->commandCollection.at(size - 1)->getCommand();
	if (!regex_match(commandString, regex("(tournament )(.*)")))
	{
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
			cout << "SUCCESSFULLY LOAD MAP: " << mapName << endl;
			effectMessage = "SUCCESSFULLY LOAD MAP";
		}
		//Map FAILED to load
		else
		{
			cout << "FAILED TO LOAD MAP: " << mapName << endl;
			effectMessage = "FAILED TO LOAD MAP";
		}
		delete mapLoader;
		mapLoader = NULL;


		size = cp->commandCollection.size();
		cp->commandCollection.at(size - 1)->saveEffect(effectMessage);

	}
	else {
		cout << "";
	}
};

void StartState::exitState(CommandProcessor* cp)
{
	int size = cp->commandCollection.size();
	string commandString = cp->commandCollection.at(size - 1)->getCommand();
	if (!regex_match(commandString, regex("(tournament )(.*)"))) {
		int size = cp->commandCollection.size();
		string determineTransition = cp->commandCollection.at(size - 1)->getEffect();

		//If map is not loadeable, we go back to the StartState
		if (determineTransition == "FAILED TO LOAD MAP")
		{
			cout << "That Map Cannot Be Loaded, Enter Another Map..." << endl;
			this->context_->TransitionTo(new StartState);
		}
		else if (determineTransition == "SUCCESSFULLY LOAD MAP")
		{
			//Map was loadable, will now validate it in the next state
			this->context_->TransitionTo(new MapLoadState);
		}
	}
	else {
		this->context_->TransitionTo(new TournamentState);
	}
};



//******************SECTION 4******************
//Defining methods for the MapLoadState Class
//**********************************************


void MapLoadState::enterState(CommandProcessor* cp)
{
	//Get a command until valid
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
		}
	}

};

void MapLoadState::exitState(CommandProcessor* cp)
{

	cout << "The Valid Command For MapLoadState Has Been executed... " << endl;

	int size = cp->commandCollection.size();
	string determineTransition = cp->commandCollection.at(size - 1)->getEffect();

	//If map is not valid, we go back to the StartState
	if (determineTransition == "The Map loaded is NOT valid")
	{
		cout << "That Map IS NOT VALID, Enter Another Map..." << endl;
		this->context_->TransitionTo(new StartState);
	}

	//The map was valid
	else if (determineTransition == "The Map loaded is valid")
	{
		this->context_->TransitionTo(new MapValidatedState);
	}

};




//******************SECTION 5******************
//Defining methods for the MapValidateState Class
//**********************************************


void MapValidatedState::enterState(CommandProcessor* cp)
{
	//Get command until valid
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
			cp->commandCollection.at(size - 1)->saveEffect("Player Successfully added");

		}

		else 
		{
			cout << "No more players can be added" << endl;
			cp->commandCollection.at(size - 1)->saveEffect("Player cannot be added");
		}


	}

	else 
	{
		cp->commandCollection.at(size - 1)->saveEffect("not a valid command");

	}

};

void MapValidatedState::exitState(CommandProcessor* cp)
{
	cout << "The Valid Command For MapValidatedState Has Been executed... " << endl;

	

	//if there is atleast 2 players, go to the PlayersAddedState

	if (this->context_->playerCollection.size() >= 2) 
	{
		cout << "THERE IS 2 players now" << endl;
		this->context_->TransitionTo(new PlayersAddedState);

	}	

	// there isn't 2 players yet to start the game
	else 
	{
		this->context_->TransitionTo(new MapValidatedState);
	
	}
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
		cout << "THE NUMBER OF PLAYERS SO FAR: " << this->context_->playerCollection.size() << endl;
		if (this->context_->playerCollection.size() == 6) 
		{
			cout << "NO MORE PLAYERS CAN BE ADDED, PLEASE STOP TRYING" << endl;
		}

			//GET THE PLAYER NAME FROM THE COMMAND
			char spaceCharacter = ' ';
			size_t found = commandString.find(spaceCharacter);
			playerName = commandString.substr(found);
			playerName.erase(playerName.find_last_not_of(" \n\r\t") + 1);
			playerName.erase(0, playerName.find_first_not_of(" \n\r\t"));

			cout << "The Valid Command(addplayer) For PlayersAdded is being executed..." << endl;

			if (this->context_->playerCollection.size() < 6)
			{
				this->context_->playerCollection.emplace_back(new Player(playerName));
				cout << playerName << " HAS BEEN ADDED" << endl;
				cp->commandCollection.at(size - 1)->saveEffect("Player Successfully added");

			}

			else
			{
				cout << "No more players can be added" << endl;
				cp->commandCollection.at(size - 1)->saveEffect("Player cannot be added");
			}
	}

	else if (commandString == "gamestart")
	{
		cout << "The Valid Command(gamsestart) For PlayersAdded is being executed..." << endl;
		//PART2 CODE HERE FOR GAMESTART COMMAND
		vector<Continent*> gameContinents = this->context_->gameMap->getContinents();
		//int playerInGameNum = this->context_->playerCollection.size();
		//int eachPlayerTerritoriesNum = territoriesNum / playerNum;
		//int extraTerritoriesNum = territoriesNum % playerNum;
		//auto size = gameContinents.size();

		vector<Territory*> allTaddtoPlayer= this->context_->gameMap->getTerritories();
		//vector<Territory*> allTaddtoPlayer;
		//for each (Continent* gameC in gameContinents) {
		//	vector<Territory*> territoryV = gameC->getTerritories();
		//	for each (Territory* var in territoryV) {
		//		allTaddtoPlayer.push_back(var);
		//	}
		//}
		
		cout << this->context_->playerCollection.size();
		int s = this->context_->playerCollection.size()-1;
		for (size_t i = 0; i < 100; i++)
		{
			int a = rand() % s;
			int b = rand() % s;
			if (a != b) {
				Player* A = this->context_->playerCollection.at(a);
				Player* B = this->context_->playerCollection.at(b);
				Player* C = A;
				A = B;
				B = C;
				this->context_->playerCollection.at(a) = A;
				this->context_->playerCollection.at(b) = B;
			}
		}

		bool flag = true;
		do
		{
			for each (Player * currentplayer in this->context_->playerCollection) {
				int pickedTerritory = rand() % allTaddtoPlayer.size();
				currentplayer->occupy(allTaddtoPlayer.at(pickedTerritory));
				allTaddtoPlayer.erase(allTaddtoPlayer.begin() + pickedTerritory);
				if (allTaddtoPlayer.empty()) {
					flag = false;
					//delete(&allTaddtoPlayer); 
					break;
				}
			}
		} while (flag);
		cout << "\nAll Territories in the map are successfully assigned to all Players!\n";
		this->context_->deck.initialize();
		this->context_->deck.randomShuffle();
		for each (Player* currentplayer in this->context_->playerCollection) {
			currentplayer->ArmyUnit = 50;
			//cout << currentplayer->ArmyUnit<< "\n\n";
			currentplayer->getplayerHand()->drawFrom(this->context_->deck);
			currentplayer->getplayerHand()->drawFrom(this->context_->deck);
		} //add 50 army to armypool then draw 2card from deck
		cout << "All players have 50 army and received their initial hand of cards!\n";
		/// <summary>
		/// PUT CODE HERE TO SHOW FAIR DISTRUBITON OF TERRITORIES
		bool testGameStartup = true;
		bool displayAllPlatersT = true; // if you want to see each player's Territories
		if (testGameStartup)
		{
			int territoriesNum = 0;
			int playersTerritoriesNum = 0;
			for each (Continent * gameC in gameContinents) {
				vector<Territory*> territoryV = gameC->getTerritories();
				for each (Territory * var in territoryV) {
					territoriesNum++;
				}
			}
			bool vMe50Army = true;
			for each (Player * var in this->context_->playerCollection) {
				playersTerritoriesNum += var->getplayerOccupiedsize();
				if(displayAllPlatersT)var->displayerOcc(); 
				if (vMe50Army)vMe50Army = var->ArmyUnit == 50;
			}
			if (playersTerritoriesNum == territoriesNum) {
				cout << "All territories in the map are assigned!\n";
			}
			else cout << "Not all territories in the map are assigned\n";
			if (vMe50Army) {
				cout << "All players has 50 Army!\n";
			}
			else cout << "Not All players has 50 Army!\n";

		}
		/// </summary>
		/// <param name="cp"></param>
		cp->commandCollection.at(size - 1)->saveEffect("SUCCESS IN GAMESTART");
	}

	else 
	{
		cp->commandCollection.at(size - 1)->saveEffect("INVALID COMMAND");
	}
}






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
		this->context_->startupphase = true;
		this->context_->TransitionTo(new ReinforcementState);
		cout << "Game start!" << endl;
	}
};



//******************SECTION 7******************
//Defining methods for the AssignReinforcementState Class
//**********************************************

/*void ReinforcementState::pushPlayer() {
	for (int i = 0; i < this->context_->playerCollection.size(); i++) {
		this->context_->pList.addPlayer(*this->context_->playerCollection[i]);

	}
};*/

void ReinforcementState::enterState(CommandProcessor* cp)
{
	cout << "====================================================="<<endl;
	cout << "Begin reinforcement" << std::endl;

};

void ReinforcementState::reinforcement(Player* p) {
	int army = p->getplayerOccupiedsize() / 3;
	cout << p->getPlayerName() << " obtained " << army << " from their territories."<< endl;
	p->ArmyUnit += army;
	cout << p->getPlayerName() << " has " << p->ArmyUnit<<" army."<<endl;
};

void ReinforcementState::executeState(CommandProcessor* cp)
{
	int pAmount = this->context_->playerCollection.size();
	for (int i = 0; i < pAmount; i++) {
		reinforcement(this->context_->playerCollection[i]);
	}
};

void ReinforcementState::exitState(CommandProcessor* cp)
{
	cout << "Reinforcement finished"<<endl;
	this->context_->TransitionTo(new IssueOrderState());
};


void IssueOrderState::enterState(CommandProcessor* cp)
{
	cout << "=====================================================" << endl;
	cout << "Begin creating order" << endl;
};

void IssueOrderState::IssueDeploy(Player *p) {
	cout << p->getPlayerName() << ", please enter the amount of army you want to deploy, you have " << p->ArmyUnit << " undeployed unit" << endl;
	int army;
	cin >> army;
	cout << "please enter the target territory you wish to deploy." << endl;
	string tName;
	cin >> tName;
	Territory* t = this->context_->gameMap->findTerritorybyName(tName);
	Deploy d = Deploy(p, army, t);
	p->ArmyUnit -= army;
	p->oList->add(&d);
};

void IssueOrderState::IssueAdvance(Player *p) {
	cout << p->getPlayerName() << ", please enter the territory you want to move from." << endl;
	string tName;
	cin >> tName;
	Territory* from = this->context_->gameMap->findTerritorybyName(tName);
	cout << "please enter the amount of army you want to move." << endl;
	int army;
	cin >> army;
	cout << "please enter the territory you want to move to." << endl;;
	cin >> tName;
	Territory* to = this->context_->gameMap->findTerritorybyName(tName);
	Advance a = Advance(p, army, from, to);
	p->oList->add(&a);
	p->ArmyUnit-=army;
};

string IssueOrderState::CardPlayed(Player *p) {
	cout << "please enter the index of the card you wanna play, enter 0 to skip.";
	p->getplayerHand()->display();
	if (p->getplayerHand()->cards.size() != 0) {
		int index;
		cin >> index;
		Hand *h = p->getplayerHand();
		string card = h->playCards(index - 1, this->context_->deck);
		return card;
	}
	else {
		return "";
	}
};

void IssueOrderState::IssueAirlift(Player *p) {
	cout << p->getPlayerName() << ", please enter the territory you want to lift from." << endl;
	string tName;
	cin >> tName;
	Territory* from = this->context_->gameMap->findTerritorybyName(tName);
	cout << "please enter the amount of army you want to move." << endl;
	int army;
	cin >> army;
	cout << "please enter the territory you want to drop to." << endl;;
	cin >> tName;
	Territory* to = this->context_->gameMap->findTerritorybyName(tName);
	Airlift a = Airlift(p, army, from, to);
	p->oList->add(&a);
};

void IssueOrderState::IssueBomb(Player *p) {
	cout << p->getPlayerName() << ", please enter the territory you want to place tha bomb." << endl;
	string tName;
	cin >> tName;
	Territory* target = this->context_->gameMap->findTerritorybyName(tName);
	Bomb b = Bomb(p, target);
	p->oList->add(&b);
};

void IssueOrderState::IssueBlockade(Player *p) {
	cout << p->getPlayerName() << ", please enter the territory you want to place tha blockade." << endl;
	string tName;
	cin >> tName;
	Territory* target = this->context_->gameMap->findTerritorybyName(tName);
	Blockade b = Blockade(p, target);
	p->oList->add(&b);
};

void IssueOrderState::IssueNegotiate(Player *p) {
	cout << p->getPlayerName() << ", please enter the player you want to negotiate with." << endl;
	string pName;
	cin >> pName;
	Player targetPlayer = this->context_->findPlayerbyName(pName, this->context_->playerCollection);
	Negotiate n = Negotiate(p, &targetPlayer);
	p->oList->add(&n);
};

bool IssueOrderState::allArmyUsed() {
	for (int i = 0; i < this->context_->playerCollection.size(); i++) {
		if (this->context_->playerCollection[i]->ArmyUnit != 0) {
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
	int pAmount = this->context_->playerCollection.size();
	vector<int> endTurnIndicator(pAmount);
	fill(endTurnIndicator.begin(), endTurnIndicator.end(), 0);
	cout << "=====================================================" << endl;
	cout << "now begins deploying phase"<<endl;
	for (int i = 0; i < pAmount; i++) {
		//this->context_->playerCollection[i]->oList->displayList();
		IssueDeploy(this->context_->playerCollection[i]);
	}
	while (allArmyUsed() == false) {
		for (int i = 0; i < pAmount; i++) {
			if (this->context_->playerCollection[i]->ArmyUnit > 0) {
				cout << this->context_->playerCollection[i]->getPlayerName() << " still owns unassigned army unit, please deploy all of them before proceed."<<endl;
				//this->context_->playerCollection[i]->oList->displayList();
				IssueDeploy(this->context_->playerCollection[i]);
			}
		}
	}
	cout << "now player may advance army or play cards in hand" << endl;
	while (turnEnd(endTurnIndicator) == false) {
		for (int i = 0; i < pAmount; i++) {
			if (endTurnIndicator[i] != 3) {
				cout << "=====================================================" << endl;
				//this->context_->playerCollection[i]->oList->displayList();
				cout << this->context_->playerCollection[i]->getPlayerName() << ", please select your action" << endl << "1.advance units" << endl << "2.play cards" << endl << "3.pass turn" << endl;
				int option;
				cin >> option;
				endTurnIndicator[i] = option;
				if (option == 1) {
					IssueAdvance(this->context_->playerCollection[i]);
				}
				if (option == 2) {
					string card = CardPlayed(this->context_->playerCollection[i]);
					if (card != "") {
						if (card == "Airlift") {
							IssueAirlift(this->context_->playerCollection[i]);
						}
						if (card == "Bomb") {
							IssueBomb(this->context_->playerCollection[i]);
						}
						if (card == "Blockade") {
							IssueBlockade(this->context_->playerCollection[i]);
						}
						if (card == "Diplomacy") {
							IssueNegotiate(this->context_->playerCollection[i]);
						}
					}
					else {
						cout << "There is no card in your hand.";
					}
				}
				if (option == 3) {
					cout << "turn end, please wait for other players"<<endl;
				}
			}
		}
	}

};

void IssueOrderState::exitState(CommandProcessor* cp)
{
	this->context_->TransitionTo(new ExecuteOrderState());
};

bool ExecuteOrderState::gameEnd() {
	if (this->context_->playerCollection.size() == 1) {
		return true;
	}
	else {
		return false;
	}
};

void ExecuteOrderState::enterState(CommandProcessor* cp)
{
	cout << "All players set, begin executing player order in round robin fashion" << endl;

};

bool ExecuteOrderState::finishExecute() {
	int pAmount = this->context_->playerCollection.size();
	for (int i = 0; i < pAmount; i++) {
		if (this->context_->playerCollection[i]->oList->getOrderList().size() != 0) {
			return false;
		}
	}
	return true;
}

void ExecuteOrderState::executeState(CommandProcessor* cp)
{
	int pAmount = this->context_->playerCollection.size();
	while (finishExecute() == false) {
		for (int i = 0; i < pAmount; i++) {
			if (this->context_->playerCollection[i]->oList->getOrderList().size() != 0){
				Order* o=new Order(*this->context_->playerCollection[i]->oList->getOrderList()[0]);
				o->execute();
				this->context_->playerCollection[i]->oList->remove(0);
			}
		}
	}

};

void ExecuteOrderState::makePlayerFail(string pName, vector<Player*>& pList) {
	 int playertodelete;
	for (int i = 0; i < pList.size(); i++)
	{
		if (pName==pList.at(i)->getPlayerName())
		{
			playertodelete = i;
			delete pList.at(playertodelete);
			pList.erase(pList.begin()+i);
			cout << "player "<<pName<<" deleted"<<endl;
			cout << pList.size()<<endl;
			break;
		}
		
	}
	
};

void ExecuteOrderState::checkFailedPlayer() {
	int pAmount = this->context_->playerCollection.size();
	for (int i = 0; i < pAmount; i++) {
		if (this->context_->playerCollection[i]->getplayerOccupiedsize() == 0) {
			string name = this->context_->playerCollection[i]->getPlayerName();
			makePlayerFail(name, this->context_->playerCollection);
			this->context_->playerCollection.erase(this->context_->playerCollection.begin() + i);
			cout << "player ";
		}
	}
};

void ExecuteOrderState::exitState(CommandProcessor* cp)
{
	cout << "main game loop finished, input 1 to delete excess player(to test the win condition)" << endl;
	int option = 0;
	cin >> option;
	while (option == 1) {
		cout << "input the name of the player to be deleted" << endl;
		string pName;
		cin >> pName;
		makePlayerFail(pName, this->context_->playerCollection);
		cout << "input 1 to delete another player, input other integer to proceed" << endl;
		cin >> option;
	}

	checkFailedPlayer();
	if (gameEnd()) {
		cout << "Only 1 player remains, the winner was decided: "<< this->context_->playerCollection[0]->getPlayerName();
		this->context_->TransitionTo(new WinState);
	}
	else {
		cout << this->context_->playerCollection.size() << " Players left, proceeding to new round.";
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


