#ifndef MATHLIB_H
#define MATHLIB_H

#include <stdlib.h>
#include <stdio.h>

// Computes the remainder of dividing a by b without using the '%' operator.
// Note: This simple version assumes a and b are positive.
int mod(int a, int b);

// Returns the factorial of a nonnegative integer n.
// If n is negative, the program will exit with an error.
unsigned long factorial(int n);

// Calculates base raised to the power exponent.
// Supports negative exponents by computing the reciprocal.
double power(double base, int exponent);

#endif // MATHLIB_H
