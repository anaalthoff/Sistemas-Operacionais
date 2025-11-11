/* recebe uma string na linha de comando e a transforma numa string equivalente mas com todos os caracteres em minúsculas */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
  /* check if you have the right number of arguments */
  if (argc != 2)
  {
    printf("usage: %s string1 string2\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  // argv[1] aponta para o início da string
  // argv[1][i] acede ao i-ésimo caractere da string
  for (int i = 0; argv[1][i] != '\0'; i++)
  {
    argv[1][i] = tolower(argv[1][i]);
  }

  printf("Lowercase: %s\n", argv[1]);

  exit(EXIT_SUCCESS);
}

// argv → "lista" de argumentos
// argv[1] → "um argumento específico" (uma string)
// argv[1][i] → "um caractere específico dessa string"