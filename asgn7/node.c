#include "node.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Cite: TA Erik
Node *node_create(char *oldspeak, char *newspeak) {
    Node *n = (Node *) calloc(1, sizeof(Node));
    if (n) {
        if (oldspeak == NULL) {
            n->oldspeak = NULL;
        }

        else {
            n->oldspeak = strdup(oldspeak);
        }

        if (newspeak == NULL) {
            n->newspeak = NULL;
        }

        else {
            n->newspeak = strdup(newspeak);
        }

        n->left = NULL;
        n->right = NULL;
    }

    return n;
}

void node_delete(Node **n) {
    if (*n) {
        free((*n)->oldspeak);
        (*n)->oldspeak = NULL;
        free((*n)->newspeak);
        (*n)->newspeak = NULL;
        free(*n);
        *n = NULL;
    }
    return;
}

void node_print(Node *n) {
    if (n->oldspeak && n->newspeak) {
        printf("%s -> %s\n", n->oldspeak, n->newspeak);
        return;
    }

    if (n->oldspeak) {
        printf("%s\n", n->oldspeak);
        return;
    }
}
