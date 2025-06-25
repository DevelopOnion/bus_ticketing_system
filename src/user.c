#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "user.h"
#include "util.h"
#include "validation.h"

bool User_register() {
    char username[MAX_USERNAME_LEN];
    do {
        printf("Character allowed (A-Z a-z) (1-9) (a space)\n");
        printf("Enter username: ");
        scanf("%[^\n]c", username);
        Util_clearInputBuffer();

        if (!Validation_isValidUsername(username)) {
            printf("\nInvalid username. Please try again\n\n");
            continue;
        }

        if (!User_isUsernameUnique(username))
            printf("\nUsername already exist. Please enter another name.\n\n");
    } while (!User_isUsernameUnique(username) || !Validation_isValidUsername(username));

    char password[MAX_PASSWORD_LEN];
    do {
        printf("\nPassword must have\n");
        printf("_ Minimum length 8\n");
        printf("_ Combination of lowercase, uppercase, and digit.\n");
        printf("_ Symbol is allowed but space is not allowed\n");
        printf("Enter Password: ");
        scanf("%[^\n]c", password);
        Util_clearInputBuffer();

        if (!Validation_isValidPassword(password)) 
            printf("\nInvalid password, Please try again.\n\n");
    } while (!Validation_isValidPassword(password));

    char phonenumber[MAX_PHONENUMBER_LEN];
    do {
        printf("\nPhonenumber should start with 0\n");
        printf("Enter phonenumber: ");
        scanf("%[^\n]c", phonenumber);
        Util_clearInputBuffer();

        if (!Validation_isValidPhonenumber(phonenumber))
            printf("\nInvalid phonenumber. Please try again.\n\n");
    } while (!Validation_isValidPhonenumber(phonenumber));

    char previousId[5];
    char newId[5];
    FILE *scanner_counterFile = NULL;

    scanner_counterFile = fopen(USER_COUNTER_FILE, "r");
    if (scanner_counterFile == NULL) {
        printf("Error: Cannot load data\n.");
        fclose(scanner_counterFile);
        return false;
    }

    fscanf(scanner_counterFile, "%s", previousId);
    sprintf(newId, "U%03d", atoi(previousId) + 1);

    fclose(scanner_counterFile);

    scanner_counterFile = fopen(USER_COUNTER_FILE, "w");
    if (scanner_counterFile == NULL) {
        printf("Error: Cannot load data\n.");
        fclose(scanner_counterFile);
        return false;
    }

    fprintf(scanner_counterFile, "%d", atoi(previousId) + 1);

    fclose(scanner_counterFile);

    FILE *scanner_userFile = NULL;
    scanner_userFile = fopen(USERS_FILE, "a");
    if (scanner_userFile == NULL) {
        printf("Error: Cannot load data\n.");
        fclose(scanner_userFile);
        return false;
    }

    fprintf(scanner_userFile, "\n%s,%s,%s,%s,%s",
                        newId, username, password, phonenumber, "0");
    fclose(scanner_userFile);

    return true;
}

bool User_isUsernameUnique(char *username) {
    FILE *scanner = NULL;
    scanner = fopen(USERS_FILE, "r");

    if (scanner == NULL) {
        printf("Error: Cannot load data\n");
        fclose(scanner);
        return false;
    }

    // buffer for storing each line in the file
    char line[MAX_LINE_LEN];

    // skip header line
    fgets(line, sizeof(line), scanner);
 
    bool isUnique = true;
    while (fgets(line, sizeof(line), scanner) != NULL) {
        line[strcspn(line, "\n")] = 0;

        char tmpLine[MAX_LINE_LEN];
        strcpy(tmpLine, line);

        char* token;
        int counter_column = 0;

        token = strtok(tmpLine, ",");

        while (token != NULL) {
            counter_column++;

            if (counter_column == 2) {
                if (strcmp(token, username) == 0) // if found exisiting username
                    isUnique = false;
                break;
            }

            token = strtok(NULL, ",");
        }

        // stop checking if found
        if (!isUnique) break;
    }

    fclose(scanner);
    return isUnique;
}

int User_login() {
    char username[MAX_USERNAME_LEN];
    printf("Enter username: ");
    scanf("%[^\n]c", username);
    Util_clearInputBuffer();
    
    char password[MAX_PASSWORD_LEN];
    printf("Enter password: ");
    scanf("%[^\n]c", password);
    Util_clearInputBuffer();

    FILE *scanner_userFile = NULL;
    scanner_userFile = fopen(USERS_FILE, "r");
    if (scanner_userFile == NULL) {
        printf("Error: Cannot load data\n.");
        fclose(scanner_userFile);
        return false;
    }
    

    bool foundUsername = false;
    bool isCorrectPassword = false;
    int role;
    char line[MAX_LINE_LEN];

    // skip the heading
    fgets(line, sizeof(line), scanner_userFile);
    
    while (fgets(line, sizeof(line), scanner_userFile) != NULL) {
        line[strcspn(line, "\n")] = 0;

        char tmpLine[MAX_LINE_LEN];
        strcpy(tmpLine, line);

        char* token;
        int counter_column = 0;

        token = strtok(tmpLine, ",");

        while (token != NULL) {
            counter_column++;
            
            if (counter_column == 2) {
                if (strcmp(token, username) == 0) {
                    foundUsername = true;
                    
                    token = strtok(NULL, ",");
                    if (strcmp(token, password) == 0) {
                        isCorrectPassword = true;

                        token = strtok(NULL, ",");
                        token = strtok(NULL, ",");
                        
                        role = atoi(token);
                    }

                    break;
                }
            }

            token = strtok(NULL, ",");
        }
    }

    fclose(scanner_userFile);

    if (!foundUsername) {
        printf("Username does not exits.\n");
        return 0;
    }
    else if (!isCorrectPassword) {
        printf("Incorrect password. Please try again.\n");
        return 0;
    }

    return (role == 0) ? 1 : 2;
}
