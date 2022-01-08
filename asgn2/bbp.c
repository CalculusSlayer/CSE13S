#include "mathlib.h"

static int bbp_counter = 0;

double pi_bbp(void) {
    bbp_counter = 0;
    double pi_sum = 0;
    double current_term = 1.0;
    double k = 0.0;
    while (absolute(current_term) >= EPSILON) {
        current_term
            = (k * (120 * k + 151) + 47) / (k * (k * (k * (512 * k + 1024) + 712) + 194) + 15);
        for (int count = 0; count < k; count++) {
            current_term /= 16;
        }
        pi_sum += current_term;
        k++;
        bbp_counter++;
    }
    return pi_sum;
}

int pi_bbp_terms(void) {
    return bbp_counter;
}
