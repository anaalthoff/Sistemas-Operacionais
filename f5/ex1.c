#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    fork();
    fork();
    fork();
    printf("PID: %d\n", getpid());
    exit(EXIT_SUCCESS);
}

// Este programa cria múltiplos processos utilizando a chamada de sistema fork().
// Cada chamada a fork() cria um novo processo filho que é uma cópia do processo pai.
// Com três chamadas a fork(), o número total de processos criados é 2^3 = 8.
// Cada processo imprime o seu próprio PID (Process IDentifier) utilizando a função getpid().
// Compile o programa com:
// $ gcc -Wall ex1.c -o ex1
// E execute-o com:
// $ ./ex1
// Você verá a saída com os PIDs dos processos criados. Note que a ordem dos PIDs pode variar a cada execução, pois a criação dos processos é assíncrona.

// Analisando as 3 chamadas sequenciais a fork():
// Primeira fork():
// Existe 1 processo (o pai original).
// Após a chamada, o pai cria 1 filho.
// Total de processos: 1×2=∗∗2** (1 Pai, 1 Filho).

// Segunda fork() :
// Agora existem 2 processos.
// Ambos os processos(o pai original e o primeiro filho) executam esta fork(), e cada um cria um novo filho.
// Total de processos : 2×2 =∗∗4 * *(2 Pais, 2 Filhos).

// Terceira fork() :
// Agora existem 4 processos.
// Todos os 4 processos executam esta fork(), e cada um cria um novo filho.
// Total de processos : 4×2 =∗∗8 * *(4 Pais, 4 Filhos).