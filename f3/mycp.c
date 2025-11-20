// Escreva um programa que receba o nome de dois ficheiros como argumentos, em argv[1] e argv[2], e copie o conteúdo do primeiro ficheiro para o segundo. Se o segundo ficheiro não existir deverá ser criado. Se o ficheiro existir, o seu conteúdo será reescrito. Esta é a forma como funciona o comando cp da Bash shell.

#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "usage: %s <source_file> <destination_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Nomes dos ficheiros de origem e destino
    // Usa *, pois são ponteiros para strings
    char *source_file = argv[1];
    char *dest_file = argv[2];

    // Abrir o ficheiro de origem para leitura
    FILE *file = fopen(source_file, "r");
    if (file == NULL)
    {
        fprintf(stderr, "error: could not open %s\n", source_file);
        exit(EXIT_FAILURE);
    }

    // Abrir ficheiro de destino para escrita (cria ou sobrescreve)
    FILE *dest = fopen(dest_file, "w");
    if (dest == NULL)
    {
        fprintf(stderr, "error: could not open %s\n", dest_file);
        exit(EXIT_FAILURE);
    }

    // buffer é um array de char usado para armazenar temporariamente os dados lidos do ficheiro antes de escrever no destino.
    char buffer[BUFFER_SIZE];
    int nchars;
    // Copiar do ficheiro de origem para o de destino
    while ((nchars = fread(buffer, sizeof(char), BUFFER_SIZE, file)) > 0)
    {
        fwrite(buffer, sizeof(char), nchars, dest);
    }
    fclose(file);
    fclose(dest);
    exit(EXIT_SUCCESS);
}

// $ gcc -Wall mycp.c -o mycp
// $ cat > file1
// Lorem ipsum dolor sit amet, consectetur adipiscing elit.
// ^D
// $ ./mycp file1 file2
// $ cat file2
// Lorem ipsum dolor sit amet, consectetur adipiscing elit.
// $ cat > file3
// Cras gravida nisl tortor, eget vulputate lacus viverra non.
// ^D
// $ ./mycp file3 file2
// $ cat file2
// Cras gravida nisl tortor, eget vulputate lacus viverra non.
