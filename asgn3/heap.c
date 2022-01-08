#include "heap.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static uint32_t great = 0;
static bool found = false;
static uint32_t mother = 0;
static uint32_t left = 0;
static uint32_t right = 0;

/*
void print_array(uint32_t *A, uint32_t size) {

	for (int count = 0; count < size; count++) {
		printf("%" PRIu32 "\t", A[count]);}	
}*/

uint32_t max_child(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    left = 2 * first;
    right = left + 1;
    if (right <= last && (cmp(stats, A[right - 1], A[left - 1]) == 1)) {
        return right;
    }
    return left;
}

void fix_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    found = false;
    mother = first;
    great = max_child(stats, A, mother, last);

    while (mother <= last / 2 && !(found)) {
        if (cmp(stats, A[mother - 1], A[great - 1]) == -1) {
            swap(stats, &A[mother - 1], &A[great - 1]);
            mother = great;
            great = max_child(stats, A, mother, last);
        } else {
            found = true;
        }
    }
}

void build_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    for (uint32_t track = last / 2; track > (first - 1); track--) {
        fix_heap(stats, A, track, last);
    }
}

void heap_sort(Stats *stats, uint32_t *A, uint32_t n) {
    build_heap(stats, A, (uint32_t) 1, n);
    for (uint32_t count = n; count > 1; count--) {
        swap(stats, &A[0], &A[count - 1]);
        //		print_array(A, n);
        fix_heap(stats, A, (uint32_t) 1, count - 1);
        //		print_array(A, n);
    }
}
/*
int main(void) {
	printf("hi\n");
	Stats stats;
	stats.moves = 0;
	stats.compares = 0;
	uint32_t list[] = {4,3,2,1,0,1};
	heap_sort(&stats, list, (uint32_t) sizeof(list)/sizeof(list[0]));
	for (int count = 0; count < sizeof(list)/sizeof(list[0]); count++) {
		printf("%" PRIu32 "\t", list[count]);}	
	printf("moves = %" PRIu64 "\n", stats.moves);
	printf("compares = %" PRIu64 "\n", stats.compares);
	printf("hi2\n");

		
}
*/
