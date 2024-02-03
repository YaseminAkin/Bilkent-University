/**
* Author : Yasemin Akın
* ID: 22101782
* Section : 001
* Homework : 3
* Description : definition of Hospital Simulation*/

#ifndef HospitalSimulationMgr_h
#define HospitalSimulationMgr_h
#include "PriorityQueue.h"
#include <fstream>
#include <vector>
#include "minHeap.h"

class HospitalSimulationMgr {
private:
    PriorityQueue *pq;
    int maxAverageWaitingTime;
    vector<Doctor> doctors;
    vector<Patient> patients;
    minHeap *dqueue;
    
    void simulateWithDoctors(int numDoctors, float& averageWaitingTime, const string& filename, bool print);
    int findNextAvailableDoctor(int currentTime);
    void updateDoctorAvailability(int doctorId, int busyUntil);
    int getNextDoctorAvailabilityTime(int currentTime);
    bool areAnyDoctorsBusy(int currentTime);

public:
    HospitalSimulationMgr(int maxAverageWaitingTime, const string& filename);
    ~HospitalSimulationMgr();

    void readPatientData(const string& filename); // Read patient data from a file
    int findOptimalNumberOfDoctors(const string& filename);

};

#endif /* HospitalSimulationMgr_h */
