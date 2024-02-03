#/**
#* Author : Yasemin Akın
#* ID: 22101782
#* Section : 001
#* Homework : 3
#* Description : Makefile for the Hospital Simulation*/

simulator: Patient.o maxHeap.o minHeap.o PriorityQueue.o HospitalSimulationMgr.o
	g++ Patient.o maxHeap.o minHeap.o PriorityQueue.o HospitalSimulationMgr.o -o simulator

Patient.o: Patient.cpp Patient.h
	g++ -c Patient.cpp
	
maxHeap.o: maxHeap.cpp maxHeap.h
	g++ -c maxHeap.cpp
	
minHeap.o: minHeap.cpp minHeap.h
	g++ -c minHeap.cpp

PriorityQueue.o: PriorityQueue.cpp PriorityQueue.h
	g++ -c PriorityQueue.cpp

HospitalSimulationMgr.o: HospitalSimulationMgr.cpp HospitalSimulationMgr.h
	g++ -c HospitalSimulationMgr.cpp

clean:
	rm *.o simulator
