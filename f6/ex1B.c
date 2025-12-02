
// Altere o programa de tal forma que, em vez das mensagens enviadas, o processo pai abra um ficheiro de texto (cujo nome deve ser dado na linha de comando), leia o seu conteúdo e o passe através da “pipe” para o processo filho. Este deverá receber o conteúdo do ficheiro e escrevê-lo no “stdout”. Compile e execute o seu programa com um ficheiro de texto grande (e.g., o ficheiro com este código fonte).

#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

// Definição do tamanho máximo de uma linha
#define LINESIZE 256

int main(int argc, char *argv[])
{
    int fd[2];
    pid_t pid;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Abrir o ficheiro
    int f = open(argv[1], O_RDONLY);
    if (f == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Criar pipe
    if (pipe(fd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Criar processo filho
    if ((pid = fork()) == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0)
    { /* parent */
        // fechar leitura da pipe do pai
        close(fd[0]);
        // Ler do ficheiro e escrever na pipe
        char buffer[LINESIZE];
        // Ler do ficheiro em blocos e escrever na pipe
        ssize_t bytesRead;
        // Ler do ficheiro e escrever na pipe
        while ((bytesRead = read(f, buffer, LINESIZE)) > 0)
        {
            write(fd[1], buffer, bytesRead);
        }
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
        // fechar escrita da pipe do filho
        close(fd[1]);
        // Ler da pipe e escrever no stdout
        char buffer[LINESIZE];
        // ssize_t é um tipo de dado usado para representar o número de bytes lidos ou escritos
        ssize_t bytesRead;
        // Ler da pipe e escrever no stdout
        while ((bytesRead = read(fd[0], buffer, LINESIZE)) > 0)
        {
            write(STDOUT_FILENO, buffer, bytesRead);
        }
        close(fd[0]);
        exit(EXIT_SUCCESS);
    }
}