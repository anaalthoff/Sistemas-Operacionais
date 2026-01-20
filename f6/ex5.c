// Considere o seguinte programa que executa um ciclo infinito e só pode ser terminado com um sinal externo, e.g., SIGINT. Reescreva-o reprogramando o SIGINT de tal forma que quando recebe o dito sinal sai do ciclo e termina executando a instrução exit imediatamente a seguir. O programa pode assim terminar a sua execução de forma graciosa.

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Variável global usada como "flag" de controlo do loop
static int flag = 1;

// Handler para SIGINT (Ctrl-C)
static void handle_sigint(int signum)
{
    printf("\nSIGINT recebido, terminando o programa...\n");
    flag = 0; // altera a flag para sair do loop
}

int main(int argc, char *argv[])
{
    // Imprime o PID do processo (útil para testes com kill)
    printf("my PID is %d\n", getpid());

    // Reprograma o SIGINT para chamar handle_sigint
    // A função signal() permite associar um "handler" a um sinal específico.
    // O primeiro argumento (SIGINT) indica qual sinal queremos tratar — neste caso, SIGINT é enviado quando pressionamos Ctrl-C.
    // O segundo argumento (handle_sigint) é uma função que vai ser chamada automaticamente quando o sinal ocorrer.
    // Ou seja, em vez do processo ser terminado imediatamente pelo Ctrl-C, ele vai executar a função handle_sigint.
    // signal() retorna SIG_ERR se houver algum erro ao tentar registar o handler.
    // Por exemplo, se o sistema não permitir reprogramar esse sinal (pouco comum com SIGINT), ou se houver algum problema interno.
    
    if (signal(SIGINT, handle_sigint) == SIG_ERR)
    {
        fprintf(stderr, "Não foi possível capturar SIGINT: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Loop potencialmente infinito
    while (flag)
        pause(); // pausa até receber algum sinal

    // Sai graciosamente
    printf("Programa terminou.\n");
    exit(EXIT_SUCCESS);
}
