// Os programas p1.c e p2.c comunicam via uma “named pipe” criada com a chamada ao sistema operativo mkfifo. Usando este tipo de “pipe” pode fazer dois quaisquer processos comunicar entre si - sem precisarem de ser pai e filho

#include <stdio.h>     // printf, perror, fgets
#include <string.h>    // strlen
#include <stdlib.h>    // exit
#include <unistd.h>    // write, close
#include <sys/stat.h>  // mkfifo
#include <sys/errno.h> // errno
#include <fcntl.h>     // open, O_RDONLY

#define BUF_SIZE 128    // Tamanho máximo do buffer

int main(int argc, char *argv[])
{
    // Caminho da FIFO (tem que ser o mesmo do p1.c)
    char *myfifo = "/tmp/myfifo";

    // Abre a FIFO em modo leitura
    // OBS: Vai bloquear até o outro processo abrir para escrita
    int fd = open(myfifo, O_RDONLY);
    if (fd == -1)
    {
        // Se não conseguir abrir, mostra o erro e termina
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Loop infinito: fica esperando dados do p1.c
    while (1)
    {
        char text[BUF_SIZE];

        // Lê até BUF_SIZE bytes vindos da FIFO
        // read bloqueia até alguém escrever na FIFO
        ssize_t bytes = read(fd, text, BUF_SIZE);

        // Se read retornar 0, o outro processo fechou a FIFO
        if (bytes == 0)
        {
            printf("Escritor fechou a FIFO.\n");
            break;
        }

        // Garante que a string termina com '\0'
        text[bytes] = '\0';

        // Mostra o que foi recebido
        printf("Recebido: %s", text);
    }

    // Fecha a FIFO
    close(fd);
    exit(EXIT_SUCCESS);
}