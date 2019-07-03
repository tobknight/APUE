#include "apue.h"

static void
sig_int(int signo){
    printf("caught SIGINT\n");
}

static void
sig_child(int signo){
    printf("caught SIGCHILD\n");
}

int main(void){
    if(signal(SIGINT, sig_int) == SIG_ERR)
        err_sys("signal(SIGINT) ERROR");
    if(signal(SIGCHLD, sig_child) == SIG_ERR)
        err_sys("signal(SIGCHLD) error");
    if(system("/bin/ed") < 0)
        err_sys("system() error");
    exit(0);

}
