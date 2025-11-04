#include <stdio.h>      // Para printf
#include <stdlib.h>     // Para exit
#include <unistd.h>     // Para read(), write(), close()
#include <fcntl.h>      // Para open()
#define BUFFER_SIZE 1024

int main(int argc, char* argv[]) {
    if (argc != 2) { // Verifica se o nome do ficheiro foi passado
        printf("usage: cat filename\n");
        exit(EXIT_FAILURE);
    }

    int fd = open(argv[1], O_RDONLY); // Abre o ficheiro em modo leitura
    if (fd == -1) { // Caso erro
        printf("error: cannot open %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    int nbytes = read(fd, buffer, BUFFER_SIZE); // Lê até 1024 bytes

    while (nbytes > 0) { // Enquanto conseguir ler
        write(STDOUT_FILENO, buffer, nbytes); // Escreve no terminal
        nbytes = read(fd, buffer, BUFFER_SIZE);
    }

    close(fd); // Fecha o ficheiro
    exit(EXIT_SUCCESS);
}
