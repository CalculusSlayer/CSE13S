#include "quick.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

//int partition(Stats *stats, uint32_t *A, uint32_t lo, uint32_t hi);

//void quick_sorter(Stats *stats, uint32_t *A, uint32_t lo, uint32_t hi);

//static uint32_t p;
//static uint32_t i;

int partition(Stats *stats, uint32_t *A, uint32_t lo, uint32_t hi) {
    uint32_t i = lo - 1;
    for (uint32_t j = lo; j < hi; j++) {
        if (cmp(stats, A[j - 1], A[hi - 1]) == -1) {
            i += 1;
            swap(stats, &A[i - 1], &A[j - 1]); // check here
        }
    }
    swap(stats, &A[i], &A[hi - 1]);
    return i + 1;
}

void quick_sorter(Stats *stats, uint32_t *A, uint32_t lo, uint32_t hi) {
    if (lo < hi) {
        uint32_t p = partition(stats, A, lo, hi);
        quick_sorter(stats, A, lo, p - 1);
        quick_sorter(stats, A, p + 1, hi);
    }
}

void quick_sort(Stats *stats, uint32_t *A, uint32_t n) {
    quick_sorter(stats, A, 1, n);
}

/*
int main(void) {
	Stats stats;
	stats.moves = 0;
	stats.compares = 0;
	uint32_t list[] = {4,3,2,1,0,1};
	quick_sort(&stats, list, sizeof(list)/sizeof(list[0]));
	for (int count = 0; count < sizeof(list)/sizeof(list[0]); count++) {
		printf("%" PRIu32 "\t", list[count]);}	
	printf("moves = %" PRIu64 "\n", stats.moves);
	printf("compares = %" PRIu64 "\n", stats.compares);

		
}
*/
