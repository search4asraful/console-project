#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COURSES 100
#define MAX_STUDENTS 100

typedef struct {
    int roll;
    char name[50];
} Course;

typedef struct {
    int roll;
    char name[50];
    int assignedCourses[MAX_COURSES];
    int courseCount;
} Student;

Course courses[MAX_COURSES];
int courseCount = 0;
Student students[MAX_STUDENTS];
int studentCount = 0;

void addCourse();
void viewCourses();
void updateCourse();
void deleteCourse();
void assignCourseToStudent();
void deassignCourseFromStudent();
void coursesMenu();

void loadCourses() {
    FILE *file = fopen("courses.txt", "r");
    if (file != NULL) {
        while (fscanf(file, "%d %[^\n]", &courses[courseCount].roll, courses[courseCount].name) == 2) {
            courseCount++;
        }
        fclose(file);
    } else {
        printf("Could not load courses. Ensure 'courses.txt' exists and is correctly formatted.\n");
    }
}

void saveCourses() {
    FILE *file = fopen("courses.txt", "w");
    if (file == NULL) {
        printf("Error opening file for saving courses.\n");
        return;
    }
    for (int i = 0; i < courseCount; i++) {
        fprintf(file, "%d %s\n", courses[i].roll, courses[i].name);
    }
    fclose(file);
}

void coursesMenu() {
    int choice;
    loadCourses();

    do {
        printf("\n--- Courses Management System ---\n");
        printf("1. Add Course\n");
        printf("2. View Courses\n");
        printf("3. Update Course\n");
        printf("4. Delete Course\n");
        printf("5. Return to Main Menu\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                clearConsole();
                addCourse();
                break;
            case 2:
                clearConsole();
                viewCourses();
                break;
            case 3:
                clearConsole();
                updateCourse();
                break;
            case 4:
                clearConsole();
                deleteCourse();
                break;
            case 5:
                clearConsole();
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalroll choice. Please try again.\n");
        }
    } while (choice != 5);
    return;
}

void addCourse() {
    if (courseCount >= MAX_COURSES) {
        printf("Maximum number of courses reached.\n");
        return;
    }

    Course newCourse;
    printf("Enter course Roll: ");
    scanf("%d", &newCourse.roll);
    printf("Enter course name: ");
    getchar();
    fgets(newCourse.name, sizeof(newCourse.name), stdin);
    newCourse.name[strcspn(newCourse.name, "\n")] = 0;

    courses[courseCount++] = newCourse;
    saveCourses();
    printf("Course added successfully.\n");
}

void viewCourses() {
    if (courseCount == 0) {
        printf("No courses available.\n");
        return;
    }

    printf("\n--- List of Courses ---\n");
    for (int i = 0; i < courseCount; i++) {
        printf("Roll: %d, Name: %s\n", courses[i].roll, courses[i].name);
    }
}

void updateCourse() {
    int roll;
    printf("Enter the Roll of the course to update: ");
    scanf("%d", &roll);

    for (int i = 0; i < courseCount; i++) {
        if (courses[i].roll == roll) {
            printf("Current name: %s\n", courses[i].name);
            printf("Enter new name (leave blank to keep current): ");
            getchar();
            char newName[50];
            fgets(newName, sizeof(newName), stdin);
            newName[strcspn(newName, "\n")] = 0;
            if (strlen(newName) > 0) {
                strcpy(courses[i].name, newName);
                saveCourses();
            }
            printf("Course updated successfully.\n");
            return;
        }
    }
    printf("Course with Roll %d not found.\n", roll);
}

void deleteCourse() {
    int roll;
    printf("Enter the Roll of the course to delete: ");
    scanf("%d", &roll);

    for (int i = 0; i < studentCount; i++) {
        for (int j = 0; j < students[i].courseCount; j++) {
            if (students[i].assignedCourses[j] == roll) {
                printf("Cannot delete course Roll %d. It is assigned to student Roll %d.\n", roll, students[i].roll);
                return;
            }
        }
    }

    for (int i = 0; i < courseCount; i++) {
        if (courses[i].roll == roll) {
            for (int j = i; j < courseCount - 1; j++) {
                courses[j] = courses[j + 1];
            }
            courseCount--;
            saveCourses();
            printf("Course with Roll %d has been deleted successfully.\n", roll);
            return;
        }
    }
    printf("Course with Roll %d not found.\n", roll);
}
