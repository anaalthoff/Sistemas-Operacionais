// Se a função execlp executa com sucesso, como é que o processo filho sinaliza o seu término ao processo pai?

// Quando execlp executa com sucesso, ele não volta ao processo filho — ele substitui totalmente o código do processo filho pelo novo programa.
// Ou seja, se execlp funcionar, nenhuma instrução após ele no processo filho é executada.
// Então como o pai fica a saber que o filho terminou?
// Através do sinal enviado automaticamente pelo kernel quando o processo filho termina.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    /* fork a child process */
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
    {
        /* child process */
        int retv = execlp(argv[1], argv[1], NULL);
        if (retv == -1)
        {
            perror("execlp");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        /* parent process */
        int retv = waitpid(pid, NULL, 0);
        if (retv == -1)
        {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
    }
    exit(EXIT_SUCCESS);
}

// Este programa cria um processo filho utilizando a chamada de sistema fork().
// O processo filho utiliza a função execlp() para substituir a sua imagem de processo pelo programa especificado no primeiro argumento da linha de comando (argv[1]).
// execlp substitui o processo e nunca retorna se tiver sucesso.
// O kernel envia ao pai o sinal SIGCHLD quando o filho termina.
// O processo pai espera o término do processo filho utilizando a chamada de sistema waitpid().

// Compile o programa com:
// $ gcc -Wall ex4.c -o ex4
// E execute-o com um comando válido, por exemplo:
// $ ./ex4 ls -l

// O programa irá listar os arquivos do diretório atual, pois o processo filho executa o comando 'ls -l'.