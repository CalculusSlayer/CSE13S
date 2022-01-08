#include "bv.h"
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <math.h>

struct BitVector {
    uint32_t length;
    uint8_t *vector;
};

BitVector *bv_create(uint32_t length) {
    BitVector *bv = (BitVector *) malloc(sizeof(BitVector));

    if (bv) {
        bv->length = length;
        bv->vector = (uint8_t *) calloc(ceil(length / 8.0), sizeof(uint8_t));
        if (!bv->vector) {
            free(bv);
            bv = NULL;
        }
    }

    return bv;
}

void bv_delete(BitVector **bv) {
    if (*bv && (*bv)->vector) {
        free((*bv)->vector);
        free(*bv);
        *bv = NULL;
    }

    return;
}

uint32_t bv_length(BitVector *bv) {
    return bv->length;
}

bool bv_set_bit(BitVector *bv, uint32_t i) {
    if (i < bv_length(bv)) {
        bv->vector[i / 8] |= 1 << (i % 8);
        return true;
    }

    return false;
}

bool bv_clr_bit(BitVector *bv, uint32_t i) {
    if (i < bv_length(bv)) {
        bv->vector[i / 8] &= ~(1 << (i % 8));
        return true;
    }

    return false;
}

// Recycled from my asgn 5
bool bv_get_bit(BitVector *bv, uint32_t i) {
    uint8_t some_vect = 0;

    if (i >= bv_length(bv)) {
        return false;
    }

    else {
        some_vect = 1 << (i % 8);
        some_vect &= bv->vector[i / 8];
        some_vect = some_vect >> (i % 8);

        if (some_vect == 1) {
            return true;
        }

        return false;
    }
}

void bv_print(BitVector *bv) {
    for (uint32_t i = 0; i < bv_length(bv); i++) {
        if (bv_get_bit(bv, i)) {
            printf("1 ");
        }

        else {
            printf("0 ");
        }
    }
    printf("\n");
}
