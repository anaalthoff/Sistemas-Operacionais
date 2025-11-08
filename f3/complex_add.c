#include "complex.h"

complex *complex_add(complex *z, complex *w)
{
    // z e w são ponteiros para structs complex
    return complex_new(z->x + w->x, z->y + w->y);
}

// ->x → parte real de z
// z->y → parte imaginária de z
// w->x → parte real de w
// w->y → parte imaginária de w