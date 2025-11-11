#include "complex.h"

// retorna a parte imaginária do número complexo z
double complex_im(complex *z)
{
    return z->y;
}