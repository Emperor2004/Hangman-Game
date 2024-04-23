// Header file: student.h
#include <stdio.h>
#define MAX_STUDENTS 100

struct Student {
    int rollNumber;
    char name[50];
    float marks[5]; // Assuming 5 subjects
};

void addStudent();
void displayAllStudents();
void displayStudent(int rollNumber);
void updateStudent(int rollNumber);
void deleteStudent(int rollNumber);
void calculateAverageMarks();
void searchStudent(char* name);
void sortStudentsByRollNumber();
void sortStudentsByMarks(int subjectIndex);
void saveToFile();
void loadFromFile();

struct Student students[MAX_STUDENTS];
int numStudents;