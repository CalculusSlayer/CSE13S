#include "bst.h"
#include "node.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

uint64_t branches = 0;

// Cite: Slides 18 Page 55
static int max(int x, int y) {
    return x > y ? x : y;
}

// Cite: TA Erik
Node *bst_create(void) {
    return NULL;
}

// Cite: TA Erik
void bst_delete(Node **root) {

    if (*root != NULL) {

        if ((*root)->left != NULL) {
            bst_delete(&(*root)->left);
        }

        if ((*root)->right != NULL) {
            bst_delete(&(*root)->right);
        }

        node_delete(&(*root));
    }
}

// Cite: Slides 18 Page 55
uint32_t bst_height(Node *root) {
    if (root) {
        return max(bst_height(root->left), bst_height(root->right)) + 1;
    }

    return 0;
}

// Cite: TA Erik
uint32_t bst_size(Node *root) {
    if (root == NULL) {
        return 0;
    }

    return bst_size(root->left) + bst_size(root->right) + 1;
}

// Cite: TA Erik
Node *bst_find(Node *root, char *oldspeak) {
    Node *curr = root;

    if (root != NULL && oldspeak != NULL) {

        while (curr != NULL && strcmp(curr->oldspeak, oldspeak) != 0) {
            branches += 1;

            if (strcmp(curr->oldspeak, oldspeak) > 0) {
                curr = curr->left;
            }

            else {
                curr = curr->right;
            }
        }
    }

    return curr;
}
// Cite: TA Eugene
Node *bst_insert(Node *root, char *oldspeak, char *newspeak) {
    if (root == NULL) {
        return node_create(oldspeak, newspeak);
    }

    if (strcmp(root->oldspeak, oldspeak) > 0) {
        root->left = bst_insert(root->left, oldspeak, newspeak);
        branches += 1;
    }

    else if (strcmp(root->oldspeak, oldspeak) < 0) {
        root->right = bst_insert(root->right, oldspeak, newspeak);
        branches += 1;
    }

    return root;
}

void bst_print(Node *root) {
    if (root) {
        bst_print(root->left);
        node_print(root);
        bst_print(root->right);
    }
}
