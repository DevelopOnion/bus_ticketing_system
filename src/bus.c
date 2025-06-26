#include "bus.h"
#include "validation.h"

bool Admin_addBus() {
    Bus newBus;
    // Generate a new bus ID
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
    scanf("%s", newBus.name);
    printf("Enter Origin: ");
    scanf("%s", newBus.origin);
    printf("Enter Destination: ");
    scanf("%s", newBus.destination);
    printf("Enter Departure Time (HH:MM): ");
    scanf("%s", newBus.departureTime);
    printf("Enter Total Seats: ");
    scanf("%d", &newBus.totalSeats);
    char route[MAX_ORIGIN_LEN + MAX_DESTINATION_LEN + 2];
    sprintf(route, "%s-%s", newBus.origin, newBus.destination);

    fprintf(scanner_busesFile, "\n%s,%s,%s,%s,%d", 
            newBus.busID, newBus.name, route, 
            newBus.departureTime, newBus.totalSeats);

    fclose(scanner_busesFile);
    printf("New bus added successfully.\n");
    return true;
}

