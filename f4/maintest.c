/* exemplifica o uso da fun¸c˜ao main na sua forma mais
geral em C*/

#include <stdio.h>
int main (int argc, char* argv[]) {
  printf("# arguments = %d\n", argc - 1); // argc - 1 exclui o nome do programa da contagem
  printf("the command arguments are: %s\n", argv[0]);
  for (int i = 1; i < argc ; i++)
    printf("argv[%d]=%s\n", i, argv[i]);
  return 0;
}

/* $ gcc -Wall maintest.c -o maintest
e experimente-o com os comandos:
$ ./maintest
$ ./maintest mercury
$ ./maintest mercury venus
$ ./maintest mercury venus earth
$ ./maintest mercury venus earth mars */