#include <stdio.h>

#include "util.h"

void Util_clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void Util_exitProgram() {
    printf("Exiting the program...\n");
    exit(1);
}