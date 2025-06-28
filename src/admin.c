#include "admin.h"
#include "util.h"

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
    bool hasBookings = false;

    // skip heading line
    fgets(line, sizeof(line), scanner_bookingsFile);

    while (fgets(line, sizeof(line), scanner_bookingsFile) != NULL) {
        hasBookings = true;
        char bookingID[MAX_ID_LEN], userID[MAX_ID_LEN], busID[MAX_ID_LEN],
             seatNumber[MAX_ID_LEN], passengerName[MAX_NAME_LEN], date[MAX_DATE_LEN],
             contact[MAX_PHONENUMBER_LEN];

        sscanf(line, "\n%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s", 
               bookingID, userID, busID, seatNumber, passengerName, contact, date);

        printf("\nBooking ID: %s\n", bookingID);
        printf("User ID: %s\n", userID);
        printf("Bus ID: %s\n", busID);
        printf("Seat Number: %s\n", seatNumber);
        printf("Passenger Name: %s\n", passengerName);
        printf("Contact: %s\n", contact);
        printf("Departure Date: %s\n", date);
    }
}

void Admin_Logout() {
    printf("\nLogging out...\n");
}