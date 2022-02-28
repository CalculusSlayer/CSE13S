#include <stdio.h> // delete when done
#include <limits.h>
/*
 * All of your code goes in here. You need to finish these functions.
 */

int maximum(int *nums, int len) {
	int max = 0;
	for (int count = 0; count < len; count ++) {
		if (count == 0) {
			max = nums[count];
		}
		else if (nums[count] > max) {
			max = nums[count];
		}
	}

	return max;
}

int sum_positive(int *nums, int len) {
	int sum = 0;
	for (int count = 0; count < len; count++) {
		if (nums[count] > 0) {
			sum += nums[count];
		}
	}

 	return sum;
}


int my_sum(int x, int y) {
	return x + y;
}

int my_max(int x, int y) {
	if (x > y) {
		return x;
	}
	else {
		return y;
	}
}

int pos_sum(int x, int y) {
	if (y > 0) {
		return x + y;
	}
	else {
		return x;
	}
}

int neg_count(int x, int y) {
	if (y < 0) {
		x++;
	}
	return x;
		
}

int reduce(int *nums, int len, int (*f)(int,int), int initial){
  int val = initial;
  for (int count = 0; count < len; count++) {
	val = f(val, nums[count]);
  }	
  return val;
}

int maximum_with_reduce(int *nums, int size) {
  return reduce(nums, size, my_max, INT_MIN);
}

int sum_positive_with_reduce(int *nums, int size) {
  return reduce(nums, size, pos_sum, 0);
}

int count_negative_with_reduce(int *nums, int size) {
  return reduce(nums, size, neg_count, 0);
}

/*
int main(void) {
	int arr[] = {-1, -2, 3, 4};
	printf("maximum - %d\n", maximum(arr, 4));
	printf("sum_positive - %d\n", sum_positive(arr, 4));
	printf("reduce - %d\n", reduce(arr, 4, my_sum, 0));
	printf("max_w_reduce - %d\n", maximum_with_reduce(arr, 4));
	printf("pos_reduce_sum - %d\n", sum_positive_with_reduce(arr, 4));
	printf("count_negative_terms - %d\n", count_negative_with_reduce(arr, 4));
	printf("**********************\n");

	int arr2[] = {-4, -7, 42, -4, -99, 30};
	printf("%d\n", maximum(arr2, 6));
	printf("%d\n", sum_positive(arr2, 6));

	return 0;
}
*/

