#ifndef USER_H
#define USER_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

#include "global.h"

// user struct
typedef struct User {
    char userID[MAX_ID_LEN];
    char username[MAX_NAME_LEN];
    char password[MAX_PASSWORD_LEN];
    char phoneNumber[MAX_PHONENUMBER_LEN];
    int role;
} User;

User User_register(); 
bool User_isUsernameUnique(char *username);
User User_login();
void User_showUserMenu(User *currentUser);
void User_logout(User *currentUser);
void User_showAvailableBuses();

#endif