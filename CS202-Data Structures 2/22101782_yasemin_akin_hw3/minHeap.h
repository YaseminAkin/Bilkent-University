/**
* Author : Yasemin Akın
* ID: 22101782
* Section : 001
* Homework : 3
* Description : header file for a min heap*/

#ifndef minHeap_h
#define minHeap_h

#include <stdio.h>

class Doctor {
    
public:
    int id;
    int availableAtTime;

    Doctor(int id) : id(id), availableAtTime(0) {}
    Doctor(){};
    bool operator>(const Doctor& other) const {
            return availableAtTime > other.availableAtTime;
        }
};

class minHeap {
    
public:
    minHeap(int capacity);
    bool heapIsEmpty() const;
    void heapInsert(const Doctor& newDoctor);
    void heapDelete();
    Doctor getMin();
    int getSize();
    
protected:
    void heapRebuild(int root);
    void swap(Doctor& a, Doctor& b);
    
private:
    Doctor *doctors;
    int size;
    int capacity;
};
#endif /* minHeap_h */
