//Fellipe Jardanovski
//Felipe Jiao

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ROWS 3
#define COLS 3
#define THREADS 3

int matrix[ROWS][COLS] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};
int vector[COLS] = {1, 2, 3};
int result[ROWS];

typedef struct {
    int row;
} ThreadArgs;

// Função executada por cada thread
void *multiplyRow(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    int row = args->row;

    for (int j = 0; j < COLS; j++) {
        result[row] += matrix[row][j] * vector[j];
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[THREADS];
    ThreadArgs threadArgs[THREADS];

    // Inicializa as threads
    for (int i = 0; i < THREADS; i++) {
        threadArgs[i].row = i;
        pthread_create(&threads[i], NULL, multiplyRow, (void *)&threadArgs[i]);
    }

    // Aguarda as threads terminarem
    for (int i = 0; i < THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Imprime o resultado
    printf("Result:\n");
    for (int i = 0; i < ROWS; i++) {
        printf("%d\n", result[i]);
    }

    return 0;
}
