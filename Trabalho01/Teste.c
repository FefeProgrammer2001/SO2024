#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_USERS 10000

pthread_mutex_t lock;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int currentTime = 0;
int currentDirection = -1; // -1 indica que a escada não está se movendo

typedef struct {
    int arrivalTime;
    int direction; // 0 = esquerda para direita, 1 = direita para esquerda
} User;

User users[MAX_USERS];
int nUsers = 0;

void* simulateUser(void* arg) {
    User* user = (User*) arg;
    
    pthread_mutex_lock(&lock);
    
    while (currentDirection != -1 && currentDirection != user->direction) {
        pthread_cond_wait(&cond, &lock);
    }
    
    if (currentDirection == -1 || currentTime < user->arrivalTime) {
        currentTime = user->arrivalTime;
    }
    
    currentDirection = user->direction;
    
    currentTime += 10;
    
    if ((nUsers - 1 == user->arrivalTime) || (user->arrivalTime + 1 < nUsers && users[user->arrivalTime + 1].direction != user->direction)) {
        currentDirection = -1;
        pthread_cond_broadcast(&cond);
    }
    
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    char filename[100];
    printf("Digite o nome do arquivo com os exemplos de entrada: ");
    scanf("%s", filename);

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    fscanf(file, "%d", &nUsers);
    for (int i = 0; i < nUsers; i++) {
        fscanf(file, "%d %d", &users[i].arrivalTime, &users[i].direction);
    }
    fclose(file);

    pthread_mutex_init(&lock, NULL);
    pthread_t threads[nUsers];

    // Cria uma thread para cada usuário
    for (int i = 0; i < nUsers; i++) {
        pthread_create(&threads[i], NULL, simulateUser, (void*) &users[i]);
    }

    // Espera todas as threads terminarem
    for (int i = 0; i < nUsers; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);

    printf("O último momento em que a escada para: %d\n", currentTime);
    return 0;
}
