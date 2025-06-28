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
bool Validation_isValidPassword(const char *password);

/**
 * Description: check if Username meet the requirement to not
 * Paramater: pointer to character array
 * Return: (bool) true - if valid
 *                false - if invalid
 */
bool Validation_isValidUsername(const char *username);

/**
 * Description: check if phonenumber meet the requirement to not
 * Paramater: pointer to character array
 * Return: (bool) true - if valid
 *                false - if invalid
 */

bool Validation_isValidSeats(int totalSeats);
bool Validation_isValidPhonenumber(const char *phonenumber);
bool Validation_isValidTimeFormat(const char *timeStr);
bool Validation_isValidRoute(const char *destination, const char *origin);

#endif