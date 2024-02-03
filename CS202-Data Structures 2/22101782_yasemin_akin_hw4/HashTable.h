/**
* Title: Hash Tables
* Author: Yasemin Akın
* ID: 22101782
* Section: 001
* Homework: 4
* Description: HashTable.h file contains the definition of a HashTable */

#ifndef HashTable_h
#define HashTable_h

#include <stdio.h>
#include "KmerNode.h"
#include <fstream>
#include <iostream>
#include <algorithm>

class HashTable {
    
public:
    HashTable();
    ~HashTable();

    // Separate Chaining Functions
    void addKmer_chain(string kmer, int position);
    void fillHashTable_chain(string filename, int k);
    KmerNode* findKmer_chain(string kmer);

    // Quadratic Probing Functions
    void addKmer_quadratic(string kmer, int position);
    void fillHashTable_quadratic(string filename, int k);
    KmerNode* findKmer_quadratic(string kmer);
    
    void printAll_chain() const;
    void printAll_quadratic() const;
    void go_to_positions(string inputFileName, int range, KmerNode *found);

private:
    static const int SEPERATE_CHANING_TABLE_SIZE = 7;
    static const int QUADRATIC_PROBING_TABLE_SIZE = 71;

    KmerNode* seperateChaningHashTable[SEPERATE_CHANING_TABLE_SIZE];
    KmerNode* quadraticProbingHashTable[QUADRATIC_PROBING_TABLE_SIZE];

    int hashFunctionSeperateChaining(const string& kmer) const;
    int hashFunctionQuadraticProbing(const string& kmer) const;
    string toLowerCase(string str);
    int quadtraticProbingSize = 0;
};

#endif /* HashTable_h */
