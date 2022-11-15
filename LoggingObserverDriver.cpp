#include <iostream>
#include <fstream>

#include "CommandProcessing.h"
#include "LoggingObserver.h"
#include "Orders.h"
#include <map>
#include <windows.h> 


using namespace std;



inline void testLoggingObserver() {
	std::remove("GameLog.txt");

	map<string, string> expectedKeywordsFromOutput;

	expectedKeywordsFromOutput = {
			{"Game engine's new state", "StartState"},
			{"Command ", "loadmap"},
			{"Command's effect", "default"},
			{"Order issued", "unknown order"},
		    {"Order executed", "Deploy troops"}};

	LoggingObserver* lg = new LoggingObserver();
	CommandProcessor* cp = new CommandProcessor();
	FileCommandProcessorAdapter* fcp = new FileCommandProcessorAdapter();
	StateController* sc = new StateController(new StartState());	

	sc->enterState(fcp);		
	sc->executeState(fcp); 
	sc->exitState(fcp);

	OrderList* ol = new OrderList();
	Deploy* deployOrder = new Deploy();

	ol->add(deployOrder);
	deployOrder->execute();

	string gameLogContent;
	string gameLogLine;

	// Read from the text file
	ifstream gameLogFile("GameLog.txt");



	while (getline(gameLogFile, gameLogLine)) {
		gameLogContent.append(gameLogLine);
	}

	gameLogFile.close();

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


	for (auto const& t : expectedKeywordsFromOutput)
	{
		cout << t.first << " : ";
		if (gameLogContent.find(t.first) != std::string::npos) {
			SetConsoleTextAttribute(hConsole, 10);
			cout << "SUCCESS" << endl;
		}
		else {
			SetConsoleTextAttribute(hConsole, 12);
			cout << "FAILURE" << endl;

		}
		SetConsoleTextAttribute(hConsole, 15);
	}


}

int main() {

	testLoggingObserver();
}


