#include <stdio.h>
#include <string.h>

#include "bus.h"
#include "admin.h"
#include "user.h"
#include "util.h"

int main(void) {
    User currentUser;

    int option;
    do {
        printf("\n========== Bus Ticketing System ==========\n");
        printf("1. Admin Menu\n");
        printf("2. User Menu\n");
        printf("3. Register New User\n");
        printf("4. Exit\n");
        printf("Please select an option: ");
        scanf("%d", &option);
        Util_clearInputBuffer();

        switch (option) {
            case 1:
                currentUser = User_login();

                if (currentUser.userID[0] == '\0') {
                    printf("\nLogin failed. Please try again.\n");
                    break;
                }

                if (currentUser.role == 1) {
                    printf("\nLogin successful.\n");
                    Admin_showAdminMenu(&currentUser);
                }
                else {
                    printf("\nAccess denied. You do not have admin privileges.\n");
                }

                currentUser.userID[0] = '\0';

                break;
            case 2:
                currentUser = User_login();

                if (currentUser.userID[0] == '\0') {
                    printf("\nLogin failed. Please try again.\n");
                    break;
                }

                if (currentUser.role == 0) {
                    printf("\nLogin successful.\n");
                    User_showUserMenu(&currentUser);
                }
                else {
                    printf("\nAccess denied. This isn't a user account\n");
                }

                currentUser.userID[0] = '\0';

                break;
            case 3:
                User_register();
                break;
            case 4:
                Util_exitProgram();
            default:
                printf("\nInvalid option. Please try again.\n");
        }
    } while (option != 4);

    User_showUserMenu(&currentUser);
    
    return 0;
}