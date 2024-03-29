#define _GNU_SOURCE
#include <stdlib.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sched.h>
#include <stdio.h>

// 64kB stack
#define FIBER_STACK 1024*64

// Estrutura para passar argumentos para a thread
struct ThreadArgs {
    int value;
};

// A função que a thread executará
int threadFunction(void* argument) {
    struct ThreadArgs* args = (struct ThreadArgs*)argument;
    printf("Thread filha recebe o argumento %d\n", args->value);
    printf("Thread em execucao\n");
    return 0;
}

int main() {
    void* stack;
    pid_t pid;

    // Alocando a stack
    stack = malloc(FIBER_STACK);
    if (stack == 0) {
        perror("Malloc: nao conseguiu alocar a stack");
        exit(1);
    }

    printf("Criando thread filha\n");

    // Argumentos para passar para a thread
    struct ThreadArgs args = {30}; // Exemplo de valor a ser passado

    // Chamar a chamada de sistema clone para criar a thread filha
    pid = clone(&threadFunction, (char*)stack + FIBER_STACK,
                SIGCHLD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, &args);
    
    if (pid == -1) {
        perror("clone");
        exit(2);
    }

    // Aguardar a thread filha terminar
    pid = waitpid(pid, 0, 0);
    
    if (pid == -1) {
        perror("waitpid");
        exit(3);
    }

    // Liberar o stack
    free(stack);
    
    printf("Thread filha libera espaco na Stack\n");
    
    return 0;
}
