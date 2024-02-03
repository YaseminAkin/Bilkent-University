/**
* Title: Hash Tables
* Author: Yasemin Akın
* ID: 22101782
* Section: 001
* Homework: 4
* Description: KmerNode.h file contains the definition of a KmerNode */

#ifndef KmerNode_h
#define KmerNode_h

#include <stdio.h>
using namespace std;
#include <string>
#include <vector>

class KmerNode {
    
public:
    KmerNode();
    KmerNode(const string& kmer, vector<int> startPosVector, KmerNode* nextKmer = NULL) : kmer(kmer), startPosVector(startPosVector), nextKmer(nextKmer) {}
    string getKmer() const {
        return kmer;
    }
    vector<int> getStartPosVector() const {
        return this->startPosVector;
    }
    KmerNode* getNextKmer() const {
        return this->nextKmer;
    }
    void setNextKmer(KmerNode* newKmer) {
        this->nextKmer = newKmer;
    }
    void addPosition(int position) {
        startPosVector.push_back(position);
    }
    
private:
    string kmer;
    vector<int> startPosVector;
    KmerNode* nextKmer;
};

#endif /* KmerNode_h */
