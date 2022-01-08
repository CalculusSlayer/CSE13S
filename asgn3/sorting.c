#include "heap.h"
#include "insert.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stats.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define OPTIONS "aeisqr:n:p:h"
typedef enum { HEAP, INSERTION, SHELL, QUICK, SEED, SIZE, ELEMENTS, HELP } Algs;
//const char *names[] = {"
void randomize_array(uint32_t *A, uint32_t size_of_array, uint32_t seed) {
    srand(seed);
    for (uint32_t count = 0; count < size_of_array; count++) {
        A[count] = random() & 0x3FFFFFFF;
    }
}
void print_array(uint32_t *A, uint32_t size_of_array, uint32_t elements) {
    uint32_t heap_count;
    for (heap_count = 0; heap_count < ((elements <= size_of_array) ? elements : size_of_array);
         heap_count++) {
        printf("%13" PRIu32, A[heap_count]);
        if ((heap_count + 1) % 5 == 0) {
            printf("\n");
        }
    }
    if (heap_count % 5 != 0) {
        printf("\n");
    }
}
int main(int argc, char **argv) {
    int opt = 0;
    Set flags = empty_set();
    uint32_t seed = 13371453;
    uint32_t size_of_array = 100;
    uint32_t elements = 100;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            flags = insert_set(HEAP, flags);
            flags = insert_set(INSERTION, flags);
            flags = insert_set(SHELL, flags);
            flags = insert_set(QUICK, flags);
            break;
        case 'e': flags = insert_set(HEAP, flags); break;
        case 'i': flags = insert_set(INSERTION, flags); break;
        case 's': flags = insert_set(SHELL, flags); break;
        case 'q': flags = insert_set(QUICK, flags); break;
        case 'r':
            //printf("%s\n", optarg);
            flags = insert_set(SEED, flags);
            seed = (uint32_t) strtoul(optarg, NULL, 10);
            //printf("%" PRIu32 "\n", seed);
            break;
        case 'n':
            flags = insert_set(SIZE, flags);
            size_of_array = (uint32_t) strtoul(optarg, NULL, 10);
            //printf("%u\n", size_of_array);
            break;
        case 'p':
            flags = insert_set(ELEMENTS, flags);
            elements = (uint32_t) strtoul(optarg, NULL, 10);
            //printf("%u\n", elements);
            break;
        case 'h': flags = insert_set(HELP, flags); break;
        }
    }
    Stats stats;
    stats.moves = 0;
    stats.compares = 0;
    uint32_t *A = (uint32_t *) calloc(size_of_array, sizeof(uint32_t));
    if (member_set(HEAP, flags)) {
        reset(&stats);
        randomize_array(A, size_of_array, seed);
        heap_sort(&stats, A, size_of_array);
        printf("Heap Sort, %" PRIu32 " elements, %" PRIu64 " moves, %" PRIu64 " compares\n",
            size_of_array, stats.moves, stats.compares);
        print_array(A, size_of_array, elements);
    }
    if (member_set(INSERTION, flags)) {
        reset(&stats);
        randomize_array(A, size_of_array, seed);
        insertion_sort(&stats, A, size_of_array);
        printf("Insertion Sort, %" PRIu32 " elements, %" PRIu64 " moves, %" PRIu64 " compares\n",
            size_of_array, stats.moves, stats.compares);
        print_array(A, size_of_array, elements);
    }
    if (member_set(QUICK, flags)) {
        reset(&stats);
        randomize_array(A, size_of_array, seed);
        quick_sort(&stats, A, size_of_array);
        printf("Quick Sort, %" PRIu32 " elements, %" PRIu64 " moves, %" PRIu64 " compares\n",
            size_of_array, stats.moves, stats.compares);
        print_array(A, size_of_array, elements);
    }
    if (member_set(SHELL, flags)) {
        reset(&stats);
        randomize_array(A, size_of_array, seed);
        shell_sort(&stats, A, size_of_array);
        printf("Shell Sort, %" PRIu32 " elements, %" PRIu64 " moves, %" PRIu64 " compares\n",
            size_of_array, stats.moves, stats.compares);
        print_array(A, size_of_array, elements);
    }
    if (member_set(HELP, flags)) {
        printf("SYNOPSIS\n");
        printf("\tA collection of comparision-based sorting algorithms.\n");
        printf("\nUSAGE\n\t./sorting [-haeisqn:p:r:] [-n length] [-p elements] [-r seed]\n\n");
        printf("OPTIONS\n");
        printf("\t%-15s display program help and usage.\n", "-h");
        printf("\t%-15s enable all sorts.\n", "-a");
        printf("\t%-15s enable Heap Sort.\n", "-e");
        printf("\t%-15s enable Insertion Sort.\n", "-i");
        printf("\t%-15s enable Shell Sort.\n", "-s");
        printf("\t%-15s enable Quick Sort.\n", "-q");
        printf("\t%-15s specify number of array elements (default: 100).\n", "-n length");
        printf("\t%-15s specify number of elements to print (default: 100).\n", "-p elements");
        printf("\t%-15s specify random seed (default: 13371453).\n", "-r seed");
    }
    /*
    Stats stats;
    stats.moves = 0;
    stats.compares = 0;
    uint32_t list1[] = { 4, 5, 1, 0, 4, 2, 40, 100, 999, 400, 99999, 5000, 4999 };
    //	uint32_t list2[] = { 4, 5, 1, 0, 4, 2, 40, 100, 999, 400, 99999, 5000, 4999 };
    //	uint32_t list3[] = { 4, 5, 1, 0, 4, 2, 40, 100, 999, 400, 99999, 5000, 4999 };
    insertion_sort(&stats, list1, sizeof(list1) / sizeof(list1[0]));
    print_array(list1, sizeof(list1) / sizeof(list1[0]));
    printf("moves = %" PRIu64 "\n", stats.moves);
    printf("compares = %" PRIu64 "\n", stats.compares);
    */

    free(A);
    return 0;
}
