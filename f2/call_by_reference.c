#include <stdio.h>

// os parâmetros são os endereços
void swap(int *p1, int *p2)

{
    // a troca altera os valores originais
    int temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

int main()
{
    // cria n1 e n2 na memória principal
    int n1 = 1;
    int n2 = 2;
    // passa os ENDEREÇOS de n1 e n2 para a função swap
    swap(&n1, &n2);
    printf("n1: %d n2: %d\n", n1, n2);
    return 0;
}

// main:
// +------+   +------+
// | n1=1 |   | n2=2 |
// +------+   +------+

// swap:
// p1 --> endereço de n1
// p2 --> endereço de n2

// *temp = *p1 -> temp=1
// *p1 = *p2 -> n1=2
// *p2 = temp -> n2=1

// Depois do swap:
// main:
// +------+   +------+
// | n1=2 |   | n2=1 |
// +------+   +------+
