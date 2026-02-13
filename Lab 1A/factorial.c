#include "mathlib.h"

unsigned long factorial(int n) {
    if (n < 0) {
        fprintf(stderr, "Error: Factorial of a negative number is undefined.\n");
        exit(EXIT_FAILURE);
    }
    if (n == 0) { // Base case: factorial of 0 is 1
        return 1;
    }
    return n * factorial(n - 1); // Recursive call
}
