/**
* Author : Yasemin Akın
* ID: 22101782
* Section : 001
* Homework : 3
* Description : Patient cpp file including Patient class for describing the Patients' attributes */

#include <stdio.h>
#include "Patient.h"

// Constructor
Patient::Patient(int id, int priority, int arrivalTime, int serviceTime)
    : id(id), priority(priority), arrivalTime(arrivalTime), serviceTime(serviceTime) {}

// Setters
void Patient::setId(int newId) {
    id = newId;
}

void Patient::setPriority(int newPriority) {
    priority = newPriority;
}

void Patient::setArrivalTime(int newArrivalTime) {
    arrivalTime = newArrivalTime;
}

void Patient::setServiceTime(int newServiceTime) {
    serviceTime = newServiceTime;
}

// Getters
int Patient::getId() const {
    return id;
}

int Patient::getPriority() const {
    return priority;
}

int Patient::getArrivalTime() const {
    return arrivalTime;
}

int Patient::getServiceTime() const {
    return serviceTime;
}

string Patient::toString() const {
    stringstream ss;
    ss << "Patient ID: " << id
       << ", Priority: " << priority
       << ", Arrival Time: " << arrivalTime
       << ", Service Time: " << serviceTime;
    return ss.str();
}
