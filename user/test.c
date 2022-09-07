#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char *argv[]){
    char buf[10];
    int i = 0;
    while(read(0, &buf[i], 10)){
        i++;
    }
    printf("%s\n", buf);
    exit(0);
}