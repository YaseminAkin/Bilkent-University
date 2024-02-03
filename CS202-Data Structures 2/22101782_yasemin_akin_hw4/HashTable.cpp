/**
* Title: Hash Tables
* Author: Yasemin Akın
* ID: 22101782
* Section: 001
* Homework: 4
* Description: HashTable.cpp file contains the implementation of a HashTable */

#include "HashTable.h"

HashTable::HashTable() {
    for( int i = 0; i < QUADRATIC_PROBING_TABLE_SIZE; i++) {
        quadraticProbingHashTable[i] = nullptr;
    }
    for( int i = 0; i < SEPERATE_CHANING_TABLE_SIZE; i++) {
        seperateChaningHashTable[i] = nullptr;
    }
}

HashTable::~HashTable() {
    
    for (int i = 0; i < SEPERATE_CHANING_TABLE_SIZE; ++i) {
        KmerNode* current = seperateChaningHashTable[i];
        while (current != nullptr) {
            KmerNode* temp = current;
            current = current->getNextKmer();
            delete temp;
        }
    }

    for (int i = 0; i < QUADRATIC_PROBING_TABLE_SIZE; ++i) {
        if (quadraticProbingHashTable[i] != nullptr) {
            delete quadraticProbingHashTable[i];
        }
    }
}

int HashTable::hashFunctionSeperateChaining(const string& kmer) const {
    int hash = 0;
        for (char c : kmer) {
            hash += static_cast<int>(c);
        }
        int index = hash % SEPERATE_CHANING_TABLE_SIZE;

        if (index < 0) {
            cerr << "Negative index detected in s. Hash: " << hash << "at index: " << index << endl;
        }

        return index;
}

int HashTable::hashFunctionQuadraticProbing(const string& kmer) const {
    int hash = 0;
        for (char c : kmer) {
            hash += static_cast<int>(c);
        }
        int index = hash % QUADRATIC_PROBING_TABLE_SIZE;

        if (index < 0) {
            cerr << "Negative index detected in q. Hash: " << hash << " at index: " << index << endl;
        }

        return index;
}

string HashTable::toLowerCase(string str) {
    transform(str.begin(), str.end(), str.begin(), [](unsigned char c){ return tolower(c); });
    return str;
}

void HashTable::fillHashTable_chain(string filename, int k) {
    ifstream inFile(filename);
    string text;
    if (inFile.is_open()) {
        inFile >> text;
        inFile.close();

        for (int i = 0; i + k <= text.length(); i+=k) {
            string kmer = text.substr(i, k);
            kmer = toLowerCase(kmer);
            addKmer_chain(kmer, i);
        }
    } else {
        cerr << "Unable to open file: " << filename << endl;
    }
}

KmerNode* HashTable::findKmer_chain(string kmer) {
    kmer = toLowerCase(kmer);
    int hashIndex = hashFunctionSeperateChaining(kmer);
    KmerNode* current = seperateChaningHashTable[hashIndex];

//    Search for the kmer in the chain
    while (current != nullptr) {
        if (current->getKmer() == kmer) {
            return current; // K-mer found
        }
        current = current->getNextKmer();
    }

    return nullptr; // Kmer not found
}

void HashTable::addKmer_chain(string kmer, int position) {
    int hashIndex = hashFunctionSeperateChaining(kmer);
    KmerNode* head = seperateChaningHashTable[hashIndex];

//    Search for the kmer in the chain
    KmerNode* current = head;
    while (current != nullptr) {
        if (current->getKmer() == kmer) {
//            Kmer found, add position to the existing node
            current->addPosition(position);
            return;
        }
        current = current->getNextKmer();
    }

//    Kmer not found, add new KmerNode to the front of the chain
    KmerNode* newNode = new KmerNode(kmer, {position});
    newNode->setNextKmer(head);
    seperateChaningHashTable[hashIndex] = newNode;
}

void HashTable::addKmer_quadratic(string kmer, int position) {
    int hashIndex = hashFunctionQuadraticProbing(kmer);
    int i = 0;

    while (quadraticProbingHashTable[hashIndex] != nullptr && quadraticProbingHashTable[hashIndex]->getKmer() != kmer) {
//        Quadratic probing
        i++;
        hashIndex = (hashIndex + i * i) % QUADRATIC_PROBING_TABLE_SIZE;
    }

    if (quadraticProbingHashTable[hashIndex] == nullptr) {
//        Insert new KmerNode if not already present
        quadraticProbingHashTable[hashIndex] = new KmerNode(kmer, {position});
        quadtraticProbingSize++;
    } else {
//        Kmer already present, add position to its vector
        quadraticProbingHashTable[hashIndex]->addPosition(position);
    }
}

void HashTable::fillHashTable_quadratic(string filename, int k) {
    ifstream inFile(filename);
    string text;
    if (inFile.is_open()) {
        inFile >> text;
        inFile.close();

        for (int i = 0; i + k <= text.length(); i+=k) {
            string kmer = text.substr(i, k);
            kmer = toLowerCase(kmer);
            addKmer_quadratic(kmer, i);
//            Full table size is reached
            if(quadtraticProbingSize >= QUADRATIC_PROBING_TABLE_SIZE) {
                break;
            }
        }
    } else {
        cerr << "Unable to open file: " << filename << endl;
    }
}

KmerNode* HashTable::findKmer_quadratic(string kmer) {
    kmer = toLowerCase(kmer);
    int hashIndex = hashFunctionQuadraticProbing(kmer);
    int i = 0;

    while (quadraticProbingHashTable[hashIndex] != nullptr) {
        if (quadraticProbingHashTable[hashIndex]->getKmer() == kmer) {
            return quadraticProbingHashTable[hashIndex]; // K-mer found
        }

//        Quadratic probing
        i++;
        hashIndex = (hashIndex + i * i) % QUADRATIC_PROBING_TABLE_SIZE;
//        All indexes are searched
        if (i == QUADRATIC_PROBING_TABLE_SIZE) {
            break;
        }
    }

    return nullptr; // Kmer not found
}

void HashTable::printAll_chain() const {
    for (int i = 0; i < SEPERATE_CHANING_TABLE_SIZE; i++) {
        KmerNode* current = seperateChaningHashTable[i];
        while (current != nullptr) {
            cout << "Kmer = '" << current->getKmer() << "' at positions = ";
            for (int pos : current->getStartPosVector()) {
                cout << pos << " ";
            }
            cout << endl;
            current = current->getNextKmer();
        }
    }
}

void HashTable::printAll_quadratic() const {
    for (int i = 0; i < QUADRATIC_PROBING_TABLE_SIZE; i++) {
        if (quadraticProbingHashTable[i] != nullptr) {
            cout << "Kmer = '" << quadraticProbingHashTable[i]->getKmer() << "' at positions = ";
            for (int pos : quadraticProbingHashTable[i]->getStartPosVector()) {
                cout << pos << " ";
            }
            cout << endl;
        }
    }
}

void HashTable::go_to_positions(string inputFileName, int range, KmerNode *found) {
    
    if (found == nullptr) {
        cout << "Kmer node given to go_to_positions is nullptr!" << endl;
        return;
    }

    ifstream inFile(inputFileName);
    if (!inFile.is_open()) {
        cerr << "File cannot be opened!" << endl;
        return;
    }

    string text;
    inFile >> text;
    inFile.close();

    for (int pos : found->getStartPosVector()) {
        int start = pos;
//        Ensure that the end of the extended Kmer does not exceeds text.length().
        int end = min(static_cast<int>(text.length()), pos + range + static_cast<int>(found->getKmer().length()));

        cout << "-> " << text.substr(start, end - start) << " (generated from position " << pos << ")" << endl;
    }
}
