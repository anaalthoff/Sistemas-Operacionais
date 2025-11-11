#include "complex.h"

complex *complex_mul(complex *z, complex *w)
{
    return complex_new(z->x * w->x - z->y * w->y,
                       z->x * w->y + z->y * w->x);
}

// i² = -1
// por isso o produto das partes imaginárias é subtraído da parte real
// e o produto cruzado das partes real e imaginária é somado na parte imaginária