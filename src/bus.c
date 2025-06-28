#include "bus.h"
#include "validation.h"
#include "util.h"

bool Bus_addBus() {
    Bus newBus;
    
    FILE *scanner_counterFile = fopen(BUSES_COUNTER_FILE, "r");
    if (scanner_counterFile == NULL) {
        printf("Error: Cannot load data.\n");
        fclose(scanner_counterFile);
        return false;
    }

    char previousBusID[MAX_ID_LEN];

    fscanf(scanner_counterFile, "%s", previousBusID);
    sprintf(newBus.busID, "BUS%03d", atoi(previousBusID) + 1);

    fclose (scanner_counterFile);

    scanner_counterFile = fopen(BUSES_COUNTER_FILE, "w");
    if (scanner_counterFile == NULL) {
        printf("Error: Cannot load data.\n");
        fclose(scanner_counterFile);
        return false;
    }
    fprintf(scanner_counterFile, "%d", atoi(previousBusID) + 1);
    fclose(scanner_counterFile);

    FILE *scanner_busesFile = fopen(BUSES_FILE, "a");
    if (scanner_busesFile == NULL) {
        printf("Error: Cannot load data.\n");
        return false;
    }
    
    printf("Enter Bus Name: ");
    scanf("%[^\n]c", newBus.name);
    Util_clearInputBuffer();

    do {
        printf("Enter Origin: ");
        scanf("%[^\n]c", newBus.origin);
        Util_clearInputBuffer();

        printf("Enter Destination: ");
        scanf("%[^\n]c", newBus.destination);
        Util_clearInputBuffer();

        if (!Validation_isValidRoute(newBus.destination, newBus.origin)) {
            printf("Invalid route. It must me different and not empty\n");
        }

    } while (!Validation_isValidRoute(newBus.destination, newBus.origin));
    

    do {
        printf("Enter Departure Time (HH:MM)24 hours format: ");
        scanf("%s", newBus.departureTime);

        if (!Validation_isValidTimeFormat(newBus.departureTime)) {
            printf("Invalid time format. Please use HH:MM format.\n");
        }
    } while (!Validation_isValidTimeFormat(newBus.departureTime));

    do {
        printf("Enter Total Seats: ");
        scanf("%d", &newBus.totalSeats);
        Util_clearInputBuffer();

        if (Validation_isValidSeats(newBus.totalSeats) == false) {
            printf("Invalid number of seats. It must be a positive integer.\n");
        }
    } while (Validation_isValidSeats(newBus.totalSeats) == false);
    

    char route[MAX_LOCATION_LEN * 2 + 2];
    sprintf(route, "%s-%s", newBus.origin, newBus.destination);

    fprintf(scanner_busesFile, "\n%s,%s,%s,%s,%d", 
            newBus.busID, newBus.name, route, 
            newBus.departureTime, newBus.totalSeats);

    fclose(scanner_busesFile);
    printf("New bus added successfully.\n");

    return true;
}

void Bus_viewBuses() {
    printf("\n========== ALL BUSES ==========\n");
    FILE *scanner_busesFile = fopen(BUSES_FILE, "r");
    if (scanner_busesFile == NULL) {
        printf("Error: Cannot load data.\n");
        return;
    }

    char line[MAX_LINE_LEN];
    bool hasBuses = false;

    // skip heading line
    fgets(line, sizeof(line), scanner_busesFile);

    while (fgets(line, sizeof(line), scanner_busesFile)) {
        hasBuses = true;
        char busID[MAX_ID_LEN], name[MAX_NAME_LEN], origin[MAX_LOCATION_LEN], 
             destination[MAX_LOCATION_LEN], departureTime[MAX_DEPARTURE_TIME_LEN];
        int totalSeats;

        sscanf(line, "\n%s,%s,%s-%s,%s,%d", 
            busID, name, origin, destination, departureTime, &totalSeats);

        printf("\nBus ID: %s\n", busID);
        printf("Name: %s\n", name);
        printf("Origin: %s\n", origin);
        printf("Destination: %s\n", destination);
        printf("Departure Time: %s\n", departureTime);
        printf("Total Seats: %d\n", totalSeats);
    }

    fclose(scanner_busesFile);

    if (!hasBuses) {
        printf("No buses available.\n");
    }
}



