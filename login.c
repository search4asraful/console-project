#include <stdio.h>
#include <string.h>
#include "login.h"

#define MAX_TRIES 3
#define USER_DB "users.txt"

int login() {
    char inputUsername[50];
    char inputPassword[50];
    char username[50];
    char password[50];
    int attempts = 0;

    while (attempts < MAX_TRIES) {
        printf("\n");
        printf("Enter username: ");
        scanf("%s", inputUsername);
        printf("Enter password: ");
        scanf("%s", inputPassword);

        FILE *file = fopen(USER_DB, "r");
        if (file == NULL) {
            printf("Error opening user database.\n");
            return 0;
        }

        int found = 0;

        while (fscanf(file, "%s %s", username, password) != EOF) {
            if (strcmp(inputUsername, username) == 0 && strcmp(inputPassword, password) == 0) {
                printf("Login successful!\n");
                found = 1;
                break;
            }
        }

        fclose(file);

        if (found) {
            return 1;
        } else {
            clearConsole();
            printf("Invalid username or password. Please try again.\n");
            attempts++;
        }
    }

    printf("Too many failed attempts. Exiting.\n");
    return 0;
}
