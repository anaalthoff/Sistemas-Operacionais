// O exemplo seguinte mostra a manipulação e o tratamento de sinais pelo utilizador. Na função main, aparece a função signal que regista qual o tratamento que deve ser dado, quando o processo que executa o código recebe os sinais SIGUSR1 e SIGUSR2. Para testar o exemplo, abra um terminal novo envie o sinal SIGUSR1 ao processo cujo pid é n usando o comando kill -SIGUSR1 n.

#include <errno.h>      // Permite aceder à variável errno, que indica erros das funções do sistema
#include <signal.h>     // Contém definições para sinais e manipulação de sinais (signal, SIGUSR1, SIGUSR2, etc.)
#include <stdio.h>      // Permite usar funções de entrada/saída como printf e fprintf
#include <stdlib.h>     // Contém funções gerais como exit()
#include <string.h>     // Contém funções para manipulação de strings, como strerror()
#include <unistd.h>     // Contém funções do POSIX, como getpid() e pause()

// Função que trata o sinal SIGUSR1
// "static" indica que a função só é visível neste ficheiro (não pode ser chamada fora dele)
static void handler1() {
    printf("caught SIGUSR1\n");  // Quando o processo recebe SIGUSR1, imprime esta mensagem
}

// Função que trata o sinal SIGUSR2
static void handler2() {
    printf("caught SIGUSR2\n");  // Quando o processo recebe SIGUSR2, imprime esta mensagem
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

    // Loop infinito para manter o programa a correr
    // pause() faz o processo esperar até receber algum sinal
    // Assim, o programa não termina e pode receber sinais SIGUSR1 ou SIGUSR2
    for (;;)
        pause();
}


// Como enviar sinais (em outro terminal)

// Abre um outro terminal e usa o comando kill:
// Enviar SIGUSR1:
// kill -SIGUSR1 12345

// Output no terminal onde o programa está rodando:
// caught SIGUSR1

// Enviar SIGUSR2:
// kill -SIGUSR2 12345

// Output:
// caught SIGUSR2