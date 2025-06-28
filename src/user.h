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

/**
 * Description: register user to database
 * Paramater: None
 * Return: true - if successfull
 *         false - if failed 
 */
bool User_register(); 

/**
 * Description: helper function to register that
 *              check to see if any username already exist in database
 * Paramater: pointer to character array
 * Return: (bool) true - if successfull
 *                false - if failed 
 */
bool User_isUsernameUnique(char *username);

/**
 * Description: login process for both admin or user
 * Paramater: None
 * Return: int 1 - login user sucessfully
 *             2 - login admin sucessfully
 *             0 - login failed
 */
int User_login();

#endif