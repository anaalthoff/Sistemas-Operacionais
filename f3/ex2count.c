/* recebe duas strings na linha de comando e indica quantas vezes a primeira ocorre na segunda */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  /* check if you have the right number of arguments */
  /* argv[0] é sempre o nome do programa. Então, para receber duas strings na linha de comando, é preciso 3 argumentos (argv[0] é o programa, argv[1] e argv[2] são as strings) */
  if ( argc != 3 ) {
    printf("usage: %s string1 string2\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  /* verifica quantas vezes a primeira string ocorre na segunda */
  int count = 0;
  /* Cria um ponteiro p que aponta para o início da segunda string (onde vai buscar a primeira string). */
  char *p = argv[2];
  /* precisa avançar o ponteiro a cada iteração: p++. Sem isso, fica na mesma posição e cria um loop infinito*/
  while ((p = strstr(p, argv[1]))) {
      count++;
      p++;
  }

  printf("A string '%s' ocorre %d vezes na string '%s'\n", argv[1], count, argv[2]);

  free(p);
  exit(EXIT_SUCCESS);
}
