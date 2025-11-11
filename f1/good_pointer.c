#include <stdio.h>
#include <stdlib.h>

int *get_int()
{
    // malloc() retorna um ponteiro, então não dá para armazenar em uma variável inteira (int p).
    int *p = (int *)malloc(sizeof(int));
    *p = 2;
    // não dá para retornar &p, porque &p retorna o endereço de uma variável local
    return p;
}

// malloc(sizeof(int)) reserva espaço suficiente para um inteiro no HEAP.

int main()
{
    int *p = get_int();
    printf("integer = %d\n", *p);
    free(p); // libera a memória alocada no heap
    return 0;
}

// malloc(sizeof(int)): 
// -> reserva um bloco de memória no heap com tamanho suficiente para um inteiro.
// -> retorna o endereço do início desse bloco (por exemplo, 0x7ffeab12c480).
// -> esse endereço é um void * (ponteiro genérico).

// (int *):
// -> converte o void * retornado por malloc para um ponteiro para inteiro (int *).

// int *p = ...
// -> declara p como um ponteiro para int e guarda o endereço retornado por malloc.

// *p = 2;
// O operador * (asterisco) acessa o valor armazenado no endereço apontado por p.
// *p = 2; significa “coloque o valor 2 dentro da memória apontada por p”