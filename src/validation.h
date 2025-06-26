#ifndef VALIDATION_H
#define VALIDATION_H

#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

/**
 * Description: check if password meet the requirement to not
 * Paramater: pointer to character array
 * Return: (bool) true - if valid
 *                false - if invalid
 */
bool Validation_isValidPassword(char *password);

/**
 * Description: check if Username meet the requirement to not
 * Paramater: pointer to character array
 * Return: (bool) true - if valid
 *                false - if invalid
 */
bool Validation_isValidUsername(char *username);

/**
 * Description: check if phonenumber meet the requirement to not
 * Paramater: pointer to character array
 * Return: (bool) true - if valid
 *                false - if invalid
 */
bool Validation_isValidPhonenumber(char *phonenumber);

#endif