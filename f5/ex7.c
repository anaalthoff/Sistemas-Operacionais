/* Altere o programa anterior por forma a manter uma história dos comandos por ela
executados. Implemente um comando myhistory que recebe um inteiro n como argumento
e imprime os últimos n comandos executados pela shell. Sugestão: aproveite o comando
tail da Bash shell. */

#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_ARGS 64
#define HISTORY_FILE ".myhistory"

int main(int argc, char *argv[])
{
    for (;;)
    {
        fprintf(stdout, "$ ");

        char buf[1024];
        char *command = fgets(buf, sizeof(buf), stdin);

        if (command == NULL || strcmp(command, "exit\n") == 0)
            break;

        buf[strlen(buf) - 1] = '\0'; // remove '\n'

        // Guardar comando no histórico
        FILE *hist = fopen(HISTORY_FILE, "a");
        if (hist != NULL)
        {
            fprintf(hist, "%s\n", buf);
            fclose(hist);
        }

        // Separar a linha em tokens
        char *args[MAX_ARGS];
        int i = 0;
        char *token = strtok(buf, " ");
        while (token != NULL && i < MAX_ARGS - 1)
        {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (args[0] == NULL)
            continue;

        // Comando interno: myhistory n
        if (strcmp(args[0], "myhistory") == 0 && args[1] != NULL)
        {
            pid_t pid = fork();
            if (pid == 0)
            {
                char *tailArgs[] = {
                    "tail",
                    "-n",
                    args[1],
                    HISTORY_FILE,
                    NULL};
                execvp("tail", tailArgs);
                perror("execvp");
                exit(EXIT_FAILURE);
            }
            waitpid(pid, NULL, 0);
            continue;
        }

        // fork + execvp normal
        pid_t pid = fork();
        if (pid == 0)
        {
            execvp(args[0], args);
            perror("execvp");
            exit(EXIT_FAILURE);
        }

        waitpid(pid, NULL, 0);
    }

    exit(EXIT_SUCCESS);
}
