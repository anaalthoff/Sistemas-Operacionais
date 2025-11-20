// Com base no programa anterior, escreva um comando mycat que:
// • recebe como argumento o nome de um ficheiro e imprime o seu conteúdo (semelhante ao comando cat com 1 argumento);
// • recebe como argumento os nomes de vários ficheiros e imprime o conteúdo de todos eles sequencialmente (semelhante ao comando cat com vários argumentos).

#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        // stderr: fluxo de saída padrão para mensagens de erro
        // exemplo do texto de saída: usage: ./mycat <file1> [file2 ... fileN]
        fprintf(stderr, "usage: %s <file1> [file2 ... fileN]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];

    // int é igual a 1, porque argv[0] é o nome do programa
    for (int i = 1; i < argc; i++)
    {
        // abre o ficheiro argv[i]
        FILE *file = fopen(argv[i], "r");
        if (file == NULL)
        {
            fprintf(stderr,"error: could not open %s\n", argv[i]);
            exit(EXIT_FAILURE);
        }

        // lê e escreve o conteúdo do ficheiro
        // nchars: número de bytes efetivamente lidos do arquivo
        int nchars = fread(buffer, sizeof(char), BUFFER_SIZE, file);
        while (nchars > 0) {
            fwrite(buffer, sizeof(char), nchars, stdout);
            nchars = fread(buffer, sizeof(char), BUFFER_SIZE, file);
        }
        fclose(file);
    }
    exit(EXIT_SUCCESS);
}

// $ gcc -Wall mycat.c -o mycat
// $ cat > file1
// Lorem ipsum dolor sit amet, consectetur adipiscing elit.
// Cras gravida nisl tortor, eget vulputate lacus viverra non.
// Proin pharetra gravida condimentum.
// Nam imperdiet dictum placerat.
// ^D
// $ cat > file2
// Sed convallis hendrerit scelerisque.
// Sed sodales sagittis nulla vitae auctor.
// Quisque lobortis tortor vitae ligula ullamcorper fermentum.
// Aliquam interdum, metus sed rhoncus gravida,
// nibh nisl porttitor tortor, in finibus mauris erat et lacus.
// ^D
// $ cat > file3
// Aliquam sit amet arcu molestie, sodales sem vitae, semper nisi.
// Curabitur lacinia vel metus in aliquam.
// Fusce non tellus pulvinar, tincidunt quam ac, rhoncus turpis.
// ^D
// $ ./mycat file1
// Lorem ipsum dolor sit amet, consectetur adipiscing elit.
// Cras gravida nisl tortor, eget vulputate lacus viverra non.
// Proin pharetra gravida condimentum.
// Nam imperdiet dictum placerat.
// $ ./mycat file1 file2 file3
// Lorem ipsum dolor sit amet, consectetur adipiscing elit.
// Cras gravida nisl tortor, eget vulputate lacus viverra non.
// Proin pharetra gravida condimentum.
// Nam imperdiet dictum placerat.
// Sed convallis hendrerit scelerisque.
// Sed sodales sagittis nulla vitae auctor.
// Quisque lobortis tortor vitae ligula ullamcorper fermentum.
// Aliquam interdum, metus sed rhoncus gravida,
// nibh nisl porttitor tortor, in finibus mauris erat et lacus.
// Aliquam sit amet arcu molestie, sodales sem vitae, semper nisi.
// Curabitur lacinia vel metus in aliquam.
// Fusce non tellus pulvinar, tincidunt quam ac, rhoncus turpis.