#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Observer;

class ILoggable
{
public:
    /// <summary>
    /// Retrieves the string to log from the object
    /// </summary>
    /// <returns></returns>
    virtual string StringToLog() = 0;
};

class Observer {
public:
    /// <summary>
    /// Observer constructor
    /// </summary>
    Observer();

    /// <summary>
    /// Observer copy constructor
    /// </summary>
    Observer(const Observer& observer);

    /// <summary>
    /// Updates the log file using the stringToLog method from the given loggable object
    /// </summary>
    /// <param name="loggableObject">The given Loggable object</param>
    virtual void update(ILoggable* loggableObject);

    Observer& operator=(const Observer& observer);
    friend ostream& operator<<(ostream& os, const Observer& observer);
};

class LoggingObserver : public Observer
{
public:
    /// <summary>
    /// LoggingObserver constructor
    /// </summary>
    LoggingObserver();

    /// <summary>
    ///  LoggingObserver copy constructor
    /// </summary>
    /// <param name="loggingObserver"></param>
    LoggingObserver(const LoggingObserver& loggingObserver);

    friend ostream& operator<<(ostream& os, const LoggingObserver& loggingObserver);
    LoggingObserver& operator=(const LoggingObserver& loggingObserver);
};

class Subject {
public:
    /// <summary>
    /// Subject constructor
    /// </summary>
    Subject();

    /// <summary>
    ///  Subject copy constructor
    /// </summary>
    /// <param name="subject"></param>
    Subject(const Subject& subject);

    /// <summary>
    /// Notifies all the attached observer
    /// </summary>
    /// <param name="loggableObject">the loggable object to get the stringToLog from</param>
    void notify(ILoggable* loggableObject);

    /// <summary>
    /// Attach the given observer to the subject
    /// </summary>
    /// <param name="observer">The given observer</param>
    void attach(Observer* observer);

    Subject& operator=(const Subject& subject);

    friend ostream& operator<<(ostream& os, const Subject& subject);
private:
    vector<Observer*> observers; //  The list of observers to notify 
};