#include "kernel/types.h"
#include "user/user.h"

int main(){
    int fd1[2], fd2[2];
    char buf[5];

    if(pipe(fd1) == -1 || pipe(fd2) == -1){
        printf("pipe error!\n");
        exit(-1);
    }

    int pid = fork();

    if(pid == -1){
        printf("fork error!\n");
        exit(-2);
    }
    else if(pid == 0){
        close(fd1[1]);
        read(fd1[0], buf, 4);
        printf("%d: received %s\n", getpid(), buf);
        close(fd2[0]);
        write(fd2[1], "pong", 4);

        exit(0);
        
    }
    else{
        close(fd1[0]);
        write(fd1[1], "ping", 4);
        close(fd2[1]);
        read(fd2[0], buf, 4);
        printf("%d: received %s\n", getpid(), buf);
        
        exit(0);
    }
    return 0;
}