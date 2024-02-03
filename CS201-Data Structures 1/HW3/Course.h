/**
* Title: Linked Lists
* Author : Yasemin Akın
* ID: 22101782
* Section : 2
* Homework : 3
* Description :
*/

#ifndef Course_h
#define Course_h

#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;

class Course {
public:
    int courseId;
    string courseTitle;
    
    Course(int newId = 0, string newTitle = "");
    void displayCourse ();
};
#endif /* Course_h */
