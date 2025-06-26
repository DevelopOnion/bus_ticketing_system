#include "admin.h"
#include "util.h"

#define MAX_LINE_LEN 512
#define MAX_ID_LEN 8

void Admin_showAdminMenu() {
    int option;
    do {
        printf("Admin menu:\n");
        printf("1. Manage buses\n");
        printf("2. View all booking\n");
        printf("3. Log out\n");
        printf("Enter option: ");
        scanf("%d", &option);
        Util_clearInputBuffer();

        switch (option) {
            case 1:
                Admin_manageBuses();
                break;
            case 2:
                Admin_viewAllBookings();
                break;
            case 3:
                Admin_Logout();
                break;
            default:
                printf("Invalid option.\n");
        }

    } while (option != 3);
}   

void Admin_manageBuses() {
    return;
}

void Admin_viewAllBookings() {
    printf("\n========== ALL BOOKING ==========\n");

    FILE *scanner_bookingsFile = NULL;
    scanner_bookingsFile = fopen(BOOKING_FILE, "r");
    if (scanner_bookingsFile == NULL) {
        printf("Error: Cannot open file\n");
    }

    char line[MAX_LINE_LEN];
    int counter_booking = 0;

    // skip heading line
    fgets(line, sizeof(line), scanner_bookingsFile);

    while (fgets(line, sizeof(line), scanner_bookingsFile) != NULL) {
        line[strcspn(line, "\n")] = 0;

        counter_booking++;
        printf("\nBooking %d\n", counter_booking);

        char tmpLine[MAX_LINE_LEN];
        strcpy(tmpLine, line);
        
        char* token;

        token = strtok(tmpLine, ",");
        printf("Booking ID: %s\n", token);
        
        char userID[8];
        token = strtok(NULL, ",");
        strcpy(userID, token);

        token = strtok(NULL, ",");
        printf("Bus ID: %s\n", token);

        token = strtok(NULL, ",");
        printf("Seat Number: %s\n", token);

        token = strtok(NULL, ",");
        printf("Passenger Name: %s\n", token);

        token = strtok(NULL, ",");
        printf("Phone Number: %s\n", token);

        token = strtok(NULL, ",");
        printf("Booking Date: %s\n", token);

        token = strtok(NULL, ",");
    }
}

void Admin_Logout() {
    printf("\nLogging out...\n");
}