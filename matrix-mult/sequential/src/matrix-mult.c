#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define MAX_NUM 5

int** initMatrix(int m, int n) {
    int** mat = (int**) malloc(sizeof(int*) * m);
    
    for (int i = 0; i < m; i++) {
        mat[i] = (int*) malloc(sizeof(int) * n);
    }
    
    return mat;
}

int** generateRandomMatrix(int** mat, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            mat[i][j] = rand() % MAX_NUM;
        }
    }
    
    return mat;
}

void printMatrix(int** mat, int m, int n) {
    printf("[");
    
    for (int i = 0; i < m; i++) {
        printf(" ");
        
        for (int j = 0; j < n; j++) {
            printf("%d ", mat[i][j]);
        }
        
        if (i != m - 1) printf("\n");
    }
    
    printf("]\n");
}

int main(int argc, char **argv) {
    srand(time(NULL));
    
    int **A, **B, **C;
    int m, n;
    int sum;
    
    struct timeval start_t, end_t;
    double total_t;
    
    if (argv[1] == NULL || argv[2] == NULL || 
        atoi(argv[1]) < 1 || atoi(argv[2]) < 1) {
        printf("Modo de usar: %s (m > 0) (n > 0)\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    m = atoi(argv[1]);
    n = atoi(argv[2]);
    
    A = initMatrix(m, n);
    B = initMatrix(m, n);
    C = initMatrix(m, n);
    
    generateRandomMatrix(A, m, n);
    generateRandomMatrix(B, m, n);
    
    gettimeofday(&start_t, NULL);
    
    int i, j, k;
    
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            for (k = 0; k < m; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    
    gettimeofday(&end_t, NULL);
    
    total_t = ((end_t.tv_sec  - start_t.tv_sec) * 1000000u + 
         end_t.tv_usec - start_t.tv_usec) / 1.e6;

    /*printf("Matrix A: \n");
    printMatrix(A, m, n);
    
    printf("Matrix B: \n");
    printMatrix(B, m, n);
    
    printf("Result: \n");
    printMatrix(C, m, n);*/
    
    printf("Time elapsed: %lfs\n", total_t);
}