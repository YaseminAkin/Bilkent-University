//
//  add.c
//  Add
//
//  Created by Yasemin Akın on 7.02.2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

typedef struct student {
    int id;
    char name[64];
    double cgpa;
    struct student *next;
    struct student *prev;
} Student;

Student *create(int id, const char *name, double cgpa) {
    Student *stud = malloc(sizeof(Student));
    if (stud) {
        stud->id = id;
        strcpy(stud->name, name);
        stud->cgpa = cgpa;
        stud->next = stud->prev = NULL;
    }
    return stud;
}

void insert(Student **head, Student *stud) {
    if (!*head || (*head)->id >= stud->id) {
        stud->next = *head;
        if (*head) {
            (*head)->prev = stud;
        }
        *head = stud;
    } else {
        Student *curr = *head;
        while (curr->next && curr->next->id < stud->id) {
            curr = curr->next;
        }
        stud->next = curr->next;
        if (curr->next) {
            curr->next->prev = stud;
        }
        curr->next = stud;
        stud->prev = curr;
    }
}

int main() {
    Student *head = NULL;
    const int num = 20000;
    struct timeval start, end;
    long elapsedTime;

    gettimeofday(&start, NULL);

    for (int i = 0; i < num; ++i) {
        int id = rand() % (99999999 - 10000000 + 1) + 10000000;
        double cgpa = 4.0;
        char name[64] = "Yasemin";
        Student *stud = create(id, name, cgpa);
        insert(&head, stud);
    }

    gettimeofday(&end, NULL);

    elapsedTime = ((end.tv_sec - start.tv_sec) * 1000.0) + ((end.tv_usec - start.tv_usec) / 1000.0);

    return 0;
}
