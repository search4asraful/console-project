#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include "login.h"
#include "register.h"

void addStudent();
void viewStudents();
void updateStudent();
void deleteStudent();
void showMenu();
void clearConsole();
void coursesMenu();

int main()
{
    int choice;
    int loggedIn = 0;

    while (!loggedIn)
    {
        clearConsole();
        printf("--- Welcome to, Student Management System ---\n\n");
        printf("1. Login\n");
        printf("2. Register\n");
        printf("3. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            clearConsole();
            if (login())
            {
                loggedIn = 1;
                showMenu();
                return 0;
            }
            else
            {
                printf("Access denied.\n");
                printf("Press any key to continue...\n");
                getch();
            }
            break;
        case 2:
            clearConsole();
            registerUser ();
            break;
        case 3:
            clearConsole();
            printf("\nExiting the application. Goodbye!\n");
            return 0;
        default:
            clearConsole();
            printf("Invalid choice. Please try again.\n");
            printf("Press any key to continue...\n");
            getch();
            break;
        }
    }

    return 0;
}

void clearConsole()
{
    system("clear || cls");
}

void showMenu()
{
    int choice;
    clearConsole();
    printf("Welcome to, Main menu.\n\n");

    do
    {
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Update Student\n");
        printf("4. Delete Student\n");
        printf("5. Courses\n");
        printf("6. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
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
            printf("\nInvalid roll choice. Please try again.\n");
        }
    }
    while (choice != 6);
}

void addStudent()
{
    FILE *file = fopen("students.csv", "a");
    if (file == NULL)
    {
        printf("Error opening file for adding student.\n");
        return;
    }

    char name[50];
    int roll, age;

    printf("Enter student Roll: ");
    scanf("%d", &roll);
    printf("Enter student name: ");
    scanf(" %[^\n]", name);
    printf("Enter student age: ");
    scanf("%d", &age);

    fprintf(file, "%d,%s,%d\n", roll, name, age);
    fclose(file);
    printf("Student added successfully.\n");
}

void viewStudents()
{
    FILE *file = fopen("students.csv", "r");
    if (file == NULL)
    {
        printf("Error opening file for viewing students.\n");
        return;
    }

    int roll, age;
    char name[50];

    printf("\n--- List of Students ---\n");
    while (fscanf(file, "%d,%[^,],%d", &roll, name, &age) != EOF)
    {
        printf("Roll: %d, Name: %s, Age: %d\n", roll, name, age);
    }
    fclose(file);
}

void updateStudent()
{
    FILE *file = fopen("students.csv", "r");
    if (file == NULL)
    {
        printf("Error opening file for updating student.\n");
        return;
    }

    int roll, newId, age, newAge;
    char name[50], newName[50];
    int found = 0;

    printf("Enter the Roll of the student to update: ");
    scanf("%d", &roll);

    FILE *tempFile = fopen("temp.csv", "w");
    if (tempFile == NULL)
    {
        printf("Error opening temporary file.\n");
        fclose(file);
        return;
    }

    while (fscanf(file, "%d,%[^,],%d", &newId, name, &age) != EOF)
    {
        if (newId == roll)
        {
            printf("Current name: %s, Current age: %d\n", name, age);
            printf("Enter new name for student (leave blank to keep current name, '*' to return to menu): ");
            getchar();
            fgets(newName, sizeof(newName), stdin);

            newName[strcspn(newName, "\n")] = 0;

            if (strcmp(newName, "*") == 0)
            {
                printf("Returning to menu...\n");
                fclose(file);
                fclose(tempFile);
                remove("temp.csv");
                return;
            }

            if (strlen(newName) == 0)
            {
                strcpy(newName, name);
            }

            printf("Enter new age for student (or press enter to keep current age): ");
            char ageInput[10];
            fgets(ageInput, sizeof(ageInput), stdin);

            if (strlen(ageInput) > 0 && ageInput[0] != '\n')
            {
                newAge = atoi(ageInput);
            }
            else
            {
                newAge = age;
            }

            fprintf(tempFile, "%d,%s,%d\n", newId, newName, newAge);
            found = 1;
        }
        else
        {
            fprintf(tempFile, "%d,%s,%d\n", newId, name, age);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("students.csv");
    rename("temp.csv", "students.csv");

    if (found)
    {
        printf("Student updated successfully.\n");
    }
    else
    {
        printf("Student with Roll %d not found.\n", roll);
    }
}

void deleteStudent()
{
    FILE *file = fopen("students.csv", "r");
    if (file == NULL)
    {
        printf("Error opening file for deleting student.\n");
        return;
    }

    int roll, newId, age;
    char name[50];
    int found = 0;

    printf("Enter the Roll of the student to delete: ");
    scanf("%d", &roll);

    FILE *tempFile = fopen("temp.csv", "w");
    if (tempFile == NULL)
    {
        printf("Error opening temporary file.\n");
        fclose(file);
        return;
    }

    while (fscanf(file, "%d,%[^,],%d", &newId, name, &age) != EOF)
    {
        if (newId == roll)
        {
            found = 1;
            printf("Deleted student: Roll = %d, Name = %s, Age = %d\n", newId, name, age);
            continue;
        }
        fprintf(tempFile, "%d,%s,%d\n", newId, name, age);
    }

    fclose(file);
    fclose(tempFile);

    remove("students.csv");
    rename("temp.csv", "students.csv");

    if (found)
    {
        printf("Student deleted successfully.\n");
    }
    else
    {
        printf("Student with Roll %d not found.\n", roll);
    }
}
