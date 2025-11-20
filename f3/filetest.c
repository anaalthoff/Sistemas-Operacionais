// Considere o seguinte programa que abre um ficheiro (cujo nome é passado como um argumento do programa, argv[1] no código), lê o seu conteúdo em blocos de BUFFER_SIZE bytes de cada vez e escreve esses bytes para o terminal (stdout).

#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 1024
int main(int argc, char *argv[])
{
    // FILE: tipo especial, representa um arquivo aberto. Não é o conteúdo do arquivo, mas sim uma estrutura que mantém informações sobre o arquivo (posição do ponteiro, modo de abertura, etc.).
    // *file: ponteiro para FILE.
    // fopen(...): função da biblioteca <stdio.h> que abre um arquivo. Retorna um ponteiro para FILE.
    // argv[1]: nome do arquivo passado como primeiro argumento da linha de comando. Exemplo: se executar: ./prog texto.txt, então argv[1] = "texto.txt".
    // "r": modo de abertura do arquivo. Aqui "r" significa read-only
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("error: could not open %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    // char buffer[BUFFER_SIZE]: array de caracteres que serve como buffer temporário para armazenar os dados lidos do arquivo.
    char buffer[BUFFER_SIZE];
    // fread(...): função da biblioteca <stdio.h> que lê dados de um arquivo.
    // buffer: é um ponteiro para o bloco de memória (buffer) onde os dados lidos serão armazenados (fread)
    // sizeof(char): tamanho de cada elemento a ser lido (aqui, 1 byte, pois char tem tamanho 1 byte)
    // BUFFER_SIZE: número máximo de elementos a serem lidos (aqui, até BUFFER_SIZE bytes)
    // file: ponteiro para o arquivo de onde os dados serão lidos
    // nchars: número de bytes efetivamente lidos do arquivo
    int nchars = fread(buffer, sizeof(char), BUFFER_SIZE, file);
    while (nchars > 0)
    {
        // fwrite(...): função da biblioteca <stdio.h> que escreve dados para um arquivo (aqui, stdout).
        // buffer: é um ponteiro para o bloco de memória (buffer) onde os dados a serem escritos estão armazenados (fwrite)
        // sizeof(char): tamanho de cada elemento a ser escrito (aqui, 1 byte, pois char tem tamanho 1 byte)
        // nchars: número de elementos a serem escritos (aqui, número de bytes efetivamente lidos do arquivo)
        // stdout: arquivo padrão de saída (terminal)
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
// Consulte a página de manual das funções fopen, fread, fwrite e fclose e tente compreender como o programa funciona. Que acontece se definir BUFFER_SIZE com 1? Ele vai contiuar funcionando, mas será muito mais lento, pois fará uma chamada de sistema para cada byte lido/escrito. E se definir BUFFER_SIZE com 1000000? Ele também vai funcionar, desde que o ficheiro não seja maior que 1 milhão de bytes. Se for maior, o programa vai ler e escrever apenas os primeiros 1 milhão de bytes do ficheiro.