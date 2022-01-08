#include "mathlib.h"

static int euler_counter = 0;

double pi_euler(void) {
    euler_counter = 0;
    long double pi_sum = 0.0;
    long double current_term = 1.0;
    long double val = 0.0;
    while (absolute(current_term) >= EPSILON) {
        current_term = 1.0 / ((val + 1.0) * (val + 1.0));
        pi_sum += current_term;
        euler_counter++;
        val++;
    }
    return sqrt_newton(6 * pi_sum);
}

int pi_euler_terms(void) {
    return euler_counter;
}
