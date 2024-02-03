/**
* Title: Binary Search Trees
* Author : Yasemin Akın
* ID: 22101782
* Section : 001
* Homework : 2
* Description : header file for the pointer-based implementation of Binary Search Tree Node whose keys are strings
*/

#ifndef BSTNode_h
#define BSTNode_h

#include <stdio.h>
using namespace std;
#include <string>

class BSTNode {
    
public:
    string getItem() const;
    int getFrequency() const;
    void incrementFrequency();
    BSTNode* getLeftChildPtr();
    BSTNode* getRightChildPtr();
    
private:
    BSTNode();
    BSTNode(const string& nodeItem, BSTNode *left = NULL, BSTNode *right = NULL);
    string item;
    int frequency;
    BSTNode *leftChildPtr;
    BSTNode *rightChildPtr;
    friend class BST;
};

#endif /* BSTNode_h */
