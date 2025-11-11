/* exemplifica o uso da função main na sua forma mais geral em C*/

#include <stdio.h>
// int é o tipo de retorno da função main. Main retorna um númeor para o SO, 0 significa que terminou com sucesso
// int argc → argument count (contagem de argumentos). Inclui o nome do programa.
// char* argv[] → argument vector (vetor de argumentos). É um array de strings (cadeias de caracteres terminado em '\0') que contém os argumentos passados na linha de comando
int main (int argc, char* argv[]) {
  // %d: marcador de formato para inteiros
  printf("# arguments = %d\n", argc - 1); // argc - 1 exclui o nome do programa da contagem
  // %s: marcador de formato para strings
  printf("the command arguments are: %s\n", argv[0]);
  for (int i = 1; i < argc ; i++)
    printf("argv[%d]=%s\n", i, argv[i]);
  return 0;
}

/* Compile o programa com o comando: $ gcc -Wall maintest.c -o maintest
e experimente-o com os comandos:
$ ./maintest
$ ./maintest mercury
$ ./maintest mercury venus
$ ./maintest mercury venus earth
$ ./maintest mercury venus earth mars */

// Exemplo de argc e argv em C:
// ./meu_programa ola mundo
// Saída esperada:
// # arguments = 3
// the command arguments are: ("./meu_programa", "ola", "mundo")./meu_programa
// argv[0] → "./meu_programa"
// argv[1] → ola
// argv[2] → mundo