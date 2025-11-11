#include <stdio.h>

    void swap(int n1, int n2)
    {
        int temp = n1;
        n1 = n2;
        n2 = temp;
    }

int main()
{
    // cria n1 e n2 na memória principal
    int n1 = 1;
    int n2 = 2;
    // passa apenas CÓPIAS de n1 e n2 para a função swap
    swap(n1, n2);
    printf("n1: %d n2: %d\n", n1, n2);
    return 0;
}

// main:
// +------+   +------+
// | n1=1 |   | n2=2 |
// +------+   +------+

// Durante swap(int n1, int n2):
// swap:
// +------+   +------+
// | n1=1 |   | n2=2 |  <- cópias locais
// +------+   +------+
// temp=1
// n1=n2 -> n1=2
// n2=temp -> n2=1

// Ao sair da função:
// As cópias locais de swap são destruídas.
// main continua com n1=1, n2=2.