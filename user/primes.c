#include "kernel/types.h"
#include "user/user.h"
#define MAX 34


int main(){
    int num[MAX];
    for(int i = 0; i < MAX; i++)
        num[i] = i + 2;
    int len = MAX;
    while(len != 0){
        int fd[2];
        if(pipe(fd) < 0){
            printf("pipe error!\n");
            exit(-1);
        }
        int pid = fork();
        if(pid < 0){
            printf("fork error\n");
            exit(-2);
        }
        else if(pid > 0){
            close(fd[0]);
            for(int i = 0 ; i < len; i++)
                write(fd[1], &num[i], sizeof(int));
            close(fd[1]);
            wait(0);
            exit(0);
        }
        else{
            close(fd[1]);
            len = 0;
            while(read(fd[0], &num[len++], sizeof(int)) != 0);
            len--;
            int prime = num[0];
            printf("prime %d\n", prime);
            int index = 0;
            for(int i = 0; i < len; i++)
                if(num[i] % prime != 0)
                    num[index++] = num[i];
            len = index;
        }
    }
    exit(0);
}