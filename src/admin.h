#ifndef ADMIN_H
#define ADMIN_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "global.h"

/**
 * Description: Display all of the option for admin menu
 * Paramater: None
 * Return: void
 */
void Admin_showAdminMenu();

void Admin_manageBuses();

/**
 * Description: Display all of the booking details
 * Parameter: None
 * Return: void
 */
void Admin_viewAllBookings();

/**
 * Description: Log out admin and return to the main menu
 * Parameter: None
 * Return: void
 */
void Admin_Logout();

#endif