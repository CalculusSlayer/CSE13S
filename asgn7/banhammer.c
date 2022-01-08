#include "ht.h"
#include "bf.h"
#include "parser.h"
#include "messages.h"

#include <inttypes.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define OPTIONS     "ht:f:s"
#define REG_PATTERN "[A-Za-z0-9_]+(('|-)[A-Za-z0-9_]+)*" // Cite: TA Erik

int main(int argc, char **argv) {

    int opt = 0;
    bool no_input = true;
    bool h_flag = false;
    bool s_flag = false;

    uint32_t ht_size_set = 2 << 15; // Hash table is 2^16
    uint32_t bf_size_set = 2 << 19; // BLoom Filter size is 2^20

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        no_input = false;
        switch (opt) {

        case 'h': h_flag = true; break;

        case 's': s_flag = true; break;

        case 't': ht_size_set = atoi(optarg); break;

        case 'f': bf_size_set = atoi(optarg); break;
        }
    }

    if (h_flag == true) {
        printf("SYPNOSIS\n");
        printf("  A word filtering program for the GPRSC.\n");
        printf("  Filters out and reports bad words parsed from stdin.\n\n");
        printf("USAGE\n");
        printf("  ./banhammer [-hs] [-t size] [-f size]\n\n");
        printf("OPTIONS\n");
        printf("  -h     \tProgram usage and help.\n");
        printf("  -s     \tPrint program statistics.\n");
        printf("  -t size\tSpecify hash table size (default: 2^16).\n");
        printf("  -f size\tSpecify bloom filter size (default: 2^20.\n");
    }

    else {

        // Cite: TA Erik
        if (bf_size_set <= 0) {
            fprintf(stderr, "ERROR with bloom filter size.\n");
            exit(EXIT_FAILURE);
        }

        // Cite: TA Erik
        if (ht_size_set <= 0) {
            fprintf(stderr, "ERROR with hash table size.\n");
            exit(EXIT_FAILURE);
        }

        BloomFilter *bf = bf_create(bf_size_set);
        HashTable *ht = ht_create(ht_size_set);
        char badspeak[1024];

        FILE *badfile = fopen("badspeak.txt", "r");

        // Cite: TA Erik
        while (fscanf(badfile, "%s\n", badspeak) != EOF) {
            bf_insert(bf, badspeak);
            ht_insert(ht, badspeak, NULL);
        }

        fclose(badfile);

        FILE *oldfile = fopen("newspeak.txt", "r");
        char oldspeak[1024], newspeak[1024];

        // Cite: TA Erik
        while (fscanf(oldfile, "%s %s\n", oldspeak, newspeak) != EOF) {
            bf_insert(bf, oldspeak);
            ht_insert(ht, oldspeak, newspeak);
        }

        fclose(oldfile);

        // Cite: TA Erik
        regex_t reg;

        if (regcomp(&reg, REG_PATTERN, REG_EXTENDED)) {
            fprintf(stderr, "Error with reg!!!\n");
            exit(EXIT_FAILURE);
        }

        char *word = NULL;
        Node *mixedmsg = bst_create();
        Node *badmsg = bst_create();

        while ((word = next_word(stdin, &reg))) {
            for (char *pointer = word; *pointer != '\0'; pointer++) {
                *pointer = tolower(*pointer);
            }

            if (bf_probe(bf, word)) {
                Node *n = ht_lookup(ht, word);

                if (n != NULL && n->newspeak != NULL) {
                    mixedmsg = bst_insert(mixedmsg, n->oldspeak, n->newspeak);
                }

                else if (n != NULL && n->newspeak == NULL) {
                    badmsg = bst_insert(badmsg, n->oldspeak, n->newspeak);
                }
            }
        }

        if (s_flag) {
            fprintf(stdout, "Average BST size: %.6lf\n", (double) ht_avg_bst_size(ht));
            fprintf(stdout, "Average BST height: %.6lf\n", (double) ht_avg_bst_height(ht));
            fprintf(stdout, "Average branches traversed: %.6lf\n", (double) branches / lookups);
            fprintf(stdout, "Hash table load: %.6lf%c\n", (double) 100 * ht_count(ht) / ht_size(ht),
                37);
            fprintf(stdout, "Bloom filter load: %.6lf%c\n",
                (double) 100 * bf_count(bf) / bf_size(bf), 37);
        }

        else {

            if (bst_size(mixedmsg) > 0 && bst_size(badmsg) == 0) {
                printf("%s", goodspeak_message);
                bst_print(mixedmsg);
            }

            else if (bst_size(mixedmsg) > 0 && bst_size(badmsg) > 0) {
                printf("%s", mixspeak_message);
                bst_print(badmsg);
                bst_print(mixedmsg);
            }

            else if (bst_size(mixedmsg) == 0 && bst_size(badmsg) > 0) {
                printf("%s", badspeak_message);
                bst_print(badmsg);
            }
        }

        // Delete memory allocated for
        clear_words();
        regfree(&reg);
        bst_delete(&badmsg);
        bst_delete(&mixedmsg);
        bf_delete(&bf);
        ht_delete(&ht);
    }

    return 0;
}
