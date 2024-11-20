#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TRIES 3
#define USER_DB "users.csv"

int login()
{
    char inputUsername[50];
    char inputPassword[50];
    char username[50];
    char password[50];
    int attempts = 0;

    while (attempts < MAX_TRIES)
    {
        printf("Enter username: ");
        scanf("%s", inputUsername);
        printf("Enter password: ");
        scanf("%s", inputPassword);

        FILE *file = fopen(USER_DB, "r");
        if (file == NULL)
        {
            printf("Error opening user database.\n");
            return 0;
        }

        int found = 0;

        char line[100];
        while (fgets(line, sizeof(line), file))
        {
            line[strcspn(line, "\n")] = 0;

            char *token = strtok(line, ",");
            if (token != NULL)
            {
                strcpy(username, token);
                token = strtok(NULL, ",");
                if (token != NULL)
                {
                    strcpy(password, token);
                }

                if (strcmp(inputUsername, username) == 0 && strcmp(inputPassword, password) == 0)
                {
                    printf("Login successful!\n");
                    found = 1;
                    break;
                }
            }
        }

        fclose(file);

        if (found)
        {
            return 1;
        }
        else
        {
            clearConsole();
            printf("Invalid username or password. Please try again.\n");
            attempts++;
        }
    }
    clearConsole();
    printf("Too many failed attempts.\n\n");
    return 0;
}
