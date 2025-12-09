// Ao invés das “pipes”, os “sockets” permitem a comunicação bidirecional.

#include <sys/wait.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char buf[1024];
    // sockets() cria um endpoint de comunicação bidirecional e retorna um file descriptor que se refere a esse endpoint
    // int sockets[2] - array que irá conter os dois file descriptors criados
    // Cada extremo pode ler e escrever
    int sockets[2], retv;
    // retv armazena o valor de retorno das funções chamadas
    // socketpair() cria um par de sockets interconectados
    // AF_UNIX - domínio de comunicação local
    // SOCK_STREAM - tipo de socket orientado a conexão
    // 0 - protocolo padrão
    // sockets - array onde os file descriptors serão armazenados
    retv = socketpair(AF_UNIX, SOCK_STREAM, 0, sockets);
    if (retv == -1)
    {
        perror("socketpair");
        exit(EXIT_FAILURE);
    }
    // Criar processo filho
    retv = fork();
    if (retv == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    // Processo pai
    if (retv > 0)
    { /* parent */
        char string1[] = "In every walk with nature...";
        // O pai FECHA o socket 1, mas usa o socket 0 tanto para ler quanto para escrever.
        close(sockets[1]);
        // sockets[0] - usado para receber dados
        // string1 é enviado para o processo filho
        // sixzeof(string1) - tamanho da string1
        // Pai envia string1 ao filho
        // Pai espera o filho responder
        //Imprime a resposta
        write(sockets[0], string1, sizeof(string1));
        read(sockets[0], buf, sizeof(buf));
        printf("message from %d-->%s\n", getpid(), buf);
        close(sockets[0]);
        retv = wait(NULL);
        if (retv == -1)
        {
            perror("wait");
            exit(EXIT_FAILURE);
        }
    }
    else
    { /* child */
        char string2[] = "...one receives far more than he seeks.";
        close(sockets[0]);
        // Lê a mensagem do pai
        // Imprime
        // Envia string2 de volta ao pai
        read(sockets[1], buf, sizeof(buf));
        printf("message from %d-->%s\n", getppid(), buf);
        write(sockets[1], string2, sizeof(string2));
        close(sockets[1]);
        exit(EXIT_SUCCESS);
    }
}