/* Considere o seguinte programa que abre um ficheiro (cujo nome ´e passado como um argumento do programa, argv[1] no c´odigo), lˆe o seu conte´udo em blocos de BUFFER_SIZE bytes de cada vez e escreve esses bytes para o terminal (stdout). */

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024
int main(int argc, char* argv[]) {
FILE* file = fopen(argv[1], "r");
if ( file == NULL ) {
printf("error: could not open %s\n", argv[1]);
exit(EXIT_FAILURE);
}
char buffer[BUFFER_SIZE];
int nchars = fread(buffer, sizeof(char), BUFFER_SIZE, file);
while (nchars > 0) {
fwrite(buffer, sizeof(char), nchars, stdout);
nchars = fread(buffer, sizeof(char), BUFFER_SIZE, file);
}
fclose(file);
exit(EXIT_SUCCESS);
}