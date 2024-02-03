/**
* Title: Linked Lists
* Author : Yasemin Akın
* ID: 22101782
* Section : 2
* Homework : 3
* Description :
*/

#ifndef Student_h
#define Student_h

#include <stdio.h>
#include "Course.h"
class Student {
public:
    int studId;
    string studName;
    string studLastName;
    
    struct courseNode {
        Course course;
        courseNode* next;
        courseNode() : next(nullptr){}
    };
    courseNode* headCourseList;
    
    Student(int newId = 0, string newName = "", string newLastName = "");
    ~Student();
    
    void addCourse(int courseId, string courseTitle);
    void withdrawCourse(int courseId, bool flagCancel);
    
    void displayStudent();
    void displayStudent2();
    bool hasCourse(int courseId, string& courseTitle);
    
};
#endif /* Student_h */
