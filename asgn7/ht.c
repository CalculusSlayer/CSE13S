#include "ht.h"
#include "salts.h"
#include "speck.h"
#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "bst.h"
#include <inttypes.h>

uint64_t lookups = 0;

struct HashTable {
    uint64_t salt[2];
    uint32_t size;
    Node **trees;
};

// Cite: TA Erik
HashTable *ht_create(uint32_t size) {
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
    ht->size = size;

    ht->salt[0] = SALT_HASHTABLE_LO;
    ht->salt[1] = SALT_HASHTABLE_HI;
    ht->trees = (Node **) calloc(size, sizeof(Node *));

    return ht;
}

// Cite: TA Erik
void ht_delete(HashTable **ht) {

    for (uint32_t i = 0; i < (*ht)->size; i++) {
        if ((*ht)->trees[i] != NULL) {
            bst_delete(&(*ht)->trees[i]);
        }
    }

    free((*ht)->trees);
    free(*ht);
    *ht = NULL;
}

uint32_t ht_size(HashTable *ht) {
    return ht->size;
}

// Cite: TA Erik
Node *ht_lookup(HashTable *ht, char *oldspeak) {
    lookups += 1;
    uint32_t index = hash(ht->salt, oldspeak) % ht->size;
    return bst_find(ht->trees[index], oldspeak);
}

// Cite: TA Erik
void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    lookups += 1;
    uint32_t index = hash(ht->salt, oldspeak) % ht->size;
    ht->trees[index] = bst_insert(ht->trees[index], oldspeak, newspeak);
}

// Cite: TA Erik
uint32_t ht_count(HashTable *ht) {
    uint32_t count = 0;

    for (uint32_t i = 0; i < ht->size; i++) {

        if (ht->trees[i] != NULL) {
            count += 1;
        }
    }

    return count;
}

// Cite: TA Erik
double ht_avg_bst_size(HashTable *ht) {
    double avgsize = 0;

    for (uint32_t i = 0; i < ht->size; i++) {
        avgsize += bst_size(ht->trees[i]);
    }

    return (double) avgsize / ht_count(ht);
}

// Cite: TA Erik
double ht_avg_bst_height(HashTable *ht) {
    double avgheight = 0;

    for (uint32_t i = 0; i < ht->size; i++) {
        avgheight += bst_height(ht->trees[i]);
    }

    return (double) avgheight / ht_count(ht);
}

void ht_print(HashTable *ht) {
    for (uint32_t i = 0; i < ht->size; i++) {
        printf("%d", (int) i);
    }
}
