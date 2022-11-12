#include <iostream>;
#include <cctype>;
#include <cstdlib>;

#include <string>
#include <sstream>
#include <memory>
#include <fstream>
#include <cstdlib>




using namespace std;
#include "CommandProcessing.h";
#include "GameEngine.h";


//SECTION 1 - Command
void Command::setCommand(string c)
{
    commandName = c;
};

void Command::saveEffect(string e)
{
    effectName = e;
};

string Command::getEffect()
{
    std::string v_temp = "def";
    v_temp = effectName;
    return v_temp;
};

string Command::getCommand()
{
    std::string v_temp = "def";
    v_temp = commandName;
    return v_temp;
};

Command::Command()
{
    commandName = "default";
    effectName = "default";

};

Command::Command(string newCommand)
{
    commandName = newCommand;
    effectName = "default"; //no effect yet
};


Command::Command(const Command& copyCommand)
{
    commandName = copyCommand.commandName;
    effectName = copyCommand.effectName;
};



//destructor
Command::~Command() {};


//SECTION 2 - CommandProcessor

vector < Command* > commandCollection;

CommandProcessor::CommandProcessor() {};
CommandProcessor::~CommandProcessor() = default;

void CommandProcessor::readCommand() {
    string inputFromReadCommand = "def";
    cout << "Please input a command." << endl;
    cin >> inputFromReadCommand;

    cout << "inputFromReadCommand  is: " << inputFromReadCommand << endl;
   
    saveCommand(inputFromReadCommand);
};


void CommandProcessor::saveCommand(string s) {
     //assign command type from input

    commandCollection.emplace_back(new Command(s)); //save the command to collection
    this->notify(this);
};


void CommandProcessor::getCommand()
{
    readCommand();
};



//checks if the command is in the appropriate state and returns true.
//if command or state is invalid, returns false

bool CommandProcessor::validate(string currentState)
{   
    int sizeOfVector = commandCollection.size();
    string latestCommand = commandCollection[sizeOfVector - 1]->getCommand();

    if ((latestCommand == "loadmap") && (currentState == "StartState" || currentState == "MapLoadState"))
    {
      return true; 
    }
    else if ( (latestCommand == "validatemap") && currentState == "MapLoadState")
    { 
        return true; 
    }
    else if (latestCommand == "addplayer" && (currentState == "MapValidatedState" || currentState == "PlayersAddedState"))
    { 
        return true; 
    }

    else if ((latestCommand == "gamestart") && currentState == "PlayersAddedState") 
    {
        return true; 
    }
    else if ((latestCommand == "replay") && currentState == "WinState") 
    { 
        return true;
    }
    else if ((latestCommand == "quit") && currentState == "WinState")
    {
        return true;
    }

    else
    {
        return false; 
    
    }
    return false;
};

string CommandProcessor::StringToLog() {
    Command* latestCommand = this->commandCollection[this->commandCollection.size() - 1];
    return "Command : " + latestCommand->commandName
        + "\nCommand's effect : " + latestCommand->effectName;
}

string StateController::StringToLog() {
    return "Game engine's new state : " + this->currentStateName;
}



int FileLineReader::lineCount = 1;
void FileLineReader::incrementLineCount()
{
    lineCount = lineCount + 1;
};

FileLineReader::FileLineReader()
{
    file = "no file";
};

FileLineReader::FileLineReader(string fileName)
{
    file = fileName; 
};

string FileLineReader::readLineFromFile()
{
    ifstream commandFile;
    commandFile.open(file);
    string line = "default";
    int current_line = 0;


    if (!commandFile.is_open()) 
    {
        cout << "FAILURE TO OPEN FILE" << endl;
        return "error";
    }


    while (!commandFile.eof()) 
    {
        current_line++;
        getline(commandFile, line);
        if (current_line == lineCount) 
        {
            incrementLineCount();
            cout << "COMMAND: " << line << "COUNTER: " << lineCount;
            break;

        }
    }
    return line;
};


FileCommandProcessorAdapter::FileCommandProcessorAdapter() 
{
    fr = new FileLineReader("C:\\Users\\Roger\\Desktop\\gameTest2.txt");


}

void FileCommandProcessorAdapter::readCommand() 
{
    string commandFromFile = "default";
    cout << "Reading Command From File." << endl;
    commandFromFile = fr->readLineFromFile();
    cout << "Command From File  is: " << commandFromFile << endl;
    saveCommand(commandFromFile);
}








/*
//ostream overload
ostream& operator << (ostream& outputStream,
    const Command& c) {
    outputStream << "Command has: \ncommand:" << c.commandName << endl;
    outputStream << "effect: " << c.effectName << endl;
    return outputStream;
};
*/








