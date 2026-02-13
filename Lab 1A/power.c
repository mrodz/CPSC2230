#include "mathlib.h"

double power(double base, int exponent) {
    double result = 1.0;
    int exp = exponent;
    
    // Handle negative exponents.
    if (exp < 0) {
        base = 1.0 / base;
        exp = -exp;
    }
    
    for (int i = 0; i < exp; i++) {
        result *= base; // Multiply result by base for each iteration
    }
    return result;
}
