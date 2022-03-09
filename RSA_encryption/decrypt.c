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

    char *pvname = "rsa.priv";
    FILE *infile = stdin;
    FILE *outfile = stdout;
    char *infile_name = NULL;
    char *outfile_name = NULL;

    int opt = 0;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {

        switch (opt) {

        case 'h': h_flag = true; break;

        case 'v': v_flag = true; break;

        case 'n': pvname = optarg; break;

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
        printf("  Decrypts data using RSA decryption.\n");
        printf("  Decrypted data is encrypted by the encrypt program.\n");
        printf("\n");
        printf("USAGE\n");
        printf("  ./decrypt [-hv] [-i infile] [-o outfile] -n privkey\n");
        printf("\n");
        printf("OPTIONS\n");
        printf("  -h             Display program help and usage.\n");
        printf("  -v             Display verbose program output.\n");
        printf("  -i infile      Input file of data to decrypt (default: stdin).\n");
        printf("  -o outfile     Output file for decrypted data (default: stdout).\n");
        printf("  -n pvfile      Private key file (default: rsa.priv).\n");
    }

    else {
        FILE *pvfile = fopen(pvname, "r");
        if (pvfile == NULL) {
            fprintf(stderr, "Error with the private file.\n");
            exit(EXIT_FAILURE);
        }

        mpz_t n, d;
        mpz_inits(n, d, NULL);

        rsa_read_priv(n, d, pvfile);

        if (v_flag) {
            printf("n (%zu bits) = ", mpz_sizeinbase(n, 2));
            gmp_printf("%Zd\n", n);
            printf("d (%zu bits) = ", mpz_sizeinbase(d, 2));
            gmp_printf("%Zd\n", d);
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

        rsa_decrypt_file(infile, outfile, n, d);

        fclose(pvfile);
        fclose(infile);
        fclose(outfile);
        mpz_clears(n, d, NULL);
    }

    return 0;
}
