/*
 ============================================================================
 Name        : soma-seq.c
 Author      : Ronaldo Vieira
 Version     : 1.1.0
 Copyright   : MIT License
 Description : Soma sequencial de números de uma lista
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG 0
#define printflush(s, ...) do {if (DEBUG) {printf(s, ##__VA_ARGS__); fflush(stdout);}} while (0)

static long get_nanos(void) {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return (long) ts.tv_sec * 1000000000L + ts.tv_nsec;
}

int* get_random_nums(int amount) {
    int *rand_nums = (int *) malloc(sizeof(int) * amount);
    int i;

    for (i = 0; i < amount; i++) {
        rand_nums[i] = rand() % 10;
    }

    return rand_nums;
}

int main(int argc, char* argv[]) {
	srand(time(NULL));

	int i, sum = 0;
	int *rand_nums = NULL;
	long start, end, total;

	if (argc != 2) {
		printf("Usage: %s (size of array >= 2*p)\n", argv[0]);

		return -1;
	}

	int amount = atoi(argv[1]);

	if (amount < 0) {
		printf("Error: Size of array must be greater than zero.\n");

		return -1;
	}

	rand_nums = (int*) get_random_nums(amount);

	printflush("Created the array: [");
	for (i = 0; i < amount - 1; i++) {
		printflush("%d, ", rand_nums[i]);
	}
	printflush("%d]\n", rand_nums[amount - 1]);

	start = get_nanos();

	for (i = 0; i < amount; i++) {
		sum += rand_nums[i];
	}
	
	end = get_nanos();

	printflush("Sum is %d\n", sum);
	printf("Time elapsed: %ldns\n", end - start);

	return 0;
}