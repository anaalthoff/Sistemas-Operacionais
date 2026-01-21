#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        pid_t pid = fork();

        if (pid == 0)
        { // Processo filho
            printf("%d: %s\n", getpid(), argv[i]);
            exit(EXIT_SUCCESS);
        }
    }

    // Processo pai espera todos os filhos
    for (int i = 1; i < argc; i++)
        wait(NULL);

    exit(EXIT_SUCCESS);
}


// Este programa cria um processo filho para cada argumento fornecido na linha de comando.
// Cada processo filho imprime o seu próprio PID e o argumento correspondente.
// O processo pai espera que todos os processos filhos terminem antes de sair.