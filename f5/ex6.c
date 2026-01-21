/*
Altere o programa anterior por forma a que os comandos possam ser executados com
argumentos. Sugestão: use a função execvp (em vez de execlp) e use a função strtok
para separar o nomes do comando e os respectivos argumentos dados na “string” command
*/

#include <sys/wait.h> // para waitpid()
#include <stdio.h>    // para printf, fgets, perror, stdout
#include <stdlib.h>   // para exit, EXIT_FAILURE, EXIT_SUCCESS
#include <string.h>   // para strlen
#include <errno.h>    // para verificar erros (não usado diretamente)
#include <unistd.h>   // para fork(), execlp(), etc.

int main(int argc, char *argv[])
{
    for (;;)
    {
        fprintf(stdout, "$ "); // → imprime $ (o prompt do shell)
        char buf[1024]; // → cria um buffer para guardar a linha digitada.
        char *command = fgets(buf, sizeof(buf), stdin); // → lê uma linha inteira do teclado.
        // Sair caso o utilizador envie EOF (Ctrl+D)
        // Sair caso o utilizador escreva "exit"
        if (command == NULL || strcmp(command, "exit\n") == 0)
            break;
        command[strlen(buf) - 1] = '\0';

        // Separar a linha em tokens (comando + argumentos)
        char *args[64]; // Array de argumentos (até 63 argumentos + NULL)
        int i = 0;
        char *token = strtok(buf, " "); // separa por espaço
        while (token != NULL)
        {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL; // Terminar o array com NULL (obrigatório para execvp)

        /* call fork and check return value */
        // Cria processo filho
        pid_t pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0)
        {
            /* child */
            execvp(args[0], args);  // args[0] = comando, args[] = array de argumentos
            // Se execvp retornar, houve erro
            perror("execvp");
            exit(EXIT_FAILURE);
        }
        /* shell waits for command to finish before giving prompt again */
        int retv = waitpid(pid, NULL, 0);
        if (retv == -1)
        {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
    }
    exit(EXIT_SUCCESS);
}