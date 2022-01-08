#include "insert.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

void insertion_sort(Stats *stats, uint32_t *A, uint32_t n) {
    for (int i = 1, j, temp; (uint32_t) i < n; i++) {
        j = i;
        temp = move(stats, A[i]);
        while (j > 0 && cmp(stats, temp, A[j - 1]) == -1) {
            A[j] = move(stats, A[j - 1]);
            j -= 1;
        }
        A[j] = move(stats, temp);
    }
    return;
}

/*
int main(void) {
	Stats stats;
	stats.moves = 0;
	stats.compares = 0;

	uint32_t *list = (uint32_t *) calloc(100, sizeof(uint32_t));
	for (int count = 0; count < 100; count++){
		printf("%" PRIu32 "\t", list[count]);
	}
	uint32_t list2[] = {9, 4, 3, 1};
	insertion_sort(&stats, list2, sizeof(list2)/sizeof(list2[0]));
	for (int count = 0; count < 4; count++){
		printf("%" PRIu32 "\t", list2[count]);
	}
		printf("moves = %" PRIu64 "\t", stats.moves);
		printf("compares = %" PRIu64 "\n", stats.compares);
//		printf("%" PRIu64 "\t", list[count]);
//
	//free(list);
	return 0;

}
*/
