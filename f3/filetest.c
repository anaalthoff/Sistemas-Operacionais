// Considere o seguinte programa que abre um ficheiro (cujo nome é passado como um argumento do programa, argv[1] no código), lê o seu conteúdo em blocos de BUFFER_SIZE bytes de cada vez e escreve esses bytes para o terminal (stdout).

#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 1024
int main(int argc, char *argv[])
{
    // FILE: tipo especial, representa um arquivo aberto. Não é o conteúdo do arquivo, mas sim uma estrutura que mantém informações sobre o arquivo (posição do ponteiro, modo de abertura, etc.).
    // *file: ponteiro para FILE.
    // fopen(...): função da biblioteca <stdio.h> que abre um arquivo. Retorna um ponteiro para FILE.
    // argv[1]: nome do arquivo passado como primeiro argumento da linha de comando. Exemplo: se você executar: ./prog texto.txt, então argv[1] = "texto.txt".
    // "r": modo de abertura do arquivo. Aqui "r" significa read-only
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("error: could not open %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    char buffer[BUFFER_SIZE];
    int nchars = fread(buffer, sizeof(char), BUFFER_SIZE, file);
    while (nchars > 0)
    {
        fwrite(buffer, sizeof(char), nchars, stdout);
        nchars = fread(buffer, sizeof(char), BUFFER_SIZE, file);
    }
    fclose(file);
    exit(EXIT_SUCCESS);
}

// Compile o programa e experimente-o com os seguintes comandos:
// $ gcc -Wall filetest.c -o filetest
// $ cat > quote.txt
// Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras gravida nisl tortor, eget vulputate lacus viverra non. Proin pharetra gravida condimentum. Nam imperdiet dictum placerat.
// ^D
// $ ./filetest quote.txt
// Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras gravida nisl tortor, eget vulputate lacus viverra non. Proin pharetra gravida condimentum. Nam imperdiet dictum placerat.$
// Consulte a página de manual das funções fopen, fread, fwrite e fclose e tente compreender como o programa funciona. Que acontece se definir BUFFER_SIZE com 1?