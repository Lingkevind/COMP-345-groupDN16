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
}

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
  
    cout << "Please input a command" << endl;
    //cin.ignore(); //needed to use cin in getline() after using "cin <<" previously
    getline(cin, inputFromReadCommand); //to include whitespace in string
    cout << "inputFromReadCommand is: " << inputFromReadCommand << endl;



    saveCommand(inputFromReadCommand);
};


void CommandProcessor::saveCommand(string s) {
    //assign command type from input

    commandCollection.emplace_back(new Command(s)); //save the command to collection
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

    if ((regex_match(latestCommand, regex("(loadmap )(.*)"))) && (currentState == "StartState" || currentState == "MapLoadState"))
    {
        return true;
    }

    else if ((regex_match(latestCommand, regex("(tournament )(.*)"))) && (currentState == "StartState"))
    {
        return validateTournament(latestCommand);
    }
    else if ((latestCommand == "validatemap") && currentState == "MapLoadState")
    {
        return true;
    }
    else if (((regex_match(latestCommand, regex("(addplayer )(.*)"))) ) && (currentState == "MapValidatedState" || currentState == "PlayersAddedState"))
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

bool CommandProcessor::validateTournament(string currentCommand) {
    int x = currentCommand.find("-");
    string subCommand = currentCommand.substr(x, currentCommand.length());
    if (regex_match(subCommand, regex("(-M<)(.*)")))
    {
        int z = currentCommand.find(">")-4;
        string content = subCommand.substr(3, z);
        if (!validM(content)) 
        {
            return false;
        }
        x = currentCommand.find(">");
        subCommand = subCommand.substr(x, currentCommand.length());
        if (regex_match(subCommand, regex("(>-P<)(.*)"))) 
        {
            z = currentCommand.find(">") - 5;
            content = subCommand.substr(4, z);
            if (!validP(content)) 
            {
                return false;
            }
            subCommand = subCommand.substr(1,subCommand.length());
            x = currentCommand.find(">");
            subCommand = subCommand.substr(x, currentCommand.length());
            if (regex_match(subCommand, regex("(>-G<)(.*)"))) 
            {
                z = currentCommand.find(">") - 5;
                content = subCommand.substr(4, z);
                int count = stoi(content);
                if (!validG(count)) 
                {
                    return false;
                }
                subCommand = subCommand.substr(1, subCommand.length());
                x = currentCommand.find(">");
                subCommand = subCommand.substr(x, currentCommand.length());
                if (regex_match(subCommand, regex("(>-D<)(.*)"))) 
                {
                    z = currentCommand.find(">") - 5;
                    content = subCommand.substr(4, z);
                    int count = stoi(content);
                    if (!validD(count)) 
                    {
                        return false;
                    }
                    if (&subCommand.back() == ">") 
                    {
                        return true;
                    }
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
};

bool CommandProcessor::validM(string M) {
    vector<string> collection;
    string subM = M;
    int x = subM.find(",");
    while (x != -1)
    {
        string content=subM.substr(0,x-1);
        collection.push_back(content);
        subM = subM.substr(x + 1, subM.length());
        x = subM.find(",");
    }
    if (collection.size() == 0||collection.size() > 5) {
        cout << "Map amount has exceeded the limit range from 1 to 5";
        return false;
    }
    for (int i = 0; i < collection.size(); i++) 
    {
        if (!regex_match(collection[i], regex("(.*)(.map)")))
        {
            cout << collection[i]<<" has the invalid format";
            return false;
        }
    }
    return true;
}

bool CommandProcessor::validP(string P) {
    vector<string> collection;
    string subP = P;
    int x = subP.find(",");
    while (x != -1)
    {
        string content = subP.substr(0, x - 1);
        collection.push_back(content);
        subP = subP.substr(x + 1, subP.length());
        x = subP.find(",");
    }
    if (collection.size()<2 || collection.size() > 4) {
        cout << "Player amount has exceeded the limit range from 2 to 4";
        return false;
    }
    string strats = "Aggressive Benevolent Neutral Cheater";
    for (int i = 0; i < collection.size(); i++)
    {
        if (strats.find(collection[i])==string::npos)
        {
            cout << collection[i] << " is an invalid strategy";
            return false;
        }
    }
    return true;
}

bool CommandProcessor::validG(int G) {
    if (G < 1 || G > 5) {
        cout << "Game amount set has exceeded the limit range from 1 to 5";
        return false;
    }
    return true;
}

bool CommandProcessor::validD(int D) {
    if (D < 10 || D > 50) {
        cout << "Turn amount set has exceeded the limit range from 10 to 50";
        return false;
    }
    return true;
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
    fr = new FileLineReader("gameTest3.txt");


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







