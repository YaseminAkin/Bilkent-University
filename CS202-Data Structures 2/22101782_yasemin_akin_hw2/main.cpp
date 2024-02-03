/**
* Title: Binary Search Trees
* Author : Yasemin Akın
* ID: 22101782
* Section : 001
* Homework : 2
* Description : driver file for testing BST 
*/

#include <iostream>
#include "KmerTree.h"
using namespace std;
#include <ctime>

void timeAnalysis(string inputfilename, int k) {
    ifstream inFile(inputfilename);
    string text;
    inFile >> text;
    inFile.close();
    
    if (text.length() < 45000) {
       cerr << "Input text is not large enough for analysis." << endl;
       return;
    }

    KmerTree tree;
    clock_t start, end;
    double duration;
    size_t kmerCount = 0;

    start = clock();
    for (size_t i = 0; i + k <= text.length(); i += k) {
        string kmer = text.substr(i, k);
        tree.addKmer(kmer);
        kmerCount++;
        if (kmerCount % 1000 == 0 && kmerCount <= 10000) {
            end = clock();
            duration = double(end - start) / CLOCKS_PER_SEC;
            int uniqueKmers = tree.getUniqueKmerCount();
            int height = tree.getHeight();
            
            cout << "After adding " << kmerCount << " kmers:" << endl;
            cout << "1. Number of unique kmers: " << uniqueKmers << endl;
            cout << "2. Height of the BST: " << height << endl;
            cout << "3. Time taken for this period: " << duration << " seconds" << endl << endl;
            
            start = clock(); // Reset the clock for the next period
        }
    }
}

int main(int argc, char* argv[]) {

    if (argc < 3){
        cout << "Missing arguments" << endl;
    }
    else {
        int k = atoi(argv[1]);
        string inputFileName = argv[2];
        
        timeAnalysis(inputFileName, k);
//        //  Kmer Tree Initialization
//        KmerTree kmer_tree = KmerTree();
//        kmer_tree.generateTree(inputFileName, k);
//
//        // Printing all kmers with their frequencies
//        // Format detail about each line for printAll: <tab><entry><newline>
//        cout << "All kmers in alphabetical order: " << endl;
//        kmer_tree.printAll();
//        cout << "------------------------------------------------" << endl;
//
//        // Inorder Traversal
//        cout << "Inorder traversal: " << endl;
//        vector<string> inorder_vect;
//        kmer_tree.inorderTraverse(inorder_vect);
//        for (auto itr : inorder_vect){
//            cout << itr << " ";}
//        cout << endl;
//        cout << "------------------------------------------------" << endl;
//
//        // Adding a kmer to the existing tree
//        string str1 = "one";
//        kmer_tree.addKmer(str1);
//
//        cout << "After adding " << str1 << ": "  << endl;
//        vector<string> inorder_vect_2;
//        kmer_tree.inorderTraverse(inorder_vect_2);
//        for (auto itr : inorder_vect_2){
//            cout << itr << " ";}
//        cout << endl;
//        cout << "------------------------------------------------" << endl;
//
//        // Deleting the kmers.
//        // Notice that deleting the kmer deletes the node from the tree completely.
//        kmer_tree.searchTreeDelete("ood");
//        kmer_tree.searchTreeDelete("has");
//        kmer_tree.searchTreeDelete("woo");
//        kmer_tree.searchTreeDelete("one");
//
//        cout << "After deleting ood, has, woo, and one: " << endl;
//        vector<string> inorder_vect_3;
//        kmer_tree.inorderTraverse(inorder_vect_3);
//        for (auto itr : inorder_vect_3){
//            cout << itr << " ";}
//        cout << endl;
//        cout << "------------------------------------------------" << endl;
//
//        // Number of unique kmers in the tree
//        cout << "Number of unique kmers = " << kmer_tree.getUniqueKmerCount() << endl;
//        cout << "------------------------------------------------" << endl;
//
//        // Adding the kmer "xyz" to the existing tree
//        str1 = "xyz";
//        kmer_tree.addKmer(str1);
//
//        // Number of  kmers in the tree now
//        cout << "After adding " << str1 << "...";
//        cout << "Number of unique kmers = " << kmer_tree.getUniqueKmerCount() << endl;
//        cout << "------------------------------------------------" << endl;
//
//        // Number of kmers that start with the character "h"
//        char ch = 'h';
//        cout << "Number of kmers that start with " << ch << " = " << kmer_tree.getNumberOfKmerThatStartWith(ch) << endl;
//        cout << "------------------------------------------------" << endl;
//
//        // Printing all kmers with their frequencies
//        cout << "All kmers in alphabetical order: " << endl;
//        kmer_tree.printAll();
//        cout << "------------------------------------------------" << endl;
//
//        // Kmer Tree Height
//        cout << "Kmer Tree height is = " << kmer_tree.getHeight() << endl;
    }
    return 0;
}
