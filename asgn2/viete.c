#include "mathlib.h"

static int viete_counter = 0;

double pi_viete(void) {
    viete_counter = 0;
    double pi_product = 1.0;
    double current_term = 0;
    double previous_term = 20.0;
    while (absolute(current_term / 2.0 - previous_term / 2.0) >= EPSILON) {
        previous_term = current_term;
        current_term = sqrt_newton(2 + previous_term);
        pi_product *= current_term / 2;
        viete_counter++;
    }
    return 2.0f / pi_product;
}

int pi_viete_factors(void) {
    return viete_counter;
}
