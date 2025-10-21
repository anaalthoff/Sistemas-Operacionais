/* recebe uma string na linha de comando e a transforma numa string equivalente mas com todos os caracteres em minúsculas */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char* argv[]) {
  /* check if you have the right number of arguments */
  if ( argc != 2 ) {
    printf("usage: %s string1 string2\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  
  /* create a copy of string */
  char *p1 = strdup(argv[1]);
  /* printf("p1 holds:%s\n", p1); */

  /* convert to lowercase */
  for (int i = 0; p1[i] != '\0'; i++) {
      p1[i] = tolower((unsigned char)p1[i]);
  }

  printf("Lowercase:%s\n", p1);

  /* Como fazer sem copiar */
  /* for (int i = 0; argv[1][i] != '\0'; i++) {
      argv[1][i] = tolower((unsigned char)argv[1][i]);
  } */

  /* free allocated memory from malloc and strdup */
  free(p1);
  exit(EXIT_SUCCESS);
}
