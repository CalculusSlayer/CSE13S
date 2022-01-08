#include "mathlib.h"

static int e_counter = 0;

double e(void) {
    e_counter = 0;
    double e_sum = 1.0;
    e_counter += 1;
    double temp = 1.0;
    double current_term = 100.0;
    while (absolute(current_term) >= EPSILON) {
        current_term = 1.000000000 / temp;
        e_sum += current_term;
        e_counter += 1;
        temp *= e_counter;
    }
    return e_sum;
}

int e_terms(void) {
    return e_counter;
}
