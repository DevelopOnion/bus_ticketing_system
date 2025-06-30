#ifndef ADMIN_H
#define ADMIN_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "user.h"

void Admin_showAdminMenu(User *currentUser);
void Admin_manageBuses();
void Admin_viewAllBookings();
void Admin_Logout(User *currentUser);

#endif