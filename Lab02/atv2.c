#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define SIZE 100

int main() {
    int fd[2];
    pid_t pid;
    char stringPai[] = "Olá, filho!";
    char buffer[SIZE];

    //Criar um pipe
    if (pipe(fd) == -1) {
        fprintf(stderr, "Pipe failed");
        return 1;
    }

    pid = fork(); //Fork para o processo filho

    if (pid < 0) { // error occurred
        fprintf(stderr, "Fork Failed");
        return 1;
    } else if (pid > 0) {
        close(fd[0]);

        write(fd[1], stringPai, strlen(stringPai) + 1);
        close(fd[1]);

    } else { // child process
        close(fd[1]); // Terminar o envio de mensagem do processo 1

        read(fd[0], buffer, SIZE); 
        printf("Mensagem recebida: %s\n", buffer);

        char stringFilho[] = "Olá, pai!";
        write(fd[1], stringFilho, strlen(stringFilho) + 1);
        close(fd[1]);

        read(fd[0], buffer, SIZE);
        printf("Mensagem recebida: %s\n", buffer);

        close(fd[0]);
    }
    return 0;
}
