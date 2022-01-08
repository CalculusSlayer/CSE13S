#include "mathlib.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#define OPTIONS "aebmrvnsh"

int main(int argc, char **argv) {
    int opt = 0;
    bool no_input = true;
    bool a_flag = false;
    bool e_flag = false;
    bool b_flag = false;
    bool m_flag = false;
    bool r_flag = false;
    bool v_flag = false;
    bool n_flag = false;
    bool s_flag = false;
    bool h_flag = false;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        no_input = false;
        switch (opt) {
        case 'a': a_flag = true; break;
        case 'e': e_flag = true; break;
        case 'b': b_flag = true; break;
        case 'm': m_flag = true; break;
        case 'r': r_flag = true; break;
        case 'v': v_flag = true; break;
        case 'n': n_flag = true; break;
        case 's': s_flag = true; break;
        case 'h': h_flag = true; break;
        }
    }

    if (a_flag == true) {
        e_flag = true;
        b_flag = true;
        m_flag = true;
        r_flag = true;
        v_flag = true;
        n_flag = true;
    }
    if (e_flag == true) {
        double yolk1 = e();
        printf(
            "e() = %16.15lf, M_E = %16.15lf, diff = %16.15lf\n", yolk1, M_E, absolute(M_E - yolk1));
        if (s_flag) {
            printf("e() terms = %i\n", e_terms());
        }
    }
    if (r_flag == true) {
        double yolk2 = pi_euler();
        printf("pi_euler() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", yolk2, M_PI,
            absolute(M_PI - yolk2));
        if (s_flag) {
            printf("pi_euler() terms = %i\n", pi_euler_terms());
        }
    }
    if (b_flag == true) {
        double yolk3 = pi_bbp();
        printf("pi_bbp() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", yolk3, M_PI,
            absolute(M_PI - yolk3));
        if (s_flag) {
            printf("pi_bbp() terms = %i\n", pi_bbp_terms());
        }
    }
    if (m_flag == true) {
        double yolk4 = pi_madhava();
        printf("pi_madhava() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", yolk4, M_PI,
            absolute(M_PI - yolk4));
        if (s_flag) {
            printf("pi_madhava() terms = %i\n", pi_madhava_terms());
        }
    }
    if (v_flag == true) {
        double yolk5 = pi_viete();
        printf("pi_viete() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", yolk5, M_PI,
            absolute(M_PI - yolk5));
        if (s_flag) {
            printf("pi_viete() terms = %i\n", pi_viete_factors());
        }
    }
    if (n_flag == true) {
        for (double num1 = 0.0; num1 < 9.999; num1 += 0.1) {
            printf("sqrt_newton(%lf) = %16.15lf, sqrt(%lf) = %16.15lf, diff = %16.15lf\n", num1,
                sqrt_newton(num1), num1, sqrt(num1), absolute(sqrt_newton(num1) - sqrt(num1)));
            if (s_flag) {
                printf("sqrt_newton() terms = %d\n", sqrt_newton_iters());
            }
        }
    }
    if (h_flag == true || no_input == true) {
        printf("To run a program: \t $ ./mathlib <flags>\n");
        printf("-a \t Runs all tests.\n");
        printf("-e \t Runs e approximation test.\n");
        printf("-b \t Runs Bailey-Borwein-Plouffe pi approximation test.\n");
        printf("-m \t Runs Madhava pi approximation test.\n");
        printf("-r \t Runs Euler sequence pi approximation test.\n");
        printf("-v \t Runs Viete pi approximation test.\n");
        printf("-n \t Runs Newton-Raphson square root approximation tests.\n");
        printf("-s \t Enable printing of statistics to see computed terms for each tested "
               "function.\n");
        printf("-h \t Display a help message detailing program usage.\n");
    }
    return 0;
}
