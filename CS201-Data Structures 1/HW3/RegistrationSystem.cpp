/**
* Title: Linked Lists
* Author : Yasemin Akın
* ID: 22101782
* Section : 2
* Homework : 3
* Description :
*/

#include "RegistrationSystem.h"

RegistrationSystem::RegistrationSystem () {
    this->headStudentList = nullptr;
}

RegistrationSystem::~RegistrationSystem () {
    while (headStudentList != nullptr) {
        studentNode *nextHead = headStudentList->next;
        if (nextHead != nullptr) {
            nextHead->prev = nullptr;
        }
        //deleting node
        delete headStudentList;
        //continuing with next node
        headStudentList = nextHead;
    }
    headStudentList = nullptr;
}

void RegistrationSystem::addStudent ( const int studentId , const string firstName , const string lastName ) {
    for(studentNode* iterPtr = headStudentList; iterPtr != nullptr; iterPtr = iterPtr->next) {
        if(iterPtr->student.studId == studentId) {
            cout<<"Student "<<studentId<<" already exists"<<endl;
            return;
        }
    }
    studentNode* newNode = new studentNode;
    newNode->student.studId = studentId;
    newNode->student.studName = firstName;
    newNode->student.studLastName = lastName;
    newNode->student.headCourseList = nullptr; //we already assign student.headCourseList to nullptr at Student constructor, but reassign to make sure a new student does not have any added courses yet.
    
    if (headStudentList == nullptr) {
        // If the list is empty, make the new node the head
        headStudentList = newNode;
        cout<<"Student "<<studentId<<" has been added"<<endl;
    }
    else if (studentId < headStudentList->student.studId) {
        // If the new node's courseId is smaller than the head's courseId,
        // insert the new node at the beginning
        newNode->next = headStudentList;
        headStudentList->prev = newNode;
        headStudentList = newNode;
        cout<<"Student "<<studentId<<" has been added"<<endl;
    }
    else {
        studentNode* current = headStudentList;
        // Find the appropriate position to insert the new node
        while (current->next != nullptr && studentId >= current->next->student.studId) {
            current = current->next;
        }
        // Insert the new node after the current node
        newNode->next = current->next;
        newNode->prev = current;
        if (current->next != nullptr) {
            current->next->prev = newNode;
        }
        current->next = newNode;
        cout<<"Student "<<studentId<<" has been added"<<endl;
    }
}

void RegistrationSystem::deleteStudent ( const int studentId ) {
    if(headStudentList == nullptr) {
        cout<<"Student "<<studentId<<" does not exist"<<endl;
        return;
    }
    if(headStudentList != nullptr) {
        //if head node must be deleted
        if (headStudentList->student.studId == studentId) {
            studentNode* tempPtr = headStudentList;
            headStudentList = headStudentList->next;
            if (headStudentList != nullptr) {
                headStudentList->prev = nullptr;
            }
            delete tempPtr;
            cout<<"Student "<<studentId<<" has been deleted"<<endl;
            return;
        }
        
        studentNode* current = headStudentList;
        while (current != nullptr && current->student.studId != studentId) {
            current = current->next;
        }
        
        if (current == nullptr) {
            // Course not found in the list
            cout<<"Student "<<studentId<<" does not exist"<<endl;
            return;
        }

        // Remove the current node
        studentNode* prevNode = current->prev;
        studentNode* nextNode = current->next;
        if (prevNode != nullptr) {
            prevNode->next = nextNode;
        }
        if (nextNode != nullptr) {
            nextNode->prev = prevNode;
        }
        delete current;
        cout<<"Student "<<studentId<<" has been deleted"<<endl;
    }
}

void RegistrationSystem::addCourse ( const int studentId , const int courseId , const string courseName ) {
    for(studentNode* iterPtr = headStudentList; iterPtr != nullptr; iterPtr = iterPtr->next) {
        string title = "";
        if(iterPtr->student.hasCourse(courseId, title)) {
            if(title != courseName) {
                cout<<"Course "<<courseId<<" already exists with another name"<<endl;
                return;
            }
        }
    }
    for(studentNode* iterPtr = headStudentList; iterPtr != nullptr; iterPtr = iterPtr->next) {
        if(iterPtr->student.studId == studentId) {
            iterPtr->student.addCourse(courseId, courseName);
            return;
        }
    }
    cout<<"Student "<<studentId<<" does not exist"<<endl;
}

void RegistrationSystem::withdrawCourse ( const int studentId , const int courseId ) {
    bool flagCancel = false;
    for(studentNode* iterPtr = headStudentList; iterPtr != nullptr; iterPtr = iterPtr->next) {
        if(iterPtr->student.studId == studentId) {
            iterPtr->student.withdrawCourse(courseId, flagCancel);
            return;
        }
    }
    cout<<"Student "<<studentId<<" does not exist"<<endl;
}

void RegistrationSystem::cancelCourse ( const int courseId ) {
    bool flagCancel = true;
    string courseTitle = "";
    bool flag = false;
    for(studentNode* iterPtr = headStudentList; iterPtr != nullptr; iterPtr = iterPtr->next) {
        if(iterPtr->student.hasCourse(courseId, courseTitle)) {
            flag = true;
            iterPtr->student.withdrawCourse(courseId, flagCancel);
        }
    }
    if(!flag) {
        cout<<"Course "<<courseId<<" does not exist"<<endl;
    }
    else {
        cout<<"Course "<<courseId<<" has been cancelled"<<endl;
    }
}

void RegistrationSystem::showStudent ( const int studentId ) {
    bool flag = false;
    for(studentNode* iterPtr = headStudentList; iterPtr != nullptr; iterPtr = iterPtr->next) {
        if(iterPtr->student.studId == studentId) {
            cout<<"Student id First name Last name"<<endl;
            iterPtr->student.displayStudent();
            flag = true;
        }
    }
    if (!flag) {
        cout<<"Student "<<studentId<<" does not exist"<<endl;
    }
}

void RegistrationSystem::showCourse ( const int courseId ) {
    bool flag = false;
    bool done = false;
    string courseTitle = "";
    for(studentNode* iterPtr = headStudentList; iterPtr != nullptr; iterPtr = iterPtr->next) {
        if(iterPtr->student.hasCourse(courseId, courseTitle)) {
            flag = true;
            if (!done) {
                cout<<"Course id Course name"<<endl;
                cout<<courseId<<" "<<courseTitle<<endl;
                done = true;
                cout<<"Student id First name Last name"<<endl;
            }
            iterPtr->student.displayStudent2();
        }
    }
    if(!flag) {
        cout<<"Course "<<courseId<<" does not exist"<<endl;
    }
}

void RegistrationSystem::showAllStudents () {
    if(headStudentList == nullptr) {
        cout<<"There are no students in the system"<<endl;
        return;
    }
    cout<<"Student id First name Last name"<<endl;
    for(studentNode* iterPtr = headStudentList; iterPtr != nullptr; iterPtr = iterPtr->next) {
        iterPtr->student.displayStudent();
    }
}
