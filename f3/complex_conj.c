#include "complex.h"

complex *complex_conj(complex *z)
{
    return complex_new(z->x, -z->y);
}

// conjugado de z = a + bi é z* = a - bi