// Adapte o exercício 1 para que imprima o conteúdo do ficheiro - os caracteres individuais - por ordem inversa.
#include <stdio.h>      // Para printf
#include <stdlib.h>     // Para exit
#include <unistd.h>     // Para read(), write(), close()
#include <fcntl.h>      // Para open()

int main(int argc, char* argv[]) {
    if (argc != 2) { // Verifica se o nome do ficheiro foi passado
        printf("usage: cat filename\n");
        exit(EXIT_FAILURE);
    }

    int fd = open(argv[1], O_RDONLY); // Abre o ficheiro em modo leitura
    int size = lseek(fd, -1, SEEK_END) +1; // Move o cursor para o fim do ficheiro para obter o tamanho
    char buffer [1];
    int nreads = read(fd, buffer, 1); // Lê o último byte
    while (nreads < size) {
        write(STDOUT_FILENO, buffer, 1);
        lseek(fd, -2, SEEK_CUR);
        nreads += read(fd, buffer, 1);
    }
    write(fd, buffer, 1); // Escreve o primeiro byte
    close(fd); // Fecha o ficheiro
    exit(EXIT_SUCCESS);
}
