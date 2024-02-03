/**
* Title: Binary Search Trees
* Author : Yasemin Akın
* ID: 22101782
* Section : 001
* Homework : 2
* Description : header  file for the pointer-based implementation of Kmer Tree whose keys are k-mers
*/

#ifndef KmerTree_h
#define KmerTree_h

#include <stdio.h>
#include "BST.h"
#include <fstream>
#include <algorithm>
#include <iostream>

class KmerTree {
public:
    void addKmer(string kmer);
    void generateTree(string fileName, int k);
    int getUniqueKmerCount();
    int getNumberOfKmerThatStartWith(char ch);
    void printAll();
    int getHeight();
    void inorderTraverse(vector<string>& inorder_vect);
    void searchTreeDelete(string key);
    
private:
    BST kmerTree;
    string toLowerCase(string str);
    int getUniqueKmerCountHelper(BSTNode* root);
    int getNumberOfKmerThatStartWithHelper(BSTNode* root, char ch);
    int getHeightHelper(BSTNode* root);
};

#endif /* KmerTree_h */
