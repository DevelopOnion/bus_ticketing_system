#include "validation.h"
#include <time.h>

bool Validation_isValidUsername(const char *username) {
    int counter_space = 0;
    for (int i = 0; i < strlen(username); i++) {
        char c = username[i];
        if (!(isalnum(c) || isspace(c))) return false;
        if (isspace(c)) counter_space++;
        if (counter_space >= 2) return false;
    }
    return true;
}

bool Validation_isValidPhonenumber(const char *phonenumber) {
    if (phonenumber[0] != '0' || strlen(phonenumber) < 9) return false;
    for (int i = 0; i < strlen(phonenumber); i++) {
        if (!isdigit(phonenumber[i])) return false;
    }
    return true;
}

bool Validation_isValidPassword(const char *password) {
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

bool Validation_isValidTimeFormat(const char *timeStr) {
    int hh, mm;
    return sscanf(timeStr, "%d:%d", &hh, &mm) == 2 
           && hh >= 0 && hh < 24 && mm >= 0 && mm < 60;
}

bool Validation_isValidRoute(const char *destination, const char *origin) {
    return strcmp(destination, origin) != 0 
           && strlen(destination) > 0 
           && strlen(origin) > 0;
}


bool Validation_isValidSeats(const int totalSeats) {
    return totalSeats > 0;
}

bool Validation_isValidDate(const char *dateStr) {
    int year, month, day;
    if (sscanf(dateStr, "%d-%d-%d", &year, &month, &day) != 3) return false;

    if (year < 1900 || year > 2100 || month < 1 || month > 12 || day < 1 || day > 31) {
        return false;
    }

    // Check for valid days in month
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        return false;
    }
    if (month == 2) {
        bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if ((isLeapYear && day > 29) || (!isLeapYear && day > 28)) {
            return false;
        }
    }

    // Get current date
    time_t now = time(NULL);
    struct tm *tm_now = localtime(&now);
    struct tm input_tm = {0};
    input_tm.tm_year = year - 1900;
    input_tm.tm_mon = month - 1;
    input_tm.tm_mday = day;
    input_tm.tm_hour = 0;
    input_tm.tm_min = 0;
    input_tm.tm_sec = 0;
    time_t input_time = mktime(&input_tm);

    // Normalize current date to midnight
    tm_now->tm_hour = 0;
    tm_now->tm_min = 0;
    tm_now->tm_sec = 0;
    time_t today_time = mktime(tm_now);

    // Check if input date is before today or more than 1 year after today
    double diff_days = difftime(input_time, today_time) / (60 * 60 * 24);
    if (diff_days < 0 || diff_days > 365) {
        return false;
    }

    return true;
}
