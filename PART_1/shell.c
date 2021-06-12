#include "apue.h"
#include <sys/wait.h>

int main(void){
    char buf[MAXLINE];
    pid_t pid;
    int status;

    printf("%% "); // print % 
    while (fgets(buf, MAXLINE, stdin)!=NULL){
        if(buf[strlen(buf)-1] == '\n')
            buf[strlen(buf)-1] = 0; // replace the \n
        
        // create a new process
        //Return a non-negative integer to the parent process
        if((pid = fork()) < 0){
            err_sys("fork error");
        // return 0 to the child
        }else if (pid == 0){
            execlp(buf, buf, (char *)0);
            err_ret("couldn't execute: %s", buf);
            exit(127);
        }

        /*parent is waiting*/
        if((pid = waitpid(pid, &status, 0)) < 0)
            err_sys("waitpid error");
        
        printf("%% ");
    }
    
    exit(0);
}