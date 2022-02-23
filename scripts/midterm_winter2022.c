#include "midterm.c"	// Copy entire midterm.c file.
						// Make sure main function is 
						// gone in the midterm.c file.

/* Function pointer used
by the linked list mapping
function */

float quadratic(float x) {
	return x * x + 1;
}

/* Function used to free memory
allocated for the linked list */

void delete_link(LLfloat **x) {
	if ((*x) == NULL) {
		free(*x);
	}

	else {
		delete_link(&((*x)->next));
		free(*x);
	}
}

// Test Cases for the Midterm
int main(void) {
	printf("\n ******TESTING #1********* \n\n");
	
	printf("Array of length 1 [1]:\n");
	long long *f1 = fibonacci_numbers(1);
	for (int i = 0; i < 1; i++) {
		printf("%lld ", f1[i]);
	}
	printf("\n\n");
	
	free(f1);

	printf("Array of length 2 [1,1]:\n");
	long long *f2 = fibonacci_numbers(2);
	for (int i = 0; i < 2; i++) {
		printf("%lld ", f2[i]);
	}
	printf("\n\n");
	
	free(f2);

	printf("Array of length 8 [1,1,2,3,5,8,13,21]:\n");
	long long *f8 = fibonacci_numbers(8);
	for (int i = 0; i < 8; i++) {
		printf("%lld ", f8[i]);
	}
	printf("\n\n");

	free(f8);
	
	printf("****** TESTING #2 ******\n");

	ShoeCustomer c1 = {.shoe_size = 10, .customer_id = 1, .num_purchases = 40};
	ShoeCustomer c2 = {.shoe_size = 4, .customer_id = 2, .num_purchases = 20};
	ShoeCustomer c3 = {.shoe_size = 7, .customer_id = 3, .num_purchases = 4};
	ShoeCustomer c4 = {.shoe_size = 16, .customer_id = 4, .num_purchases = 2};
	ShoeCustomer c5 = {.shoe_size = 2, .customer_id = 5, .num_purchases = 40};
	
	ShoeCustomer *customer_arr = malloc(sizeof(ShoeCustomer) * 5);
	*(customer_arr) = c1;
	*(customer_arr + 1) = c2;
	*(customer_arr + 2) = c3;
	*(customer_arr + 3) = c4;
	*(customer_arr + 4) = c5;
	
	printf("Unsorted customer array:\n");
	for (ShoeCustomer *p = customer_arr; p < customer_arr + 5; p++) {
		printf("%d %d %d\n", p->shoe_size, p->customer_id, p->num_purchases);
	}
	printf("\n");

	bubble_sort_customers(customer_arr, 5);
	printf("Array after bubble sort:\n");
	for (ShoeCustomer *p = customer_arr; p < customer_arr + 5; p++) {
		printf("%d %d %d\n", p->shoe_size, p->customer_id, p->num_purchases);
	}

	free(customer_arr);

	printf(" \n****TESTING #3****** \n\n");
	LLfloat *a0 = malloc(sizeof(LLfloat));
	LLfloat *a1 = malloc(sizeof(LLfloat));
	LLfloat *a2 = malloc(sizeof(LLfloat));
	LLfloat *a3 = malloc(sizeof(LLfloat));
	LLfloat *a4 = malloc(sizeof(LLfloat));
	LLfloat *a5 = malloc(sizeof(LLfloat));

	a0->val = 0;
	a1->val = 1;
	a2->val = 2;
	a3->val = 3;
	a4->val = 10;
	a5->val = 12;	

	a0->next = a1;
	a1->next = a2;
	a2->next = a3;
	a3->next = a4;
	a4->next = a5;
	a5->next = NULL;

	LLfloat *a_pointer = a0;
	printf("Original array:\n");
	while ( a_pointer != NULL ) {
		printf("%f ", a_pointer->val);
		a_pointer = a_pointer->next;
	}
	printf("\n\n");
	
	a_pointer = a0;	
	LLfloat *new_a = map_floats(quadratic, a_pointer); // Quadratic is a function defined as f(x) = x^2 + 1
	a_pointer = new_a;
	printf("Squared array:\n");
	while ( a_pointer != NULL ) {
		printf("%f ", a_pointer->val);
		a_pointer = a_pointer->next;
	}
	printf("\n");
	
	a_pointer = a0;
	printf("\nOriginal array not modified?\n");
	while ( a_pointer != NULL ) {
		printf("%f ", a_pointer->val);
		a_pointer = a_pointer->next;
	}
	printf("\n");

	delete_link(&a0);	
	delete_link(&new_a);

	printf("\n******* TESTING #4 **********\n");

	unsigned long sol4 = 10403319 & 20392939 & 99929293939;
	unsigned long calendars4[] = {10403319, 20392939, 99929293939};

	printf("Student answer: %lu\n", compute_availability(calendars4, 3));
	printf("Expected answer: %lu\n", sol4);


	return 0;
}

