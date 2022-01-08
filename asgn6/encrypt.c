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
#define OPTIONS "i:o:n:vh"

// Start of main function.
// Takes program arguments and process with getopt.
int main(int argc, char **argv) {

    bool h_flag = false;
    bool v_flag = false;
    bool i_flag = false;
    bool o_flag = false;

    char *pbname = "rsa.pub";
    FILE *infile = stdin;
    FILE *outfile = stdout;
    char *infile_name = NULL;
    char *outfile_name = NULL;

    int opt = 0;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {

        switch (opt) {

        case 'h': h_flag = true; break;

        case 'v': v_flag = true; break;

        case 'n': pbname = optarg; break;

        case 'i':
            infile_name = optarg;
            i_flag = true;
            break;

        case 'o':
            outfile_name = optarg;
            o_flag = true;
            break;
        }
    }

    // Standard Error Message if h flag is raised
    if (h_flag == true) {
        printf("SYNOPSIS\n");
        printf("  Encrypts data using RSA encryption.\n");
        printf("  Encrypted data is decrypted by the decrypt program.\n");
        printf("\n");
        printf("USAGE\n");
        printf("  ./encrypt [-hv] [-i infile] [-o outfile] -n pubkey\n");
        printf("\n");
        printf("OPTIONS\n");
        printf("  -h             Display program help and usage.\n");
        printf("  -v             Display verbose program output.\n");
        printf("  -i infile      Input file of data to encrypt (default: stdin).\n");
        printf("  -o outfile     Output file for encrypted data (default: stdout).\n");
        printf("  -n pbfile      Public key file (default: rsa.pub).\n");
    }

    else {

        FILE *pbfile = fopen(pbname, "r");
        if (pbfile == NULL) {
            fprintf(stderr, "Error with the public file.\n");
            exit(EXIT_FAILURE);
        }

        char *user = malloc(100); // Remember to free the memory allocated here.

        mpz_t n, e, s, m;
        mpz_inits(n, e, s, m, NULL);

        rsa_read_pub(n, e, s, user, pbfile);

        if (v_flag) {
            printf("user = %s\n", user);
            printf("s (%zu bits) = ", mpz_sizeinbase(s, 2));
            gmp_printf("%Zd\n", s);
            printf("n (%zu bits) = ", mpz_sizeinbase(n, 2));
            gmp_printf("%Zd\n", n);
            printf("e (%zu bits) = ", mpz_sizeinbase(e, 2));
            gmp_printf("%Zd\n", e);
        }

        if (i_flag) {
            infile = fopen(infile_name, "r");
            if (infile == NULL) {
                fprintf(stderr, "Error with the infile.\n");
                exit(EXIT_FAILURE);
            }
        }

        if (o_flag) {
            outfile = fopen(outfile_name, "w");

            if (outfile == NULL) {
                fprintf(stderr, "Error with the outfile.\n");
                exit(EXIT_FAILURE);
            }
        }

        mpz_set_str(m, user, 62);
        if (!rsa_verify(m, s, e, n)) {
            fprintf(stderr, "Could not verify signature.\n");
            exit(EXIT_FAILURE);
        }

        rsa_encrypt_file(infile, outfile, n, e);

        free(user);
        fclose(pbfile);
        fclose(infile);
        fclose(outfile);
        mpz_clears(n, e, s, m, NULL);
    }

    return 0;
}
