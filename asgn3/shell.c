#include "shell.h"

#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void shell_sort(Stats *stats, uint32_t *A, uint32_t n) {
    int gap, i, j, k, temp;

    for (k = log(3 + 2 * n) / log(3); k > 0; k--) {
        gap = (pow(3, k) - 1) / 2;
        for (i = gap; (uint32_t) i < n; i++) {
            j = i;
            temp = move(stats, A[i]);
            while (j >= gap && cmp(stats, temp, A[j - gap]) == -1) {
                A[j] = move(stats, A[j - gap]);
                j -= gap;
            }
            A[j] = move(stats, temp);
        }
    }
}

/*
int main(void) {
	Stats stats;
	stats.moves = 0;
	stats.compares = 0;
	uint32_t list[] = {4, 3, 2, 1, 0, 1, 2};
	shell_sort(&stats, list, sizeof(list)/sizeof(list[0]));
	for (int count = 0; count < sizeof(list)/sizeof(list[0]); count++){
		printf("%" PRIu32 "\t", list[count]);}
		printf("moves = %" PRIu64 "\n", stats.moves);
		printf("compares = %" PRIu64 "\n", stats.compares);
	return 0;
}
*/
