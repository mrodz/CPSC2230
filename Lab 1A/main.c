#include <stdio.h>
#include "mathlib.h"

int main(void) {
    
    printf("\n=========================================\n\n");
    // Demonstrate mod function: 20 mod 7
    int a = 20, b = 7;
    printf("The remainder of %d divided by %d is %d\n", a, b, mod(a, b));
    
    printf("\n=========================================\n\n");
    // Demonstrate factorial function: factorial of 5
    int fact_n = 5;
    printf("Factorial of %d is %lu\n", fact_n, factorial(fact_n));

    printf("\n=========================================\n\n");
    // Demonstrate power function: 2 to the power of 8
    double base = 2.0;
    int exponent = 8;
    printf("%g to the power of %d is %g\n", base, exponent, power(base, exponent));

    printf("\n=========================================\n\n");

    return 0;
}
