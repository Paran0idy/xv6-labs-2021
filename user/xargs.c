#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char *argv[]){
    char buf[MAXARG];
    char *parse[MAXARG];

    while(1){
        memset(parse, 0, MAXARG);
        for(int i = 0; i < argc; i++) parse[i] = argv[i];
        int idx = argc, cnt = 0;
        while(read(0, &buf[cnt], sizeof(char))){
            if(buf[cnt] == '\n') break;
            cnt++;
        }
        //printf("cnt = %d, buf = %s\n", cnt, buf);
        if(cnt == 0) break;
        buf[cnt] = '\0';
        parse[idx++] = buf;
        int i = 1;
        while(i < strlen(buf)){
            if(buf[i] == ' '){
                buf[i] = '\0';
                parse[idx++] = buf + i + 1;
            }
            i++;
        }

        int pid = fork();
        if(pid == 0) exec(parse[1], parse + 1);

        wait(0);
    }
    exit(0);
}