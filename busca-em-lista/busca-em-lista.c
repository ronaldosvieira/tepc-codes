#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"

int myrank=-1, p=0;

int * create_rand_nums(int num_elements, int myrank) {
    srand (time(NULL));
    int *rand_nums = (int *) malloc(sizeof(int) * num_elements);
    int i;
    for (i = 0; i < num_elements; i++) {
        rand_nums[i] =(rand() % 10) + myrank;
    }
    return rand_nums;
}

int main(int argc, char **argv){


    int i;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    int num_elements = atoi(argv[1]);
    int valor = atoi(argv[2]);
    MPI_Status status;

    int *rand_nums = NULL;

    // calcula o intervalo em que cada processo ira procurar
    // intervalo = [inicio, fim[
    int inicio = ((int) ((1.0 * num_elements / p) * myrank));
	int fim = ((int) ((1.0 * num_elements / p) * (myrank + 1)));

    if(myrank == 0){
        rand_nums = create_rand_nums(num_elements,myrank);

        for (i = 1; i < p; i++) {
            MPI_Send(rand_nums, num_elements, MPI_INT, i, 1, MPI_COMM_WORLD);
            printf("%d: Enviei para %d\n", myrank,i);
        }

    } else {
        rand_nums = (int *) malloc(sizeof(int) * num_elements);

        MPI_Recv(rand_nums, num_elements, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
        printf("%d: Recebi \n", myrank);
    }

    printf("%d: Vou pesquisar de %d a %d\n", myrank, inicio, fim - 1 );

    for (i = inicio; i < fim ; i++) {
        if (rand_nums[i] == valor){
            printf("%d: Achei\n", myrank);
        }
    }

    MPI_Finalize();

}
