#ifndef VALIDATION_H
#define VALIDATION_H

#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

bool Validation_isValidPassword(const char *password);
bool Validation_isValidUsername(const char *username);
bool Validation_isValidSeats(const int totalSeats);
bool Validation_isValidPhonenumber(const char *phonenumber);
bool Validation_isValidTimeFormat(const char *timeStr);
bool Validation_isValidRoute(const char *destination, const char *origin);
bool Validation_isValidDate(const char *dateStr);

#endif