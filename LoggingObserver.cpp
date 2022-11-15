#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "LoggingObserver.h"
#include <chrono>
#include <ctime>

using namespace std;

Observer::Observer() {}

Observer::Observer(const Observer& observer) {
}

void Observer::update(ILoggable* loggableObject) {
	ofstream logFile;
	logFile.open("GameLog.txt", std::ios_base::app);
	// Logs the string to log into the GameLog file
	logFile << loggableObject->StringToLog() << endl; 
	logFile.close();

}

Observer& Observer::operator=(const Observer& observer) {
	return *this;
}

ostream& operator<<(ostream& os, const Observer& observer) {
	os << observer << endl;
	return os;			
}


Subject::Subject(const Subject& subject) {
	this->observers = subject.observers;	
	this->attach(new LoggingObserver());
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

Subject& Subject::operator=(const Subject& subject) {
	this->observers = subject.observers;
	return *this;
}

ostream& operator<<(ostream& os, const Subject& subject) {
	os << "Total number of observer for the subject : " << subject.observers.size() << endl;
	return os;	
}

LoggingObserver::LoggingObserver() {}

LoggingObserver::LoggingObserver(const LoggingObserver& observer) {}

LoggingObserver& LoggingObserver::operator=(const LoggingObserver& loggingObserver) {
	return *this;
}

ostream& operator<<(ostream& os, const LoggingObserver& loggingObserver) {
	os << loggingObserver << endl;
	return os;
}