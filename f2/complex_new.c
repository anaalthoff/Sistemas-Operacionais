#include <stdlib.h>
#include "complex.h"

complex *complex_new(double x, double y)
{
    complex *z = (complex *)malloc(sizeof(complex));
    z->x = x; //“O membro x do struct apontado por z recebe o valor da variável x.”
    z->y = y; //“O membro y do struct apontado por z recebe o valor da variável y.”
    return z; // retorna o ponteiro z
}

// z é um ponteiro para o struct
// Para acessar os membros do struct, usa-se '->' em vez de '.'

// z->x acessa a parte real do número complexo que z aponta.
// z->y é a parte imaginária do número complexo apontado por z.

// z->x = 1.0; // mesma coisa que (*z).x = 1.0
// z->y = 2.0; // mesma coisa que (*z).y = 2.0

// z é um ponteiro para um struct complex alocado no heap (com malloc)
