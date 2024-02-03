/**
* Author : Yasemin Akın
* ID: 22101782
* Section : 001
* Homework : 3
* Description : Patient header file defines a single Patient */

#ifndef Patient_h
#define Patient_h

#include <string>
#include <sstream> 

using namespace std;

class Patient {
    
public:
    // Constructor
    Patient(int id, int priority, int arrivalTime, int serviceTime);
    Patient() : id(0), priority(0), arrivalTime(0), serviceTime(0) {}
    
    // Setters
    void setId(int newId);
    void setPriority(int newPriority);
    void setArrivalTime(int newArrivalTime);
    void setServiceTime(int newServiceTime);

    // Getters
    int getId() const;
    int getPriority() const;
    int getArrivalTime() const;
    int getServiceTime() const;
    
    string toString() const;
    
private:
    int id;
    int priority;
    int arrivalTime;
    int serviceTime;
    
};
#endif /* Patient_h */
