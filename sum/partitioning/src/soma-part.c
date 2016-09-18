/*
 ============================================================================
 Name        : soma-part.c
 Author      : Ronaldo Vieira
 Version     : 1.0.1
 Copyright   : MIT License
 Description : Soma paralela de números de uma lista utilizando particionamento
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"

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

int main(int argc, char* argv[]){
	srand(time(NULL));

	int i;
	int sum, psum, global_sum;
	int *rand_nums = NULL; /* array of random numbers */
	int my_rank; /* rank of process */
	int p;       /* number of processes */
	MPI_Status status;   /* return status for receive */
	
	long start_t, end_t, total_t; /* time measure */
	
	/* start up MPI */
	MPI_Init(&argc, &argv);
	
	/* find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 
	
	/* find out number of processes */
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	if (argc != 2) {
		if (my_rank == 0)
			printf("Usage: %s (size of array >= 2*p)\n", argv[0]);

		MPI_Finalize();
		return -1;
	}

	int amount = atoi(argv[1]);

	if (amount < 0) {
		if (my_rank == 0)
			printf("Error: Size of array must be greater than zero.\n");

		MPI_Finalize();
		return -1;
	}

	/* find out which part of the array to sum */
	int start = ((int) ((1.0 * amount / p) * my_rank));
	int end = ((int) ((1.0 * amount / p) * (my_rank + 1)));
	
	printflush("%d: I'll sum from %d to %d\n", my_rank, start, end - 1);

	/* rank 0 creates and sends the array */
	if (my_rank == 0) {
		rand_nums = (int*) get_random_nums(amount);

		printflush("%d: Created the array: [", my_rank);
		for (i = 0; i < amount - 1; i++) {
			printflush("%d, ", rand_nums[i]);
		}
		printflush("%d]\n", rand_nums[amount - 1]);
		
		start_t = get_nanos();

        for (i = 1; i < p; i++) {
            MPI_Send(rand_nums, amount, MPI_INT, i, 0, MPI_COMM_WORLD);
            printflush("%d: Sent array to %d\n", my_rank, i);
        }
	/* other ranks receive the array from rank 0 */
	} else {
		rand_nums = (int *) malloc(sizeof(int) * amount);

		MPI_Recv(rand_nums, amount, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		printflush("%d: Received array from 0 \n", my_rank);
	}

	sum = 0;
	for (i = start; i < end ; i++) {
		sum += rand_nums[i];
	}

	printflush("%d: Finished\n", my_rank);

	/* rank 0 receives the sums */
	if (my_rank == 0) {
		global_sum = sum;

		for (i = 1; i < p; i++) {
			MPI_Recv(&psum, 1, MPI_INT, i, 1, MPI_COMM_WORLD, &status);
			global_sum += psum;

			printflush("%d: Received sum from %d\n", my_rank, i);
		}
		
		end_t = get_nanos();
		total_t = end_t - start_t;

		printflush("%d: End: Sum is %d\n", my_rank, global_sum);
		
		printf("%d: Total elapsed: %ldns\n", my_rank, total_t);
	/* other ranks send their sums to rank 0 */
	} else {
		MPI_Send(&sum, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
		printflush("%d: Sent sum to 0\n", my_rank);
	}

	free(rand_nums);

	/* shut down MPI */
	MPI_Finalize(); 
	
	return 0;
}
