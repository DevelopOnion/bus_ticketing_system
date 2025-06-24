#ifndef USER_H
#define USER_H

#include <stdbool.h>

#define USERS_FILE "../data/users.csv"
#define USER_COUNTER_FILE "../data/user_counter.txt"
#define LINE_SIZE 512
#define ID_SIZE 5
#define USER_SIZE 64
#define PASSWORD_SIZE 64
#define PHONENUMBER_SIZE 32

typedef enum Role {
    ADMIN, USER
} Role;

typedef struct User {
    char userID[ID_SIZE];
    char username[USER_SIZE];
    char password[PASSWORD_SIZE];
    char phoneNumber[PHONENUMBER_SIZE];
    Role role;
} User;

bool User_registerUser();
bool User_isUsernameUnique(char *username);

#endif