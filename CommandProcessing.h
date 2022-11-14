#pragma once
#include <string>;
#include <vector>;
#include <iostream>;
#include <fstream>
#include <cstdlib>
#ifndef   CommandProcessing
#define   CommandProcessing
#include "GameEngine.h";
#include "LoggingObserver.h"




using namespace std;


//SECTION 1 - HEADER OF Command
class Command {
public:

	//data memebers
	string effectName;
	string commandName;

	//setters and getters
	void setEffect(string e);
	void setCommand(string c);
	string getEffect();
	string getCommand();

	//construcs and destructor
	Command();
	Command(string newCommand);
	Command(const Command& copyCommand);
	~Command();
	//friend ostream& operator << (ostream& outputStream,const Command& c); //outstream overload

	void saveEffect(string effectResult);		//stores result from command 


};


//SECTION 2 - HEADER OF CommandProcessor (TARGET)
class CommandProcessor : Subject, ILoggable
{
protected:
	virtual void readCommand();	 //get command from console
	void saveCommand(string s);							 //stores command in vector 
public:
	vector <Command*> commandCollection;		//vector of command objects 
	void  getCommand();							//get newest command from commandCollection
	virtual ~CommandProcessor();		//destructor	
	CommandProcessor();							//constructor
	bool validate(string currentState);			//checks if command is valid in state
	void saveEffectOfLatestCommand(string e);
	string StringToLog();
};



//ADAPTEE 
class FileLineReader
{
public:
	static int lineCount;
	string readLineFromFile();
	~FileLineReader();
	static void incrementLineCount();
	string file;
	FileLineReader();
	FileLineReader(string fileName);

};




//SECTION 3 - ADAPTER 

class FileCommandProcessorAdapter : public CommandProcessor
{
private:
	FileLineReader* fr;

public:
	void readCommand() override;
	FileCommandProcessorAdapter();
};




#endif 
