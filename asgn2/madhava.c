#include "mathlib.h"

static int madhava_counter = 0;

double pi_madhava(void) {
    madhava_counter = 0;
    double pi_sum = 1.0;
    madhava_counter++;
    double top = 1.0;
    double bottom = 1.0;
    while (absolute(top / bottom) >= EPSILON) {
        top /= -3.0;
        bottom += 2.0;
        pi_sum += top / bottom;
        madhava_counter++;
    }
    return pi_sum * sqrt_newton(12);
}

int pi_madhava_terms(void) {
    return madhava_counter;
}
