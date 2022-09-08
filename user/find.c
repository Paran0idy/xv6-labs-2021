#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"


void find(char *path, char *target){
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;

    if((fd = open(path, 0)) < 0){
        fprintf(2, "find cannot open %s\n", path);
        return ;
    }
    if(fstat(fd, &st) < 0){
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
        return;
    }
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
        printf("ls: path too long\n");
        close(fd);
        return ;
    }
    if(st.type != T_DIR) {
        close(fd);
        return ;
    }
    strcpy(buf, path);
    p = buf + strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
        if(de.inum == 0 || strcmp(".", de.name) == 0 || strcmp("..", de.name) == 0) 
            continue;
        int flag = strcmp(de.name, target);
        memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = 0;
        //printf("%d %d\n", strlen(p), sizeof(p));
        if(flag == 0) fprintf(1, "%s\n", buf);
        find(buf, target);
    }
    close(fd);
}

int main(int argc, char *argv[]){
    if(argc < 3){
        fprintf(2, "argument counts error\n");
        exit(0);
    }
    find(argv[1], argv[2]);
    exit(0);
}