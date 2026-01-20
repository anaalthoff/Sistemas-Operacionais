// O seguinte exemplo mostra como os sinais podem ser úteis, por exemplo, para atualizar a configuração de um processo sem ter de o terminar e voltar a executar (muito menos recompilar). Isto é muito útil, por exemplo, no caso de servidores que devem manter-se sempre disponíveis (uma propriedade designada por “availability”).

#include <signal.h>
#include <stdio.h>                             
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/errno.h>

static int param; /* program parameter */

void read_parameter()
{
    FILE *fp = fopen(".config", "r");
    fscanf(fp, "param: %d\n", &param);
    fclose(fp);
}
void write_parameter()
{
    printf("param: %d\n", param);
}
void handler(int signum)
{
    read_parameter();
    write_parameter();
}
int main(int argc, char *argv[])
{
    if (signal(SIGHUP, handler) == SIG_ERR)
    {
        fprintf(stderr, "Can’t catch SIGHUP: %s", strerror(errno));
        exit(EXIT_FAILURE);
    }
    printf("my PID is %d\n", getpid());
    read_parameter();
    printf("waiting...");
    for (;;)
        pause();
}

// Execute os comandos seguintes:
// $ cat > .config
// param: 263
// ^D
// $ gcc updatable.c -o updatable
// $ ./updatable &
// my PID is 36595
// waiting...
// $ kill -HUP 36595
// param value is: 263
// $ emacs .config (change param to 321)
// $ kill -HUP 36595
// param value is: 321
// $