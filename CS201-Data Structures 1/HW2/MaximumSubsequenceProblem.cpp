//
//  MaximumSubsequenceProblem.cpp
//  HW2
//
//  Created by Yasemin Akın on 27.04.2023.
//

#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <iostream>
using namespace std;

int maxSubSum1 (int*& a, int size) {
    int maxSum = 0;
    
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            int thisSum = 0;
            for (int k = i; k <= j; k++) {
                thisSum += a[k];
            }
            if (thisSum > maxSum) {
                maxSum = thisSum;
            }
        }
    }
    return maxSum;
}

int maxSubSum2 (int*& a, int size) {
    int maxSum = 0;
    
    for (int i = 0; i < size; i++) {
        int thisSum = 0;
        for (int j = i; j < size; j++) {
            thisSum += a[j];
            
            if (thisSum > maxSum) {
                maxSum = thisSum;
            }
        }
    }
    return maxSum;
}

int max3 (int one, int two, int three) {
    int max = one;
    if(two > one) {
        max = two;
        if(three > two) {
            max = three;
        }
    }
    if(three > one) {
        max = three;
        if(two > three) {
            max = two;
        }
    }
    return max;
}

int maxSumRec (int*& a, int left, int rigth) {
    if(left == rigth) {
        if(a[left] > 0) {
            return a[left];
        }
        else {
            return 0;
        }
    }
    
    int center = (left + rigth) / 2;
    int maxLeftSum = maxSumRec(a, left, center);
    int maxRightSum = maxSumRec(a, center + 1, rigth);
    
    int maxLeftBorderSum = 0, leftBorderSum = 0;
    for (int i = center; i >= left; i--) {
        leftBorderSum += a[i];
        if (leftBorderSum > maxLeftBorderSum) {
            maxLeftBorderSum = leftBorderSum;
        }
    }
    
    int maxRightBorderSum = 0, rightBorderSum = 0;
    for (int j = center + 1; j <= rigth; j++) {
        rightBorderSum += a[j];
        if (rightBorderSum > maxRightBorderSum) {
            maxRightBorderSum = rightBorderSum;
        }
    }
    
    return max3 (maxLeftSum, maxRightSum, maxLeftBorderSum + maxRightBorderSum);
}

int maxSubSum3 (int*& a, int size) {
    return maxSumRec(a, 0, size - 1);
}

int maxSubSum4 (int*& a, int size) {
    int maxSum = 0, thisSum = 0;
    
    for (int j = 0; j < size; j++) {
        thisSum += a[j];
        
        if(thisSum > maxSum) {
            maxSum = thisSum;
        }
        else if (thisSum < 0) {
            thisSum = 0;
        }
    }
    
    return maxSum;
}

void createRandom(const int size, int *arr1, int *arr2, int *arr3, int *arr4){
    srand((int)time(0));
    for(int i = 0; i < size; i++){
        int random = rand()%size;
        arr1[i] = random;
        arr2[i] = random;
        arr3[i] = random;
        arr4[i] = random;
    }
}

int main () {
    // Declare necessary variables
    std::chrono::time_point<std::chrono::system_clock > startTime;
    std::chrono::duration< double, milli > elapsedTime;
    // Store the starting time
    int size = 10;
    int* arr1 = new int[size];
    int* arr2 = new int[size];
    int* arr3 = new int[size];
    int* arr4 = new int[size];
    createRandom(size, arr1, arr2, arr3, arr4);
    startTime = std::chrono::system_clock::now();
    maxSubSum1(arr1, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 1 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum2(arr2, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 2 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum3(arr3, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 3 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum4(arr4, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 4 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    
    cout<<endl;
    
    size = 50;
    arr1 = new int[size];
    arr2 = new int[size];
    arr3 = new int[size];
    arr4 = new int[size];
    createRandom(size, arr1, arr2, arr3, arr4);
    startTime = std::chrono::system_clock::now();
    maxSubSum1(arr1, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 1 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum2(arr2, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 2 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum3(arr3, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 3 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum4(arr4, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 4 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    
    cout<<endl;

    
    size = 100;
    arr1 = new int[size];
    arr2 = new int[size];
    arr3 = new int[size];
    arr4 = new int[size];
    createRandom(size, arr1, arr2, arr3, arr4);
    startTime = std::chrono::system_clock::now();
    maxSubSum1(arr1, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 1 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum2(arr2, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 2 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum3(arr3, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 3 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum4(arr4, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 4 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    
    cout<<endl;

    size = 1000;
    arr1 = new int[size];
    arr2 = new int[size];
    arr3 = new int[size];
    arr4 = new int[size];
    createRandom(size, arr1, arr2, arr3, arr4);
    startTime = std::chrono::system_clock::now();
    maxSubSum1(arr1, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 1 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum2(arr2, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 2 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum3(arr3, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 3 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum4(arr4, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 4 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    
    cout<<endl;
    
    size = 2500;
    arr1 = new int[size];
    arr2 = new int[size];
    arr3 = new int[size];
    arr4 = new int[size];
    createRandom(size, arr1, arr2, arr3, arr4);
    startTime = std::chrono::system_clock::now();
    maxSubSum1(arr1, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 1 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum2(arr2, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 2 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum3(arr3, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 3 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum4(arr4, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 4 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    
    cout<<endl;


    size = 5000;
    arr1 = new int[size];
    arr2 = new int[size];
    arr3 = new int[size];
    arr4 = new int[size];
    createRandom(size, arr1, arr2, arr3, arr4);
    startTime = std::chrono::system_clock::now();
    maxSubSum1(arr1, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 1 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum2(arr2, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 2 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum3(arr3, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 3 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum4(arr4, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 4 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    
    cout<<endl;
    
    size = 7500;
    arr1 = new int[size];
    arr2 = new int[size];
    arr3 = new int[size];
    arr4 = new int[size];
    createRandom(size, arr1, arr2, arr3, arr4);
    startTime = std::chrono::system_clock::now();
    maxSubSum1(arr1, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 1 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum2(arr2, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 2 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum3(arr3, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 3 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum4(arr4, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 4 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    
    cout<<endl;
    
    size = 9000;
    arr1 = new int[size];
    arr2 = new int[size];
    arr3 = new int[size];
    arr4 = new int[size];
    createRandom(size, arr1, arr2, arr3, arr4);
    startTime = std::chrono::system_clock::now();
    maxSubSum1(arr1, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 1 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum2(arr2, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 2 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum3(arr3, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 3 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum4(arr4, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 4 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    
    cout<<endl;

    size = 10000;
//    arr1 = new int[size];
    arr2 = new int[size];
    arr3 = new int[size];
    arr4 = new int[size];
    createRandom(size, arr1, arr2, arr3, arr4);
//    startTime = std::chrono::system_clock::now();
//    maxSubSum1(arr1, size);
//    // Compute the number of milliseconds that passed since the starting time
//    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 1 for size = "<<size<<" took NA milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum2(arr2, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 2 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum3(arr3, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 3 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum4(arr4, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 4 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    
    cout<<endl;
    
    size = 25000;
//    arr1 = new int[size];
    arr2 = new int[size];
    arr3 = new int[size];
    arr4 = new int[size];
    createRandom(size, arr1, arr2, arr3, arr4);
//    startTime = std::chrono::system_clock::now();
//    maxSubSum1(arr1, size);
//    // Compute the number of milliseconds that passed since the starting time
//    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 1 for size = "<<size<<" took NA milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum2(arr2, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 2 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum3(arr3, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 3 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum4(arr4, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 4 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    
    cout<<endl;

    size = 50000;
//    arr1 = new int[size];
    arr2 = new int[size];
    arr3 = new int[size];
    arr4 = new int[size];
    createRandom(size, arr1, arr2, arr3, arr4);
//    startTime = std::chrono::system_clock::now();
//    maxSubSum1(arr1, size);
//    // Compute the number of milliseconds that passed since the starting time
//    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 1 for size = "<<size<<" took NA milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum2(arr2, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 2 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum3(arr3, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 3 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum4(arr4, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 4 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    
    cout<<endl;

    size = 75000;
//    arr1 = new int[size];
    arr2 = new int[size];
    arr3 = new int[size];
    arr4 = new int[size];
    createRandom(size, arr1, arr2, arr3, arr4);
//    startTime = std::chrono::system_clock::now();
//    maxSubSum1(arr1, size);
//    // Compute the number of milliseconds that passed since the starting time
//    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 1 for size = "<<size<<" took NA milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum2(arr2, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 2 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum3(arr3, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 3 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum4(arr4, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 4 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    
    cout<<endl;
    
    size = 100000;
//    arr1 = new int[size];
    arr2 = new int[size];
    arr3 = new int[size];
    arr4 = new int[size];
    createRandom(size, arr1, arr2, arr3, arr4);
//    startTime = std::chrono::system_clock::now();
//    maxSubSum1(arr1, size);
//    // Compute the number of milliseconds that passed since the starting time
//    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 1 for size = "<<size<<" took NA milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum2(arr2, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 2 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum3(arr3, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 3 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum4(arr4, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 4 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    
    cout<<endl;
    
    size = 500000;
//    arr1 = new int[size];
//    arr2 = new int[size];
    arr3 = new int[size];
    arr4 = new int[size];
    createRandom(size, arr1, arr2, arr3, arr4);
//    startTime = std::chrono::system_clock::now();
//    maxSubSum1(arr1, size);
//    // Compute the number of milliseconds that passed since the starting time
//    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 1 for size = "<<size<<" took NA milliseconds." << endl;
//    startTime = std::chrono::system_clock::now();
//    maxSubSum2(arr2, size);
//    // Compute the number of milliseconds that passed since the starting time
//    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 2 for size = "<<size<<" took NA milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum3(arr3, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 3 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum4(arr4, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 4 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    
    cout<<endl;
    
    size = 1000000;
//    arr1 = new int[size];
//    arr2 = new int[size];
    arr3 = new int[size];
    arr4 = new int[size];
    createRandom(size, arr1, arr2, arr3, arr4);
//    startTime = std::chrono::system_clock::now();
//    maxSubSum1(arr1, size);
//    // Compute the number of milliseconds that passed since the starting time
//    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 1 for size = "<<size<<" took NA milliseconds." << endl;
//    startTime = std::chrono::system_clock::now();
//    maxSubSum2(arr2, size);
//    // Compute the number of milliseconds that passed since the starting time
//    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 2 for size = "<<size<<" took NA milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum3(arr3, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 3 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum4(arr4, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 4 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    
    cout<<endl;
    
    size = 2000000;
//    arr1 = new int[size];
//    arr2 = new int[size];
    arr3 = new int[size];
    arr4 = new int[size];
    createRandom(size, arr1, arr2, arr3, arr4);
//    startTime = std::chrono::system_clock::now();
//    maxSubSum1(arr1, size);
//    // Compute the number of milliseconds that passed since the starting time
//    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 1 for size = "<<size<<" took NA milliseconds." << endl;
//    startTime = std::chrono::system_clock::now();
//    maxSubSum2(arr2, size);
//    // Compute the number of milliseconds that passed since the starting time
//    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 2 for size = "<<size<<" took NA milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum3(arr3, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 3 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum4(arr4, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 4 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    
    cout<<endl;
    
    size = 2500000;
//    arr1 = new int[size];
//    arr2 = new int[size];
    arr3 = new int[size];
    arr4 = new int[size];
    createRandom(size, arr1, arr2, arr3, arr4);
//    startTime = std::chrono::system_clock::now();
//    maxSubSum1(arr1, size);
//    // Compute the number of milliseconds that passed since the starting time
//    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 1 for size = "<<size<<" took NA milliseconds." << endl;
//    startTime = std::chrono::system_clock::now();
//    maxSubSum2(arr2, size);
//    // Compute the number of milliseconds that passed since the starting time
//    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 2 for size = "<<size<<" took NA milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum3(arr3, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 3 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum4(arr4, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 4 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    
    cout<<endl;
    
    size = 3000000;
//    arr1 = new int[size];
//    arr2 = new int[size];
    arr3 = new int[size];
    arr4 = new int[size];
    createRandom(size, arr1, arr2, arr3, arr4);
//    startTime = std::chrono::system_clock::now();
//    maxSubSum1(arr1, size);
//    // Compute the number of milliseconds that passed since the starting time
//    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 1 for size = "<<size<<" took NA milliseconds." << endl;
//    startTime = std::chrono::system_clock::now();
//    maxSubSum2(arr2, size);
//    // Compute the number of milliseconds that passed since the starting time
//    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 2 for size = "<<size<<" took NA milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum3(arr3, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 3 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum4(arr4, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 4 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    
    cout<<endl;
    
    size = 3500000;
//    arr1 = new int[size];
//    arr2 = new int[size];
    arr3 = new int[size];
    arr4 = new int[size];
    createRandom(size, arr1, arr2, arr3, arr4);
//    startTime = std::chrono::system_clock::now();
//    maxSubSum1(arr1, size);
//    // Compute the number of milliseconds that passed since the starting time
//    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 1 for size = "<<size<<" took NA milliseconds." << endl;
//    startTime = std::chrono::system_clock::now();
//    maxSubSum2(arr2, size);
//    // Compute the number of milliseconds that passed since the starting time
//    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 2 for size = "<<size<<" took NA milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum3(arr3, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 3 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    maxSubSum4(arr4, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution of Algorithm 4 for size = "<<size<<" took " << elapsedTime.count() << " milliseconds." << endl;
    
    cout<<endl;
    
    return 0;
}
