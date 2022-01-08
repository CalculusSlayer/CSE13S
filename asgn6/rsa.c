#include "rsa.h"
#include "numtheory.h"
#include "randstate.h"
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

// Cite: TA Erik
void rsa_make_pub(mpz_t p, mpz_t q, mpz_t n, mpz_t e, uint64_t nbits, uint64_t iters) {

    mpz_t p_1, q_1, x, totient;
    mpz_inits(p_1, q_1, x, totient, NULL);
    uint64_t pbits = ((random() % 3) + 1) * nbits / 4;

    uint64_t qbits = nbits - pbits;
    make_prime(p, pbits, iters);
    make_prime(q, qbits, iters);
    mpz_sub_ui(p_1, p, 1);
    mpz_sub_ui(q_1, q, 1);
    mpz_mul(n, p, q);
    mpz_mul(totient, p_1, q_1);

    do {
        mpz_urandomb(e, state, nbits);
        gcd(x, e, totient);
    } while (mpz_cmp_ui(x, 1) != 0);

    mpz_clears(p_1, q_1, x, totient, NULL);
}

void rsa_write_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    gmp_fprintf(pbfile, "%Zx\n", n);
    gmp_fprintf(pbfile, "%Zx\n", e);
    gmp_fprintf(pbfile, "%Zx\n", s);
    fprintf(pbfile, "%s\n", username);
}

void rsa_read_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    gmp_fscanf(pbfile, "%Zx\n", n);
    gmp_fscanf(pbfile, "%Zx\n", e);
    gmp_fscanf(pbfile, "%Zx\n", s);
    fscanf(pbfile, "%s\n", username);
}

void rsa_make_priv(mpz_t d, mpz_t e, mpz_t p, mpz_t q) {
    mpz_t p_1, q_1;
    mpz_inits(p_1, q_1, NULL);
    mpz_sub_ui(p_1, p, 1);
    mpz_sub_ui(q_1, q, 1);
    mpz_mul(d, p_1, q_1);

    mod_inverse(d, e, d);
    mpz_clears(p_1, q_1, NULL);
}

void rsa_write_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fprintf(pvfile, "%Zx\n", n);
    gmp_fprintf(pvfile, "%Zx\n", d);
}

void rsa_read_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fscanf(pvfile, "%Zx\n", n);
    gmp_fscanf(pvfile, "%Zx\n", d);
}

void rsa_encrypt(mpz_t c, mpz_t m, mpz_t e, mpz_t n) {
    pow_mod(c, m, e, n);
}

// Cite: TA Erik
void rsa_encrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t e) {
    mpz_t m, c;
    mpz_inits(m, c, NULL);

    size_t k = (mpz_sizeinbase(n, 2) - 1) / 8;
    uint8_t *k_array = calloc(k, sizeof(uint8_t));
    k_array[0] = 0xFF;

    while (feof(infile) == 0) {
        size_t j = fread(k_array + 1, sizeof(uint8_t), k - 1, infile);
        mpz_import(m, j + 1, 1, sizeof(uint8_t), 1, 0, k_array);
        rsa_encrypt(c, m, e, n);
        gmp_fprintf(outfile, "%Zx\n", c);
    }

    mpz_clears(m, c, NULL);
    free(k_array);
}

void rsa_decrypt(mpz_t m, mpz_t c, mpz_t d, mpz_t n) {
    pow_mod(m, c, d, n);
}

// Cite: TA Erik
void rsa_decrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t d) {

    mpz_t m, c;
    size_t j = 0;

    mpz_inits(m, c, NULL);
    size_t k = (mpz_sizeinbase(n, 2) - 1) / 8;
    uint8_t *k_array = calloc(k, sizeof(uint8_t));

    while (feof(infile) == 0) {
        if (gmp_fscanf(infile, "%Zx\n", c) > 0) {
            rsa_decrypt(m, c, d, n);
        }

        mpz_export(k_array, &j, 1, sizeof(uint8_t), 1, 0, m);
        fwrite(k_array + 1, sizeof(uint8_t), j - 1, outfile);
    }

    mpz_clears(m, c, NULL);
    free(k_array);
}

void rsa_sign(mpz_t s, mpz_t m, mpz_t d, mpz_t n) {
    pow_mod(s, m, d, n);
}

bool rsa_verify(mpz_t m, mpz_t s, mpz_t e, mpz_t n) {
    mpz_t t;
    mpz_init(t);
    pow_mod(t, s, e, n);

    if (mpz_cmp(m, t) == 0) {
        mpz_clear(t);
        return true;
    }

    mpz_clear(t);
    return false;
}
