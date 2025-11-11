typedef struct
{
    double x;
    double y;
} complex;

complex* complex_new(double, double);
complex* complex_add(complex *, complex *);
complex* complex_sub(complex *, complex *);
complex* complex_mul(complex *, complex *);
complex* complex_div(complex *, complex *);
complex* complex_conj(complex *);
double complex_mod(complex *);
double complex_arg(complex *);
double complex_re(complex *);
double complex_im(complex *);

// Para executar o exemplo, compilamos primeiro a API e construimos uma biblioteca libcomplex.a que será usada pelo programa principal:
// gcc -Wall -c complex_*.c
// ar -rc libcomplex.a complex_*.o
// ar -t libcomplex.a  # lista os arquivos objeto na biblioteca
// nm libcomplex.a  # lista os símbolos definidos na biblioteca

// e compilamos depois o programa principal use_complex.c indicando ao compilador (linker) que deve usar a biblioteca libcomplex.a (-lcomplex) situada no diretório corrente (-L.):
// $ gcc -Wall use_complex.c -o use_complex -L. -lcomplex -lm
// Note que também foi incluida a biblioteca matemática -lm, necessária para funções como atan2 e sqrt, usadas em complex.c.