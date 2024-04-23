// Main Program: student_management_system.c
#include <stdio.h>
#include <string.h>
// #include "student.h"    

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

int main() {
    loadFromFile();
    int choice, roll, saved = 0, subjectIndex;
    char searchName[50];
    do {
        printf("\nStudent Record Management System\n");
        printf("1. Add Student\n2. Display All Students\n3. Display Student\n4. Update Student\n5. Delete Student\n6. Calculate Average Marks\n7. Search Student\n8. Sort Students by Roll Number\n9. Sort Students by Marks\n10. Save to File\n11. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayAllStudents();
                break;
            case 3:
                printf("Enter roll number: ");
                scanf("%d", &roll);
                displayStudent(roll);
                break;
            case 4:
                printf("Enter roll number to update: ");
                scanf("%d", &roll);
                updateStudent(roll);
                break;
            case 5:
                printf("Enter roll number to delete: ");
                scanf("%d", &roll);
                deleteStudent(roll);
                break;
            case 6:
                calculateAverageMarks();
                break;
            case 7:
                printf("Enter name to search: ");
                scanf("%s", searchName);
                searchStudent(searchName);
                break;
            case 8:
                sortStudentsByRollNumber();
                break;
            case 9:
                printf("Enter subject index to sort by marks: ");
                scanf("%d", &subjectIndex);
                sortStudentsByMarks(subjectIndex);
                break;
            case 10:
                saveToFile();
                saved = 1;
                break;
            case 11:
                if (saved == 0) saveToFile();
                printf("Exiting...");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 11);
    return 0;
}


void addStudent()
{
    if (numStudents == MAX_STUDENTS) {
        printf("Maximum number of students reached!\n");
        return;
    }
    
    struct Student newStudent;
    printf("\nEnter roll number: ");
    scanf("%d", &newStudent.rollNumber);

    for (int i = 0; i < numStudents; i++) {
        if (students[i].rollNumber == newStudent.rollNumber) {
            printf("The Student is already present!");
            return;
        }
    }

    printf("Enter name: ");
    scanf("%s", newStudent.name);
    printf("Enter marks for 5 subjects:\n");
    for (int i = 0; i < 5; i++) {
        scanf("%f", &newStudent.marks[i]);
    }
    
    students[numStudents] = newStudent;
    numStudents++;
    
    printf("\nStudent added successfully!\n");

}

void displayAllStudents()
{
    if (numStudents == 0) {
        printf("\nNo students to display!\n");
        return;
    }
    
    printf("\nStudent Records:\n");
    for (int i = 0; i < numStudents; i++) {
        printf("\nRoll Number: %d\n", students[i].rollNumber);
        printf("Name: %s\n", students[i].name);
        printf("Marks: ");
        for (int j = 0; j < 5; j++) {
            printf("%.2f ", students[i].marks[j]);
        }
        printf("\n\n");
    }
}

void displayStudent(int rollNumber)
{
    int found = 0;
    for (int i = 0; i < numStudents; i++) {
        if (students[i].rollNumber == rollNumber) {
            printf("Roll Number: %d\n", students[i].rollNumber);
            printf("Name: %s\n", students[i].name);
            printf("Marks: ");
            for (int j = 0; j < 5; j++) {
                printf("%.2f ", students[i].marks[j]);
            }
            printf("\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("\nStudent not found!\n");
    }
}

void updateStudent(int rollNumber)
{
    int found = 0;
    for (int i = 0; i < numStudents; i++) {
        if (students[i].rollNumber == rollNumber) {
            printf("\nEnter new name: ");
            scanf("%s", students[i].name);
            printf("\nEnter new marks for 5 subjects: \n");
            for (int j = 0; j < 5; j++) {
                scanf("%f", &students[i].marks[j]);
            }
            printf("\nStudent details updated successfully!\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("\nStudent not found!\n");
    }
}

void deleteStudent(int rollNumber)
{
    int found = 0;
    for (int i = 0; i < numStudents; i++) {
        if (students[i].rollNumber == rollNumber) {
            for (int j = i; j < numStudents - 1; j++) {
                students[j] = students[j + 1];
            }
            numStudents--;
            printf("\nStudent deleted successfully!\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("\nStudent not found!\n");
    }
}

void calculateAverageMarks()
{
    if (numStudents == 0) {
        printf("\nNo students to calculate average marks!\n");
        return;
    }
    
    float totalMarks = 0;
    for (int i = 0; i < numStudents; i++) {
        for (int j = 0; j < 5; j++) {
            totalMarks += students[i].marks[j];
        }
    }
    float averageMarks = totalMarks / (numStudents * 5);
    printf("\nAverage marks of all students: %.2f\n", averageMarks);
}

void searchStudent(char *name)
{
    int found = 0;
    for (int i = 0; i < numStudents; i++) {
        if (strcmp(students[i].name, name) == 0) {
            printf("\nRoll Number: %d\n", students[i].rollNumber);
            printf("Name: %s\n", students[i].name);
            printf("Marks: ");
            for (int j = 0; j < 5; j++) {
                printf("%.2f ", students[i].marks[j]);
            }
            printf("\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("\nStudent not found!\n");
    }
}

void sortStudentsByRollNumber()
{
    // Sort students by roll number
    for (int i = 0; i < numStudents - 1; i++) {
        for (int j = 0; j < numStudents - i - 1; j++) {
            if (students[j].rollNumber > students[j + 1].rollNumber) {
                struct Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    printf("\nStudents sorted by roll number!\n");
}

void sortStudentsByMarks(int subjectIndex)
{
    // Sort students by marks in a particular subject
    for (int i = 0; i < numStudents - 1; i++) {
        for (int j = 0; j < numStudents - i - 1; j++) {
            if (students[j].marks[subjectIndex] > students[j + 1].marks[subjectIndex]) {
                struct Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    printf("\nStudents sorted by marks in subject %d!\n", subjectIndex);
}

void saveToFile()
{
    FILE *file = fopen("student_records.txt", "w");
    if (file == NULL) {
        printf("\nError opening file!\n");
        return;
    }
    
    for (int i = 0; i < numStudents; i++) {
        fprintf(file, "%d, %s", students[i].rollNumber, students[i].name);
        for (int j = 0; j < 5; j++) {
            fprintf(file, ", %.2f", students[i].marks[j]);
        }
        fprintf(file, "\n");
    }
    
    fclose(file);
    printf("\nStudent records saved to file!\n");
}

void loadFromFile()
{
    FILE *file = fopen("student_records.txt", "r");
    if (file == NULL) {
        printf("\nNo saved records found!\n");
        return;
    }

    while (!feof(file)) {
        struct Student newStudent;
        fscanf(file, "%d, %s", &newStudent.rollNumber, newStudent.name);
        for (int j = 0; j < 5; j++) {
            fscanf(file, ", %f", &newStudent.marks[j]);
        }
        students[numStudents] = newStudent;
        numStudents++;
    }
    
    
    fclose(file);
    printf("\nStudent records loaded from file!\n");
}

