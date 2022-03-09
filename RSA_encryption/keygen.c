#include "randstate.h"
#include "rsa.h"
#include "numtheory.h"
#include "gmp.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define OPTIONS "b:i:n:d:s:vh"

// Start of main function.
// Takes program arguments and process with getopt.

int main(int argc, char **argv) {

    bool h_flag = false;
    bool v_flag = false;

    char *pbname = "rsa.pub";
    char *pvname = "rsa.priv";

    uint64_t num_bits = 256;
    uint64_t iterations = 50;
    uint64_t seed = (uint64_t) time(NULL);

    int opt = 0;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {

        switch (opt) {

        case 'h': h_flag = true; break;

        case 'v': v_flag = true; break;

        case 'n': pbname = optarg; break;

        case 'd': pvname = optarg; break;

        case 'b': num_bits = (uint64_t) atoi(optarg); break;

        case 'i': iterations = (uint64_t) atoi(optarg); break;

        case 's': seed = (uint64_t) atoi(optarg); break;
        }
    }

    // Standard Error Message if h flag is raised
    if (h_flag == true) {
        printf("SYNOPSIS\n");
        printf("  Generates an RSA public/private key pair.\n");
        printf("\n");
        printf("USAGE\n");
        printf("  ./keygen [-hv] [-b bits] -n pbfile -d pvfile\n");
        printf("\n");
        printf("OPTIONS\n");
        printf("  -h             Display program help and usage.\n");
        printf("  -v             Display verbose program output.\n");
        printf("  -b bits        Minimum bits needed for public key n (default: 256).\n");
        printf("  -i confidence  Miller-Rabin iterations for testings primes (default: 50).\n");
        printf("  -n pbfile      Public key file (default: rsa.pub).\n");
        printf("  -d pvfile      Private key file (default: rsa.priv).\n");
        printf("  -s seed        Random seed for testing.\n");
    }

    else {
        // Cite: TA Erik
        FILE *pbfile = fopen(pbname, "w");
        if (pbfile == NULL) {
            fprintf(stderr, "Error with the public file.\n");
            exit(EXIT_FAILURE);
        }

        FILE *pvfile = fopen(pvname, "w");
        if (pvfile == NULL) {
            fprintf(stderr, "Error with the private file.\n");
            exit(EXIT_FAILURE);
        }

        // Cite: TA Erik
        fchmod(fileno(pvfile), 0600);
        randstate_init(seed);

        mpz_t s, p, q, n, e, d;
        mpz_inits(s, p, q, n, e, d, NULL);

        rsa_make_pub(p, q, n, e, num_bits, iterations);
        rsa_make_priv(d, e, p, q);

        char *username = getenv("USER");
        mpz_set_str(s, username, 62);
        rsa_sign(s, s, d, n);

        rsa_write_pub(n, e, s, username, pbfile);
        rsa_write_priv(n, d, pvfile);

        if (v_flag) {
            printf("user = %s\n", username);
            printf("s (%zu bits) = ", mpz_sizeinbase(s, 2));
            gmp_printf("%Zd\n", s);
            printf("p (%zu bits) = ", mpz_sizeinbase(p, 2));
            gmp_printf("%Zd\n", p);
            printf("q (%zu bits) = ", mpz_sizeinbase(q, 2));
            gmp_printf("%Zd\n", q);
            printf("n (%zu bits) = ", mpz_sizeinbase(n, 2));
            gmp_printf("%Zd\n", n);
            printf("e (%zu bits) = ", mpz_sizeinbase(e, 2));
            gmp_printf("%Zd\n", e);
            printf("d (%zu bits) = ", mpz_sizeinbase(d, 2));
            gmp_printf("%Zd\n", d);
        }

        fclose(pbfile);
        fclose(pvfile);
        mpz_clears(s, p, q, n, e, d, NULL);
    }

    return 0;
}
