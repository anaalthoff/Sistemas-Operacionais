#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int value = 0;
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
    {
        /* child process */
        value = 1;
        printf("CHILD: value = %d, addr = %p\n", value, &value);
        exit(EXIT_SUCCESS);
    }
    else
    {
        /* parent process */
        // waitpid(): É uma chamada de sistema (system call) que suspende a execução do processo chamador (o pai) até que um dos seus filhos especificados mude de estado (ou seja, termine, seja interrompido, etc.).
        int retv = waitpid(pid, NULL, 0); // O valor 0 indica que o waitpid() deve bloquear a execução do pai até que o filho termine.
        // O PID do processo filho que terminou (neste caso, o valor de pid), se for bem-sucedida. -1 se ocorrer um erro.
        if (retv == -1)
        {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
        printf("PARENT: value = %d, addr = %p\n", value, &value);
        exit(EXIT_SUCCESS);
    }
}

// Este programa demonstra a criação de um processo filho utilizando a chamada de sistema fork().
// Após a criação do processo filho, tanto o processo pai quanto o filho possuem suas próprias cópias da variável 'value'.
// O processo filho define 'value' como 1 e imprime seu valor e endereço.
// O processo pai espera o término do filho usando waitpid() e então imprime o valor e endereço de sua própria cópia de 'value', que permanece 0.
// Compile o programa com:
// $ gcc -Wall ex3.c -o ex3
// E execute-o com:
// $ ./ex3
// Você verá a saída mostrando os valores e endereços das variáveis em ambos os processos. Note que os endereços podem ser iguais, mas os valores são diferentes, evidenciando a separação de memória entre os processos.

// Porquê o waitpid() é Necessário?

// O waitpid() é crucial neste contexto para evitar a criação de "processos zumbi" (zombie processes).

// Quando um processo filho termina, ele liberta a maioria dos seus recursos. No entanto, a sua entrada na tabela de processos (incluindo o PID e o status de saída) permanece até que o seu pai a recolha (faça um wait ou waitpid).

// Se o processo pai terminar antes de o filho terminar e o status de saída do filho ser recolhido, o filho torna-se um processo órfão e é adotado pelo processo init (PID 1), que se encarrega de fazer a colheita do status.

// Se o pai terminar depois do filho, mas sem chamar waitpid(), o filho finalizado permanece como um processo zumbi até que o pai termine (ou até que o sistema seja reiniciado), desperdiçando uma pequena quantidade de recursos do sistema.

// CHILD: value = 1, addr = 0x7ffd7f7f742c
// PARENT: value = 0, addr = 0x7ffd7f7f742c

// Endereços Virtuais: O endereço (addr = 0x7ffd7f7f742c) que é impresso é um endereço de memória virtual, não um endereço físico real.

// Cópias Idênticas: O kernel do Linux (e outros sistemas Unix-like) copia o mapa de memória virtual do pai para o filho. Portanto, a variável value está localizada no mesmo endereço virtual em ambos os processos.

// Memória Física: No entanto, o sistema de memória virtual do computador mapeia este endereço virtual para diferentes endereços de memória física (RAM) para o pai e para o filho.