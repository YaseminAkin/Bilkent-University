/**
* Title: Algorithm analysis & Sorting
* Author : Yasemin Akın
* ID: 22101782
* Section : 001
* Homework : 1
* Description : Header file for sorting.cpp
*/

#ifndef sorting_h
#define sorting_h
class sorting {
public:
    void insertionSort (int *arr, const int size, int &compCount, int &moveCount);
    void swap(int &x, int &y, int &moveCount);
    int indexOfLargest(const int *arr, int size, int &compCount);
    void selectionSort (int *arr, const int size, int &compCount, int &moveCount);
    void merge (int *arr, int left, int middle, int right, int &compCount, int &moveCount);
    void mergesort (int *arr, int first, int last, int &compCount, int &moveCount);
    void mergeSort (int *arr, const int size, int &compCount, int &moveCount);
    void partition(int *arr, int first, int last, int &pivotIndex, int &compCount, int &moveCount);
    void quicksort(int *arr, int first, int last, int &compCount, int &moveCount);
    void quickSort (int *arr, const int size, int &compCount, int &moveCount);
    void bubbleSort(int *arr, int n, int &compCount, int &moveCount);
    void hybridsort(int *arr, int left, int right, int &compCount, int &moveCount);
    void hybridSort (int *arr, const int size, int &compCount, int &moveCount);
};

#endif /* sorting_h */
