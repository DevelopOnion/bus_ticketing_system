#include "booking.h"
#include "util.h"
#include "global.h"
#include "validation.h"

void Booking_bookTicket(User *currentUser) {
    char checkDate[MAX_DATE_LEN];
    do {
        printf("\nValid booking date now -> one year from now\n");
        printf("Enter the date you want to check (YYYY-MM-DD): ");
        scanf("%[^\n]", checkDate);
        Util_clearInputBuffer();
        
        if (!Validation_isValidDate(checkDate)) {
            printf("Invalid date.\n");
        }
    } while (!Validation_isValidDate(checkDate));

    Bus availableBues[MAX_BUS_COUNT];
    int count = Booking_getAvailableBuses(checkDate, availableBues);
    
    for (int i = 0; i < count; i++) {
        printf("\n(%d) %s(%s)\n", i + 1, availableBues[i].name, availableBues[i].busID);
        printf("Departure From: %s\n", availableBues[i].origin);
        printf("Going To: %s\n", availableBues[i].destination);
        printf("Departure Time: %s\n", availableBues[i].departureTime);
        printf("Total Seats: %d\n", availableBues[i].totalSeats);
        printf("Available Seats: %d\n", availableBues[i].availableSeats);
    }

    printf("\n========== BOOK TICKET ==========\n");

    int busOption;
    do {
        printf("\nEnter the bus option number you want to book: ");
        scanf("%d", &busOption);
        Util_clearInputBuffer();

        if (busOption < 1 || busOption > count) {
            printf("Invalid option.\n");
            continue;
        }
    } while (busOption < 1 || busOption > count);
    
    Bus selectedBus = availableBues[busOption - 1];
    printf("\nYou selected bus: %s (%s)\n", selectedBus.name, selectedBus.busID);
    printf("Departure From: %s\n", selectedBus.origin);
    printf("Going To: %s\n", selectedBus.destination);
    printf("Departure Time: %s\n", selectedBus.departureTime);
    printf("Total Seats: %d\n", selectedBus.totalSeats);
    printf("Available Seats: %d\n", selectedBus.availableSeats);

    Booking_printAvailableSeats(&selectedBus, checkDate);

    Booking newBooking;
    do {
        printf("\nPlease enter the seat number you want to book: ");
        scanf("%d", &newBooking.seatNumber);
        Util_clearInputBuffer();

        printf("You entered seat number: %d\n", newBooking.seatNumber);

        if (newBooking.seatNumber < 1 || newBooking.seatNumber > selectedBus.totalSeats) {
            printf("Invalid seat number. Please try again.\n");
            continue;
        }
        else if (!Booking_isSeatAvailable(selectedBus.busID, checkDate, newBooking.seatNumber)) {
            printf("Seat %d is already booked. Please choose another seat.\n", newBooking.seatNumber);
            continue;
        }
    } while (newBooking.seatNumber < 1 || newBooking.seatNumber > selectedBus.totalSeats || !Booking_isSeatAvailable(selectedBus.busID, checkDate, newBooking.seatNumber));

    // Create booking entry
    FILE *scanner_bookingFile = fopen(BOOKING_FILE, "a");
    if (scanner_bookingFile == NULL) {
        printf("Error: Cannot open booking file\n");
        return;
    }

    FILE *scanner_bookingFileCounter = fopen(BOOKINGS_COUNTER_FILE, "r");
    if (scanner_bookingFileCounter == NULL) {
        printf("Error: Cannot open booking counter file\n");
        fclose(scanner_bookingFile);
        return;
    }

    char lastBookingID[MAX_ID_LEN];
    fgets(lastBookingID, sizeof(lastBookingID), scanner_bookingFileCounter);
    int lastID = atoi(lastBookingID);
    sprintf(newBooking.bookingID, "BKG%03d", lastID + 1);

    fclose(scanner_bookingFileCounter);

    scanner_bookingFileCounter = fopen(BOOKINGS_COUNTER_FILE, "w");
    if (scanner_bookingFileCounter == NULL) {
        printf("Error: Cannot open booking counter file for writing\n");
        fclose(scanner_bookingFile);
        return;
    }
    fprintf(scanner_bookingFileCounter, "%d", lastID + 1);
    fclose(scanner_bookingFileCounter);

    strcpy(newBooking.userID, currentUser->userID);
    strcpy(newBooking.busID, selectedBus.busID);
    strcpy(newBooking.passengerName, currentUser->username);
    strcpy(newBooking.contact, currentUser->phoneNumber);
    strcpy(newBooking.departureDate, checkDate);
    fprintf(scanner_bookingFile, "\n%s,%s,%s,%d,%s,%s,%s", 
            newBooking.bookingID, newBooking.userID, newBooking.busID, newBooking.seatNumber, newBooking.passengerName, newBooking.contact, newBooking.departureDate);
    fclose(scanner_bookingFile);
    printf("Booking successful! Your booking ID is: %s\n", newBooking.bookingID);
}

void Booking_viewMyBookings() {
    return;
}
void Booking_cancelBooking() {
    return;
}

// Helper function: fills buses[] with available buses for a date, returns count
int Booking_getAvailableBuses(const char *date, Bus buses[]) {
    FILE *scanner_busesFile = fopen(BUSES_FILE, "r");
    if (scanner_busesFile == NULL) {
        printf("Error: Cannot open buses file\n");
        return 0;
    }
    char line[MAX_LINE_LEN];
    int count = 0;

    // skip heading line
    fgets(line, sizeof(line), scanner_busesFile);

    while (fgets(line, sizeof(line), scanner_busesFile) != NULL) {
        char busID[MAX_ID_LEN], name[MAX_NAME_LEN], route[MAX_LOCATION_LEN * 2], departureTime[MAX_DEPARTURE_TIME_LEN];
        int totalSeats;
        int parsed = sscanf(line, "%[^,],%[^,],%[^,],%[^,],%d", busID, name, route, departureTime, &totalSeats);
        if (parsed != 5) {
            printf("Warning: Could not parse bus info: %s\n", line);
            continue;
        }
        // Count booked seats for this bus on the selected date
        int bookedSeats = 0;
        FILE *scanner_bookingFile = fopen(BOOKING_FILE, "r");
        if (scanner_bookingFile != NULL) {
            char bookingLine[MAX_LINE_LEN];
            fgets(bookingLine, sizeof(bookingLine), scanner_bookingFile); // skip header
            while (fgets(bookingLine, sizeof(bookingLine), scanner_bookingFile) != NULL) {
                char bID[MAX_ID_LEN], bUserID[MAX_ID_LEN], bBusID[MAX_ID_LEN], seatNumber[MAX_SEAT_NUMBER_LEN], passengerName[MAX_NAME_LEN], contact[MAX_PHONENUMBER_LEN], bDate[MAX_DATE_LEN];
                int parsedBooking = sscanf(bookingLine, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,\n]", bID, bUserID, bBusID, seatNumber, passengerName, contact, bDate);
                if (parsedBooking == 7 && strcmp(bBusID, busID) == 0 && strcmp(bDate, date) == 0) {
                    bookedSeats++;
                }
            }
            fclose(scanner_bookingFile);
        }
        else {
            printf("Warning: Cannot open booking file, skipping bus %s\n", busID);
            continue;
        }
        // Fill bus struct
        strncpy(buses[count].busID, busID, MAX_ID_LEN);
        strncpy(buses[count].name, name, MAX_NAME_LEN);
        // Split route
        char *dash = strchr(route, '-');
        if (dash) {
            int len = dash - route;
            strncpy(buses[count].origin, route, len);
            buses[count].origin[len] = '\0';
            strncpy(buses[count].destination, dash + 1, MAX_LOCATION_LEN - 1);
            buses[count].destination[MAX_LOCATION_LEN - 1] = '\0';
        } else {
            strncpy(buses[count].origin, route, MAX_LOCATION_LEN - 1);
            buses[count].origin[MAX_LOCATION_LEN - 1] = '\0';
            buses[count].destination[0] = '\0';
        }
        strncpy(buses[count].departureTime, departureTime, MAX_DEPARTURE_TIME_LEN);
        buses[count].totalSeats = totalSeats;
        buses[count].availableSeats = totalSeats - bookedSeats;
        count++;
    }
    fclose(scanner_busesFile);
    return count;
}

void Booking_printAvailableSeats(const Bus *bus, const char *date) {
    printf("\nAvailable seats for %s (%s) on %s:\n", bus->name, bus->busID, date);
    int totalSeats = bus->totalSeats;
    int seatBooked[totalSeats + 1];
    for (int i = 1; i <= totalSeats; i++) seatBooked[i] = 0;

    FILE *scanner_bookingFile = fopen(BOOKING_FILE, "r");
    if (scanner_bookingFile != NULL) {
        char bookingLine[MAX_LINE_LEN];
        fgets(bookingLine, sizeof(bookingLine), scanner_bookingFile); // skip header
        while (fgets(bookingLine, sizeof(bookingLine), scanner_bookingFile) != NULL) {
            char bID[MAX_ID_LEN], bUserID[MAX_ID_LEN], bBusID[MAX_ID_LEN], seatNumberStr[MAX_SEAT_NUMBER_LEN], passengerName[MAX_NAME_LEN], contact[MAX_PHONENUMBER_LEN], bDate[MAX_DATE_LEN];
            int parsedBooking = sscanf(bookingLine, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,\n]", bID, bUserID, bBusID, seatNumberStr, passengerName, contact, bDate);
            if (parsedBooking == 7 && strcmp(bBusID, bus->busID) == 0 && strcmp(bDate, date) == 0) {
                int seatNum = atoi(seatNumberStr);
                if (seatNum < 1 || seatNum > totalSeats) continue;
                seatBooked[seatNum] = 1;
            }
        }
        fclose(scanner_bookingFile);
    }
    else {
        printf("No bookings found for this bus on %s.\n", date);
        return;
    }
    // Print available seats
    printf("Available seat numbers: ");
    int found = 0;
    for (int i = 1; i <= totalSeats; i++) {
        if (!seatBooked[i]) {
            printf("%d ", i);
            found = 1;
        }
    }
    if (!found) {
        printf("None");
    }    
    printf("\n");
}

bool Booking_isSeatAvailable(const char *busID, const char *date, int seatNumber) {
    FILE *scanner_bookingFile = fopen(BOOKING_FILE, "r");
    if (scanner_bookingFile == NULL) {
        printf("Error: Cannot open booking file\n");
        return false;
    }
    char bookingLine[MAX_LINE_LEN];

    fgets(bookingLine, sizeof(bookingLine), scanner_bookingFile); // skip header

    while (fgets(bookingLine, sizeof(bookingLine), scanner_bookingFile) != NULL) {
        char bID[MAX_ID_LEN], bUserID[MAX_ID_LEN], bBusID[MAX_ID_LEN], seatNumberStr[MAX_SEAT_NUMBER_LEN], passengerName[MAX_NAME_LEN], contact[MAX_PHONENUMBER_LEN], bDate[MAX_DATE_LEN];
        int parsedBooking = sscanf(bookingLine, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,\n]", bID, bUserID, bBusID, seatNumberStr, passengerName, contact, bDate);
        if (parsedBooking == 7 && strcmp(bBusID, busID) == 0 && strcmp(bDate, date) == 0) {
            int bookedSeat = atoi(seatNumberStr);
            if (bookedSeat == seatNumber) {
                fclose(scanner_bookingFile);
                return false; // seat is already booked
            }
        }
    }
    fclose(scanner_bookingFile);
    return true; // seat is available
}