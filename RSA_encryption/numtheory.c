#include "numtheory.h"
#include "randstate.h"

#include <gmp.h>

// Used Asgn 6 Pseudocode
void gcd(mpz_t d, mpz_t a, mpz_t b) {

    mpz_t t, temp1, temp2;
    mpz_inits(t, temp1, temp2, NULL);
    mpz_set(temp1, a);
    mpz_set(temp2, b);

    while (mpz_cmp_si(temp2, 0) != 0) {
        mpz_set(t, temp2);
        mpz_mod(temp2, temp1, temp2);
        mpz_set(temp1, t);
    }

    mpz_set(d, temp1);
    mpz_clears(t, temp1, temp2, NULL);
}

// Used Asgn 6 Pseudocode
void mod_inverse(mpz_t i, mpz_t a, mpz_t n) {

    mpz_t r, rr, t, tt, q, temp1, temp2;
    mpz_inits(r, rr, t, tt, q, temp1, temp2, NULL);

    mpz_set(r, n);
    mpz_set(rr, a);

    mpz_set_si(t, 0);
    mpz_set_si(tt, 1);

    while (mpz_cmp_si(rr, 0) != 0) {
        mpz_fdiv_q(q, r, rr);

        // (r, r') <- (r', r-q*r')
        mpz_set(temp1, rr);
        mpz_set(temp2, r);
        mpz_submul(temp2, q, rr);
        mpz_set(r, temp1);
        mpz_set(rr, temp2);

        // (t, t') <- (t', t-q*t')
        mpz_set(temp1, tt);
        mpz_set(temp2, t);
        mpz_submul(temp2, q, tt);
        mpz_set(t, temp1);
        mpz_set(tt, temp2);
    }

    if (mpz_cmp_si(r, 1) > 0) {
        mpz_set_ui(i, 0);
        mpz_clears(r, rr, t, tt, q, temp1, temp2, NULL);
        return;
    }

    if (mpz_cmp_si(t, 0) < 0) {
        mpz_add(t, t, n);
    }

    mpz_set(i, t);
    mpz_clears(r, rr, t, tt, q, temp1, temp2, NULL);
    return;
}

// Used asgn 6 pseudocode.
void pow_mod(mpz_t out, mpz_t base, mpz_t exponent, mpz_t modulus) {

    mpz_t v, p, exponent_copy;
    mpz_inits(v, p, exponent_copy, NULL);

    mpz_set_ui(v, 1);
    mpz_set(p, base);

    mpz_set(exponent_copy, exponent);

    while (mpz_cmp_si(exponent_copy, 0) > 0) {

        if (mpz_odd_p(exponent_copy) != 0) {
            mpz_mul(v, v, p);
            mpz_mod(v, v, modulus);
        }

        mpz_mul(p, p, p);
        mpz_mod(p, p, modulus);

        mpz_fdiv_q_ui(exponent_copy, exponent_copy, 2);
    }

    mpz_set(out, v);
    mpz_clears(v, p, exponent_copy, NULL);
}

// Used asgn 6 pseudocode.
bool is_prime(mpz_t n, uint64_t iters) {

    mpz_t a, s, r, temp1, y, j, temp2, exponent1, n_copy, iters_copy;
    mpz_inits(a, s, r, temp1, y, j, temp2, exponent1, n_copy, iters_copy, NULL);
    mp_bitcnt_t shift = 1;

    if (mpz_cmp_si(n, 2) < 0) {
        return false;
    }

    if (mpz_cmp_si(n, 2) == 0 || mpz_cmp_si(n, 3) == 0) {
        return true;
    }

    if (mpz_odd_p(n) == 0) {
        return false;
    }

    mpz_sub_ui(temp1, n, 1);
    while (true) {

        if (mpz_odd_p(temp1) == 0) {
            mpz_fdiv_q_2exp(temp1, temp1, shift);
            mpz_add_ui(s, s, 1);
        }

        else {
            break;
        }
    }

    mpz_set(r, temp1);

    mpz_set_ui(exponent1, 2);
    for (uint64_t count1 = 0; count1 < iters; count1++) {
        mpz_sub_ui(temp1, n, 3);
        mpz_urandomm(a, state, temp1);
        mpz_add_ui(a, a, 2);
        pow_mod(y, a, r, n);
        mpz_sub_ui(temp1, n, 1);
        if (mpz_cmp_si(y, 1) != 0 && mpz_cmp(y, temp1) != 0) {
            mpz_set_ui(j, 1);

            mpz_sub_ui(temp1, s, 1);
            mpz_sub_ui(temp2, n, 1);
            while (mpz_cmp(j, temp1) <= 0 && mpz_cmp(y, temp2) != 0) {
                pow_mod(y, y, exponent1, n);
                if (mpz_cmp_si(y, 1) == 0) {
                    mpz_clears(a, s, r, temp1, y, j, temp2, exponent1);
                    return false;
                }
                mpz_add_ui(j, j, 1);
            }
            if (mpz_cmp(y, temp2) != 0) {
                mpz_clears(a, s, r, temp1, y, j, temp2, exponent1);
                return false;
            }
        }
    }
    mpz_clears(a, s, r, temp1, y, j, temp2, exponent1, NULL);
    return true;
}

// Used Asgn 6 Pseudo. Cite: TA Eugene told me to offset bits by
// a certain number.
void make_prime(mpz_t p, uint64_t bits, uint64_t iters) {
    while (true) {
        mpz_urandomb(p, state, bits + 10);
        if (is_prime(p, iters)) {
            break;
        }
    }
}
