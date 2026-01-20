// Os programas p1.c e p2.c comunicam via uma “named pipe” criada com a chamada ao sistema operativo mkfifo. Usando este tipo de “pipe” pode fazer dois quaisquer processos comunicar entre si - sem precisarem de ser pai e filho

// • Cria uma named pipe (FIFO) em /tmp/myfifo
// • Abre essa FIFO para escrita
// • Lê texto do teclado
// • Envia esse texto pela FIFO para outro processo

#include <stdio.h>     // printf, perror, fgets
#include <string.h>    // strlen
#include <stdlib.h>    // exit
#include <unistd.h>    // write, close
#include <sys/stat.h>  // mkfifo
#include <sys/errno.h> // errno
#include <fcntl.h>     // open, O_WRONLY

#define BUF_SIZE 128 // Tamanho do buffer de leitura

int main(int argc, char *argv[])
{
    // Caminho da FIFO (named pipe)
    char *myfifo = "/tmp/myfifo";

    // Cria a FIFO com permissões 0666 (leitura/escrita para todos)
    int rv = mkfifo(myfifo, 0666);

    // Se deu erro ao criar
    if (rv == -1)
    {
        // Se o erro for "já existe", tudo bem, continuamos
        if (errno != EEXIST)
        {
            perror("mkfifo");
            exit(EXIT_FAILURE);
        }
    }

    // Abre a FIFO em modo escrita
    // OBS: vai bloquear até alguém abrir para leitura no outro processo
    int fd = open(myfifo, O_WRONLY);
    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Loop infinito: lê do teclado e envia pela FIFO
    while (1)
    {
        char text[BUF_SIZE];

        // Lê uma linha do teclado
        fgets(text, BUF_SIZE, stdin);

        // Envia a string para o outro processo pela FIFO
        write(fd, text, strlen(text) + 1);
    }

    // Fecha a FIFO (nunca chega aqui porque o while é infinito)
    close(fd);
    exit(EXIT_SUCCESS);
}