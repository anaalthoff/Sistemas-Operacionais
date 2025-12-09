// Modifique o programa de tal forma que o processo pai abra um ficheiro de texto e transfira o seu conteúdo para o processo filho. Por sua vez o processo filho deve receber o conteúdo, passar todos os caracteres para maiúsculas e devolvê-los para o processo pai que os imprime no “stdout”.

#include <sys/wait.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int sockets[2];
    char buf[1024];

    if (socketpair(AF_UNIX, SOCK_STREAM, 0, sockets) == -1)
    {
        perror("socketpair");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    // Processo pai
    if (pid > 0)
    {                      /* parent */
        close(sockets[1]); // Pai usa sockets[0]
        // Abre o ficheiro
        FILE *f = fopen(argv[1], "r");
        if (!f)
        {
            perror("open");
            exit(EXIT_FAILURE);
        }

        // Lê ficheiro e envia ao filho
        size_t n = fread(buf, 1, sizeof(buf), f);
        fclose(f);

        write(sockets[0], buf, n);     // envia só os bytes lidos
        shutdown(sockets[0], SHUT_WR); // sinaliza “acabou o envio”

        // Lê resposta do filho
        int r = read(sockets[0], buf, sizeof(buf));
        buf[r] = '\0';

        printf("PAI recebeu:\n%s\n", buf);

        close(sockets[0]);
        wait(NULL);
    }

    // Processo filho
    else
    {
        close(sockets[0]); // Filho usa sockets[1]

        int r = read(sockets[1], buf, sizeof(buf));

        // Converte para MAIÚSCULAS
        for (int i = 0; i < r; i++)
            buf[i] = toupper((unsigned char)buf[i]);

        write(sockets[1], buf, r);

        close(sockets[1]);
        exit(EXIT_SUCCESS);
    }

    return 0;
}
