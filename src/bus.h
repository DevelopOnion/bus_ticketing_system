#ifndef BUS_H
#define BUS_H

#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>


#define MAX_BUSES 100
#define BUSES_FILE "../data/buses.csv"
#define BUSES_COUNTER_FILE "../data/bus_counter.txt"

#define MAX_ID_LEN 8
#define MAX_NAME_LEN 64
#define MAX_ORIGIN_LEN 64
#define MAX_DESTINATION_LEN 64
#define MAX_DEPARTURE_TIME_LEN 8


typedef struct Bus {
    char busID[MAX_ID_LEN];
    char name[MAX_NAME_LEN];
    char origin[MAX_ORIGIN_LEN];
    char destination[MAX_DESTINATION_LEN];
    char departureTime[MAX_DEPARTURE_TIME_LEN];
    int totalSeats;
} Bus;

// Function Prototypes
bool Admin_addBus();
bool Admin_editBus();  
bool Admin_deleteBus();
bool Admin_viewBuses();

int Admin_loadBuses(Bus buses[], int max);
int Admin_saveAllBuses(Bus buses[], int count);


#endif