/**
* Author : Yasemin Akın
* ID: 22101782
* Section : 001
* Homework : 3
* Description : implementation file for a min heap*/

#include "minHeap.h"

minHeap::minHeap(int capacity) {
    this->capacity = capacity;
    this->size = 0;
    this->doctors = new Doctor[this->capacity];
}

bool minHeap::heapIsEmpty() const {
    return (size == 0);
}

int minHeap::getSize(){ return size;}

void minHeap::heapInsert(const Doctor& newDoctor) {
    if (size >= capacity) { return; }
    // Place the new item at the end of the heap
    doctors[size] = newDoctor;

    // Trickle new item up to its proper position
    int place = size;
    int parent = (place - 1) / 2;
    while (place > 0 && (doctors[place].availableAtTime < doctors[parent].availableAtTime ||
                         (doctors[place].availableAtTime == doctors[parent].availableAtTime && doctors[place].id < doctors[parent].id))) {
        swap(doctors[place], doctors[parent]);
        place = parent;
        parent = (place - 1) / 2;
    }
    ++size;
}

void minHeap::heapDelete() {
    if (heapIsEmpty()) {return;}
    else {
        doctors[0] = doctors[--size];
        heapRebuild(0);
    }
}

void minHeap::heapRebuild(int root) {
    int child = 2 * root + 1; // Index of root's left child, if any
    if (child < size) {
        // Find the right child's index, if it exists
        int rightChild = child + 1;

        // Determine which child to compare with
        if (rightChild < size && (doctors[rightChild].availableAtTime < doctors[child].availableAtTime ||
                                  (doctors[rightChild].availableAtTime == doctors[child].availableAtTime && doctors[rightChild].id < doctors[child].id))) {
            child = rightChild;
        }

        // If root’s item is larger than the selected child, swap values
        if (doctors[root].availableAtTime > doctors[child].availableAtTime ||
            (doctors[root].availableAtTime == doctors[child].availableAtTime && doctors[root].id > doctors[child].id)) {
            swap(doctors[root], doctors[child]);
            heapRebuild(child); // Transform the new subtree into a heap
        }
    }
}

void minHeap::swap(Doctor& a, Doctor& b) {
    Doctor temp = a;
    a = b;
    b = temp;
}

Doctor minHeap::getMin() {
    return doctors[0];
}
