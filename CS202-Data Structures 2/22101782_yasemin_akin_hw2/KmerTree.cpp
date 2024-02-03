/**
* Title: Binary Search Trees
* Author : Yasemin Akın
* ID: 22101782
* Section : 001
* Homework : 2
* Description : cpp  file for the pointer-based implementation of Kmer Tree whose keys are k-mers
*/

#include "KmerTree.h"

void KmerTree::addKmer(string kmer) {
    string lowerKmer = toLowerCase(kmer);
    BSTNode* node = kmerTree.searchTreeRetrieve(lowerKmer, kmerTree.getRoot());
    if (node != nullptr) {
        node->incrementFrequency();
    }
    else {
        kmerTree.searchTreeInsert(lowerKmer);
    }
}
void KmerTree::generateTree(string fileName, int k) {
    ifstream inFile(fileName);
    string text;
    inFile >> text;
    inFile.close();

    for (size_t i = 0; i + k <= text.length(); i += k) {
        string kmer = text.substr(i, k);
        addKmer(kmer);
    }
}

int KmerTree::getUniqueKmerCount() {
    return getUniqueKmerCountHelper(kmerTree.getRoot());
}

int KmerTree::getUniqueKmerCountHelper(BSTNode* root) {
    if (root == nullptr) {
        return 0;
    }
    return 1 + getUniqueKmerCountHelper(root->getLeftChildPtr()) + getUniqueKmerCountHelper(root->getRightChildPtr());
}

int KmerTree::getNumberOfKmerThatStartWith(char ch) {
    return getNumberOfKmerThatStartWithHelper(kmerTree.getRoot(), tolower(ch));
}

int KmerTree::getNumberOfKmerThatStartWithHelper(BSTNode* root, char ch) {
    if (root == nullptr) {
        return 0;
    }

    int count = 0;
    if (tolower(root->getItem()[0]) == ch) {
        count = 1;
    }

    count += getNumberOfKmerThatStartWithHelper(root->getLeftChildPtr(), ch);
    count += getNumberOfKmerThatStartWithHelper(root->getRightChildPtr(), ch);

    return count;
}

void KmerTree::searchTreeDelete(string key) {
    kmerTree.searchTreeDelete(key);
}

void KmerTree::inorderTraverse(vector<string>& inorder_vect) {
    inorder_vect = kmerTree.inorderTraversal(kmerTree.getRoot());
}
void KmerTree::printAll() {
    vector<string> kmerList;
    inorderTraverse(kmerList);
    for (const string& kmer : kmerList) {
        BSTNode* node = kmerTree.searchTreeRetrieve(kmer, kmerTree.getRoot());
        if (node != nullptr) {
            cout <<"    "<< node->getItem() << ", frequency = " << node->getFrequency() << endl;
        }
    }
}

int KmerTree::getHeight() {
    return getHeightHelper(kmerTree.getRoot());
}

int KmerTree::getHeightHelper(BSTNode* root) {
    if (root == nullptr) {
        return 0;
    }

    int leftHeight = getHeightHelper(root->getLeftChildPtr());
    int rightHeight = getHeightHelper(root->getRightChildPtr());

    return 1 + max(leftHeight, rightHeight);
}

string KmerTree::toLowerCase(string str) {
    transform(str.begin(), str.end(), str.begin(), [](unsigned char c){ return tolower(c); });
    return str;
}
