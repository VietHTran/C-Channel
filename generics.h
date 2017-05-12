#ifndef GENERIC_H
#define GENERIC_H
#define CAT(x, y) x ## y
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//Check if condition is true then display error report
void checkerr(bool condition, const char* message) {
    if (condition) {
        perror(message);
        exit(1);
    }
}

#endif
