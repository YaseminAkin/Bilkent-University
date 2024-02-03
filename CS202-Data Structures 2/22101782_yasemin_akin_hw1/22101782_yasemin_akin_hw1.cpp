/**
* Title: Algorithm analysis & Sorting
* Author : Yasemin Akın
* ID: 22101782
* Section : 001
* Homework : 1
* Description : main file for generating arrays and calling sorting functions */

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "sorting.h"
#include <cmath>
#include <ctime>
using namespace std;

//function to create 5 identical arrays of random integers in passed size value
void createRandom(const int size, int *arrInsertion, int *arrSelection, int *arrMerge, int *arrQuick, int *arrHybrid){
    srand((int)time(0));
    for(int i = 0; i < size; i++){
        int random = rand()%size;
        arrInsertion[i] = random;
        arrSelection[i] = random;
        arrMerge[i] = random;
        arrQuick[i] = random;
        arrHybrid[i] = random;
    }
}

void createAscending(const int size, int *arrInsertion, int *arrSelection, int *arrMerge, int *arrQuick, int *arrHybrid){
    int j = 0;
    srand((int)time(0));
    for(int i = 1; i <= size/log2(size)+1; i++){
        for(; j < size && j < log2(size)*i; j++){
            int random = rand()%size+size*i;
            arrInsertion[j] = random;
            arrSelection[j] = random;
            arrMerge[j] = random;
            arrQuick[j] = random;
            arrHybrid[j] = random;
        }
    }
}

void createDescending(const int size, int *arrInsertion, int *arrSelection, int *arrMerge, int *arrQuick, int *arrHybrid){
    int k = size-1;
    int j = 0;
    srand((int)time(0));
    for(int i = 1; i <= size/log2(size)+1; i++){
        for(; j < size && j < log2(size)*i; j++){
            int random = rand()%size+size*i;
            arrInsertion[k] = random;
            arrSelection[k] = random;
            arrMerge[k] = random;
            arrQuick[k] = random;
            arrHybrid[k] = random;
            k--;
        }
    }
}

void printTableHeader(int size) {
    std::cout << "------------------------------------------------------------------------------------\n";
    std::cout << std::left << std::setw(24) << "";
    std::cout << std::left << std::setw(24) << "Elapsed Time (ms)";
    std::cout << std::left << std::setw(24) << "Comp. Count";
    std::cout << std::left << "Move Count" << std::endl;
    std::cout << "Array Size: " << size << "\n";
}

void printTableRow(const std::string& algorithm, double time, int compCount, int moveCount) {
    std::cout << std::left << std::setw(24) << algorithm;
    std::cout << std::left << std::setw(24) << time;
    std::cout << std::left << std::setw(24) << compCount;
    std::cout << std::left << moveCount << "\n";
}

void question2b1(const int size) {
    int* arrInsertion = new int[size];
    int* arrSelection = new int[size];
    int* arrMerge = new int[size];
    int* arrQuick = new int[size];
    int* arrHybrid = new int[size];
    createRandom(size, arrInsertion, arrSelection, arrMerge, arrQuick, arrHybrid);

    clock_t clk;
    string print;
    int compCount;
    int moveCount;
    double time;

    printTableHeader(size);
    sorting sort = sorting();
    // Insertion Sort
    clk = clock();
    compCount = 0;
    moveCount = 0;
    sort.insertionSort(arrInsertion, size, compCount, moveCount);
    clk = clock() - clk;
    time = (double)clk * 1000 / CLOCKS_PER_SEC;
    printTableRow("Insertion Sort", time, compCount, moveCount);
    delete[] arrInsertion;

    // Selection Sort
    clk = clock();
    compCount = 0;
    moveCount = 0;
    sort.selectionSort(arrSelection, size, compCount, moveCount);
    clk = clock() - clk;
    time = (double)clk * 1000 / CLOCKS_PER_SEC;
    printTableRow("Selection Sort", time, compCount, moveCount);
    delete[] arrSelection;

    // Merge Sort
    clk = clock();
    compCount = 0;
    moveCount = 0;
    sort.mergeSort(arrMerge, size, compCount, moveCount);
    clk = clock() - clk;
    time = (double)clk * 1000 / CLOCKS_PER_SEC;
    printTableRow("Merge Sort", time, compCount, moveCount);
    delete[] arrMerge;

    // Quick Sort
    clk = clock();
    compCount = 0;
    moveCount = 0;
    sort.quickSort(arrQuick, size, compCount, moveCount);
    clk = clock() - clk;
    time = (double)clk * 1000 / CLOCKS_PER_SEC;
    printTableRow("Quick Sort", time, compCount, moveCount);
    delete[] arrQuick;

    // Hybrid Sort
    clk = clock();
    compCount = 0;
    moveCount = 0;
    sort.hybridSort(arrHybrid, size, compCount, moveCount);
    clk = clock() - clk;
    time = (double)clk * 1000 / CLOCKS_PER_SEC;
    printTableRow("Hybrid Sort", time, compCount, moveCount);
    delete[] arrHybrid;
}

void question2b2(const int size) {
    int* arrInsertion = new int[size];
    int* arrSelection = new int[size];
    int* arrMerge = new int[size];
    int* arrQuick = new int[size];
    int* arrHybrid = new int[size];
    createAscending(size, arrInsertion, arrSelection, arrMerge, arrQuick, arrHybrid);

    clock_t clk;
    string print;
    int compCount;
    int moveCount;
    double time;

    printTableHeader(size);
    sorting sort = sorting();
    // Insertion Sort
    clk = clock();
    compCount = 0;
    moveCount = 0;
    sort.insertionSort(arrInsertion, size, compCount, moveCount);
    clk = clock() - clk;
    time = (double)clk * 1000 / CLOCKS_PER_SEC;
    printTableRow("Insertion Sort", time, compCount, moveCount);
    delete[] arrInsertion;

    // Selection Sort
    clk = clock();
    compCount = 0;
    moveCount = 0;
    sort.selectionSort(arrSelection, size, compCount, moveCount);
    clk = clock() - clk;
    time = (double)clk * 1000 / CLOCKS_PER_SEC;
    printTableRow("Selection Sort", time, compCount, moveCount);
    delete[] arrSelection;

    // Merge Sort
    clk = clock();
    compCount = 0;
    moveCount = 0;
    sort.mergeSort(arrMerge, size, compCount, moveCount);
    clk = clock() - clk;
    time = (double)clk * 1000 / CLOCKS_PER_SEC;
    printTableRow("Merge Sort", time, compCount, moveCount);
    delete[] arrMerge;

    // Quick Sort
    clk = clock();
    compCount = 0;
    moveCount = 0;
    sort.quickSort(arrQuick, size, compCount, moveCount);
    clk = clock() - clk;
    time = (double)clk * 1000 / CLOCKS_PER_SEC;
    printTableRow("Quick Sort", time, compCount, moveCount);
    delete[] arrQuick;

    // Hybrid Sort
    clk = clock();
    compCount = 0;
    moveCount = 0;
    sort.hybridSort(arrHybrid, size, compCount, moveCount);
    clk = clock() - clk;
    time = (double)clk * 1000 / CLOCKS_PER_SEC;
    printTableRow("Hybrid Sort", time, compCount, moveCount);
    delete[] arrHybrid;
}

void question2b3(const int size) {
    int* arrInsertion = new int[size];
    int* arrSelection = new int[size];
    int* arrMerge = new int[size];
    int* arrQuick = new int[size];
    int* arrHybrid = new int[size];
    createDescending(size, arrInsertion, arrSelection, arrMerge, arrQuick, arrHybrid);

    clock_t clk;
    string print;
    int compCount;
    int moveCount;
    double time;

    printTableHeader(size);
    sorting sort = sorting();
    // Insertion Sort
    clk = clock();
    compCount = 0;
    moveCount = 0;
    sort.insertionSort(arrInsertion, size, compCount, moveCount);
    clk = clock() - clk;
    time = (double)clk * 1000 / CLOCKS_PER_SEC;
    printTableRow("Insertion Sort", time, compCount, moveCount);
    delete[] arrInsertion;

    // Selection Sort
    clk = clock();
    compCount = 0;
    moveCount = 0;
    sort.selectionSort(arrSelection, size, compCount, moveCount);
    clk = clock() - clk;
    time = (double)clk * 1000 / CLOCKS_PER_SEC;
    printTableRow("Selection Sort", time, compCount, moveCount);
    delete[] arrSelection;

    // Merge Sort
    clk = clock();
    compCount = 0;
    moveCount = 0;
    sort.mergeSort(arrMerge, size, compCount, moveCount);
    clk = clock() - clk;
    time = (double)clk * 1000 / CLOCKS_PER_SEC;
    printTableRow("Merge Sort", time, compCount, moveCount);
    delete[] arrMerge;

    // Quick Sort
    clk = clock();
    compCount = 0;
    moveCount = 0;
    sort.quickSort(arrQuick, size, compCount, moveCount);
    clk = clock() - clk;
    time = (double)clk * 1000 / CLOCKS_PER_SEC;
    printTableRow("Quick Sort", time, compCount, moveCount);
    delete[] arrQuick;

    // Hybrid Sort
    clk = clock();
    compCount = 0;
    moveCount = 0;
    sort.hybridSort(arrHybrid, size, compCount, moveCount);
    clk = clock() - clk;
    time = (double)clk * 1000 / CLOCKS_PER_SEC;
    printTableRow("Hybrid Sort", time, compCount, moveCount);
    delete[] arrHybrid;
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        std::cout << arr[i];
        if (i < size - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}

int main() {
//    print header for part 2b1
    cout<<"            Part 2-b-1: Performance analysis of random integers array"<<endl;
    question2b1(1000);
    question2b1(5000);
    question2b1(10000);
    question2b1(20000);
    cout<<"\n"<<endl;
//    print header for part 2b2
    cout<<"             Part 2-b-2: Performance analysis of ascending integers array"<<endl;
    question2b2(1000);
    question2b2(5000);
    question2b2(10000);
    question2b2(20000);
    cout<<"\n"<<endl;
//    print header for part 2b3
    cout<<"             Part 2-b-3: Performance analysis of descending integers array"<<endl;
    question2b3(1000);
    question2b3(5000);
    question2b3(10000);
    question2b3(20000);
    cout<<"\n"<<endl;
    return 0;
}
