// & (endereço da variável)
// * (conteúdo de endereço)

#include <stdio.h>

int main() {
    int i, j, *p, *q;

    i = 5;
    printf("i=%d\n", i); // j ainda indefinido (valor lixo)

    p = &i;
    printf("p aponta para i (%p)\n", p);

    *p = 7; // muda o valor de i através do ponteiro
    printf("i=%d, j=%d, *p=%d\n", i, j, *p);

    j = 3;
    printf("i=%d, j=%d\n", i, j);

    p = &j; // agora p aponta para j
    q = p;  // q também aponta para j
    printf("p=%p, q=%p (ambos apontam para j)\n", p, q);

    p = &i; // p volta a apontar para i
    *q = 2; // altera o valor de j, pois q ainda aponta para j
    printf("i=%d, j=%d\n", i, j);

    return 0;
}

