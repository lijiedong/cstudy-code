#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
extern char **environ;
int main(){
    puts("Begin");
    // 刷新缓冲区
    fflush(NULL);
    pid_t pid;
    pid = fork();
    if (pid<0) {
        perror("fork()");
        exit(1);
    }
    if (pid==0) {
        execl("/bin/sleep", "httpd", "100", NULL);

       // execl("/bin/sleep", "sleep", "100", NULL);
        // execl替换进程出错
        perror("execl()");
        exit(1);
    }
    wait(NULL);
    puts("End");
    exit(0);
}