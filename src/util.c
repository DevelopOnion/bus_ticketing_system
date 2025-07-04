#include <stdio.h>

#include "util.h"

void Util_clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void Util_exitProgram() {
    printf("\nExiting the program...\n");
    exit(1);
}