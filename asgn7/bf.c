#include "bf.h"
#include "salts.h"
#include "inttypes.h"
#include "bv.h"
#include "speck.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct BloomFilter {
    uint64_t primary[2];
    uint64_t secondary[2];
    uint64_t tertiary[2];
    BitVector *filter;
};

// Cite: TA Erik
BloomFilter *bf_create(uint32_t size) {
    BloomFilter *bf = (BloomFilter *) malloc(sizeof(BloomFilter));

    bf->primary[0] = SALT_PRIMARY_LO;
    bf->primary[1] = SALT_PRIMARY_HI;
    bf->secondary[0] = SALT_SECONDARY_LO;
    bf->secondary[1] = SALT_SECONDARY_HI;
    bf->tertiary[0] = SALT_TERTIARY_LO;
    bf->tertiary[1] = SALT_TERTIARY_HI;

    bf->filter = bv_create(size);
    return bf;
}

// Cite: TA Erik
void bf_delete(BloomFilter **bf) {
    bv_delete(&(*bf)->filter);
    free(*bf);
    *bf = NULL;
}

uint32_t bf_size(BloomFilter *bf) {
    return bv_length(bf->filter);
}

// Cite: TA Erik
void bf_insert(BloomFilter *bf, char *oldspeak) {
    bv_set_bit(bf->filter, hash(bf->primary, oldspeak) % bf_size(bf));
    bv_set_bit(bf->filter, hash(bf->secondary, oldspeak) % bf_size(bf));
    bv_set_bit(bf->filter, hash(bf->tertiary, oldspeak) % bf_size(bf));
}

// Cite: TA Erik
bool bf_probe(BloomFilter *bf, char *oldspeak) {
    return bv_get_bit(bf->filter, hash(bf->primary, oldspeak) % bf_size(bf))
           & bv_get_bit(bf->filter, hash(bf->secondary, oldspeak) % bf_size(bf))
           & bv_get_bit(bf->filter, hash(bf->tertiary, oldspeak) % bf_size(bf));
}

// Cite: TA Erik
uint32_t bf_count(BloomFilter *bf) {
    uint32_t count = 0;

    for (uint32_t i = 0; i < bv_length(bf->filter); i++) {
        count += bv_get_bit(bf->filter, i);
    }

    return count;
}

void bf_print(BloomFilter *bf) {
    for (uint32_t i = 0; i < bf_size(bf); i++) {
        if (bv_get_bit(bf->filter, i)) {
            printf("1 ");
        } else
            printf("0 ");
    }
}
