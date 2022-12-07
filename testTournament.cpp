#include "GameEngine.h";
#include "CommandProcessing.h";
#include<random>
#include <iostream>
using namespace std;
//the free funtion for console input
void consoleInput() 
{
	CommandProcessor* cp = new CommandProcessor();
	FileCommandProcessorAdapter* fcp = new FileCommandProcessorAdapter();
	StateController* sc = new StateController(new StartState());

	
	while (sc->startupphase == 0)
	{
		sc->enterState(cp);							//greetings
		sc->executeState(cp);							//call the commandProcessor methods until we get the right command, execute command 
		sc->exitState(cp);							//transition to next state 	

	}
	while (sc->startupphase == 1)
	{
		sc->enterState(cp);							//greetings
		sc->executeState(cp);							//call the commandProcessor methods until we get the right command, execute command 
		sc->exitState(cp);
	}
}
//the free functions for file input
void fileInput()
{
	CommandProcessor* cp = new CommandProcessor();
	FileCommandProcessorAdapter* fcp = new FileCommandProcessorAdapter();
	StateController* sc = new StateController(new StartState());

	while (sc->startupphase == 0)
	{
		sc->enterState(fcp);							//greetings
		sc->executeState(fcp);							//call the commandProcessor methods until we get the right command, execute command 
		sc->exitState(fcp);							//transition to next state 	

	}
	while (sc->startupphase == 1)
	{
		sc->enterState(fcp);							//greetings
		sc->executeState(fcp);							//call the commandProcessor methods until we get the right command, execute command 
		sc->exitState(fcp);
	}
}

int main() {
	//setting the seed as time value so every run gets different rng value
	srand(time(NULL));
	cout << "***Welcome to tournament Tester***\nPlease select the input Mode:" << endl;
	cout << "0.console input\n1.file input"<<endl;
	int option = 0;
	cin >> option;
	if (option == 0) {
		consoleInput();
	}
	else if (option == 1) {
		fileInput();
	}
	else {
		cout << "That is not a valid option";
	}
	cout << "==================================================\nthank you for using";
	string s;
	cin >> s;
	return 0;
}