/**
* Title: Linked Lists
* Author : Yasemin Akın
* ID: 22101782
* Section : 2
* Homework : 3
* Description :
*/

#ifndef RegistrationSystem_h
#define RegistrationSystem_h

#include <stdio.h>
#include "Student.h"

class RegistrationSystem {
public :
    struct studentNode {
        Student student;
        studentNode* next;
        studentNode* prev;
        
    studentNode() : next(nullptr), prev(nullptr){}
    };
    studentNode* headStudentList;
    RegistrationSystem () ;
    ~ RegistrationSystem () ;
    void addStudent ( const int studentId , const string firstName , const string
    lastName ) ;
    void deleteStudent ( const int studentId ) ;
    void addCourse ( const int studentId , const int courseId , const string
    courseName ) ;
    void withdrawCourse ( const int studentId , const int courseId ) ;
    void cancelCourse ( const int courseId ) ;
    void showStudent ( const int studentId ) ;
    void showCourse ( const int courseId ) ;
    void showAllStudents () ;
};
#endif /* RegistrationSystem_h */
