#include "mathlib.h"

int mod(int a, int b) {
    if (b == 0) {
        fprintf(stderr, "Error: Division by zero in mod function.\n"); // fprintf to stderr
        exit(EXIT_FAILURE);
    }
    int remainder = a;
    while (remainder >= b) { 
        // Subtract b from remainder until it's less than b
        remainder -= b;
    }
    return remainder;
}
