#include <stdio.h>
#include "login.h"

void addStudent();
void viewStudents();
void updateStudent();
void deleteStudent();
void showMenu();
void clearConsole();
void coursesMenu();

int main() {
    if (login()) {
        showMenu();
    } else {
        clearConsole();
        printf("Access denied.\n");
    }

    return 0;
}

void clearConsole() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void showMenu() {
    int choice;
    clearConsole();
    printf("Welcome to the console App! *(SMS)\n\n");

    do {
        printf("\n--- Student Management System ---\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Update Student\n");
        printf("4. Delete Student\n");
        printf("5. Courses\n");
        printf("6. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                clearConsole();
                addStudent();
                break;
            case 2:
                clearConsole();
                viewStudents();
                break;
            case 3:
                clearConsole();
                updateStudent();
                break;
            case 4:
                clearConsole();
                deleteStudent();
                break;
            case 5:
                clearConsole();
                coursesMenu();
                break;
            case 6:
                clearConsole();
                printf("\nExiting the application. Goodbye!\n");
                break;
            default:
                clearConsole();
                printf("\nInvalroll choice. Please try again.\n");
        }
    } while (choice != 6);
}

void addStudent() {
    FILE *file = fopen("students.txt", "a");
    if (file == NULL) {
        printf("Error opening file for adding student.\n");
        return;
    }

    char name[50];
    int roll;

    printf("Enter student Roll: ");
    scanf("%d", &roll);
    printf("Enter student name: ");
    scanf(" %[^\n]", name);

    fprintf(file, "%d %s\n", roll, name);
    fclose(file);
    printf("Student added successfully.\n");
}

void viewStudents() {
    FILE *file = fopen("students.txt", "r");
    if (file == NULL) {
        printf("Error opening file for viewing students.\n");
        return;
    }

    int roll;
    char name[50];

    printf("\n--- List of Students ---\n");
    while (fscanf(file, "%d %[^\n]", &roll, name) != EOF) {
        printf("Roll: %d, Name: %s\n", roll, name);
    }
    fclose(file);
}

void updateStudent() {
    FILE *file = fopen("students.txt", "r");
    if (file == NULL) {
        printf("Error opening file for updating student.\n");
        return;
    }

    int roll, newId;
    char name[50], newName[50];
    int found = 0;

    printf("Enter the Roll of the student to update: ");
    scanf("%d", &roll);

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error opening temporary file.\n");
        fclose(file);
        return;
    }

    while (fscanf(file, "%d %[^\n]", &newId, name) != EOF) {
        if (newId == roll) {
            printf("Current name: %s\n", name);
            printf("Enter new name for student (leave blank to go back to menu): ");
            getchar();
            fgets(newName, sizeof(newName), stdin);

            newName[strcspn(newName, "\n")] = 0;

            if (strlen(newName) == 0) {
                printf("Returning to menu...\n");
                fclose(file);
                fclose(tempFile);
                remove("temp.txt");
                return;
            }

            fprintf(tempFile, "%d %s\n", newId, newName);
            found = 1;
        } else {
            fprintf(tempFile, "%d %s\n", newId, name);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found) {
        printf("Student updated successfully.\n");
    } else {
        printf("Student with Roll %d not found.\n", roll);
    }
}

void deleteStudent() {
    FILE *file = fopen("students.txt", "r");
    if (file == NULL) {
        printf("Error opening file for deleting student.\n");
        return;
    }

    int roll, newId;
    char name[50];
    int found = 0;

    printf("Enter the Roll of the student to delete: ");
    scanf("%d", &roll);

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error opening temporary file.\n");
        fclose(file);
        return;
    }

    while (fscanf(file, "%d %[^\n]", &newId, name) != EOF) {
        if (newId == roll) {
            found = 1;
            printf("Deleted student: Roll = %d, Name = %s\n", newId, name);
            continue;
        }
        fprintf(tempFile, "%d %s\n", newId, name);
    }

    fclose(file);
    fclose(tempFile);

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found) {
        printf("Student deleted successfully.\n");
    } else {
        printf("Student with Roll %d not found.\n", roll);
    }
}
