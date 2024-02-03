/**
* Title: Binary Search Trees
* Author : Yasemin Akın
* ID: 22101782
* Section : 001
* Homework : 2
* Description : header file for the pointer-based implementation of Binary Search Tree whose keys are strings
*/

#ifndef BST_h
#define BST_h

#include <stdio.h>
#include "BSTNode.h"
#include <vector>

class BST {
    
public:
    BST();
    BST(const BST& tree);
    ~BST();
    void searchTreeInsert(string key);
    void searchTreeDelete(string key);
    vector<string> inorderTraversal(BSTNode* root);
    BSTNode* getRoot();
    BSTNode* searchTreeRetrieve(string kmer, BSTNode* root);
    
private:
    BSTNode *root;
    void destruct(BSTNode*& root);
    void insertItem(string &key, BSTNode *&root);
    void deleteItem(string &keySearch, BSTNode *&root);
    void deleteNodeItem(BSTNode *&deleteNode);
    void processLeftmost(BSTNode *&nodePtr, string &item);
    void inorderTraversal(vector<string>& vec, BSTNode* root);
};

#endif /* BST_h */
