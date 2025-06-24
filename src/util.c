#include <stdio.h>

#include "util.h"

void Util_clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}