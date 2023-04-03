#include <stdio.h>
#include <unistd.h>
#include<sys/wait.h>

//                          (principal)
//                               |
//              +----------------+--------------+
//              |                               |
//           filho_1                         filho_2
//              |                               |
//    +---------+-----------+          +--------+--------+
//    |         |           |          |        |        |
// neto_1_1  neto_1_2  neto_1_3     neto_2_1 neto_2_2 neto_2_3

// ~~~ printfs  ~~~
//      principal (ao finalizar): "Processo principal %d finalizado\n"
// filhos e netos (ao finalizar): "Processo %d finalizado\n"
//    filhos e netos (ao inciar): "Processo %d, filho de %d\n"

// Obs:
// - netos devem esperar 5 segundos antes de imprmir a mensagem de finalizado (e terminar)
// - pais devem esperar pelos seu descendentes diretos antes de terminar

    /*************************************************
     * Dicas:                                        *
     * 1. Leia as intruções antes do main().         *
     * 2. Faça os prints exatamente como solicitado. *
     * 3. Espere o término dos filhos                *
     *************************************************/
    
int main(int argc, char** argv) {
    for (int i = 0; i < 2; i++) {
        int childPid = fork();
        if (childPid == 0) {
            printf("Processo %d, filho de %d\n", getpid(), getppid());
            fflush(NULL);
            for (int j = 0; j < 3; j++) {
                int grandChildPid = fork();
                if (grandChildPid == 0) {
                    printf("Processo %d, filho de %d\n", getpid(), getppid());
                    fflush(NULL);   
                    sleep(5);
                    printf("Processo %d finalizado\n", getpid());
                    fflush(NULL);   
                    return 0;
                }
            }
            while (wait(NULL) >= 0);
            printf("Processo %d finalizado\n", getpid());
            fflush(NULL);
            return 0;
        }
    }
    while(wait(NULL) >= 0);
    printf("Processo principal %d finalizado\n", getpid());
    return 0;
}
