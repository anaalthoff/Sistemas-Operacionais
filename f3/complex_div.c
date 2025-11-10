#include <stdlib.h>
#include "complex.h"

complex *complex_div(complex *z, complex *w)
{
    double denom = w->x * w->x + w->y * w->y;
    if (denom == 0)
        return NULL; // evitar divisão por zero
    return complex_new((z->x * w->x + z->y * w->y) / denom,
                       (z->y * w->x - z->x * w->y) / denom);
}

// Para eliminar o imaginário do denominador, multiplica-se o numerador e o denominador pelo conjugado do denominador
// Conjugado de w = a + bi é w* = a - bi
// (a + bi)(a - bi) = a² + b²
// (c + di)(a - bi) = (ca - cbi) + (adi + db) -> (ca + db) + i(da - cb) (parte real + i * parte imaginária)