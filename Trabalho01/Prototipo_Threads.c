#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Estrutura para armazenar dados de uma pessoa
typedef struct {
    int chegada;
    int direcao;
} Pessoa;

// Variáveis globais para o estado da escada rolante
int ultimoTempo = 0;
int direcaoAtual = -1; // -1 significa parada, 0 esquerda para direita, 1 direita para esquerda
pthread_mutex_t lock;

// Função para simular o uso da escada rolante por uma pessoa
void *usarEscada(void *arg) {
    Pessoa *p = (Pessoa *)arg;
    
    pthread_mutex_lock(&lock);
    // Verifica se precisa esperar mudar a direção
    if (direcaoAtual != -1 && direcaoAtual != p->direcao) {
        p->direcao = ultimoTempo + 1;
        ultimoTempo += 10 ;
        pthread_exit(NULL);
    }
    direcaoAtual = p->direcao;
    if (p->chegada < ultimoTempo) {
        ultimoTempo = p->chegada;
        ultimoTempo += 10; // Tempo para atravessar
    }
    

    if (p->chegada > ultimoTempo) {
        ultimoTempo = p->chegada;
        ultimoTempo += 10 ;
    }
    pthread_mutex_unlock(&lock);
    
    pthread_exit(NULL);
}

int main() {
    FILE *arquivo;
    Pessoa *pessoas;
    int n, i;
    
    arquivo = fopen("E_1", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }
    
    fscanf(arquivo, "%d", &n);
    pessoas = (Pessoa *)malloc(n * sizeof(Pessoa));
    
    for (i = 0; i < n; i++) {
        fscanf(arquivo, "%d %d", &pessoas[i].chegada, &pessoas[i].direcao);
    }
    
    fclose(arquivo);
    
    pthread_t threads[n];
    pthread_mutex_init(&lock, NULL);
    
    for (i = 0; i < n; i++) {
        pthread_create(&threads[i], NULL, usarEscada, (void *)&pessoas[i]);
    }
    
    for (i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("Momento em que a última pessoa saiu da escada rolante: %d\n", ultimoTempo);
    
    free(pessoas);
    pthread_mutex_destroy(&lock);
    return 0;
}
