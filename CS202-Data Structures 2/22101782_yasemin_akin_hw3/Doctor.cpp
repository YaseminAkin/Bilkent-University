//
//  Doctor.cpp
//  22101782_yasemin_akin_hw3
//
//  Created by Yasemin Akın on 1.12.2023.
//

#include <stdio.h>

class Doctor {
public:
    int id;
    int availableAtTime;

    Doctor(int id) : id(id), availableAtTime(0) {}
    bool operator>(const Doctor& other) const {
            return availableAtTime > other.availableAtTime;
        }
};
