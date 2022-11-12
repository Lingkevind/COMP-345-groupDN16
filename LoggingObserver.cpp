#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "LoggingObserver.h"
#include <chrono>
#include <ctime>

using namespace std;

void Observer::update(ILoggable* loggableObject) {
	ofstream logFile;
	logFile.open("GameLog.txt", std::ios_base::app);
	logFile << loggableObject->StringToLog() << endl;
	logFile.close();

}

Subject::Subject() {
	this->attach(new LoggingObserver());
}

void Subject::notify(ILoggable* loggableObject) {
	for (int i = 0; i < this->observers.size(); i++) {
		this->observers[i]->update(loggableObject);
	}
}

void Subject::attach(Observer* observer) {
	this->observers.push_back(observer);
}