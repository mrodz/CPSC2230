/* * Unit tests for the mathlib library.
 * This file can be compiled excluding the **main.c** file because both files have a `main` function.
 * The tests check the functionality of mod, factorial, and power functions.
 * Each test prints whether it passed or failed, along with expected and actual results.
 * The main function aggregates the results of all tests and prints the total number of failures.   
*/
#include <stdio.h>
#include "mathlib.h"

// Test the mod function.
// Expected: mod(20, 7) == 6 and mod(15, 4) == 3.
int test_mod(void) {
    int failures = 0;
    int result;

    result = mod(20, 7);
    if (result != 6) {
        printf("FAILED\ttest_mod_20_7\n");
        printf("      \tExpected: 6\n");
        printf("      \tActual  : %d\n", result);
        failures++;
    } else {
        printf("PASSED\ttest_mod_20_7\n");
    }

    result = mod(15, 4);
    if (result != 3) {
        printf("FAILED\ttest_mod_15_4\n");
        printf("      \tExpected: 3\n");
        printf("      \tActual  : %d\n", result);
        failures++;
    } else {
        printf("PASSED\ttest_mod_15_4\n");
    }

    return failures;
}

// Test the factorial function.
// Expected: factorial(5) == 120 and factorial(0) == 1.
int test_factorial(void) {
    int failures = 0;
    unsigned long long result;

    result = factorial(5);
    if (result != 120ULL) {
        printf("FAILED\ttest_factorial_5\n");
        printf("      \tExpected: 120\n");
        printf("      \tActual  : %llu\n", result);
        failures++;
    } else {
        printf("PASSED\ttest_factorial_5\n");
    }

    result = factorial(0);
    if (result != 1ULL) {
        printf("FAILED\ttest_factorial_0\n");
        printf("      \tExpected: 1\n");
        printf("      \tActual  : %llu\n", result);
        failures++;
    } else {
        printf("PASSED\ttest_factorial_0\n");
    }
    return failures;
}

// Test the power function.
// Expected: power(2, 8) == 256,
//           power(5, 0) == 1,
//           power(2, -3) == 0.125.
int test_power(void) {
    int failures = 0;
    double result;

    result = power(2, 8);
    if (result != 256.0) {
        printf("FAILED\ttest_power_2_8\n");
        printf("      \tExpected: 256\n");
        printf("      \tActual  : %g\n", result);
        failures++;
    } else {
        printf("PASSED\ttest_power_2_8\n");
    }

    result = power(5, 0);
    if (result != 1.0) {
        printf("FAILED\ttest_power_5_0\n");
        printf("      \tExpected: 1\n");
        printf("      \tActual  : %g\n", result);
        failures++;
    } else {
        printf("PASSED\ttest_power_5_0\n");
    }

    result = power(2, -3);
    if (result != 0.125) {
        printf("FAILED\ttest_power_2_neg3\n");
        printf("      \tExpected: 0.125\n");
        printf("      \tActual  : %g\n", result);
        failures++;
    } else {
        printf("PASSED\ttest_power_2_neg3\n");
    }
    return failures;
}

int main(void) {
    int total_failures = 0;

    total_failures += test_mod();
    total_failures += test_factorial();
    total_failures += test_power();

    if (total_failures == 0) {
        printf("PASSED\tall_tests\n");
    } else {
        printf("FAILED\tall_tests\n");
        printf("      \tNumber of failed tests: %d\n", total_failures);
    }

    return 0;
}
