#include <stdio.h>    // funções de I/O, como fopen, fgetc, printf
#include <stdlib.h>   // funções de utilidade, como exit
#include <string.h>   // para manipulação de strings (não estritamente necessário aqui)
#include <unistd.h>  // necessário para getopt, optind, opterr, optarg
#include <ctype.h>    // para isspace() que identifica espaços, tabs e quebras de linha

// Função que percorre o ficheiro e faz as contagens
void count_file(FILE *file, int count_chars, int count_words, int count_lines) {
    int c;              // variável para armazenar cada caractere lido
    int in_word = 0;    // flag para rastrear se estamos dentro de uma palavra
    long chars = 0;     // contador de caracteres
    long words = 0;     // contador de palavras
    long lines = 0;     // contador de linhas

    // lê caractere por caractere até o fim do ficheiro
    while ((c = fgetc(file)) != EOF) {
        if (count_chars) chars++;             // incrementa contador de caracteres, se solicitado
        if (count_lines && c == '\n') lines++; // incrementa contador de linhas ao encontrar '\n'

        if (count_words) {                     // se a opção de contar palavras está ativa
            if (isspace(c)) {                 // se o caractere é espaço, tab ou newline
                if (in_word) {                // se estávamos dentro de uma palavra
                    words++;                  // palavra completa, incrementa contador
                    in_word = 0;              // reset da flag, saímos da palavra
                }
            } else {
                in_word = 1;                  // estamos dentro de uma palavra
            }
        }
    }

    // Se o ficheiro não termina com espaço, conta a última palavra
    if (count_words && in_word) words++;

    // Exibe resultados de acordo com as opções passadas
    if (count_chars) printf("%ld\n", chars);
    if (count_words) printf("%ld\n", words);
    if (count_lines) printf("%ld\n", lines);
}

int main(int argc, char *argv[]) {
    int opt;                // variável para armazenar cada opção processada pelo getopt
    int count_chars = 0;    // flag para contar caracteres
    int count_words = 0;    // flag para contar palavras
    int count_lines = 0;    // flag para contar linhas

    // Processa as opções da linha de comando (-c, -w, -l)
    while ((opt = getopt(argc, argv, "cwl")) != -1) {
        switch(opt) {
            case 'c': count_chars = 1; break;  // ativa contagem de caracteres
            case 'w': count_words = 1; break;  // ativa contagem de palavras
            case 'l': count_lines = 1; break;  // ativa contagem de linhas
            default:
                fprintf(stderr, "Uso: %s [-c|-w|-l] arquivo\n", argv[0]);
                exit(EXIT_FAILURE);            // sai se opção inválida
        }
    }

    // Verifica se o usuário forneceu o nome do ficheiro
    if (optind >= argc) {
        fprintf(stderr, "Erro: ficheiro não especificado.\n");
        exit(EXIT_FAILURE);
    }

    // Abre o ficheiro no modo leitura
    FILE *file = fopen(argv[optind], "r");
    if (!file) {                     // verifica se abriu corretamente
        perror("Erro ao abrir ficheiro");
        exit(EXIT_FAILURE);
    }

    // Chama a função que faz a contagem
    count_file(file, count_chars, count_words, count_lines);

    // Fecha o ficheiro
    fclose(file);

    // Programa finalizado com sucesso
    return 0;
}
