#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

// Fellipe Jardanovski
// Felipe Jiao

// Definindo o tamanho da pilha para as threads
#define FIBER_STACK 1024*64

struct c {
    int saldo;
};
typedef struct c conta;

conta from, to;
int valor;
pthread_mutex_t lock; // Definindo um mutex

// Função executada pelas threads
void* transferencia(void *arg)
{
    // Usando mutex para garantir exclusão mútua
    pthread_mutex_lock(&lock);
    
    if (from.saldo >= valor) {
        from.saldo -= valor;
        to.saldo += valor;
        printf("Transferência de %d concluída com sucesso!\n", valor);
        printf("Saldo de c1: %d\n", from.saldo);
        printf("Saldo de c2: %d\n", to.saldo);
    } else {
        printf("Saldo insuficiente para a transferência de %d!\n", valor);
    }
    
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main()
{
    pthread_t threads[10];
    int i;

    // Inicializando o mutex
    if (pthread_mutex_init(&lock, NULL) != 0) {
        perror("pthread_mutex_init: could not initialize mutex");
        exit(1);
    }

    // saldo das contas
    from.saldo = 100;
    to.saldo = 100;

    printf("Transferindo 10 para a conta c2\n");
    valor = 10;

    // Criando as threads
    for (i = 0; i < 10; i++) {
        if (pthread_create(&threads[i], NULL, transferencia, NULL) != 0) {
            perror("pthread_create");
            exit(2);
        }
    }

    // Esperando todas as threads terminarem
    for (i = 0; i < 10; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destruindo o mutex
    pthread_mutex_destroy(&lock);

    printf("Transferências concluídas e memória liberada.\n");
    return 0;
}
