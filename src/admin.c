#include "admin.h"
#include "util.h"

void showAdminMenu() {
    int option;
    do {
        printf("Admin menu:\n");
        printf("1. Manage buses\n");
        printf("2. View all booking\n");
        printf("3. Log out\n");
        printf("Enter option: ");
        scanf("%d, &option");
        Util_clearInputBuffer();

        // switch (option) {
        //     case 1:
        //         manageBuses();
        //         break;
        //     case 2:
        //         viewAllBookings();
        //         break;
        //     case 3:
        //         adminLogout();
        //         break;
        //     default:
        //         printf("Invalid option.\n");
        // }
        option = 3;

    } while (option != 3);
}   

void manageBuses() {
    /* 
    * addBus()
    * editBus()
    * deleteBus()
	* viewBuses()
    */
}
