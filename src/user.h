#ifndef USER_H
#define USER_H

#include <stdbool.h>

#define USERS_FILE "../data/users.csv"
#define USER_COUNTER_FILE "../data/user_counter.txt"
#define LINE_SIZE 512
#define ID_SIZE 5
#define USERNAME_SIZE 64
#define PASSWORD_SIZE 64
#define PHONENUMBER_SIZE 32

typedef struct User {
    char userID[ID_SIZE];
    char username[USERNAME_SIZE];
    char password[PASSWORD_SIZE];
    char phoneNumber[PHONENUMBER_SIZE];
    int role;
} User;

bool User_register();
bool User_isUsernameUnique(char *username);
int User_login();

#endif