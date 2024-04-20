#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

//Fellipe Jardanovski
//Felipe Jiao

typedef struct { //Estrutura que define como será armazenado as pessoas que vão acessar a escada
    int chegada;
    int direcao;
} Pessoa;

int ultimoTempo = 0;
int direcaoAtual = -1;
pthread_mutex_t lock;
sem_t semEscada;

Pessoa *fila0, *fila1;
int inicio0 = 0, fim0 = 0, inicio1 = 0, fim1 = 0;

void *usarEscada(void *arg) {
    Pessoa *p = (Pessoa *)arg;

    pthread_mutex_lock(&lock);
    if (p->direcao == 0) {
        fila0[fim0++] = *p;
    } else {
        fila1[fim1++] = *p;
    }
    pthread_mutex_unlock(&lock);
    
    sem_wait(&semEscada); // Espera pela escada se necessário

    pthread_mutex_lock(&lock);
    if (p->direcao == direcaoAtual || direcaoAtual == -1) {
        ultimoTempo = p->chegada > ultimoTempo ? p->chegada : ultimoTempo;
        ultimoTempo += 10; // Soma ao tempo final
        direcaoAtual = p->direcao;
    }
    pthread_mutex_unlock(&lock);

    sem_post(&semEscada); // Libera a escada para a próxima pessoa ou mudança de direção
    pthread_exit(NULL);
}

int main() {
    FILE *arquivo;
    Pessoa *pessoas;
    int n, i;
    char nomeArquivo[256];

    printf("Digite o nome do arquivo: ");
    scanf("%255s", nomeArquivo);

    arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }

    fscanf(arquivo, "%d", &n);
    pessoas = (Pessoa *)malloc(n * sizeof(Pessoa));
    fila0 = (Pessoa *)malloc(n * sizeof(Pessoa));
    fila1 = (Pessoa *)malloc(n * sizeof(Pessoa));

    for (i = 0; i < n; i++) {
        fscanf(arquivo, "%d %d", &pessoas[i].chegada, &pessoas[i].direcao);
    }

    fclose(arquivo);

    pthread_t threads[n];
    pthread_mutex_init(&lock, NULL);
    sem_init(&semEscada, 0, 1); // Inicializa o semáforo permitindo 1 acesso por vez

    for (i = 0; i < n; i++) {
        pthread_create(&threads[i], NULL, usarEscada, (void *)&pessoas[i]);
    }

    for (i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Momento em que a última pessoa saiu da escada rolante: %d\n", ultimoTempo);

    free(pessoas);
    free(fila0);
    free(fila1);
    pthread_mutex_destroy(&lock);
    sem_destroy(&semEscada);
    return 0;
}

