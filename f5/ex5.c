#include <sys/wait.h>   // para waitpid()
#include <stdio.h>      // para printf, fgets, perror, stdout
#include <stdlib.h>     // para exit, EXIT_FAILURE, EXIT_SUCCESS
#include <string.h>     // para strlen
#include <errno.h>      // para verificar erros (não usado diretamente)
#include <unistd.h>     // para fork(), execlp(), etc.

int main(int argc, char *argv[])
{
    // Loop infinito — o shell fica rodando até o usuário fechar
    // 1) mostrando o prompt
    // 2) esperando um comando
    // 3) executando o comando até o usuário digitar Ctrl+D (EOF).
    for (;;)
    {
        fprintf(stdout, "$ "); // → imprime $ (o prompt do shell)
        char buf[1024]; // → cria um buffer para guardar a linha digitada.
        char *command = fgets(buf, sizeof(buf), stdin); // → lê uma linha inteira do teclado.
        // Sair caso o utilizador envie EOF (Ctrl+D)
        // Sair caso o utilizador escreva "exit"
        if (command == NULL || strcmp(command, "exit\n") == 0)
            break;
        // Insere o terminador de string '\0' no lugar do '\n' lido pelo fgets, pois o terminador é um caracterizador de string e assim é possível chamar as funções de manipulação de strings corretamente
        command[strlen(buf) - 1] = '\0';

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
            // execlp substitui o processo filho pelo comando
            // command deve ser um executável válido no PATH do sistema
            // os argumentos são: o comando, exemplo do segundo argumento: ls -l, e o último mostra que o número de argumentos acabou. Essa função exige isso, pois é um número variável de argumentos.
            int retv = execlp(command, command, (char *)0);
            // Se execlp funcionar: o processo filho não volta para o código C — o programa é substituído!
            // não vai funcionar comandos como 'ls -l'.
            // execlp NÃO faz parsing da linha de comando.
            // Ele espera que cada argumento seja passado como argumentos separados, NÃO como uma única string.
            if (retv == -1)
            {
                perror("execlp");
                exit(EXIT_FAILURE);
            }
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

/*
int waitpid(pid_t pid, int *status, int options);

O que waitpid faz?

waitpid faz o processo pai:
- esperar por um processo filho terminar
    ou
- verificar o estado de um processo filho (sem necessariamente esperar)

E devolve:
- o PID do processo que terminou
- 0 (em alguns modos)
- ou -1 em caso de erro

Argumento 1: pid

Define qual processo filho você quer esperar.
Valores possíveis:
- pid > 0
Espera apenas o processo com esse PID específico.
Exemplo:
waitpid(child_pid, ...);  

- pid == -1
Espera qualquer processo filho (equivalente a wait()).

- pid == 0
Espera qualquer processo filho que pertença ao mesmo grupo de processos.

-pid < -1
Espera por qualquer processo cujo grupo de processos seja |pid|.

Argumento 2: status

É um ponteiro onde o kernel coloca o código de término do processo filho.
Exemplo:
int status;
waitpid(pid, &status, 0);

Depois você usa macros para interpretar o resultado:
✔ O filho terminou normalmente?
WIFEXITED(status)

✔ Qual foi o código de retorno?
WEXITSTATUS(status)

✔ O filho morreu por um sinal?
WIFSIGNALED(status)

✔ Qual sinal?
WTERMSIG(status)

Quando você passa NULL?
waitpid(pid, NULL, 0);

→ Você ignora o código de saída do filho.
→ Só está interessado em esperar que ele termine.

Argumento 3: options

Controla o comportamento de waitpid.

Aqui estão os mais usados:
✔ 0
Modo padrão → bloqueia até o filho terminar.

✔ WNOHANG
Não bloqueia.
Se o filho ainda não terminou → retorna 0 imediatamente.
Uso típico:
waitpid(pid, &status, WNOHANG);

✔ WUNTRACED
Retorna também se um processo filho foi parado (via sinal SIGSTOP, p.ex.)

✔ WCONTINUED
Retorna se um processo parado voltou a correr (SIGCONT)

✔ WSTOPPED (sinônimo de WUNTRACED)
Retorna quando o filho entra em estado "stopped".
Pode combinar opções:
waitpid(pid, &status, WNOHANG | WUNTRACED);
*/