#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    for (int i = 0; i < 4; i++)
        fork();
    printf("PID: %d\n", getpid());
    exit(EXIT_SUCCESS);
}

// Este programa cria múltiplos processos utilizando a chamada de sistema fork().
// Cada chamada a fork() cria um novo processo filho que é uma cópia do processo pai.
// Com quatro chamadas a fork(), o número total de processos criados é 2^4 = 16.
// Cada processo imprime o seu próprio PID (Process IDentifier) utilizando a função getpid().
// Compile o programa com:
// $ gcc -Wall ex2.c -o ex2
// E execute-o com:
// $ ./ex2
// Você verá a saída com os PIDs dos processos criados. Note que a ordem dos PIDs pode variar a cada execução, pois a criação dos processos é assíncrona.