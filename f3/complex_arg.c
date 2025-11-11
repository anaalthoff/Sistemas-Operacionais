#include <math.h>
#include "complex.h"

double complex_arg(complex *z)
{
    return atan2(z->y, z->x);
}

// atan2 calcula o ângulo do ponto (x, y) em relação à origem (0, 0), retornando um valor em radianos no intervalo [-π, π]
// atan2 (y, x) é mais seguro que atan(y/x), pois leva em conta o sinal de x e y para determinar o quadrante correto do ângulo e evita divisão por zero quando x é 0