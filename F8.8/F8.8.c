#include "apue.h"
#include <sys/wait.h>

int
main(void){
    pid_t pid;

    if((pid = fork()) < 0){
        err_sys("fork error");
    }else if (pid == 0){    /* first child*/
        if ((pid = fork()) < 0)
            err_sys("fork error");
        else if (pid > 0)
            exit(0);    /* parent of second fork.  first child -> second child. */
    

       /*
        *We 're the second child; our parent becomes init as soon
        *as our real parent calls exit() in the statement above.
        *Here's where we'd continue executing, knowing that when
        *we're done, init will reap our status.
        */
        sleep(2); /*Reducing the chance of race between first fork and second fork, Sleep is not guarantee to
                prevent collision*/
        printf("second child, parent pid = %ld\n", (long)getppid());
        exit(0);        
    }

    if (waitpid(pid, NULL, 0) != pid)
        err_sys("waitpid error");
    /*
     * We're the parent (the original process); we continue executing,
     * knowing that we're not the parent of the second child.
     */
    exit(0);
//    return 0;
}
