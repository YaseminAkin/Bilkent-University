/**
* Title: Binary Search Trees
* Author : Yasemin Akın
* ID: 22101782
* Section : 001
* Homework : 2
* Description : cpp file for the pointer-based implementation of Binary Search Tree Node whose keys are strings
*/

#include "BSTNode.h"

BSTNode::BSTNode() {}
BSTNode::BSTNode(const string& nodeItem, BSTNode *left, BSTNode *right) {
    item = nodeItem;
    leftChildPtr = left;
    rightChildPtr = right;
    frequency = 1;
}
string BSTNode::getItem() const{
    return this->item;
}

int BSTNode::getFrequency() const {
    return this->frequency;
}

void BSTNode::incrementFrequency() {
    this->frequency = this->frequency + 1;
}

BSTNode* BSTNode::getLeftChildPtr() {
    return this->leftChildPtr;
}
BSTNode* BSTNode::getRightChildPtr() {
    return this->rightChildPtr;
}
