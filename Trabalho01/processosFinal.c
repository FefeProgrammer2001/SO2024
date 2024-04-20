#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <fcntl.h>

#define MAX_PESSOAS 10000

//Fellipe Jardanovski
//Felipe Jiao

typedef struct {
    int chegada;
    int direcao;
} Pessoa;

// Variáveis globais para o estado da escada rolante
int *ultimoTempo;
int *direcaoAtual;

// Semáforo para controle de direção
sem_t *semaforo;

void usarEscada(Pessoa *p) {
    sem_wait(semaforo);  // Espera pelo semáforo para verificar a direção

    if (*direcaoAtual != p->direcao) {
        *direcaoAtual = p->direcao;
    }
    if (p->chegada > *ultimoTempo) {
        *ultimoTempo = p->chegada;
    }
    *ultimoTempo += 10; // Tempo para atravessar

    sem_post(semaforo);  // Libera o semáforo
}

int main() {
    FILE *arquivo;
    Pessoa pessoas[MAX_PESSOAS];
    int n, i;
    char filename[256];

    printf("Digite o nome do arquivo: "); // Lê o arquivo com as entradas
    scanf("%255s", filename);

    arquivo = fopen(filename, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    fscanf(arquivo, "%d", &n);
    for (i = 0; i < n; i++) {
        fscanf(arquivo, "%d %d", &pessoas[i].chegada, &pessoas[i].direcao);
    }
    fclose(arquivo);

    ultimoTempo = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    direcaoAtual = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *ultimoTempo = 0;
    *direcaoAtual = -1;

    semaforo = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    sem_init(semaforo, 1, 1);  // Compartilhamento entre os processos

    for (i = 0; i < n; i++) {
        if (fork() == 0) {
            usarEscada(&pessoas[i]);
            exit(0);
        }
    }

    for (i = 0; i < n; i++) {
        wait(NULL); // Espera todos os processos filhos terminarem
    }

    printf("Momento em que a última pessoa saiu da escada rolante: %d\n", *ultimoTempo);

    sem_destroy(semaforo);
    munmap(ultimoTempo, sizeof(int));
    munmap(direcaoAtual, sizeof(int));
    munmap(semaforo, sizeof(sem_t));

    return 0;
}
