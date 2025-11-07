#include <stdio.h>
int main()
{
    int i;
    int primes[] = {2, 3, 5, 7, 11};
    for (i = 0; i < sizeof(primes) / sizeof(int); i++)
        printf("%p: %d <--> %p: %d\n",
               &(primes[i]), primes[i], primes + i, *(primes + i));
    return 0;
}

// 0x7ffd0dc3ce00: 2 <--> 0x7ffd0dc3ce00: 2
// 0x7ffd0dc3ce04: 3 <--> 0x7ffd0dc3ce04: 3
// 0x7ffd0dc3ce08: 5 <--> 0x7ffd0dc3ce08: 5
// 0x7ffd0dc3ce0c: 7 <--> 0x7ffd0dc3ce0c: 7
// 0x7ffd0dc3ce10: 11 <--> 0x7ffd0dc3ce10: 11

// Cada incremento de i corresponde a 4 bytes - msg + i move 4 bytes a frente

// O endereço de memória (&(primes[i]))
// O conteúdo do elemento (primes[i])
// O endereço calculado como ponteiro (primes + i)
// O conteúdo via ponteiro (*(primes + i))