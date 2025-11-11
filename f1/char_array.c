#include <stdio.h>

int main()
{
    int i;
    char msg[] = "Hello World";
    for (i = 0; i < sizeof(msg); i++)
        printf("%p: %c <--> %p: %c\n",
               &(msg[i]), msg[i], msg + i, *(msg + i));
    return 0;
}

// 0x7ffd5e59da3c: H <--> 0x7ffd5e59da3c: H
// 0x7ffd5e59da3d: e <--> 0x7ffd5e59da3d: e
// 0x7ffd5e59da3e: l <--> 0x7ffd5e59da3e: l
// 0x7ffd5e59da3f: l <--> 0x7ffd5e59da3f: l
// 0x7ffd5e59da40: o <--> 0x7ffd5e59da40: o
// 0x7ffd5e59da41:   <--> 0x7ffd5e59da41:  
// 0x7ffd5e59da42: W <--> 0x7ffd5e59da42: W
// 0x7ffd5e59da43: o <--> 0x7ffd5e59da43: o
// 0x7ffd5e59da44: r <--> 0x7ffd5e59da44: r
// 0x7ffd5e59da45: l <--> 0x7ffd5e59da45: l
//0x7ffd5e59da46: d <--> 0x7ffd5e59da46: d
// 0x7ffd5e59da47:  <--> 0x7ffd5e59da47:

// Cada incremento de i corresponde a 1 byte - msg + i move 1 byte a frente

// O endereço de memória (&(msg[i]))
// O conteúdo do elemento (msg[i])
// O endereço calculado como ponteiro (msg + i)
// O conteúdo via ponteiro (*(msg + i))