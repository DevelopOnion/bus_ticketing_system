#ifndef ADMIN_H
#define ADMIN_H

#include <stdio.h>
#include <string.h>

#define BOOKING_FILE "../data/bookings.csv"

/**
 * Description: Display all of the option for admin menu
 * Paramater: None
 * Return: void
 */
void Admin_showAdminMenu();
void Admin_manageBuses();
void Admin_viewAllBookings();
void Admin_Logout();

#endif