#include <math.h>
#include "complex.h"

double complex_mod(complex *z)
{
    return sqrt(z->x * z->x + z->y * z->y);
}

// módulo de z = a + bi é |z| = √(a² + b²)
// onde a é a parte real (z->x) e b é a parte imaginária (z->y)
// o módulo de um número complexo |z| representa a distância do ponto (a, b) à origem (0, 0) no plano complexo
// No plano complexo, o eixo x representa a parte real e o eixo y representa a parte imaginária.
// O número complexo z pode ser visto como um vetor a partir da origem até o ponto (a, b). 
// O módulo |z| é o comprimento desse vetor.