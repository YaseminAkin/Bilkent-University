/**
* Author : Yasemin Akın
* ID: 22101782
* Section : 001
* Homework : 3
* Description : implementation of Hospital Simulation, including the main function*/

#include <stdio.h>
#include "HospitalSimulationMgr.h"
#include <limits>

int main(int argc, const char * argv[]) {
    
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <filename> <awaitingTime>" << endl;
        return 1;
    }

    string filename = argv[1];
    int avgwaitingTime = stoi(argv[2]);
    
    ifstream file(filename);
        if (!file) {
            cerr << "Error: File could not be opened." << endl;
            return 0;
        }

    HospitalSimulationMgr simulation (avgwaitingTime, filename);
    simulation.findOptimalNumberOfDoctors(filename);

    return 0;
}

HospitalSimulationMgr::HospitalSimulationMgr(int awaitingTime, const string& filename) : pq(nullptr), dqueue(nullptr), maxAverageWaitingTime(awaitingTime) {
    readPatientData(filename); // Load patient data to the patients vector

}

HospitalSimulationMgr::~HospitalSimulationMgr() {
    delete pq;
    delete dqueue;
}

void HospitalSimulationMgr::readPatientData(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: File could not be opened." << endl;
        return;
    }

    int numPatients;
    file >> numPatients;

    pq = new PriorityQueue(numPatients);
    
    for (int i = 0; i < numPatients; i++) {
        int id, priority, arrivalTime, serviceTime;
        file >> id >> priority >> arrivalTime >> serviceTime;
        Patient newPatient(id, priority, arrivalTime, serviceTime);
        patients.emplace_back(id, priority, arrivalTime, serviceTime);
    }

    file.close();
}

// Starter method
int HospitalSimulationMgr::findOptimalNumberOfDoctors(const string& filename) {
    int numDoctors = 1;
    
    float averageWaitingTime = std::numeric_limits<float>::max(); // Ensure that the initial averageWaitingTime is always larger than the input value, so that the simulation will definitely enter the following loop
    while (averageWaitingTime > maxAverageWaitingTime) {
        dqueue = new minHeap(numDoctors);
        simulateWithDoctors(numDoctors, averageWaitingTime, filename, false);
        if (averageWaitingTime > maxAverageWaitingTime) {
            numDoctors++;
        }
        delete dqueue;
    }
    dqueue = new minHeap(numDoctors);
    cout<<endl;
    cout<<"Minimum number of doctors required: "<<numDoctors<<endl;
    cout<<endl;
    simulateWithDoctors(numDoctors, averageWaitingTime, filename, true);
    return numDoctors;
}

void HospitalSimulationMgr::simulateWithDoctors(int numDoctors, float& averageWaitingTime, const string& filename, bool print) {
    doctors.clear();
    
    for (int i = 0; i < numDoctors; ++i) {
        doctors.emplace_back(i);
        dqueue->heapInsert(doctors[i]); // Add doctors to the priority queue
    }

    int currentTime = 0;
    int totalWaitingTime = 0;
    int numTreatedPatients = 0;
    int patientIndex = 0;

    if(print) {
        cout <<"Simulation with "<<numDoctors<<" doctors:" << endl;
        cout<<endl;
    }

    while (patientIndex < patients.size() || !pq->pqIsEmpty()) {
        // Check and add new arriving patients to the priority queue
        while (patientIndex < patients.size() && patients[patientIndex].getArrivalTime() <= currentTime) {
            pq->pqInsert(patients[patientIndex]);
            patientIndex++;
        }

        // Assign next patient to a doctor if available
        if (!pq->pqIsEmpty()) {
            Patient currentPatient;
            
            int doctorId = findNextAvailableDoctor(currentTime);
            if (doctorId != -1) {
                pq->pqDelete(currentPatient); // Get the next patient
                currentTime = max(currentTime, doctors[doctorId].availableAtTime);
                int waitingTime = currentTime - currentPatient.getArrivalTime();
                totalWaitingTime += waitingTime;

                if(print) {
                    cout << "Doctor " << doctorId << " takes patient " << currentPatient.getId()
                    << " at minute " << currentTime
                    << " (wait: " << waitingTime << " mins)" << endl;
                }

                updateDoctorAvailability(doctorId, currentTime + currentPatient.getServiceTime());

                numTreatedPatients++;
            }
            else {
                // Advance time to when the next doctor becomes available
                currentTime = getNextDoctorAvailabilityTime(currentTime);
            }
        } else if (patientIndex < patients.size()) {
            // Advance time to the next patient's arrival if there are no patients in the queue
            currentTime = max(currentTime, patients[patientIndex].getArrivalTime());
        } else {
            // Advance time to when the next doctor becomes available
            currentTime = getNextDoctorAvailabilityTime(currentTime);
        }
    }
    averageWaitingTime = (numTreatedPatients > 0) ? (float)(totalWaitingTime) / numTreatedPatients : 0.0f;
    cout<<endl;
    if(print) {cout <<"Average waiting time: "<<averageWaitingTime<<" minutes" << endl;}
    cout<<endl;
}


int HospitalSimulationMgr::getNextDoctorAvailabilityTime(int currentTime) {
    int nextAvailableTime = numeric_limits<int>::max();
    for (const auto& doctor : doctors) {
        if (doctor.availableAtTime > currentTime) {
            nextAvailableTime = min(nextAvailableTime, doctor.availableAtTime);
        }
    }
    return nextAvailableTime;
}

int HospitalSimulationMgr::findNextAvailableDoctor(int currentTime) {

    while (!dqueue->heapIsEmpty() && dqueue->getMin().availableAtTime <= currentTime) {
            int doctorId = dqueue->getMin().id;
        dqueue->heapDelete(); // Remove the doctor from the queue
            return doctorId;
        }
        return -1; // No available doctor found
}

void HospitalSimulationMgr::updateDoctorAvailability(int doctorId, int busyUntil) {
    if (doctorId >= 0 && doctorId < doctors.size()) {
        doctors[doctorId].availableAtTime = busyUntil;
        dqueue->heapInsert(doctors[doctorId]);
    }
}
