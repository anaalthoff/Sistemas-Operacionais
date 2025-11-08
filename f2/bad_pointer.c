#include <stdio.h>

int *get_int()
{
    int i = 2;
    return &i;
}

// A variável i é local à função get_int().
// Quando a função termina, a memória da variável i é liberada (ela estava na STACK).
// Ao fazer return &i;, estamos retornando o endereço de uma variável que já deixou de existir.
// O ponteiro retornado (int *) aponta para uma área de memória inválida (lixo).

int main()
{
    int *p = get_int();
    printf("integer = %d\n", *p);
    return 0;
}

// p recebe um endereço inválido.
// Quando tentamos fazer *p, estamos acessando memória que não pertence mais à variável i.
// O comportamento é indefinido: pode imprimir 2, pode imprimir lixo, pode causar segmentation fault, depende do compilador e do sistema operacional.