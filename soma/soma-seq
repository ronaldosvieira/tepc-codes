/*
 ============================================================================
 Name        : soma-seq.c
 Author      : Ronaldo Vieira
 Version     : 1.0.0
 Copyright   : MIT License
 Description : Soma sequencial de números de uma lista
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG 1
#define printflush(s, ...) do {if (DEBUG) {printf(s, ##__VA_ARGS__); fflush(stdout);}} while (0)

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

	printf("Created the array: [");
	for (i = 0; i < amount - 1; i++) {
		printf("%d, ", rand_nums[i]);
	}
	printflush("%d]\n", rand_nums[amount - 1]);

	for (i = 0; i < amount; i++) {
		sum += rand_nums[i];
	}

	printflush("Sum is %d\n", sum);

	return 0;
}
