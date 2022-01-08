#include "mathlib.h"

static int newton_number = 0;

double sqrt_newton(double x) {
    newton_number = 0;
    double z = 0.0;
    double y = 1.0;
    while (absolute(y - z) > EPSILON) {
        z = y;
        y = 0.5 * (z + x / z);
        newton_number++;
    }
    return y;
}

int sqrt_newton_iters(void) {
    return newton_number;
}
