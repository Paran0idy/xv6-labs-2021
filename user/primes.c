#include "kernel/types.h"
#include "user/user.h"
#define MAX 34

int main(){
    int num[MAX];
    for(int i = 0; i < MAX; i++)
        num[i] = i + 2;
    int cnt = MAX;
    while(cnt != 0){
        int fd[2];
        if(pipe(fd) == -1){
            printf("pipe error!\n");
            exit(-1);
        }
        int pid = fork();
        if(pid < 0){
            printf("fork error!\n");
            exit(-2);
        }
        else if(pid > 0){
            close(fd[0]);
            for(int i = 0; i < cnt; i++)
                write(fd[1], &num[i], sizeof(num[0]));
            close(fd[1]);
            wait(0);
            exit(0);
        }
        else{
            close(fd[1]);
            cnt = 0;
            while(read(fd[0], &num[cnt++], sizeof(num[0])) != 0);
            int primes = num[0];
            printf("prime %d\n", primes);
            close(fd[0]);
            int index = 0;
            for(int i = 0; i < cnt; i++)
                if(num[i] % primes != 0)
                    num[index++] = num[i];
            cnt = index;
        }
    }
    exit(0);
}