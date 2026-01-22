// Considere o seguinte programa que implementa uma “pipe” entre processos pai e filho.
// Pipe é um canal de comunicação unidirecional que pode ser usado para comunicação entre processos relacionados, como processos pai e filho.
// Socket pair é usado para comunicação bidirecional entre processos, mas pipe é mais simples e adequado para comunicação unidirecional.

#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Definição do tamanho máximo de uma linha
#define LINESIZE 256

int main(int argc, char *argv[])
{
    // Criação do pipe
    // fd - onde irá criar os file descriptors
    // um para leitura, outro para escrita
    // fd[0] - leitura
    // fd[1] - escrita
    int fd[2];
    // pid_t significa "process ID type"
    // usado para armazenar o ID do processo
    pid_t pid;
    if (pipe(fd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    // para acontecer o pipe, ele deve vir antes do fork, ou os processos não irão conseguir se comuicar
    // Criar processo filho
    if ((pid = fork()) == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid > 0)
    { /* parent */
        char line[LINESIZE] = "Lorem ipsum dolor sit amet ...";
        close(fd[0]);
        write(fd[1], line, strlen(line));
        close(fd[1]);
        if (wait(NULL) == -1)
        {
            perror("wait");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }
    else
    { /* child */
        char line[LINESIZE];
        close(fd[1]);
        int nbytes = read(fd[0], line, LINESIZE);
        write(STDOUT_FILENO, line, nbytes);
        close(fd[0]);
        exit(EXIT_SUCCESS);
    }
}