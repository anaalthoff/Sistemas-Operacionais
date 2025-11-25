// Por vezes, queremos processar um ficheiro de texto lendo-o linha por linha. Para este prop´osito, a função getline é mais robusta e segura do que as suas congêneres na libc. Quando invocada com um apontador NULL no local onde deveria estar o endere¸co do buffer (line) onde a linha do ficheiro deveria ser escrita, a função faz ela própria a reserva desse espaço no heap e retorna com a linha copiada para essa localização e o apontador inicializado. Aqui está um exemplo simples da sua utilização. Leia o manual para saber mais detalhes.

// getline é uma função POSIX que lê uma linha inteira de um ficheiro, realocando automaticamente o buffer se necessário.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    /* open file, exit on error */
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("error: could not open %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    /* read file, line by line */
    // Guarda o número de caracteres lidos em cada chamada de getline. Exemplo: se a linha tiver 18 caracteres, read será 18.
    ssize_t read;
    // Inicializa o tamanho atual do buffer apontado por line.
    // Como está 0, significa: "Ainda não tenho buffer; getline() deve alocar um para mim".
    size_t size = 0;
    // line começa como NULL, justamente para o getline saber que precisa:
    // alocar memória no heap
    // guardar o endereço dessa memória em line
    // Depois da primeira leitura, line não será mais NULL — será um buffer reutilizado.
    char *line = NULL;
    // Contador das linhas do ficheiro
    int lineno = 1;
    // (read = getline(&line, &size, file))
    // getline lê uma linha do arquivo e guarda dentro de line.
    // Se necessário, realoca e ajusta size.
    // Retorna:
    // número de caracteres lidos
    // ou -1 se chegou ao fim do ficheiro
    // != -1 -> Enquanto houver linhas, continua.
    while ((read = getline(&line, &size, file)) != -1)
    {
        printf("[%5d]: %s", lineno, line);
        lineno++;
    }
    /* free allocated buffer */
    free(line);  
    /* close file */
    fclose(file);
    /* return gracefully */
    exit(EXIT_SUCCESS);
}