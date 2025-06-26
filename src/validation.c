#include "validation.h"

bool Validation_isValidUsername(char *username) {
    int counter_space = 0;
    for (int i = 0; i < strlen(username); i++) {
        char c = username[i];
        if (!(isalnum(c) || isspace(c))) return false;
        if (isspace(c)) counter_space++;
        if (counter_space >= 2) return false;
    }
    return true;
}

bool Validation_isValidPhonenumber(char *phonenumber) {
    if (phonenumber[0] != '0' || strlen(phonenumber) < 9) return false;
    for (int i = 0; i < strlen(phonenumber); i++) {
        if (!isdigit(phonenumber[i])) return false;
    }
    return true;
}

bool Validation_isValidPassword(char *password) {
    // verify length
    int len = strlen(password);
    if (len < 8) return false;

    bool hasDigit = false;
    bool hasUpper = false;
    bool hasLower = false;
    
    for (int i = 0; i < len; i++) {
        char c = password[i];
        if (isspace(c)) return false;
        if (isupper(c)) hasUpper = true;
        if (islower(c)) hasLower = true;
        if (isdigit(c)) hasDigit = true;
    }

    return hasUpper && hasLower && hasDigit;
}

int IsValidTimeFormat(const char *timeStr) {
    int hh, mm;
    return sscanf(timeStr, "%d:%d", &hh, &mm) == 2 
    && hh >= 0 && hh < 24 && mm >= 0 && mm < 60;

}