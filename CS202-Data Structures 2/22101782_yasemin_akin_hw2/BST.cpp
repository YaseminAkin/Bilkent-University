/**
* Title: Binary Search Trees
* Author : Yasemin Akın
* ID: 22101782
* Section : 001
* Homework : 2
* Description : cpp file for the pointer-based implementation of Binary Search Tree whose keys are strings
*/

#include "BST.h"
#include <iostream>
using namespace std;

//-------------------------------------------------------------------------------------------------------------
//Default Constructor
BST::BST() {
    root = NULL;
}
//Copy Constructor
BST::BST(const BST& tree) {
    root = tree.root;
}
//-------------------------------------------------------------------------------------------------------------
//Destructor
BST::~BST() {
    destruct(root);
}
//Destructor helper function
void BST::destruct(BSTNode*& root) {
    if(root!=NULL){
        if((root->rightChildPtr == NULL)&&(root->leftChildPtr == NULL)){
            delete root;
            root = NULL;
        }
        else{
            destruct(root->leftChildPtr);
            destruct(root->rightChildPtr);
        }
    }
}
//-------------------------------------------------------------------------------------------------------------
BSTNode* BST::getRoot() {
    return this->root;
}
//-------------------------------------------------------------------------------------------------------------
//Insertion Functions
void BST::searchTreeInsert(string key) {
    insertItem(key, root);
}
void BST::insertItem(string& key, BSTNode*& treePtr) {
    if(treePtr == NULL){
        treePtr = new BSTNode(key, NULL, NULL);
    }
    else if(key == treePtr->item){return;}
    else if(key < treePtr->item){
        insertItem(key, treePtr->leftChildPtr);
    }
    else{
        insertItem(key, treePtr->rightChildPtr);
    }
}
//-------------------------------------------------------------------------------------------------------------
//Deletion Functions
void BST::searchTreeDelete(string key) {
    deleteItem(key, root);
}
void BST::deleteItem(string& key, BSTNode*& treePtr) {
    if(treePtr==NULL){return;}
    else if(key == treePtr->item){
        deleteNodeItem(treePtr);
    }
    else if(key < treePtr->item){
        deleteItem(key, treePtr->leftChildPtr);
    }
    else{
        deleteItem(key, treePtr->rightChildPtr);
    }
}

void BST::deleteNodeItem(BSTNode*& nodePtr) {
    BSTNode *deletePtr;
    string replacementItem;
//leaf
    if((nodePtr->leftChildPtr == NULL) && (nodePtr->rightChildPtr == NULL)){
        delete nodePtr;
        nodePtr = NULL;
    }
//no left child
    else if (nodePtr->leftChildPtr == NULL){
        deletePtr = nodePtr;
        nodePtr = nodePtr->rightChildPtr;
        deletePtr->rightChildPtr = NULL;
        delete deletePtr;
    }
//no right child
    else if (nodePtr->rightChildPtr == NULL){
        deletePtr = nodePtr;
        nodePtr = nodePtr->leftChildPtr;
        deletePtr->leftChildPtr = NULL;
        delete deletePtr;
    }
//two children
    else{
        processLeftmost(nodePtr->rightChildPtr, replacementItem);
        nodePtr->item = replacementItem;
    }
}

void BST::processLeftmost(BSTNode*& nodePtr, string& item) {
    if (nodePtr->leftChildPtr == NULL) {
        item = nodePtr->item;
        BSTNode *deletePtr = nodePtr;
        nodePtr = nodePtr->rightChildPtr;
        deletePtr->rightChildPtr = NULL;
        delete deletePtr;
    }
    else
        processLeftmost(nodePtr->leftChildPtr, item);
}
//-------------------------------------------------------------------------------------------------------------
//Inorder Traversal
vector<string> BST::inorderTraversal(BSTNode* root) {
    vector<string> vec;
    inorderTraversal(vec, root);
    return vec;
}

void BST::inorderTraversal(vector<string>& vec, BSTNode* root) {
    if (root != NULL) {
        inorderTraversal(vec, root->leftChildPtr); // Visit left subtree
        vec.push_back(root->getItem());       // Visit node itself
        inorderTraversal(vec, root->rightChildPtr); // Visit right subtree
    }
}
//-------------------------------------------------------------------------------------------------------------
BSTNode* BST::searchTreeRetrieve(string kmer, BSTNode* root) {
    if (root == NULL) {
        return nullptr;
    }
    else if (kmer == root->getItem()) {
        return root;
    }
    else if (kmer < root->getItem()) {
        return searchTreeRetrieve(kmer, root->leftChildPtr);
    }
    else {
        return searchTreeRetrieve(kmer, root->rightChildPtr);
    }
}
