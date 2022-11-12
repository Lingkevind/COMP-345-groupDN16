#include "GameEngine.h";
#include "CommandProcessing.h";

#include <iostream>
using namespace std;

inline void testCommandProcessor(int n) {

	LoggingObserver* lg = new LoggingObserver();
	CommandProcessor* cp = new CommandProcessor();
	FileCommandProcessorAdapter* fcp = new FileCommandProcessorAdapter();
	StateController* sc = new StateController(new StartState());
	


	//commands from console
	if (n == 1) 
	{
		while (true)
		{
			sc->enterState(cp);							//greetings
			sc->executeState(cp);							//call the commandProcessor methods until we get the right command, execute command 
			sc->exitState(cp);							//transition to next state 	

		}	
	}

	//commands from file

	if (n == 2)
	{
		while (true)
		{
			sc->enterState(fcp);							//greetings
			sc->executeState(fcp);							//call the commandProcessor methods until we get the right command, execute command 
			sc->exitState(fcp);							//transition to next state 	
		}
	}


	
	int size = cp->commandCollection.size();

	for (int i = 0; i < cp->commandCollection.size(); i++)
	{
		cout << "COMMAND: " << cp->commandCollection[i]->getCommand() << endl;
		cout << "EFFECT : " << cp->commandCollection[i]->getEffect() << endl;
		cout << endl;
	}

	int x = 5;
	cin >> x;
}
