/* recebe duas strings na linha de comando e indica se a primeira ocorre na segunda */

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

  /* verifica se a primeira string ocorre na segunda */
  // strstr: procura por uma substring (needle) dentro de outra string (haystack).
  // haystack → a string principal onde vamos procurar
  // needle → a substring que queremos encontrar
  if (strstr(argv[2], argv[1])) {
      printf("A string '%s' ocorre na string '%s'\n", argv[1], argv[2]);
  } else {
      printf("A string '%s' não ocorre na string '%s'\n", argv[1], argv[2]);
  }

  exit(EXIT_SUCCESS);
}
