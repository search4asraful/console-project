#include <stdio.h>
#include <string.h>

void registerUser ()
{
    char username[50], password[50];
    FILE *file = fopen("users.csv", "a+");

    if (file == NULL)
    {
        printf("Error opening user file for registration.\n");
        return;
    }

    printf("Enter a username to register: ");
    scanf("%s", username);
    printf("Enter a password: ");
    scanf("%s", password);

    char fileUsername[50], filePassword[50];
    int userExists = 0;

    rewind(file);
    while (fscanf(file, "%[^,],%s\n", fileUsername, filePassword) != EOF)
    {
        if (strcmp(username, fileUsername) == 0)
        {
            printf("Username already exists. Please choose a different username.\n");
            userExists = 1;
            break;
        }
    }

    if (!userExists)
    {
        fprintf(file, "%s,%s\n", username, password);
        printf("Registration successful! You can now log in.\n");
    }

    fclose(file);
    printf("Press any key to continue...\n");
    getchar();
    getchar();
}
