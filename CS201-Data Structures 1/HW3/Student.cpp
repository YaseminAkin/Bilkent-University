/**
* Title: Linked Lists
* Author : Yasemin Akın
* ID: 22101782
* Section : 2
* Homework : 3
* Description :
*/

#include "Student.h"

Student::Student(int newId, string newName, string newLastName) {
    this->studId = newId;
    this->studName = newName;
    this->studLastName = newLastName;
    this->headCourseList = nullptr;
}
Student::~Student() {
    while (headCourseList != nullptr) {
        
        courseNode *nextHead = headCourseList->next;
        //deleting node
        delete headCourseList;
        //continuing with next node
        headCourseList = nextHead;
    }
    headCourseList = nullptr;
    
}

void Student::addCourse(int courseId, string courseTitle) {
    
    
    for(courseNode* iterPtr = headCourseList; iterPtr != nullptr; iterPtr = iterPtr->next) {
        if(iterPtr->course.courseId == courseId) {
            cout<<"Student "<<studId<<" is already enrolled in course "<<courseId<<endl;
            return;
        }
    }
    courseNode* newNode = new courseNode;
    newNode->course.courseId = courseId;
    newNode->course.courseTitle = courseTitle;
    
    if (headCourseList == nullptr) {
        // If the list is empty, make the new node the head
        headCourseList = newNode;
        newNode->next = nullptr;
        cout<<"Course "<<courseId<<" has been added to student "<<studId<<endl;
    }
    else {
        courseNode* temp = headCourseList;
        //inserting to be the first node
        if(courseId < temp->course.courseId) {
            newNode->next = headCourseList;
            headCourseList = newNode;
            cout<<"Course "<<courseId<<" has been added to student "<<studId<<endl;
            return;
        }
        //insterting somewhere middle
        while (temp->next != nullptr) {
            if (courseId > temp->next->course.courseId) {
                temp = temp->next;
            }
            else {
                newNode->next = temp->next;
                temp->next = newNode;
                cout<<"Course "<<courseId<<" has been added to student "<<studId<<endl;
                return;
            }
        }
        //instering as the last node
        if(courseId > temp->course.courseId) {
            temp->next = newNode;
            newNode->next = nullptr;
            cout<<"Course "<<courseId<<" has been added to student "<<studId<<endl;
        }
    }
}

void Student::withdrawCourse(int courseId, bool flagCancel) {
    
    if(headCourseList != nullptr) {
        //if head node must be deleted
        if (headCourseList->course.courseId == courseId) {
            courseNode* tempPtr = headCourseList->next;
            delete headCourseList;
            headCourseList = tempPtr;
            if(!flagCancel) {
                cout<<"Student "<<studId<<" has been withdrawn from course "<<courseId<<endl;
            }
            return;
        }
        //looking for subscriber
        for(courseNode* iterPtr = headCourseList; iterPtr->next != nullptr; iterPtr = iterPtr->next) {
            if(iterPtr->next->course.courseId == courseId) {
                courseNode* tempPtr = iterPtr->next->next;
                delete iterPtr->next;
                iterPtr->next = tempPtr;
                if(!flagCancel) {
                    cout<<"Student "<<studId<<" has been withdrawn from course "<<courseId<<endl;
                }
                return;
            }
        }
    }
    if(!flagCancel) {
        cout<<"Student "<<studId<<" is not enrolled in course "<<courseId<<endl;
    }
}

void Student::displayStudent() {
    cout<<studId<<" "<<studName<<" "<<studLastName<<endl;
    if(headCourseList != nullptr) {
        cout<<"Course id Course name"<<endl;
        for(courseNode* iterPtr = headCourseList; iterPtr != nullptr; iterPtr = iterPtr->next) {
            iterPtr->course.displayCourse();
        }
    }
}

void Student::displayStudent2() {
    cout<<studId<<" "<<studName<<" "<<studLastName<<endl;
}

bool Student::hasCourse(int courseId, string& courseTitle) {
    for(courseNode* iterPtr = headCourseList; iterPtr != nullptr; iterPtr = iterPtr->next) {
        if(iterPtr->course.courseId == courseId) {
            courseTitle = iterPtr->course.courseTitle;
            return true;
        }
    }
    return false;
}
