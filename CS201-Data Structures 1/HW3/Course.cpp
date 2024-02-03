/**
* Title: Linked Lists
* Author : Yasemin Akın
* ID: 22101782
* Section : 2
* Homework : 3
* Description :
*/

#include "Course.h"

Course::Course(int newId, string newTitle) {
    this->courseId = newId;
    this->courseTitle = newTitle;
}

void Course::displayCourse () {
    cout<<courseId<<" "<<courseTitle<<endl;
}
