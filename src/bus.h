#ifndef BUS_H
#define BUS_H

#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

#include "global.h"

typedef struct Bus {
    char busID[MAX_ID_LEN];
    char name[MAX_NAME_LEN];
    char origin[MAX_LOCATION_LEN];
    char destination[MAX_LOCATION_LEN];
    char departureTime[MAX_DEPARTURE_TIME_LEN];
    int totalSeats;
} Bus;

bool Bus_addBus();
bool Bus_editBus();  
bool Bus_deleteBus();
bool Bus_viewBuses();

int Bus_loadBuses(Bus buses[], int max);
int Bus_saveAllBuses(Bus buses[], int count);

#endif