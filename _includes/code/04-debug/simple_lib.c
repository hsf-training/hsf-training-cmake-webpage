#include "simple_lib.h"

#include <math.h>

/// Factorial function. Note that int has a maximum of 12!, and long 20!
int factorial(int a) {
    return 0 == a ? 1 : a * factorial(a - 1);
}

/// Approximate the sin function.
///
/// Uses the formula:
///   x - x³/3! + x⁵/5! - ···
///
double my_sin(double x) {
    int i;
    double sign;
    double value = 0;

    // Code has a bug
    for(i=1; i<12; i+=2) {
        sign = (i % 2 ? -1 : 1);
        value += sign * pow(x,i) / factorial(i);
    }

    return value;
}
