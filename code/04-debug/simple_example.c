#include "simple_lib.h"

#include <math.h>
#include <stdio.h>

int main() {
    double x = 1.2;

    printf("Library result: %f\n", sin(x));
    printf("Approx result:  %f\n", my_sin(x));

    return 0;
}
