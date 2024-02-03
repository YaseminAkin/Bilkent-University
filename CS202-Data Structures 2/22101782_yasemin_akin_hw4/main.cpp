/**
* Title: Hash Tables
* Author: Yasemin Akın
* ID: 22101782
* Section: 001
* Homework: 4
* Description: main.cpp file */

#include <iostream>
#include "HashTable.h"
#include <chrono>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <k> <input_file>" << endl;
        return 1;
    }

    int k = stoi(argv[1]);
    string inputFileName = argv[2];

    // Create HashTable instances for separate chaining and quadratic probing
    HashTable hashTableChain;
    HashTable hashTableQuadratic;

    // Fill both hash tables with content from the file
    hashTableChain.fillHashTable_chain(inputFileName, k);
    hashTableQuadratic.fillHashTable_quadratic(inputFileName, k);
    
    cout<<"Printing the hash table created with seperated chaining method:"<<endl;
    cout<<endl;
    hashTableChain.printAll_chain();
    cout<<endl;
    cout<<"Printing the hash table created with quadratic probing method (full hash table was not handled):"<<endl;
    cout<<endl;
    hashTableQuadratic.printAll_quadratic();
    cout<<endl;

    // Choose a k-mer to find
    string kmerToFind = "xyv"; // Replace this with an actual k-mer from your data
    cout<<"Kmer to find: '"<< kmerToFind <<"'"<<endl;
   
    // Measure time for separate chaining
    auto start = std::chrono::high_resolution_clock::now();
    KmerNode* resultChain = hashTableChain.findKmer_chain(kmerToFind);
    auto stop = std::chrono::high_resolution_clock::now();
    auto durationChain = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    cout << "Time taken to retrieve kmer = '"<< kmerToFind <<"' in hash table built with separate chaining: " << durationChain.count() << " microseconds." << endl;

    // Measure time for quadratic probing
    start = std::chrono::high_resolution_clock::now();
    KmerNode* resultQuadratic = hashTableQuadratic.findKmer_quadratic(kmerToFind);
    stop = std::chrono::high_resolution_clock::now();
    auto durationQuadratic = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    cout << "Time taken to retrieve kmer = '"<< kmerToFind <<"' in hash table built with quadratic probing: " << durationQuadratic.count() << " microseconds." << endl;
    cout<<endl;
    
    // Testing go_to_positions method according to the printed hash table information
    int range = 2;
    cout<<"Testing go_to_positions method according to the printed hash table information for kmer = '"<< kmerToFind <<"' and range = "<< range <<endl;
    hashTableQuadratic.go_to_positions(inputFileName, range, resultQuadratic);
    cout<<endl;
    
    // Choose a k-mer to find
    kmerToFind = "bom"; // Replace this with an actual k-mer from your data
    cout<<"Kmer to find: '"<< kmerToFind <<"'"<<endl;
   
    // Measure time for separate chaining
    start = std::chrono::high_resolution_clock::now();
    resultChain = hashTableChain.findKmer_chain(kmerToFind);
    stop = std::chrono::high_resolution_clock::now();
    durationChain = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    cout << "Time taken to retrieve kmer = '"<< kmerToFind <<"' in hash table built with separate chaining: " << durationChain.count() << " microseconds." << endl;

    // Measure time for quadratic probing
    start = std::chrono::high_resolution_clock::now();
    resultQuadratic = hashTableQuadratic.findKmer_quadratic(kmerToFind);
    stop = std::chrono::high_resolution_clock::now();
    durationQuadratic = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    cout << "Time taken to retrieve kmer = '"<< kmerToFind <<"' in hash table built with quadratic probing: " << durationQuadratic.count() << " microseconds." << endl;
    cout<<endl;
    
    // Testing go_to_positions method according to the printed hash table information
    range = 3;
    cout<<"Testing go_to_positions method according to the printed hash table information for kmer = '"<< kmerToFind <<"' and range = "<< range <<endl;
    hashTableQuadratic.go_to_positions(inputFileName, range, resultQuadratic);
    cout<<endl;
    
    // Choose a k-mer to find
    kmerToFind = "xrw"; // Replace this with an actual k-mer from your data
    cout<<"Kmer to find: '"<< kmerToFind <<"'"<<endl;
   
    // Measure time for separate chaining
    start = std::chrono::high_resolution_clock::now();
    resultChain = hashTableChain.findKmer_chain(kmerToFind);
    stop = std::chrono::high_resolution_clock::now();
    durationChain = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    cout << "Time taken to retrieve kmer = '"<< kmerToFind <<"' in hash table built with separate chaining: " << durationChain.count() << " microseconds." << endl;

    // Measure time for quadratic probing
    start = std::chrono::high_resolution_clock::now();
    resultQuadratic = hashTableQuadratic.findKmer_quadratic(kmerToFind);
    stop = std::chrono::high_resolution_clock::now();
    durationQuadratic = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    cout << "Time taken to retrieve kmer = '"<< kmerToFind <<"' in hash table built with quadratic probing: " << durationQuadratic.count() << " microseconds." << endl;
    cout<<endl;
        
    // Testing go_to_positions method according to the printed hash table information
    range = 4;
    cout<<"Testing go_to_positions method according to the printed hash table information for kmer = '"<< kmerToFind <<"' and range = "<< range <<endl;
    hashTableQuadratic.go_to_positions(inputFileName, range, resultQuadratic);
    cout<<endl;
    
    return 0;
}
