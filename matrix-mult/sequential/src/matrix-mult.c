#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUM 5

static long get_nanos(void) {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return (long) ts.tv_sec * 1000000000L + ts.tv_nsec;
}

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
    
    int start_t, end_t, total_t;
    
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
    
    start_t = get_nanos();
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            sum = 0;
            
            for (int k = 0; k < m; k++) {
                sum += A[i][k] * B[k][j];
            }
            
            C[i][j] = sum;
        }
    }
    
    end_t = get_nanos();
    
    total_t = end_t - start_t;
    
    /*printf("Matrix A: \n");
    printMatrix(A, m, n);
    
    printf("Matrix B: \n");
    printMatrix(B, m, n);
    
    printf("Result: \n");
    printMatrix(C, m, n);*/
    
    printf("Time elapsed: %ld\nns", (long) total_t);
}