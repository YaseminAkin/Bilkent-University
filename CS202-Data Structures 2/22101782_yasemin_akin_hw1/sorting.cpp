/**
* Title: Algorithm analysis & Sorting
* Author : Yasemin Akın
* ID: 22101782
* Section : 001
* Homework : 1
* Description : implementation of required sorting algorithms */

#include <stdio.h>
#include "sorting.h"
using namespace std;
// --------------------------------------------------------------------------------------
void sorting::insertionSort(int *arr, const int size, int &compCount, int &moveCount) {
    for (int unsorted = 1; unsorted < size; ++unsorted) {
        int nextItem = arr[unsorted];
        moveCount++;
        int loc = unsorted;

        for (; (loc > 0) && (arr[loc - 1] > nextItem); --loc) {
            compCount++;
            arr[loc] = arr[loc - 1]; // Shift the element to the right
            moveCount++;
        }
        arr[loc] = nextItem; // Insert the 'nextItem' in the correct position
        moveCount++;
        compCount++;
    }
}
// --------------------------------------------------------------------------------------
void sorting::swap(int &x, int &y, int &moveCount) {
    int temp = x;
    x = y;
    y = temp;
    moveCount = moveCount + 3;
}

int sorting::indexOfLargest(const int *arr, int size, int &compCount) {
    int indexSoFar = 0;
    for (int currentIndex=1; currentIndex < size; ++currentIndex) {
        if (arr[currentIndex] > arr[indexSoFar]) {
            indexSoFar = currentIndex;
        }
        compCount++;
    }
    return indexSoFar;
}

void sorting::selectionSort (int *arr, const int size, int &compCount, int &moveCount){
    for (int last = size-1; last >= 1; --last) {
        int largest = indexOfLargest(arr, last+1, compCount);
        swap(arr[largest], arr[last], moveCount);
      }
}
// --------------------------------------------------------------------------------------
// merges the sub-arrays into a sorted, complete array
void sorting::merge (int *arr, int left, int middle, int right, int &compCount, int &moveCount){
    int *merged = new int [1+right-left]; //temporary array which the sorted elements placed to
    int tmpIndex = 0, firstHalfBeginning = left, secondHalfBeginning = 1+middle; //variable to store the size-1 of the currently sorted-merged array, first half's starting index, second half's starting index
    while(firstHalfBeginning <= middle && secondHalfBeginning <= right){
        if(arr[firstHalfBeginning] > arr[secondHalfBeginning]){
            
            merged[tmpIndex] = arr[secondHalfBeginning];
            moveCount++;
            tmpIndex++;
            secondHalfBeginning++;
        }
        else{
            merged[tmpIndex] = arr[firstHalfBeginning];
            moveCount++;
            tmpIndex++;
            firstHalfBeginning++;
        }
        compCount++;
    }
    while(firstHalfBeginning <= middle){
        merged[tmpIndex] = arr[firstHalfBeginning];
        tmpIndex++;
        firstHalfBeginning++;
        moveCount++;
    }
    while(secondHalfBeginning <= right){
        merged[tmpIndex] = arr[secondHalfBeginning];
        tmpIndex++;
        secondHalfBeginning++;
        moveCount++;
    }
    for(int i = 0; i < tmpIndex; i++){
        arr[left+i] = merged[i];
        moveCount++;
    }
    delete [] merged;
}

// main recursive mergeSort function which calls the merge function at the end
void sorting::mergesort (int *arr, int first, int last, int &compCount, int &moveCount){
    
    if (first < last) {
      int mid = (first + last)/2;       // index of midpoint
      mergesort(arr, first, mid, compCount, moveCount);
      mergesort(arr, mid+1, last, compCount, moveCount);
      // merge the two halves
      merge(arr, first, mid, last, compCount, moveCount);
    }
}

// function which calls the main recursive function which has different parameters
void sorting::mergeSort (int *arr, const int size, int &compCount, int &moveCount){
    // calling the helper recursive function
    mergesort(arr, 0, size-1, compCount, moveCount);
}
// --------------------------------------------------------------------------------------
void sorting::partition(int *arr, int first, int last, int &pivotIndex, int &compCount, int &moveCount) {
    // Precondition: theArray[first..last] is an array; first <= last.
    // Postcondition: Partitions theArray[first..last] such that:
    //   S1 = theArray[first..pivotIndex-1] < pivot
    //   theArray[pivotIndex] == pivot
    //   S2 = theArray[pivotIndex+1..last] >= pivot
   
    // place pivot in theArray[first]
    // choosePivot(arr, first, last);

    int pivot = arr[first];              // copy pivot
    moveCount++;
    // initially, everything but pivot is in unknown
       int lastS1 = first;              // index of last item in S1
       int firstUnknown = first + 1;    // index of first item in unknown
       
        // move one item at a time until unknown region is empty
       for (  ; firstUnknown <= last; ++firstUnknown) {
           // Invariant: theArray[first+1..lastS1] < pivot
           //            theArray[lastS1+1..firstUnknown-1] >= pivot

           // move item from unknown to proper region
           if (arr[firstUnknown] < pivot) {  // belongs to S1
               ++lastS1;
               swap(arr[firstUnknown], arr[lastS1], moveCount);
           }  // else belongs to S2
           compCount++;
       }
       // place pivot in proper position and mark its location
       swap(arr[first], arr[lastS1], moveCount);
       pivotIndex = lastS1;
}

void sorting::quicksort(int *arr, int first, int last, int &compCount, int &moveCount) {
// Precondition: theArray[first..last] is an array.
// Postcondition: theArray[first..last] is sorted.
    int pivotIndex;

    if (first < last) {
        // create the partition: S1, pivot, S2
        partition(arr, first, last, pivotIndex, compCount, moveCount);

        // sort regions S1 and S2
        quicksort(arr, first, pivotIndex-1, compCount, moveCount);
        quicksort(arr, pivotIndex+1, last, compCount, moveCount);
   }
}

void sorting::quickSort (int *arr, const int size, int &compCount, int &moveCount){
    quicksort(arr, 0, size-1, compCount, moveCount);
}
// --------------------------------------------------------------------------------------
void sorting::bubbleSort(int *arr, int n, int &compCount, int &moveCount) {
    bool sorted = false;
    
    for (int pass = 1; (pass < n) && !sorted; ++pass) {
        sorted = true;
        for (int index = 0; index < n - pass; ++index) {
            int nextIndex = index + 1;
            if (arr[index] > arr[nextIndex]) {
                swap(arr[index], arr[nextIndex], moveCount);
                sorted = false;
            }
            compCount++;
        }
    }
}

void sorting::hybridsort(int *arr, int left, int right, int &compCount, int &moveCount) {
    if (left < right) {
        int size = right - left + 1;
        
        if (size <= 20) {
            bubbleSort(arr + left, size, compCount, moveCount);
        } else {
            int mid = (left + right) / 2;
            hybridsort(arr, left, mid, compCount, moveCount);
            hybridsort(arr, mid + 1, right, compCount, moveCount);
            
            // Merge the two sorted halves.
            merge(arr, left, mid, right, compCount, moveCount);
        }
    }
}

void sorting::hybridSort (int *arr, const int size, int &compCount, int &moveCount){
    hybridsort(arr, 0, size-1, compCount, moveCount);
}
// --------------------------------------------------------------------------------------
