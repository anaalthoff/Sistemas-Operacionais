// Adapte o código anterior para que suporte também o tratamento dos sinais SIGTSTP (enviado pelo terminal quando se usa CTRL-Z), SIGINT (enviado pelo terminal quando se usa CTRL-C) e SIGHUP (enviado pelo terminal quando o utilizador faz “logout”) imprimindo nesses casos uma mensagem adequada. Consegue fazer algo de semelhante com o sinal SIGKILL?

#include <errno.h>  // Permite aceder à variável errno, que indica erros das funções do sistema
#include <signal.h> // Contém definições para sinais e manipulação de sinais (signal, SIGUSR1, SIGUSR2, etc.)
#include <stdio.h>  // Permite usar funções de entrada/saída como printf e fprintf
#include <stdlib.h> // Contém funções gerais como exit()
#include <string.h> // Contém funções para manipulação de strings, como strerror()
#include <unistd.h> // Contém funções do POSIX, como getpid() e pause()

// Função que trata o sinal SIGUSR1
// "static" indica que a função só é visível neste ficheiro (não pode ser chamada fora dele)
static void handler1()
{
    printf("caught SIGUSR1\n"); // Quando o processo recebe SIGUSR1, imprime esta mensagem
}

// Função que trata o sinal SIGUSR2
static void handler2()
{
    printf("caught SIGUSR2\n"); // Quando o processo recebe SIGUSR2, imprime esta mensagem
}

// Função que trata o sinal SIGTSTP
static void handler3()
{
    printf("caught SIGTSTP\n"); // Quando o processo recebe SIGTSTP, imprime esta mensagem
}

// Função que trata o sinal SIGINT
static void handler4()
{
    printf("caught SIGINT\n"); // Quando o processo recebe SIGINT, imprime esta mensagem
}

// Função que trata o sinal SIGHUP
static void handler5()
{
    printf("caught SIGHUP\n"); // Quando o processo recebe SIGHUP, imprime esta mensagem
}

int main(int argc, char *argv[])
{
    // Imprime o PID do processo. Isso é útil para enviar sinais de outro terminal.
    printf("my PID is %d\n", getpid());

    // Regista handler1 para lidar com SIGUSR1
    // signal(SIGUSR1, handler1) diz "quando receber SIGUSR1, execute handler1"
    // Se ocorrer algum erro no registo, signal retorna SIG_ERR
    if (signal(SIGUSR1, handler1) == SIG_ERR)
    {
        // Se houver erro, escreve mensagem de erro em stderr e termina o programa
        fprintf(stderr, "Can’t catch SIGUSR1: %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Regista handler2 para lidar com SIGUSR2, com lógica idêntica à anterior
    if (signal(SIGUSR2, handler2) == SIG_ERR)
    {
        fprintf(stderr, "Can’t catch SIGUSR2: %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Regista handler3 para lidar com SIGTSTP, com lógica idêntica à anterior
    if (signal(SIGTSTP, handler3) == SIG_ERR)
    {
        fprintf(stderr, "Can’t catch SIGTSTP: %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Regista handler4 para lidar com SIGINT, com lógica idêntica à anterior
    if (signal(SIGINT, handler4) == SIG_ERR)
    {
        fprintf(stderr, "Can’t catch SIGINT: %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Regista handler5 para lidar com SIGHUP, com lógica idêntica à anterior
    if (signal(SIGHUP, handler5) == SIG_ERR)
    {
        fprintf(stderr, "Can’t catch SIGHUP: %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Loop infinito para manter o programa a correr
    // pause() faz o processo esperar até receber algum sinal
    // Assim, o programa não termina e pode receber sinais SIGUSR1 ou SIGUSR2
    for (;;)
        pause();
}