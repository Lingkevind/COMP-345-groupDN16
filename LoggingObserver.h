

#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Observer;

class ILoggable
{
    public:
        virtual string StringToLog() = 0;
};

class Observer {
public:
    virtual void update(ILoggable* loggableObject);

};

class LoggingObserver : public Observer
{
};

class Subject {
public:
    Subject();
    void notify(ILoggable* loggableObject);
    void attach(Observer* observer);
private:
    vector<Observer*> observers;
};




