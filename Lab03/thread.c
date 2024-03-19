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

// Função executada pela thread criada
int threadFunction(void* argument) {
    struct ThreadArgs* args = (struct ThreadArgs*)argument;
    printf("Thread filha recebeu o argumento: %d\n", args->value);
    printf("Thread filha em execucao");
    return 0;
}

int main() {
    void* stack;
    pid_t pid;

    // Aloca a stack
    stack = malloc(FIBER_STACK);
    if (stack == 0) {
        perror("Malloc: nao conseguiu alocar a stack");
        exit(1);
    }

    printf("Processo pai criando a thread filha\n");

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
    
    printf("\nThread filha liberou a Stack\n");
    
    return 0;
}
